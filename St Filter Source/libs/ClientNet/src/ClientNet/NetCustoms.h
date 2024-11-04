#pragma once
#include "MsgStreamBuffer.h"
#include <detours.h>
 //using FN_RECEIVE_MSG = bool(__thiscall*)(void* pSender, CMsgStreamBuffer* pMsg);
typedef bool (__thiscall *FN_RECEIVE_MSG)(void* pSender, CMsgStreamBuffer* pMsg);
typedef void**(__cdecl *FN_SEND_MSG)(const CMsgStreamBuffer*);
typedef enum _E_MSGHOOK_RESULT
{
    PASS_THROUGH,
    BLOCK
}E_MSGHOOK_RESULT;

typedef E_MSGHOOK_RESULT(*__MSG_HANDLER)(CMsgStreamBuffer*);
typedef std::map<UINT16 , __MSG_HANDLER>__MSG_HANDLER_MAP;
typedef  __MSG_HANDLER_MAP::iterator __MSG_HANDLER_MAP_IT;


class CNetCustoms
{
private:
    __MSG_HANDLER_MAP m_inMsgHandlerMap;
    __MSG_HANDLER_MAP m_outMsgHandlerMap;
    __MSG_HANDLER m_inMsgDefaultHandler;
    __MSG_HANDLER m_outMsgDefaultHandler;

public:
    CNetCustoms();

    ~CNetCustoms();

    E_MSGHOOK_RESULT HandleMsgIn(CMsgStreamBuffer* pMsg);
    E_MSGHOOK_RESULT HandleMsgOut(CMsgStreamBuffer* pMsg);
    void Initialize();
    static FN_RECEIVE_MSG s_fnRecvMsg;
    static FN_SEND_MSG s_fnSendMsg;

};
extern CNetCustoms* g_NetCustoms;