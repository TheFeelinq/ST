#pragma once

#include <IFMainFrame.h>
#include "IFSTEventRegisterSlotList.h"
#include <list>
#include "ICPlayer.h"


#define MEMUTIL_READ_BY_PTR_OFFSET(ptr, offset, type) \
	*(type*)(((uintptr_t)ptr) + offset)

class CIFSTEventRegister : public CIFMainFrame {
GFX_DECLARE_DYNCREATE(CIFSTEventRegister)

GFX_DECLARE_MESSAGE_MAP(CIFSTEventRegister)

public:
    CIFSTEventRegister();

    bool OnCreate(long ln) override;
    void UpdateLog();
    void OnUpdate() override;
    void ClearDDJ();
    void Clear();
    void ResetPosition();
    static struct Event
    {
        int LineNum;
        std::wstring EventName;

    };

    static std::vector<Event> EventList;
private:
    void On_BtnClick();
    void On_BtnClick2();


public:
    CIFStatic *m_custom_label;
    CIFStatic *m_time_label;

    CIFSTEventRegisterSlotList* Slot1;
    CIFSTEventRegisterSlotList* Slot2;
    CIFSTEventRegisterSlotList* Slot3;
    CIFSTEventRegisterSlotList* Slot4;
    std::n_wstring SelectedItemName;
};
