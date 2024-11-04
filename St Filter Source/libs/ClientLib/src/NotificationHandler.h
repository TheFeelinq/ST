#pragma once
#include "xlib.h"
#include <map>

class NotificationHandler
{
public:
    std::map<std::wstring, std::wstring> SpawnUniqueNotifies;
    std::map<std::wstring, std::wstring> DespawnUniqueNotifies;
    std::map<std::wstring, std::wstring> KillUniqueNotifies;

    std::wstring* GetSpawnNotify(std::wstring namestr);
    std::wstring* GetDespawnNotify(std::wstring namestr);
    std::wstring* GetKillNotify(std::wstring namestr);

    void Load();
    void Initialize();
};

extern NotificationHandler g_notificationhandler;