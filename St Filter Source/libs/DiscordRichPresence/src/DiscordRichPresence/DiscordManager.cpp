#include "DiscordManager.h"
#include <Windows.h>
#include "ICharactor.h"
#include "ICPlayer.h"
#include <string.h>
#include <sstream>
#include "TextStringManager.h"
#include <signal.h>

// String helpers!
// Check if the string starts equal to the given string
bool str_starts_with(std::string const& value, std::string const& preffix) {
	return value.rfind(preffix, 0) == 0;
}
// Check if the string ends equal to the given string
bool str_ends_with(std::string const& value, std::string const& suffix) {
	if (value.length() >= suffix.length())
		return value.compare(value.length() - suffix.length(), suffix.length(), suffix) == 0;
	return false;
}

/// static stuffs
DiscordApp DiscordManager::m_App;
bool DiscordManager::m_IsConnected;
GAME_STATE DiscordManager::m_GameState;
time_t DiscordManager::m_InGameTimestamp;

DiscordManager::DiscordManager()
{
}
void DiscordManager::Start(DiscordClientId CLIENT_ID)
{
	m_CLIENT_ID = CLIENT_ID;
	if (!m_IsStarted && !m_IsRunning)
	{
		m_IsStarted = m_IsRunning = true;
		HANDLE hThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)DiscordManager::DiscordThread, 0, 0, 0);
		// Set discord stuffs as background process (below normal)
		SetThreadPriority(hThread, -1);
	}
}

void OnUserUpdated(void* data)
{
	struct DiscordApp* app = (struct DiscordApp*)data;
	struct DiscordUser user;
	app->users->get_current_user(app->users, &user);
	app->currentUser = user;

	printf("Connected user: %s#%s\r\n", user.username, user.discriminator);

	// Update state after connection
	DiscordManager::Instance().UpdateState();
}

void UpdateActivityCallback(void* data, enum EDiscordResult result)
{
	if (result != DiscordResult_Ok)
	{
		printf("Discord Activity ( ErrCode %d )\r\n", result);
	}
}

void SignalInterrupt(int code)
{
	DiscordManager::Instance().Stop();
}

DWORD WINAPI DiscordManager::DiscordThread()
{
	// Create and set instance
	memset(&m_App, 0, sizeof(m_App));

	// Create and set events
	struct IDiscordUserEvents users_events;
	memset(&users_events, 0, sizeof(users_events));
	users_events.on_current_user_update = OnUserUpdated;

	// Set params (options)
	struct DiscordCreateParams params;
	DiscordCreateParamsSetDefault(&params);
	params.client_id = Instance().m_CLIENT_ID;
	params.flags = DiscordCreateFlags_NoRequireDiscord;
	params.event_data = &m_App;
	params.user_events = &users_events;

	// Make sure to stop this thread on exit
	signal(SIGINT, SignalInterrupt);


	// Try to create app connection
	do
	{
		EDiscordResult result = DiscordCreate(DISCORD_VERSION, &params, &m_App.core);
		if (!Instance().m_IsStarted)
		{
			Instance().m_IsRunning = false;
			return 0;
		}
		if (result == DiscordResult_Ok)
		{
			Instance().m_IsConnected = true;
			break;
		}
		// wait delay to try again
		Sleep(30000);
	} while (true);

	// Set managers
	m_App.users = m_App.core->get_user_manager(m_App.core);
	m_App.achievements = m_App.core->get_achievement_manager(m_App.core);
	m_App.activities = m_App.core->get_activity_manager(m_App.core);
	m_App.application = m_App.core->get_application_manager(m_App.core);
	m_App.lobbies = m_App.core->get_lobby_manager(m_App.core);

	// Update callbacks
	while (Instance().m_IsStarted)
	{
		m_App.core->run_callbacks(m_App.core);
		Sleep(2500);
	}

	Instance().m_IsConnected = Instance().m_IsRunning = false;
	return 0;
}


void DiscordManager::UpdateState()
{
	UpdateState(m_GameState);
}

void DiscordManager::UpdateState(GAME_STATE State)
{
	// Catch first INGAME state
	if (m_GameState != GAME_STATE::IN_GAME && State == GAME_STATE::IN_GAME)
		m_InGameTimestamp = std::time(0);
	// Set state
	m_GameState = State;

	// Avoid update if there is no connection established
	if (!m_IsConnected)
		return;

	// Create memory
	struct DiscordActivity activity;
	memset(&activity, 0, sizeof(activity));

	// Define activity by state
	switch (State)
	{
	default:
	case GAME_STATE::LOADING:
	{
		sprintf(activity.state, "Loading");
		sprintf(activity.assets.large_image, "logo");
		sprintf(activity.assets.large_text, "SilkroadOnline.com");
	}
	break;
	case GAME_STATE::SERVER_SELECTION:
	{
		sprintf(activity.state, "Selecting Server");
		sprintf(activity.assets.large_image, "logo");
		sprintf(activity.assets.large_text, "SilkroadOnline.com");
	}
	break;
	case GAME_STATE::CHARACTER_SELECTION:
	{
		sprintf(activity.state, "Selecting Character");
		sprintf(activity.assets.large_image, "logo");
		sprintf(activity.assets.large_text, "SilkroadOnline.com");
	}
	break;
	case GAME_STATE::IN_GAME:
	{
        // Show job mode activity
        switch (g_pCICPlayer->GetJobTypes())
        {
            case TRIJOB_TYPE::TRIJOB_TRADER:
                sprintf(activity.state, "Job Mode (Trader)");
                break;
            case TRIJOB_TYPE::TRIJOB_THIEF:
                sprintf(activity.state, "Job Mode (Thief)");
                break;
            case TRIJOB_TYPE::TRIJOB_HUNTER:
                sprintf(activity.state, "Job Mode (Hunter)");
                break;
            default:
                sprintf(activity.state, "In Game");
                break;
        }

        // Player details
        std::stringstream details;
        std::n_wstring nwCharName = g_pCICPlayer->GetCharName();
        std::string charName(nwCharName.begin(), nwCharName.end());
        details << charName << " Lv." << (int)g_pCICPlayer->m_level;
        // Check guild name
        std::wstring wGuildName = g_pCICPlayer->GetGuildName();
        std::string guildName(wGuildName.begin(), wGuildName.end());
        if (guildName != "")
        {
            details << " [" << guildName << "]";
        }
        sprintf(activity.details, details.str().c_str());

        // Set region if is not in job mode
        if (g_pCICPlayer->GetJobTypes() == TRIJOB_TYPE::TRIJOB_NOJOB)
        {
            // Set name
            std::wstringstream region;
            region << g_pCICPlayer->GetRegion().r;
            const std::n_wstring* nwRegionName = g_CTextStringManager->GetString(region.str().c_str());
            std::string regionName(nwRegionName->begin(), nwRegionName->end());
            sprintf(activity.assets.large_text, regionName.c_str());

            // Set keyword image
            if (regionName == "Jangan") {
                sprintf(activity.assets.large_image,"loading_zangan");
            }
            else if (regionName == "Western China Donwhang") {
                sprintf(activity.assets.large_image, "loading_dunwhang");
            }
            else if (regionName == "Hotan") {
                sprintf(activity.assets.large_image, "loading_hotan");
            }
            else if (regionName == "Samarkand") {
                sprintf(activity.assets.large_image, "loading_samarkand");
            }
            else if (regionName == "Constantinople") {
                sprintf(activity.assets.large_image, "loading_constantinople");
            }
            else if (regionName == "Alexandria") {
                sprintf(activity.assets.large_image, "loading_alex");
            }
            else if (regionName == "Baghdad") {
                sprintf(activity.assets.large_image, "loading_baghdad_2011");
            }
            else if (regionName == "Donwhang Stone Cave") {
                sprintf(activity.assets.large_image, "loading_dungeons_donwhang");
            }
            else if (str_starts_with(regionName,"Underground Level")) {
                sprintf(activity.assets.large_image, "loading_royalmausoleum");
            }
            else if (regionName == "Pharaoh tomb") {
                sprintf(activity.assets.large_image, "loading_pharaoh");
            }
            else if (regionName == "Togui Village") {
                sprintf(activity.assets.large_image, "loading_togui_2011");
            }
            else if (regionName == "Flame Mountain") {
                sprintf(activity.assets.large_image, "loading_flame_2011");
            }
            else if (str_ends_with(regionName, " of the Shipwreck")) {
                sprintf(activity.assets.large_image, "loading_wreck_2011");
            }
            else if (regionName == "Jupiter Temple") {
                sprintf(activity.assets.large_image, "loading_jupiter_field_2011");
            }
            else if (str_ends_with(regionName, "'s Room")) {
                sprintf(activity.assets.large_image, "loading_hall_2011");
            }
            else if (regionName == "Zealots Hideout") {
                sprintf(activity.assets.large_image, "loading_hideout_2011");
            }
            else if (regionName == "Petra (Dungeon)") {
                sprintf(activity.assets.large_image, "loading_petra_2011");
            }
            else if (regionName == "Devil's Garden (Dungeon)") {
                sprintf(activity.assets.large_image, "loading_garden_2011");
            }
            else {
                sprintf(activity.assets.large_image, "loading_default");
            }
        }
        else
        {
            sprintf(activity.assets.large_image, "loading_default");
        }

		sprintf(activity.assets.small_image, "logo");
		// Game website or Character race
		sprintf(activity.assets.small_text, "SilkroadOnline.com");

		// Set Timestamp (Elapsed time)
		activity.timestamps.start = m_InGameTimestamp;
	}
	break;
	}

	// Set activity
	m_App.activities->update_activity(m_App.activities, &activity, m_App.application, UpdateActivityCallback);
}

void DiscordManager::Stop()
{
	m_IsStarted = false;
}
