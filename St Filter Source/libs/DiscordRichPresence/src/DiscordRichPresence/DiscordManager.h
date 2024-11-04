#pragma once
#include "discord_game_sdk/discord.h"
#include <ctime>
#include "StdAfx.h"

struct DiscordApp {
	struct IDiscordCore* core;
	struct IDiscordUserManager* users;
	struct IDiscordAchievementManager* achievements;
	struct IDiscordActivityManager* activities;
	struct IDiscordRelationshipManager* relationships;
	struct IDiscordApplicationManager* application;
	struct IDiscordLobbyManager* lobbies;
	DiscordUser currentUser;
};

// Game status known
enum GAME_STATE : char
{
	LOADING = 0,
	FINISH = 1,
	SERVER_SELECTION = 2,
	CHARACTER_SELECTION = 3,
	IN_GAME = 4
};

// Discord wrapper class to use the new discord game sdk features
class DiscordManager
{
	/// Singleton stuffs
private:
	// Default constructor
	DiscordManager();
	DiscordManager(DiscordManager const&); // Don't Implement
	void operator=(DiscordManager const&); // Don't Implement
public:
	static DiscordManager& Instance()
	{
		// Guaranteed to be destroyed and instantiated on first use.
		static DiscordManager _this;
		return _this;
	}
	/// Continue normally
private:
	DiscordClientId m_CLIENT_ID;
	// Discord running state
	bool m_IsStarted;
	// Keep thread safe
	bool m_IsRunning;
	// Check if the discord has been connected
    static bool m_IsConnected;
	static DiscordApp m_App;
	static DWORD WINAPI DiscordThread();
    static GAME_STATE m_GameState;
    static time_t m_InGameTimestamp;
public:
    bool m_IsRegionChange;
    // Starts the connection to the discord app in a new thread
	void Start(DiscordClientId CLIENT_ID);
	// Refresh the current information using the current game state
    static void UpdateState();
	// Updates the current information from game state
    static void UpdateState(GAME_STATE);
	// Stops the connection
	void Stop();

    void UpdatePresence();
};
