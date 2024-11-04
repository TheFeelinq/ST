#pragma once

#include <IFMainFrame.h>
#include "IFSTEventXoSoMienBacLichSuSlotList.h"
#include "IFSpinControl.h"

class CIFSTEventXoSoMienBacLichSu : public CIFMainFrame {
GFX_DECLARE_DYNCREATE(CIFSTEventXoSoMienBacLichSu)

GFX_DECLARE_MESSAGE_MAP(CIFSTEventXoSoMienBacLichSu)

public:
    CIFSTEventXoSoMienBacLichSu(void);
    ~CIFSTEventXoSoMienBacLichSu(void);
    bool OnCreate(long ln) override;

    void OnUpdate() override;
    void HideLists();
    void ShowList(BYTE listid);
    bool IsPageFull(BYTE PageID, BYTE LineID);
    void Clear();
    void UpdateXsmbLichSuList();
    void ClearDDJ();
    void ResetPosition();

    static struct XSMBLichSu
    {
        int LineNum;
        std::wstring So;
        std::wstring TienCuoc;
        std::wstring TrangThai;
        std::wstring TienTe;
        std::wstring Loai;
        std::wstring Ngay;

    };

    static std::vector<XSMBLichSu> XSMBLichSuList;


private:
    void On_BtnClick();


private:
    CIFStatic *m_stt;
    CIFStatic *m_so;
    CIFStatic *tiencuoc;
    CIFStatic *trangthai;
    CIFStatic *tiente;
    CIFStatic *loai;
    CIFStatic *ngay;


    CIFSpinControl* m_spin;

    CIFSTEventXoSoMienBacLichSuSlotList* m_slot1;
    CIFSTEventXoSoMienBacLichSuSlotList* m_slot2;
    CIFSTEventXoSoMienBacLichSuSlotList* m_slot3;
    CIFSTEventXoSoMienBacLichSuSlotList* m_slot4;
    CIFSTEventXoSoMienBacLichSuSlotList* m_slot5;
    CIFSTEventXoSoMienBacLichSuSlotList* m_slot6;
    CIFSTEventXoSoMienBacLichSuSlotList* m_slot7;
    CIFSTEventXoSoMienBacLichSuSlotList* m_slot8;
    CIFSTEventXoSoMienBacLichSuSlotList* m_slot9;
    CIFSTEventXoSoMienBacLichSuSlotList* m_slot10;

};
