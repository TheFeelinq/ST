#pragma once

#include "NIFWnd.h"
#include "NIFStatic.h"
#include "NIFMainFrame.h"

class CNIFWorldMap : public CNIFMainFrame {

    
public:
    bool OnCreateIMPL(long ln);
    void OnUpdateIMPL();
    void RenderMyselfIMPL();
    void FUN_006192f0();
    int FUN_00620f70();
    void FUN_00610d30(short region,float x,float y,float z);

public:
    char pad_0x798[4];
    int m_inMapPostion_x;
    int m_inMapPostion_y;
    int m_CursorPostion_x;
    int m_CursorPostion_y;
    int m_map_state_change;
    int m_map_UniqueID;

BEGIN_FIXTURE()

        ENSURE_OFFSET(m_inMapPostion_x, 0x79C)
        ENSURE_OFFSET(m_inMapPostion_y, 0x7A0)
        ENSURE_OFFSET(m_CursorPostion_x, 0x7A4)
        ENSURE_OFFSET(m_CursorPostion_y, 0x7A8)
        ENSURE_OFFSET(m_map_state_change, 0x7AC)
        ENSURE_OFFSET(m_map_UniqueID, 0x7B0)
    END_FIXTURE()

    RUN_FIXTURE(CNIFWorldMap)
};