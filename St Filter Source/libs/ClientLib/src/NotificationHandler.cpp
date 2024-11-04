#include "NotificationHandler.h"
#include "hook.h"
#include "TextStringManager.h"
#include "GInterface.h"
#include "NetProcessIn.h"

NotificationHandler g_notificationhandler;

std::wstring* NotificationHandler::GetSpawnNotify(std::wstring namestr)
{
    std::map<std::wstring, std::wstring>::iterator it = SpawnUniqueNotifies.find(namestr);
    if (it != SpawnUniqueNotifies.end())
        return &it->second;
    return NULL;
}

std::wstring* NotificationHandler::GetDespawnNotify(std::wstring namestr)
{
    std::map<std::wstring, std::wstring>::iterator it = DespawnUniqueNotifies.find(namestr);
    if (it != DespawnUniqueNotifies.end())
        return &it->second;
    return NULL;
}

std::wstring* NotificationHandler::GetKillNotify(std::wstring namestr)
{
    std::map<std::wstring, std::wstring>::iterator it = KillUniqueNotifies.find(namestr);
    if (it != KillUniqueNotifies.end())
        return &it->second;
    return NULL;
}

void NotificationHandler::Load(void)
{
    //Spawn Notifications
    SpawnUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_CH_TIGERWOMAN", L"UIIT_MSG_APPEAR_TIGER_GIRL"));
    SpawnUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_KK_ISYUTARU", L"UIIT_MSG_APPEAR_IYUTARU"));
    SpawnUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_OA_URUCHI", L"UIIT_MSG_APPEAR_URRUCHI"));
    SpawnUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_TK_BONELORD", L"UIIT_MSG_APPEAR_BONELORD"));
    SpawnUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_RM_TAHOMET", L"UIIT_MSG_APPEAR_TAHOMET"));

    //Despawn Notifications
    DespawnUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_CH_TIGERWOMAN", L"UIIT_MSG_DEAD_TIGER_GIRL"));
    DespawnUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_KK_ISYUTARU", L"UIIT_MSG_DEAD_IYUTARU"));
    DespawnUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_OA_URUCHI", L"UIIT_MSG_DEAD_URRUCHI"));
    DespawnUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_TK_BONELORD", L"UIIT_MSG_DEAD_BONELORD"));
    DespawnUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_RM_TAHOMET", L"UIIT_MSG_DEAD_TAHOMET"));

    //Kill Notifications
    KillUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_CH_TIGERWOMAN", L"UIIT_MSG_ANYONE_DEAD_TIGER_GIRL"));
    KillUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_KK_ISYUTARU", L"UIIT_MSG_ANYONE_DEAD_IYUTARU"));
    KillUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_OA_URUCHI", L"UIIT_MSG_ANYONE_DEAD_URRUCHI"));
    KillUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_TK_BONELORD", L"UIIT_MSG_ANYONE_DEAD_BONELORD"));
    KillUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_RM_TAHOMET", L"UIIT_MSG_ANYONE_DEAD_TAHOMET"));
}

void NotificationHandler::Initialize(void)
{
    Load();

    replaceAddr(0x0086FCDD, addr_from_this(&CNetProcessIn::OnGameNotify));
}
