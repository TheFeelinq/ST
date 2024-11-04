
#include "NetCustoms.h"
#include "MsgStreamBuffer.h"
#define MSG_HANDLE_RECV_OFFSET			0x00BA8F70
#define MSG_HANDLE_SEND_OFFSET			0x008418D0

CNetCustoms* g_NetCustoms;

typedef bool (__thiscall *fnRecvMsg)(void* pSender, CMsgStreamBuffer* pMsg);
typedef void**(__cdecl *fnSendMsg)(const CMsgStreamBuffer*);

bool __fastcall HandleMsgInEx(void* pSender, void* /* dummy edx */, CMsgStreamBuffer* pMsg);
void** __cdecl HandleMsgOutEx(CMsgStreamBuffer* pMsg);


FN_RECEIVE_MSG CNetCustoms::s_fnRecvMsg = NULL;
FN_SEND_MSG CNetCustoms::s_fnSendMsg = NULL;
E_MSGHOOK_RESULT unk1 (CMsgStreamBuffer*)
 {
     return PASS_THROUGH;
 }
E_MSGHOOK_RESULT unk2 (CMsgStreamBuffer*)
{
    return PASS_THROUGH;
}

CNetCustoms::CNetCustoms()
{
    CMsgStreamBuffer* a1;
    CMsgStreamBuffer* a2;
    m_inMsgDefaultHandler = (__MSG_HANDLER)unk1(a1);
    m_outMsgDefaultHandler = (__MSG_HANDLER)unk2(a2);
}

CNetCustoms::~CNetCustoms()
{

}
void CNetCustoms::Initialize()
{
    s_fnRecvMsg = reinterpret_cast<fnRecvMsg>(MSG_HANDLE_RECV_OFFSET);
    s_fnSendMsg = reinterpret_cast<fnSendMsg>(MSG_HANDLE_SEND_OFFSET);

    DetourTransactionBegin();
    DetourAttach(&(PVOID&)s_fnRecvMsg, HandleMsgInEx);
    DetourAttach(&(PVOID&)s_fnSendMsg, HandleMsgOutEx);
    DetourTransactionCommit();
}

E_MSGHOOK_RESULT CNetCustoms::HandleMsgIn(CMsgStreamBuffer* pMsg)
{

    __MSG_HANDLER_MAP_IT it = m_inMsgHandlerMap.find(pMsg->msgid() );
    return (it != m_inMsgHandlerMap.end() ? it->second(pMsg) : m_inMsgDefaultHandler(pMsg));
}

E_MSGHOOK_RESULT CNetCustoms::HandleMsgOut(CMsgStreamBuffer* pMsg)
{
    __MSG_HANDLER_MAP_IT it = m_outMsgHandlerMap.find(pMsg->msgid() );
    return (it != m_outMsgHandlerMap.end() ? it->second(pMsg) : m_outMsgDefaultHandler(pMsg));
}

bool __fastcall HandleMsgInEx(void* pSender, void* /* dummy edx */, CMsgStreamBuffer* pMsg)
{
    //printf("v3\n");
    E_MSGHOOK_RESULT result = g_NetCustoms->HandleMsgIn(pMsg);
    bool passThrough = false;


    switch (result)
    {
        case E_MSGHOOK_RESULT::PASS_THROUGH:
            passThrough = true;
            pMsg->m_currentReadBytes=0;
            break;
        case E_MSGHOOK_RESULT::BLOCK:
            passThrough = false;
            pMsg->FlushRemaining();
            break;
    }

    if (!passThrough)
        return false;

    return CNetCustoms::s_fnRecvMsg(pSender, pMsg);
}

void** __cdecl HandleMsgOutEx(CMsgStreamBuffer* pMsg)
{
    E_MSGHOOK_RESULT result = g_NetCustoms->HandleMsgOut(pMsg);

    bool passThrough = false;

    switch (result)
    {
        case E_MSGHOOK_RESULT::PASS_THROUGH:
            passThrough = true;
            pMsg->m_currentReadBytes=0;
            break;
        case E_MSGHOOK_RESULT::BLOCK:
            passThrough = false;
            pMsg->FlushRemaining();
            break;
    }

    if (!passThrough)
        return false;

    return CNetCustoms::s_fnSendMsg(pMsg);
}

