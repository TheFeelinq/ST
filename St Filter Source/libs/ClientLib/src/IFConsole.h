#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>

typedef bool (CALLBACK ConsoleCommandFunc)(class ConsoleCommandData*);
static std::vector<std::pair<const wchar_t*, ConsoleCommandFunc*>> CustomConsoleCommands;

class ConsoleCommandData
{
public:
    char pad_0000[68]; //0x0000
    const wchar_t* FullCommand; //0x0044
};

class CIFConsole
{
public:
    static void InitializeCustomCommands();
    void OnCommandsLoading();
    void AddCommand(std::wstring commandmaintext, ConsoleCommandFunc* func, int a3);
};