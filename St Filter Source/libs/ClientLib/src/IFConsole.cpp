#include "IFConsole.h"
#include "hook.h"


static bool CALLBACK MyCuteTestingFunc(ConsoleCommandData* cmddata)
{
    wchar_t buffer[255];
    swprintf_s(buffer, L"Custom Command Debuggging, Command Entered Text: (%s).", cmddata->FullCommand);
    return true; // return key success
}

void CIFConsole::InitializeCustomCommands(void)
{
    replaceOffset(0x0055A027, addr_from_this(&CIFConsole::OnCommandsLoading));

    CustomConsoleCommands.push_back(std::pair<const wchar_t*, ConsoleCommandFunc*>(L"ChatClear", 0));
}

void CIFConsole::OnCommandsLoading(void)
{
    for (std::vector<std::pair<const wchar_t*, ConsoleCommandFunc*>>::iterator i = CustomConsoleCommands.begin(); i != CustomConsoleCommands.end(); i++)
    {
        this->AddCommand(i->first, i->second, 0);
    }
    reinterpret_cast<void(__thiscall*)(CIFConsole*)>(0x00558910)(this);
}

void CIFConsole::AddCommand(std::wstring commandmaintext, ConsoleCommandFunc* func, int a3)
{
    reinterpret_cast<void(__thiscall*)(CIFConsole*, std::wstring, ConsoleCommandFunc*, int)>(0x00555DB0)(this, commandmaintext, func, a3);
}