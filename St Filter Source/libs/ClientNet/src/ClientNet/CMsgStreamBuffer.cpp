#include "CMsgStreamBuffer.h"
#include "CPSMission.h"
int CPSMission::OnPacketRecv(MsgStreamBuffer* MsgBuffer)
{
    //Returning 1 means packet is accepted & read, 0 means fail & afair client may crash if you do return 0
    //Also, if you're planning to read original packets, set TotalReadBytes to 0 after you finish reading, because sro_client will re-read this stuff and if any byte were read before, it'll crash because it attempts to read over max bytes limit.
    return reinterpret_cast<int(__thiscall*)(CPSMission*, MsgStreamBuffer*)>(0x0084CAB0)(this, MsgBuffer);
}