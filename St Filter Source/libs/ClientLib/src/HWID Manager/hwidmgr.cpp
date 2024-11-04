#include "hwidmgr.h"
#include "memmgr.h"
#include <algorithm>
#include <ctime>

//HWID gen
#include <IPHlpApi.h>
#include <intrin.h>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "wininet.lib")

#pragma comment(lib,"ws2_32.lib")

#ifdef _UNICODE
#define tcout wcout
#else
#define tcout cout
#endif

using namespace std;

//Some stuff used only here

//Miliseconds
int wndProcTimerInterval = 0;
int pck_sent = 0;

//Original code used to send packets by SR client
//We patch it / restore it once done sending hwid packet
BYTE* bpOrigSendCode;

struct tWndProc
{
    HWND hWnd;
    UINT uMsg;
    WPARAM wParam;
    LPARAM lParam;
} srWndProc;

DWORD dwWndProc_Ret =		0;
DWORD dwWndProc_Esp =		0;
DWORD dwWndProc_Res =		0;
DWORD dwSendHook_RetAddr =	0;

BYTE* bpTmpPacketBytes = NULL;
//RAW length
int nTmpPacketBytesLen = 0;

char* encrypted_text = "thaidu0ngpr0";

//Magic, do not touch
void WritePacketData(LPBYTE _edi)
{
LPBYTE pData = (_edi + 0x34);
memcpy(pData, bpTmpPacketBytes, nTmpPacketBytesLen);
}

__declspec(naked) void SendHook_CC()
{
    //Should be ok, but verify with brain
    __asm
    {
    pop dwSendHook_RetAddr;
    mov eax, [edx + 0x2C];

    pushad;

    push edi;
    call WritePacketData;
    add esp, 4; //Restore stack
    popad;

    push edi;
    call eax;
    push dwSendHook_RetAddr;
    ret; //MEGA HAX
    }
    }

    void Send()
    {
        //static void Nop(DWORD dwAddr, size_t count);
        memmgr::Nop(HW_SEND_HOOK, 6);

        memmgr::Detour(E_DetourType::Call, HW_SEND_HOOK, (DWORD)SendHook_CC, 6);
        __asm
        {
        push 4;
        mov ecx, HW_SEND_ECX;
        mov eax, HW_SEND_CALL;
        call eax;
        }

        //Restore original client code
        memmgr::WriteBytes(HW_SEND_HOOK, bpOrigSendCode, 6);
        }
    bool _shouldRun = true;

    DWORD My_SrProcWndMsg()
    {
        switch (srWndProc.uMsg)
        {
            //Setup timer
            case WM_CREATE:
            {
                if (pck_sent == 0) {
                    SetTimer(srWndProc.hWnd, HW_WNDPROC_TIMER_ID, wndProcTimerInterval, 0);
                }
                pck_sent = 1;
            }
                break;
                //Timer tick
            case WM_TIMER:
            {
                if (srWndProc.wParam == HW_WNDPROC_TIMER_ID && _shouldRun)
                {
                    _shouldRun = false;
                    Send();
                    return 0;
                }
            }
                break;
        }
        return 1;
    }


    void CallMySrWndProc()
    {
        memcpy(&srWndProc, ((LPBYTE)ULongToPtr(dwWndProc_Esp)) + 4, 16);
        dwWndProc_Res = My_SrProcWndMsg();
    }

    __declspec(naked) void WndProcHook_CC()
    {
        __asm
        {
        pop dwWndProc_Ret;
        mov dwWndProc_Esp, esp;
        pushad;
        call CallMySrWndProc;

        //1 or 0 ??
        cmp dwWndProc_Res, 0;

        jne FINISH;

        popad;

        xor eax, eax;
        ret 0x10;

        FINISH:
        popad;
        cmp eax, 0x496;
        push dwWndProc_Ret;
        ret;
        }
        }

    void hwidmgr::Initialize()
    {
        //Hack
        //memcpy(bpOrigSendCode, (LPVOID)HW_SEND_HOOK, 6);

        bpOrigSendCode = memmgr::ReadBytes(HW_SEND_HOOK, 6);
        memmgr::Detour(E_DetourType::Call, HW_WNDPROC_HOOK, (DWORD)WndProcHook_CC, 5);
    }

    void hwidmgr::Setup(CPacket* hwidPacket, int interval)
    {
        bpTmpPacketBytes = hwidPacket->RawBytes();
        nTmpPacketBytesLen = hwidPacket->RawSize();
        wndProcTimerInterval = interval;
    }

    char * hwidmgr::GetMac()
    {
        bool foundValidAdapter = false;
        bool prevent_send = false;

        PIP_ADAPTER_INFO adapterInfo;
        DWORD dwBufSize = sizeof(adapterInfo);
        char* mac = (char*)malloc(17);
        adapterInfo = (IP_ADAPTER_INFO *)malloc(sizeof(IP_ADAPTER_INFO));
        if (adapterInfo == NULL)
            return 0;

        if (GetAdaptersInfo(adapterInfo, &dwBufSize) == ERROR_BUFFER_OVERFLOW)
        {
            adapterInfo = (IP_ADAPTER_INFO *)malloc(dwBufSize);
            if (adapterInfo == NULL)
                return 0;
        }

        if (GetAdaptersInfo(adapterInfo, &dwBufSize) == NO_ERROR)
        {
            PIP_ADAPTER_INFO pInfo = adapterInfo;

            while (pInfo)
            {

                if (pInfo->Type == 23)
                {
                    MessageBoxA(0, "You are not allowed to play with a VPN on our server", "Error", MB_OK);
                    prevent_send = true;
                    return 0;
                }

                if (pInfo->Type == 6)
                {
                    if (!foundValidAdapter)
                    {
                        //if(pInfo->Type == IP_ADAPTER_TYPE)
                        sprintf(mac, "%02X-%02X-%02X-%02X-%02X-%02X",
                                pInfo->Address[0], pInfo->Address[1],
                                pInfo->Address[2], pInfo->Address[3],
                                pInfo->Address[4], pInfo->Address[5]);
                        foundValidAdapter = true;
                    }
                }

                if (pInfo->Type == 71)
                {
                    if (!foundValidAdapter)
                    {
                        //if(pInfo->Type == IP_ADAPTER_TYPE)
                        sprintf(mac, "%02X-%02X-%02X-%02X-%02X-%02X",
                                pInfo->Address[0], pInfo->Address[1],
                                pInfo->Address[2], pInfo->Address[3],
                                pInfo->Address[4], pInfo->Address[5]);
                        foundValidAdapter = true;
                    }
                }

                pInfo = pInfo->Next;
            }

            UINT32 cpuInfo[4];
            __cpuid((int*)cpuInfo, 1);
            if ((cpuInfo[2] >> 31) & 1)
            {
                MessageBoxA(0, "Virtual machines are not allowed to play on this server", "Error", MB_OK);
                prevent_send = true;
                return 0;
            }

            if (!foundValidAdapter)
            {
                MessageBoxA(0, "No suitable adapter found for HWID lib", "Error", MB_OK);
                return 0;
            }

            if (prevent_send)
            {
                MessageBoxA(0, "No suitable adapter found for HWID lib", "Error", MB_OK);
                return 0;
            }
            else
            {
                return mac;
            }
        }

        return 0;

    }

    char * hwidmgr::Encryption() {
        if (encrypted_text == "thaidu0ngpr0") {
            encrypted_text = hwidmgr::HhhHHh();
        }

        return encrypted_text;
    }

    char * hwidmgr::HhhHHh() {
        std::string str = "";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        return "_THUCANH2017_";
    }

    char* hwidmgr::GetSerial()
    {
        DWORD dwDiskSerial = 0;
        char* buffer = (char *)malloc(30);
        char* sysVolumeLetter = (char *)malloc(2);

        GetSystemWindowsDirectoryA(buffer, 30);

        for (int i = 0; i < 3; i++)
            sysVolumeLetter[i] = buffer[i];

        sysVolumeLetter[3] = '\0';


        GetVolumeInformationA(sysVolumeLetter, NULL, NULL, &dwDiskSerial, NULL, NULL, NULL, NULL);

        sprintf(buffer, "%d\n", dwDiskSerial);

        return buffer;
    }

    char* hwidmgr::GetHWID()
    {
        std::string str = "";
        char* mac = hwidmgr::GetMac();
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        char* stat = "_hhhhhhh_DEVSOME_";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

        char* enc = hwidmgr::Encryption();
        std::string date = hwidmgr::GetDate();
        const char* date2 = date.c_str();
        char* finalBuffer = (char *)malloc(strlen(enc) + strlen(mac) + strlen(date2));
        sprintf(finalBuffer, "%s%s%s", enc, mac, date2);

        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

        return finalBuffer;
    }

    std::string hwidmgr::GetRandomString(size_t length)
    {
        srand(time(0));
        string str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        string newstr;
        int pos;
        while (newstr.size() != length) {
            pos = ((rand() % (str.size() - 1)));
            newstr += str.substr(pos, 1);
        }
        return newstr;
    }

    std::string hwidmgr::GetDate() {
        std::time_t now = std::time(0);
        std::tm* now_tm = std::gmtime(&now);
        char buf[42];
        std::strftime(buf, 42, "0001-%m-%d %H:%M", now_tm);
        return buf;
    }

    std::string hwidmgr::GetDate2() {
        std::time_t now = std::time(0);
        std::tm* now_tm = std::gmtime(&now);
        char buf[42];
        std::strftime(buf, 42, "%Y-%m-%d %H:%M", now_tm);
        return buf;
    }
