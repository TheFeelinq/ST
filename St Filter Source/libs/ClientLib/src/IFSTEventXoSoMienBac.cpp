#include "IFSTEventXoSoMienBac.h"
#include <ctime>
#include <windows.h>
#include <shellapi.h>

#include "GInterface.h"
#include "ClientNet/MsgStreamBuffer.h"
#include "CPSMission.h"
#include "PSQuickStart.h"


#include "unsorted.h"
#include "GlobalHelpersThatHaveNoHomeYet.h"
#include "ClientNet/ClientNet.h"
#include "Game.h"
#include "ICPlayer.h"
#include "IFWnd.h"
#include <BSLib\multibyte.h>

#include <IFSystemMessage.h>
#define ELECTUSEVENTTIMERS_XOSO_DANHBANGGILFSILK 63
#define ELECTUSEVENTTIMERS_XOSO_DANHBANGSILK 62
#define ELECTUSEVENTTIMERS_XOSO_DANHBANGGOLD 61
#define ELECTUSEVENTTIMERS_XOSO_DANHDE 60
#define ELECTUSEVENTTIMERS_XOSO_LICHSU 59
#define ELECTUSEVENTTIMERS_SERVERTIME 58
#define ELECTUSEVENTTIMERS_GIAIDACBIET_LABEL 57
#define ELECTUSEVENTTIMERS_GIAINHAT_LABEL 56
#define ELECTUSEVENTTIMERS_GIAINHI_LABEL 55
#define ELECTUSEVENTTIMERS_GIAIBA_LABEL 54
#define ELECTUSEVENTTIMERS_GIAIBON_LABEL 53
#define ELECTUSEVENTTIMERS_GIAINAM_LABEL 52
#define ELECTUSEVENTTIMERS_GIAISAU_LABEL 51
#define ELECTUSEVENTTIMERS_GIAIBAY_LABEL 50
#define ELECTUSEVENTTIMERS_GIAIBAY_VALUE_SLOT1 49
#define ELECTUSEVENTTIMERS_GIAIBAY_VALUE_SLOT2 48
#define ELECTUSEVENTTIMERS_GIAIBAY_VALUE_SLOT3 47
#define ELECTUSEVENTTIMERS_GIAIBAY_VALUE_SLOT4 46
#define ELECTUSEVENTTIMERS_GIAISAU_VALUE_SLOT1 45
#define ELECTUSEVENTTIMERS_GIAISAU_VALUE_SLOT2 44
#define ELECTUSEVENTTIMERS_GIAISAU_VALUE_SLOT3 43
#define ELECTUSEVENTTIMERS_GIAINAM_VALUE_SLOT1 42
#define ELECTUSEVENTTIMERS_GIAINAM_VALUE_SLOT2 41
#define ELECTUSEVENTTIMERS_GIAINAM_VALUE_SLOT3 40
#define ELECTUSEVENTTIMERS_GIAINAM_VALUE_SLOT4 39
#define ELECTUSEVENTTIMERS_GIAINAM_VALUE_SLOT5 38
#define ELECTUSEVENTTIMERS_GIAINAM_VALUE_SLOT6 37
#define ELECTUSEVENTTIMERS_GIAIBON_VALUE_SLOT1 36
#define ELECTUSEVENTTIMERS_GIAIBON_VALUE_SLOT2 35
#define ELECTUSEVENTTIMERS_GIAIBON_VALUE_SLOT3 34
#define ELECTUSEVENTTIMERS_GIAIBON_VALUE_SLOT4 33
#define ELECTUSEVENTTIMERS_GIAIBA_VALUE_SLOT1 32
#define ELECTUSEVENTTIMERS_GIAIBA_VALUE_SLOT2 31
#define ELECTUSEVENTTIMERS_GIAIBA_VALUE_SLOT3 30
#define ELECTUSEVENTTIMERS_GIAIBA_VALUE_SLOT4 29
#define ELECTUSEVENTTIMERS_GIAIBA_VALUE_SLOT5 28
#define ELECTUSEVENTTIMERS_GIAIBA_VALUE_SLOT6 27
#define ELECTUSEVENTTIMERS_GIAINHI_VALUE_SLOT1 26
#define ELECTUSEVENTTIMERS_GIAINHI_VALUE_SLOT2 25
#define ELECTUSEVENTTIMERS_GIAINHAT_VALUE_SLOT1 24
#define ELECTUSEVENTTIMERS_GIAIDB_VALUE_SLOT1 23
#define ELECTUSGRANTNAME_SOMUONDANH_LABEL 22

#define ELECTUSGRANTNAME_DIEMMUONDANH_LABEL 21
#define ELECTUSEVENTTIMERS_XOSO_XACNHAN 20
#define ELECTUSGRANTNAME_SOMUONDANH_INPUT 19
#define ELECTUSGRANTNAME_DIEMMUONDANH_INPUT 18
#define ELECTUSEVENTTIMERS_EVENTS_XOSO_LABEL 17
#define ELECTUSEVENTTIMERS_EVENTS_KETQUA_LABEL 16
#define ELECTUSEVENTTIMERS_XOSO_TOOLTIP 15
#define ELECTUSEVENTTIMERS_XOSO_TOOLTIP2 14
#define ELECTUSEVENTTIMERS_XOSO_REFRESH_BUTTON 13
#define ELECTUSEVENTTIMERS_XOSO_CLOSE_BUTTON 12

#define ELECTUSEVENTTIMERS_XOSO_TITLE 11
#define ELECTUSEVENTTIMERS_XOSO_FRAME 10



GFX_IMPLEMENT_DYNCREATE(CIFSTEventXoSoMienBac, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFSTEventXoSoMienBac, CIFMainFrame)
                    ONG_COMMAND(ELECTUSEVENTTIMERS_XOSO_CLOSE_BUTTON, &OnClick_Exit)
                    ONG_COMMAND(ELECTUSEVENTTIMERS_XOSO_REFRESH_BUTTON, &On_BtnClickKQ)
                    ONG_COMMAND(ELECTUSEVENTTIMERS_XOSO_XACNHAN, &On_BtnClick)
                    ONG_COMMAND(ELECTUSEVENTTIMERS_XOSO_LICHSU, &On_BtnClickLichSu)
                    ONG_COMMAND(ELECTUSEVENTTIMERS_XOSO_DANHDE, &On_BtnClickDanhDe)
                    ONG_COMMAND(ELECTUSEVENTTIMERS_XOSO_DANHBANGGOLD, &On_BtnClickDANHBANGGOLD)
                    ONG_COMMAND(ELECTUSEVENTTIMERS_XOSO_DANHBANGSILK, &On_BtnClickLichSuDANHBANGSILK)
                    ONG_COMMAND(ELECTUSEVENTTIMERS_XOSO_DANHBANGGILFSILK, &On_BtnClickDanhDeDANHBANGGILFSILK)

GFX_END_MESSAGE_MAP()


CIFSTEventXoSoMienBac::CIFSTEventXoSoMienBac(void)
{
    printf("> " __FUNCTION__ "\n");
}


CIFSTEventXoSoMienBac::~CIFSTEventXoSoMienBac(void)
{
    printf("> " __FUNCTION__ "\n");
}

bool CIFSTEventXoSoMienBac::OnCreate(long ln)
{
    // Populate inherited members
    CIFMainFrame::OnCreate(ln);
    // Set own title


    TB_Func_13("interface\\frame\\mframe_wnd_", 1, 0);


    RECT rect_frame = {10, 40, 579, 396};

    CIFFrame *frame = (CIFFrame *) CreateInstance(this,GFX_RUNTIME_CLASS(CIFFrame),rect_frame,80,1);
    frame->TB_Func_13("interface\\frame\\frameg_wnd_", 1, 0);

    RECT rect_background = {rect_frame.left + 10,rect_frame.top + 10,rect_frame.right - 20,rect_frame.bottom - 20};

    CIFNormalTile *tile = (CIFNormalTile *) CreateInstance(this,GFX_RUNTIME_CLASS(CIFNormalTile),rect_background,81,1);
    tile->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_f.ddj", 1, 0);




    RECT rect_button3 = {542,5,24,24};
    m_mybutton3 = (CIFButton *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFButton),rect_button3,ELECTUSEVENTTIMERS_XOSO_REFRESH_BUTTON,1);
    m_mybutton3->TB_Func_13("interface\\ifcommon\\electus\\electustitles_refresh.ddj", 1, 1);

    RECT rect_button4 = {452,188,90,23};
    m_mybutton4 = (CIFButton *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFButton),rect_button4,ELECTUSEVENTTIMERS_XOSO_XACNHAN,1);
    m_mybutton4->SetText(TSM_GETTEXTPTR("UIIT_STT_XOSO_XACNHAN"));
    m_mybutton4->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);

    RECT rect_button5 = {452,220,90,23};
    m_mybutton5 = (CIFButton *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFButton),rect_button5,ELECTUSEVENTTIMERS_XOSO_LICHSU,1);
    m_mybutton5->SetText(TSM_GETTEXTPTR("UIIT_STT_XOSO_LICHSU"));
    m_mybutton5->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);

    RECT rect_button6 = {452,252,90,23};
    m_mybutton6 = (CIFButton *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFButton),rect_button6,ELECTUSEVENTTIMERS_XOSO_DANHDE,1);
    m_mybutton6->SetText(TSM_GETTEXTPTR("UIIT_STT_XOSO_DANHDE"));
    m_mybutton6->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);

    RECT rect_button7 = {423,384,16,16};
    m_mybutton7 = (CIFButton *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFButton),rect_button7,ELECTUSEVENTTIMERS_XOSO_DANHBANGGOLD,1);
    m_mybutton7->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\checkbutton_off.ddj", 1, 1);

    RECT rect_button8 = {487,384,16,16};
    m_mybutton8 = (CIFButton *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFButton),rect_button8,ELECTUSEVENTTIMERS_XOSO_DANHBANGSILK,1);
    m_mybutton8->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\checkbutton_off.ddj", 1, 1);

    RECT rect_button9 = {548,384,16,16};
    m_mybutton9 = (CIFButton *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFButton),rect_button9,ELECTUSEVENTTIMERS_XOSO_DANHBANGGILFSILK,1);
    m_mybutton9->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\checkbutton_off.ddj", 1, 1);

    RECT rect_custom_label62 = {20,54,562,32};
    m_custom_label62 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label62,88,1);
    m_custom_label62->TB_Func_13("interface\\guild\\gil_subj_button09.ddj", 1, 0);

    RECT rect_custom_label12 = {20,9,100,20};
    m_custom_label12 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label12,ELECTUSEVENTTIMERS_XOSO_TITLE,1);
    m_custom_label12->SetText(TSM_GETTEXTPTR("UIIT_STT_XOSO_TITLE"));

    RECT rect_custom_label13 = {414,286,161,15};
    m_custom_label13 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label13,ELECTUSEVENTTIMERS_XOSO_TOOLTIP2,1);
    m_custom_label13->SetText(TSM_GETTEXTPTR("UIIT_STT_XOSO_TOOLTIP2"));

    RECT rect_custom_label14 = {10,437,573,14};
    m_custom_label13 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label14,ELECTUSEVENTTIMERS_XOSO_TOOLTIP,1);
    m_custom_label13->SetText(TSM_GETTEXTPTR("UIIT_STT_XOSO_TOOLTIP"));
    m_custom_label13->m_FontTexture.SetColor(0xFFF18706);

    RECT rect_custom_label15 = {71,59,260,14};
    m_custom_label15 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label15,ELECTUSEVENTTIMERS_EVENTS_KETQUA_LABEL,1);
    m_custom_label15->SetText(TSM_GETTEXTPTR("UIIT_STT_EVENTS_KETQUA_LABEL"));

    RECT rect_custom_label16 = {432,59,142,14};
    m_custom_label16 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label16,ELECTUSEVENTTIMERS_EVENTS_XOSO_LABEL,1);
    m_custom_label16->SetText(TSM_GETTEXTPTR("UIIT_STT_EVENTS_XOSO_LABEL"));

///////// m_edit
    RECT rect_m_edit = {524,146,50,20};
    m_edit = (CIFEdit *) (CIFEdit *) CreateInstance(this,GFX_RUNTIME_CLASS(CIFEdit),rect_m_edit,ELECTUSGRANTNAME_DIEMMUONDANH_INPUT,1);
    m_edit->BringToFront();
    m_edit->TB_Func_5(1);
    m_edit->SetFocus_MAYBE();
    RECT rect_m_edit_frame =  {rect_m_edit.left -2,rect_m_edit.top -2,rect_m_edit.right +4,rect_m_edit.bottom +4};
    CIFFrame *frame_m_edit = (CIFFrame *) CreateInstance(this,GFX_RUNTIME_CLASS(CIFFrame),rect_m_edit_frame,82,1);
    frame_m_edit->TB_Func_13("interface\\frame\\ub_pet_wnd_", 1, 0);

    RECT rect_background_m_edit = {rect_m_edit_frame.left + 2,rect_m_edit_frame.top + 2,rect_m_edit_frame.right - 4,rect_m_edit_frame.bottom - 4};
    CIFNormalTile *tile_m_edit = (CIFNormalTile *) CreateInstance(this,GFX_RUNTIME_CLASS(CIFNormalTile),rect_background_m_edit,83,1);
    tile_m_edit->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_d.ddj", 1, 0);

///////// m_edit2
    RECT rect_m_edit2 = {524,116,50,20};
    m_edit1 = (CIFEdit *) (CIFEdit *) CreateInstance(this,GFX_RUNTIME_CLASS(CIFEdit),rect_m_edit2,ELECTUSGRANTNAME_SOMUONDANH_INPUT,1);
    m_edit1->BringToFront();
    m_edit1->TB_Func_5(1);
    m_edit1->SetFocus_MAYBE();
    RECT rect_m_edit_frame2 =  {rect_m_edit2.left -2,rect_m_edit2.top -2,rect_m_edit2.right +4,rect_m_edit2.bottom +4};
    CIFFrame *frame_m_edit2 = (CIFFrame *) CreateInstance(this,GFX_RUNTIME_CLASS(CIFFrame),rect_m_edit_frame2,82,1);
    frame_m_edit2->TB_Func_13("interface\\frame\\ub_pet_wnd_", 1, 0);

    RECT rect_background_m_edit2 = {rect_m_edit_frame2.left + 2,rect_m_edit_frame2.top + 2,rect_m_edit_frame2.right - 4,rect_m_edit_frame2.bottom - 4};
    CIFNormalTile *tile_m_edit2 = (CIFNormalTile *) CreateInstance(this,GFX_RUNTIME_CLASS(CIFNormalTile),rect_background_m_edit2,83,1);
    tile_m_edit2->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_d.ddj", 1, 0);


    RECT rect_custom_label18 = {415,146,106,20};
    m_custom_label18 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label18,ELECTUSGRANTNAME_DIEMMUONDANH_LABEL,1);
    m_custom_label18->SetText(TSM_GETTEXTPTR("UIIT_STT_DIEMMUONDANH_LABEL"));

    RECT rect_custom_label21 = {415,116,106,20};
    m_custom_label21 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label21,ELECTUSGRANTNAME_SOMUONDANH_LABEL,1);
    m_custom_label21->SetText(TSM_GETTEXTPTR("UIIT_STT_SOMUONDANH_LABEL"));

    RECT rect_custom_label22 = {91,83,308,32};
    m_custom_label22 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label22,ELECTUSEVENTTIMERS_GIAIDB_VALUE_SLOT1,1);
    m_custom_label22->SetText(TSM_GETTEXTPTR("ELECTUSEVENTTIMERS_GIAIDB_VALUE_SLOT1"));

    RECT rect_custom_label23 = {91,120,308,32};
    m_custom_label23 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label23,ELECTUSEVENTTIMERS_GIAINHAT_VALUE_SLOT1,1);
    m_custom_label23->SetText(TSM_GETTEXTPTR("ELECTUSEVENTTIMERS_GIAINHAT_VALUE_SLOT1"));

    RECT rect_custom_label24 = {247,153,152,32};
    m_custom_label24 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label24,ELECTUSEVENTTIMERS_GIAINHI_VALUE_SLOT2,1);
    m_custom_label24->SetText(TSM_GETTEXTPTR("ELECTUSEVENTTIMERS_GIAINHI_VALUE_SLOT2"));

    RECT rect_custom_label25 = {91,153,152,32};
    m_custom_label25 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label25,ELECTUSEVENTTIMERS_GIAINHI_VALUE_SLOT1,1);
    m_custom_label25->SetText(TSM_GETTEXTPTR("ELECTUSEVENTTIMERS_GIAINHI_VALUE_SLOT1"));

    RECT rect_custom_label26 = {304,188,96,32};
    m_custom_label26 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label26,ELECTUSEVENTTIMERS_GIAIBA_VALUE_SLOT6,1);
    m_custom_label26->SetText(TSM_GETTEXTPTR("ELECTUSEVENTTIMERS_GIAIBA_VALUE_SLOT6"));

    RECT rect_custom_label27 = {192,188,96,32};
    m_custom_label27 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label27,ELECTUSEVENTTIMERS_GIAIBA_VALUE_SLOT5,1);
    m_custom_label27->SetText(TSM_GETTEXTPTR("ELECTUSEVENTTIMERS_GIAIBA_VALUE_SLOT5"));

    RECT rect_custom_label28 = {91,188,96,32};
    m_custom_label28 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label28,ELECTUSEVENTTIMERS_GIAIBA_VALUE_SLOT4,1);
    m_custom_label28->SetText(TSM_GETTEXTPTR("ELECTUSEVENTTIMERS_GIAIBA_VALUE_SLOT4"));

    RECT rect_custom_label29 = {304,224,96,32};
    m_custom_label29 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label29,ELECTUSEVENTTIMERS_GIAIBA_VALUE_SLOT3,1);
    m_custom_label29->SetText(TSM_GETTEXTPTR("ELECTUSEVENTTIMERS_GIAIBA_VALUE_SLOT3"));

    RECT rect_custom_label30 = {192,224,96,32};
    m_custom_label30 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label30,ELECTUSEVENTTIMERS_GIAIBA_VALUE_SLOT2,1);
    m_custom_label30->SetText(TSM_GETTEXTPTR("ELECTUSEVENTTIMERS_GIAIBA_VALUE_SLOT2"));

    RECT rect_custom_label31 = {91,224,96,32};
    m_custom_label31 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label31,ELECTUSEVENTTIMERS_GIAIBA_VALUE_SLOT1,1);
    m_custom_label31->SetText(TSM_GETTEXTPTR("ELECTUSEVENTTIMERS_GIAIBA_VALUE_SLOT1"));

    RECT rect_custom_label32 = {330,259,69,32};
    m_custom_label32 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label32,ELECTUSEVENTTIMERS_GIAIBON_VALUE_SLOT4,1);
    m_custom_label32->SetText(TSM_GETTEXTPTR("ELECTUSEVENTTIMERS_GIAIBON_VALUE_SLOT4"));

    RECT rect_custom_label33 = {247,259,69,32};
    m_custom_label33 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label33,ELECTUSEVENTTIMERS_GIAIBON_VALUE_SLOT3,1);
    m_custom_label33->SetText(TSM_GETTEXTPTR("ELECTUSEVENTTIMERS_GIAIBON_VALUE_SLOT3"));

    RECT rect_custom_label34 = {164,259,69,32};
    m_custom_label34 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label34,ELECTUSEVENTTIMERS_GIAIBON_VALUE_SLOT2,1);
    m_custom_label34->SetText(TSM_GETTEXTPTR("ELECTUSEVENTTIMERS_GIAIBON_VALUE_SLOT2"));

    RECT rect_custom_label35 = {91,259,69,32};
    m_custom_label35 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label35,ELECTUSEVENTTIMERS_GIAIBON_VALUE_SLOT1,1);
    m_custom_label35->SetText(TSM_GETTEXTPTR("ELECTUSEVENTTIMERS_GIAIBON_VALUE_SLOT1"));

    RECT rect_custom_label36 = {304,294,96,32};
    m_custom_label36 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label36,ELECTUSEVENTTIMERS_GIAINAM_VALUE_SLOT6,1);
    m_custom_label36->SetText(TSM_GETTEXTPTR("ELECTUSEVENTTIMERS_GIAINAM_VALUE_SLOT6"));

    RECT rect_custom_label37 = {191,294,96,32};
    m_custom_label37 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label37,ELECTUSEVENTTIMERS_GIAINAM_VALUE_SLOT5,1);
    m_custom_label37->SetText(TSM_GETTEXTPTR("ELECTUSEVENTTIMERS_GIAINAM_VALUE_SLOT5"));

    RECT rect_custom_label38 = {91,294,96,32};
    m_custom_label38 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label38,ELECTUSEVENTTIMERS_GIAINAM_VALUE_SLOT4,1);
    m_custom_label38->SetText(TSM_GETTEXTPTR("ELECTUSEVENTTIMERS_GIAINAM_VALUE_SLOT4"));

    RECT rect_custom_label39 = {304,328,96,32};
    m_custom_label39 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label39,ELECTUSEVENTTIMERS_GIAINAM_VALUE_SLOT3,1);
    m_custom_label39->SetText(TSM_GETTEXTPTR("ELECTUSEVENTTIMERS_GIAINAM_VALUE_SLOT3"));

    RECT rect_custom_label40 = {191,328,96,32};
    m_custom_label40 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label40,ELECTUSEVENTTIMERS_GIAINAM_VALUE_SLOT2,1);
    m_custom_label40->SetText(TSM_GETTEXTPTR("ELECTUSEVENTTIMERS_GIAINAM_VALUE_SLOT2"));

    RECT rect_custom_label41 = {91,328,96,32};
    m_custom_label41 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label41,ELECTUSEVENTTIMERS_GIAINAM_VALUE_SLOT1,1);
    m_custom_label41->SetText(TSM_GETTEXTPTR("ELECTUSEVENTTIMERS_GIAINAM_VALUE_SLOT1"));

    RECT rect_custom_label42 = {304,363,96,32};
    m_custom_label42 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label42,ELECTUSEVENTTIMERS_GIAISAU_VALUE_SLOT3,1);
    m_custom_label42->SetText(TSM_GETTEXTPTR("ELECTUSEVENTTIMERS_GIAISAU_VALUE_SLOT3"));

    RECT rect_custom_label43 = {191,363,96,32};
    m_custom_label43 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label43,ELECTUSEVENTTIMERS_GIAISAU_VALUE_SLOT2,1);
    m_custom_label43->SetText(TSM_GETTEXTPTR("ELECTUSEVENTTIMERS_GIAISAU_VALUE_SLOT2"));

    RECT rect_custom_label44 = {91,363,96,32};
    m_custom_label44 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label44,ELECTUSEVENTTIMERS_GIAISAU_VALUE_SLOT1,1);
    m_custom_label44->SetText(TSM_GETTEXTPTR("ELECTUSEVENTTIMERS_GIAISAU_VALUE_SLOT1"));

    RECT rect_custom_label45 = {327,400,69,30};
    m_custom_label45 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label45,ELECTUSEVENTTIMERS_GIAIBAY_VALUE_SLOT4,1);
    m_custom_label45->SetText(TSM_GETTEXTPTR("ELECTUSEVENTTIMERS_GIAIBAY_VALUE_SLOT4"));

    RECT rect_custom_label46 = {246,400,69,30};
    m_custom_label46 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label46,ELECTUSEVENTTIMERS_GIAIBAY_VALUE_SLOT3,1);
    m_custom_label46->SetText(TSM_GETTEXTPTR("ELECTUSEVENTTIMERS_GIAIBAY_VALUE_SLOT3"));

    RECT rect_custom_label47 = {161,400,69,30};
    m_custom_label47 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label47,ELECTUSEVENTTIMERS_GIAIBAY_VALUE_SLOT2,1);
    m_custom_label47->SetText(TSM_GETTEXTPTR("ELECTUSEVENTTIMERS_GIAIBAY_VALUE_SLOT2"));

    RECT rect_custom_label48 = {91,400,69,30};
    m_custom_label48 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label48,ELECTUSEVENTTIMERS_GIAIBAY_VALUE_SLOT1,1);
    m_custom_label48->SetText(TSM_GETTEXTPTR("ELECTUSEVENTTIMERS_GIAIBAY_VALUE_SLOT1"));

    RECT rect_custom_label49 = {20,400,69,30};
    m_custom_label49 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label49,ELECTUSEVENTTIMERS_GIAIBAY_LABEL,1);
    m_custom_label49->SetText(TSM_GETTEXTPTR("UIIT_STT_GIAIBAY_LABEL"));

    RECT rect_custom_label50 = {20,364,69,32};
    m_custom_label50 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label50,ELECTUSEVENTTIMERS_GIAISAU_LABEL,1);
    m_custom_label50->SetText(TSM_GETTEXTPTR("UIIT_STT_GIAISAU_LABEL"));

    RECT rect_custom_label51 = {20,294,69,68};
    m_custom_label51 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label51,ELECTUSEVENTTIMERS_GIAINAM_LABEL,1);
    m_custom_label51->SetText(TSM_GETTEXTPTR("UIIT_STT_GIAINAM_LABEL"));

    RECT rect_custom_label52 = {20,259,69,32};
    m_custom_label52 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label52,ELECTUSEVENTTIMERS_GIAIBON_LABEL,1);
    m_custom_label52->SetText(TSM_GETTEXTPTR("UIIT_STT_GIAIBON_LABEL"));

    RECT rect_custom_label53 = {20,189,69,68};
    m_custom_label53 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label53,ELECTUSEVENTTIMERS_GIAIBA_LABEL,1);
    m_custom_label53->SetText(TSM_GETTEXTPTR("UIIT_STT_GIAIBA_LABEL"));

    RECT rect_custom_label54 = {20,154,69,32};
    m_custom_label54 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label54,ELECTUSEVENTTIMERS_GIAINHI_LABEL,1);
    m_custom_label54->SetText(TSM_GETTEXTPTR("UIIT_STT_GIAINHI_LABEL"));

    RECT rect_custom_label55 = {20,119,69,32};
    m_custom_label55 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label55,ELECTUSEVENTTIMERS_GIAINHAT_LABEL,1);
    m_custom_label55->SetText(TSM_GETTEXTPTR("UIIT_STT_GIAINHAT_LABEL"));

    RECT rect_custom_label56 = {20,84,69,32};
    m_custom_label56 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label56,ELECTUSEVENTTIMERS_GIAIDACBIET_LABEL,1);
    m_custom_label56->SetText(TSM_GETTEXTPTR("UIIT_STT_GIAIDACBIET_LABEL"));

    RECT rect_custom_label57 = {90,9,419,14};
    m_custom_label57 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label57,ELECTUSEVENTTIMERS_SERVERTIME,1);
    m_custom_label57->SetText(TSM_GETTEXTPTR("ELECTUSEVENTTIMERS_SERVERTIME"));

    RECT rect_custom_label58 = {417,366,29,12};
    m_custom_label58 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label58,84,1);
    m_custom_label58->SetText(TSM_GETTEXTPTR("UIIT_STT_DANHGOLD_LABEL"));

    RECT rect_custom_label59 = {484,366,29,12};
    m_custom_label59 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label59,85,1);
    m_custom_label59->SetText(TSM_GETTEXTPTR("UIIT_STT_DANHSILK_LABEL"));

    RECT rect_custom_label60 = {538,366,29,12};
    m_custom_label60 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label60,86,1);
    m_custom_label60->SetText(TSM_GETTEXTPTR("UIIT_STT_DANHGILF_LABEL"));

    RECT rect_custom_label61 = {20,81,373,345};
    m_custom_label61 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label61,87,1);
    m_custom_label61->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\xoso.ddj", 1, 0);

    m_edit ->SetMaxStringInput(5);
    m_edit1 ->SetMaxStringInput(2);
/*
    m_mybutton7 ->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\checkbutton_on.ddj", 0, 0);
    m_mybutton8 ->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\checkbutton_off.ddj", 0, 0);
    m_mybutton9 ->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\checkbutton_off.ddj", 0, 0);*/
    this->ShowGWnd(false);


    return true;
}

void CIFSTEventXoSoMienBac::OnUpdate()
{
    time_t rawtime;
    struct tm * timeinfo;
    wchar_t buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    wcsftime(buffer, sizeof(buffer), L"%d-%m-%Y %H:%M:%S", timeinfo);
    m_custom_label57->SetText(buffer);
    short ALTState = GetKeyState(VK_MENU);
    if (ALTState == -127 || ALTState == -128) // ALT is hold
    {
        this->OnCloseWnd();
    }

}

void CIFSTEventXoSoMienBac::On_BtnClick()
{
    std::n_wstring input_text = m_edit->GetNText();
    std::n_wstring input_text1 = m_edit1->GetNText();
    if(input_text.empty()||input_text1.empty())
    {
        wchar_t message[1000];
        swprintf_s(message, TSM_GETTEXTPTR("UIIT_STT_INPUT_RQ"));
        CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
        int color = D3DCOLOR_ARGB(255, 255, 0, 0);
        systemmessage->WriteMessage(0xFF, color, message, 0, 1);
    }
    else if(input_text1.length()>2)
    {
        wchar_t message[1000];
        swprintf_s(message, TSM_GETTEXTPTR("UIIT_STT_INPUT_XSMB_LIMIT1"));

        CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
        int color = D3DCOLOR_ARGB(255, 255, 0, 0);
        systemmessage->WriteMessage(0xFF, color, message, 0, 1);
    }
    else if(input_text.length()>5)
    {
        wchar_t message[1000];
        swprintf_s(message, TSM_GETTEXTPTR("UIIT_STT_INPUT_XSMB_LIMIT2"));
        CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
        int color = D3DCOLOR_ARGB(255, 255, 0, 0);
        systemmessage->WriteMessage(0xFF, color, message, 0, 1);
    } else
    {
        if(this->gold) {
            CMsgStreamBuffer buf(0x1318);
            buf << std::n_string(TO_NSTRING(this->m_edit->GetNText()));
            buf << std::n_string("!eventxsmbgold");
            buf << std::n_string(TO_NSTRING(this->m_edit1->GetNText()));
            SendMsg(buf);

        }
        else if(this->silk) {
            CMsgStreamBuffer buf(0x1318);
            buf << std::n_string(TO_NSTRING(this->m_edit->GetNText()));
            buf << std::n_string("!eventxsmbsilk");
            buf << std::n_string(TO_NSTRING(this->m_edit1->GetNText()));
            SendMsg(buf);

        }
        else if(this->gilf) {
            CMsgStreamBuffer buf(0x1318);
            buf << std::n_string(TO_NSTRING(this->m_edit->GetNText()));
            buf << std::n_string("!eventxsmbgilf");
            buf << std::n_string(TO_NSTRING(this->m_edit1->GetNText()));
            SendMsg(buf);

        }
    }
}
void CIFSTEventXoSoMienBac::On_BtnClickKQ()
{
    CMsgStreamBuffer buf(0x1318);
    buf << std::n_string("!XSMBKQ");
    buf << std::n_string("!XSMBKQ");
    SendMsg(buf);


}
void CIFSTEventXoSoMienBac::On_BtnClickDANHBANGGOLD()
{
    wchar_t message[1000];
    swprintf_s(message, TSM_GETTEXTPTR("UIIT_STT_SELECT_MONEY_GOLD"));

    CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
    int color = D3DCOLOR_ARGB(255, 224, 199, 144);
    systemmessage->WriteMessage(0xFF, color, message, 0, 1);

    m_mybutton7 ->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\checkbutton_on.ddj", 0, 0);
    m_mybutton8 ->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\checkbutton_off.ddj", 0, 0);
    m_mybutton9 ->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\checkbutton_off.ddj", 0, 0);
    this->gold = true;
    this->silk = false;
    this->gilf=false;
}
void CIFSTEventXoSoMienBac::On_BtnClickLichSuDANHBANGSILK()
{
    wchar_t message[1000];
    swprintf_s(message, TSM_GETTEXTPTR("UIIT_STT_SELECT_MONEY_SILK"));


    CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
    int color = D3DCOLOR_ARGB(255, 224, 199, 144);
    systemmessage->WriteMessage(0xFF, color, message, 0, 1);
    m_mybutton7 ->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\checkbutton_off.ddj", 0, 0);
    m_mybutton8 ->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\checkbutton_on.ddj", 0, 0);
    m_mybutton9 ->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\checkbutton_off.ddj", 0, 0);
    this->gold = false;
    this->silk = true;
    this->gilf=false;

}
void CIFSTEventXoSoMienBac::On_BtnClickDanhDeDANHBANGGILFSILK()
{
    wchar_t message[1000];
    swprintf_s(message, TSM_GETTEXTPTR("UIIT_STT_SELECT_MONEY_GIFTSILK"));



    CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
    int color = D3DCOLOR_ARGB(255, 224, 199, 144);
    systemmessage->WriteMessage(0xFF, color, message, 0, 1);

    m_mybutton7 ->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\checkbutton_off.ddj", 0, 0);
    m_mybutton8 ->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\checkbutton_off.ddj", 0, 0);
    m_mybutton9 ->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\checkbutton_on.ddj", 0, 0);
    this->gold = false;
    this->silk = false;
    this->gilf=true;
}
void CIFSTEventXoSoMienBac::On_BtnClickLichSu()
{
    CMsgStreamBuffer buf(0x1318);
    buf << std::n_string("!XSMBLS");
    buf << std::n_string("!XSMBLS");
    SendMsg(buf);
    g_pCGInterface->GetEventXoSoLichSuGUI()->ShowGWnd(true);
    g_pCGInterface->GetEventXoSoLichSuGUI()->ResetPosition();
    this->OnCloseWnd();
}
void CIFSTEventXoSoMienBac::On_BtnClickDanhDe()
{
    CMsgStreamBuffer buf(0x1318);
    buf << std::n_string("!XSMBDANHDE");
    buf << std::n_string("!XSMBDANHDE");
    SendMsg(buf);


}
void CIFSTEventXoSoMienBac::OnClick_Exit()
{
    this->OnCloseWnd();


}
void CIFSTEventXoSoMienBac::ResetPosition()
{
    const ClientRes &client = theApp.GetRes();
    wnd_size v109 = this->GetSize();
    this->MoveGWnd((client.res[0].width - v109.width) / 2, (client.res[0].height - v109.height) / 4);
}