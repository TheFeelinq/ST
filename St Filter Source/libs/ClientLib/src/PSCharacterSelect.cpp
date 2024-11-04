#include "PSCharacterSelect.h"
#include "Game.h"
#include "IFButton.h"
#include "IFFade.h"
#include "IFStatic.h"
#include "IFTextBox.h"
#include "IFWnd.h"
#include "Keyframe.h"
#include "World.h"
#include <BSLib/Debug.h>
#include <remodel/MemberFunctionHook.h>
#include <HWID/HawidManager.h>
#include <HWID/base64.h>
#include "BSLib/multibyte.h"
#include "../../DiscordRichPresence/src/DiscordRichPresence/DiscordManager.h"
#include "CPSMission.h"

extern HMODULE sro_client;
#define CHARSEL_CHARPOS_1 747
#define CHARSEL_CHARPOS_2 748
#define CHARSEL_CREATE 744
#define CHARSEL_INTRO 743
#define CLIENT_OFFSET(x) ((int)sro_client + x)
#define CHARSEL_KEYFRAME_START CLIENT_OFFSET(0xAC2D88)
#define CHARSEL_KEYFRAME_END CLIENT_OFFSET(0xAC2DA8)
#define CHARSEL_KEYFRAME_CREATE_1 CLIENT_OFFSET(0xAC2DC8)
#define CHARSEL_KEYFRAME_CREATE_2 CLIENT_OFFSET(0xAC2DE8)
#define CHARSEL_KEYFRAME_CREATE_3 CLIENT_OFFSET(0xAC2E08)
#define CHARSEL_KEYFRAME_CREATE_4 CLIENT_OFFSET(0xAC2E28)
#define CHARSEL_CHARACTER_POSITION_1 CLIENT_OFFSET(0xAC2E48)
#define CHARSEL_CHARACTER_POSITION_2 CLIENT_OFFSET(0xAC2E58)
#define CHARSEL_CHARACTER_POSITION_YOFFSET CLIENT_OFFSET(0x9D7C98)
#define STATIC_CONSTRUCTOR_LIST_START 0x98065C
#define STATIC_CONSTRUCTOR_LIST_END   0x981800
#define STATIC_CONSTRUCTOR_LIST_SIZE (STATIC_CONSTRUCTOR_LIST_END - STATIC_CONSTRUCTOR_LIST_START)


#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
GlobalVar<bool, 0x00EED9B8> g_bIsUnityServer;

const Keyframe frames_intro[] = {
        Keyframe(486.626f, 10.3903f, 224.418f, 0.099325f, 0.752854f, 0.0f, 80.0f),
        Keyframe(502.171f, 8.12451f, 241.01f, 0.099325f, 0.752854f, 0.0f, 80.0f),
};
//const Keyframe frames_intro[] = {
//        Keyframe(60.0f, -15.0f, 700.0f, 0.1f, 3.0f, 0.0f, 30.0f),
//        Keyframe(60.0f, -15.0f, 660.0f, 0.1f, 3.0f, 0.0f, 30.0f),
//};



bool CPSCharacterSelect::OnCreateIMPL(long ln) {
    PutDump("CPSCharacterSelect::OnCreate(%d)\n", ln);

    theApp.sub_8371D0();

    FUN_0085b400();

    SetProcessNetMsg(true);
    m_IRM.LoadFromFile("resinfo\\pscharacterselect.txt");
    m_IRM.CreateInterfaceSection("Select", this);
    m_IRM.CreateInterfaceSection("Info", m_IRM.GetResObj(GDR_STA_CHARINFO, 1));
    m_IRM.CreateInterfaceSection("Warning", m_IRM.GetResObj(GDR_STA_WPOPUP, 1));
    m_IRM.CreateInterfaceSection("Remain", m_IRM.GetResObj(GDR_STA_REMAINTIME, 1));
    m_IRM.CreateInterfaceSection("China", m_IRM.GetResObj(GDR_STA_CHINA, 1));
    m_IRM.CreateInterfaceSection("Europe", m_IRM.GetResObj(GDR_STA_EUROPE, 1));

    m_IRM.GetResObj(GDR_TEXT_MESSAGE2, 1)->ShowGWnd(true);
    RECT TextRect = { 27,28,365,343 };
    m_textbox = (CIFTextBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFTextBox), TextRect, 10001, 0);

    if (g_bIsUnityServer) {
        m_IRM.CreateInterfaceSection("UnityServer",
                                     m_IRM.GetResObj(GDR_STA_UNITY_SERVER_NOTIFY, 1));
        m_IRM.GetResObj(GDR_STA_UNITY_SERVER_NOTIFY, 1)->ShowGWnd(true);
    }

    m_IRM.CreateInterfaceSection("ChangeName", m_IRM.GetResObj(GDR_STA_UNITY_SERVER_CHANGENAME, 1));
    m_IRM.CreateInterfaceSection("NameDuplicate", m_IRM.GetResObj(GDR_STA_NAME_DUPLICATE, 1));

    m_IRM.GetResObj(GDR_STA_SCREENUP, 1)->ApplyGlobalScale(0);
    m_IRM.GetResObj(GDR_STA_SCREENDOWN, 1)->ApplyGlobalScale(0);
    m_IRM.GetResObj(GDR_STA_TITLE, 1)->ApplyGlobalScale(0);
    m_IRM.GetResObj(GDR_STA_REGIONTITLE, 1)->ApplyGlobalScale(0);
    m_IRM.GetResObj(GDR_FADE, 1)->ApplyGlobalScale(0);

    wnd_rect a2 = m_IRM.GetResObj(GDR_STA_SCREENUP, 1)->GetBounds();

    wnd_rect v109 = m_IRM.GetResObj(GDR_STA_SCREENDOWN, 1)->GetBounds();

    const ClientResolutonData &res = CGame::GetClientDimensionStuff();

    int v12 = res.width - 209;

    int buttons_y = v109.top() + 27;

    // State: All chars visible
    m_IRM.GetResObj(GDR_BTN_CREATE, 1)->MoveGWnd(v12, buttons_y);
    m_IRM.GetResObj(GDR_BTN_BACK, 1)->MoveGWnd(v12 + 104, buttons_y);

    // State: One char selected
    m_IRM.GetResObj(GDR_BTN_START, 1)->MoveGWnd(v12 - 104, buttons_y);
    m_IRM.GetResObj(GDR_BTN_DELETE, 1)->MoveGWnd(v12, buttons_y);
    m_IRM.GetResObj(GDR_BTN_RESTORE, 1)->MoveGWnd(v12, buttons_y);
    m_IRM.GetResObj(GDR_BTN_BACK2, 1)->MoveGWnd(v12 + 104, buttons_y);
    m_IRM.GetResObj(GDR_STA_CHARINFO, 1)->MoveGWnd(res.width - 271, a2.bottom() + 41);

    // State: Char being deleted
    wnd_size size = m_IRM.GetResObj(GDR_STA_REMAINTIME, 1)->GetSize();
    m_IRM.GetResObj(GDR_STA_REMAINTIME, 1)->MoveGWnd((res.width - size.width) / 2, v109.bottom() - 102);

    m_IRM.GetResObj(GDR_TEXT_MESSAGE, 1)->MoveGWnd(v109.top() + 26, v109.bottom() + 29);
    m_IRM.GetResObj(GDR_TEXT_MESSAGE, 1)->SetGWndSize(res.width - 26, 100);

    m_IRM.GetResObj(GDR_TEXT_MESSAGE2, 1)->MoveGWnd(res.width - 701, 36);



    const ClientRes &client = theApp.GetRes();


    wnd_size v108 = m_IRM.GetResObj(GDR_STA_WPOPUP, 1)->GetSize();
    m_IRM.GetResObj(GDR_STA_WPOPUP, 1)->MoveGWnd((client.res[0].width - v108.width) / 2, (client.res[0].height - v108.height) / 2);

    v108 = m_IRM.GetResObj(GDR_STA_WPOPUP, 1)->GetSize();
    m_IRM.GetResObj(GDR_STA_UNITY_SERVER_NOTIFY, 1)->MoveGWnd((client.res[0].width - v108.width) / 2, (client.res[0].height - v108.height) / 2);
    m_IRM.GetResObj(GDR_STA_UNITY_SERVER_NOTIFY, 1)->ShowGWnd(false);

    v108 = m_IRM.GetResObj(GDR_STA_UNITY_SERVER_CHANGENAME, 1)->GetSize();
    m_IRM.GetResObj(GDR_STA_UNITY_SERVER_CHANGENAME, 1)->MoveGWnd((client.res[0].width - v108.width) / 2, (client.res[0].height - v108.height) / 2);
    m_IRM.GetResObj(GDR_STA_UNITY_SERVER_CHANGENAME, 1)->ShowGWnd(false);

    v108 = m_IRM.GetResObj(GDR_STA_NAME_DUPLICATE, 1)->GetSize();
    m_IRM.GetResObj(GDR_STA_NAME_DUPLICATE, 1)->MoveGWnd((client.res[0].width - v108.width) / 2, (client.res[0].height - v108.height) / 2);
    m_IRM.GetResObj(GDR_STA_NAME_DUPLICATE, 1)->ShowGWnd(false);
    m_textbox->SetGWndSize(400,130);
    m_textbox->MoveGWnd((client.res[0].width - v108.width) / 2, (client.res[0].height - v108.height) /10);
    m_textbox->ShowGWnd(true);
    m_IRM.GetResObj(GDR_BTN_PREV, 1)->ShowGWnd(false);
    m_IRM.GetResObj(GDR_BTN_NEXT, 1)->ShowGWnd(false);

    static int names[] = {
            GDR_STA_NAMECHANGE1,
            GDR_STA_NAMECHANGE2,
            GDR_STA_NAMECHANGE3,
            GDR_STA_NAMECHANGE4};

    for (int i = 0; i < 4; i++) {
        m_IRM.GetResObj(names[i], 1)->ShowGWnd(false);
    }

    m_IRM.GetResObj(GDR_BTN_CANCEL, 1)->MoveGWnd(v12 + 104, buttons_y);

    // Text Boxes on Idol Screen
    m_IRM.GetResObj<CIFTextBox>(GDR_TEXT_MESSAGE, 1)->SetLineHeight(15);
    m_IRM.GetResObj<CIFTextBox>(GDR_TEXT_CHINA, 1)->SetLineHeight(16);
    m_IRM.GetResObj<CIFTextBox>(GDR_TEXT_EUROPE, 1)->SetLineHeight(17);

    // Border Box for Europe Textbox on Idol Screen
    idol_label[0] = m_IRM.GetResObj<CIFStatic>(GDR_STA_EUROPE, 1);
    idol_label[0]->TB_Func_9(0);

    // Border Box for China Textbox on Idol Screen
    idol_label[1] = m_IRM.GetResObj<CIFStatic>(GDR_STA_CHINA, 1);
    idol_label[1]->TB_Func_9(0);


    m_IRM.GetResObj(GDR_STA_ISLAM, 1)->ShowGWnd(false);
    m_IRM.GetResObj(GDR_BTN_START, 1)->ShowGWnd(false);
    m_IRM.GetResObj(GDR_BTN_DELETE, 1)->ShowGWnd(false);
    m_IRM.GetResObj(GDR_BTN_RESTORE, 1)->ShowGWnd(false);
    m_IRM.GetResObj(GDR_BTN_BACK2, 1)->ShowGWnd(false);
    m_IRM.GetResObj(GDR_STA_CHARINFO, 1)->ShowGWnd(false);
    m_IRM.GetResObj(GDR_STA_WPOPUP, 1)->ShowGWnd(false);
    m_IRM.GetResObj(GDR_STA_REMAINTIME, 1)->ShowGWnd(false);

    m_IRM.GetResObj<CIFTextBox>(GDR_TB_INFO, 1)->SetLineHeight(15);

    CIFFade *screenfade = m_IRM.GetResObj<CIFFade>(GDR_SCREENFADE, 1);
    screenfade->SetColor(D3DCOLOR_ARGB(255, 0, 0, 0));
    screenfade->ShowGWnd(false);

    CIFFade *fade = m_IRM.GetResObj<CIFFade>(GDR_FADE, 1);
    fade->SetColor(D3DCOLOR_ARGB(255, 0, 0, 0));
    fade->sub_6526E0(-128, 0, 1.5, 0.0, 1);

    m_IRM.GetResObj(GDR_LOADING_CHINA, 1)->ShowGWnd(false);
    m_IRM.GetResObj(GDR_LOADING_EUROPE, 1)->ShowGWnd(false);
    m_IRM.GetResObj(GDR_LOADINGFRAME, 1)->ShowGWnd(false);
    m_IRM.GetResObj(GDR_LOADING_STA, 1)->ShowGWnd(false);
    m_IRM.GetResObj(GDR_LOADINGG, 1)->ShowGWnd(false);

    FUN_00bbda70(1);

//    GETMAP()->Func_1(0x6951);
//
//    D3DXVECTOR3 loc(960, 0, 960);
//
//    GETMAP()->Func_0(0x6951, loc);


    GETMAP()->Func_1(0x5FBC);

    D3DXVECTOR3 loc(960, 0, 960);

    GETMAP()->Func_0(0x5FBC, loc);

    m_box.SetResource("res\\interface\\box.bsr", 1);
    m_box.SetLocation(D3DXVECTOR3(155, -20, 652));
    m_box.SetRotation(3.0);

    const D3DVECTOR box_loc[] = {
            {157.0, -20, 654.40002},
            {156.2, -20, 651.6},
            {155.6, -20, 651.6},
    };

    const float box_rot[] = {
            3.31,
            3.03,
            3.0};

    const char *box_resources[] = {
            "res\\interface\\interface_idol_europe.bsr",
            "res\\interface\\interface_idol_china.bsr",
            "res\\interface\\interface_lizard.bsr"};


    for (int i = 0; i < 3; i++) {
        idols[i].SetResource(box_resources[i], 1);
        idols[i].SetLocation(box_loc[i]);
        idols[i].SetRotation(box_rot[i]);
    }


    field_0x220 = 0;

    // Map animation callback stuff
    idols[2].m_compound->Func_7(*this);
    // Something with animation speed
    idols[2].Func_3(0, 0, 0, 0, 1.0, 1.0);

    if (N0000098B == 0 || N0000098B == 10) {
        this->TriggerAnimation_Intro();
    }

    m_seconds_elapsed = 0.0f;
    m_minutes_elapsed = 0;

    field_0x11c = false;

    FUN_008560e0();

    if (g_bIsUnityServer)
        FUN_008548d0(true);

    WaitGWnd(false);

    return true;
}

void CPSCharacterSelect::FUN_0085b400() {
    reinterpret_cast<void(__thiscall *)(CPSCharacterSelect *)>(0x0085b400)(this);
}


HOOK_ORIGINAL_MEMBER(0x0085b1f0, &CPSCharacterSelect::TriggerAnimation_Intro);
void CPSCharacterSelect::TriggerAnimation_Intro() {
    FUN_00854860(m_IRM.GetResObj<CIFStatic>(GDR_STA_TITLE, 1), 255, 0.5f, 0.0f, 0);
    m_IRM.GetResObj<CIFStatic>(GDR_STA_REGIONTITLE, 1)->ShowGWnd(false);

    idol_label[0]->ShowGWnd(false);
    idol_label[1]->ShowGWnd(false);

    CIFButton *createBtn = m_IRM.GetResObj<CIFButton>(GDR_BTN_CREATE, 1);
    FUN_00854860(createBtn, 255, 0.5f, 0.0f, 0);
    wnd_pos createBtnPos = createBtn->GetPos();
    createBtn->MoveGWnd2(createBtnPos);

    CIFButton *backBtn = m_IRM.GetResObj<CIFButton>(GDR_BTN_CREATE, 1);
    FUN_00854860(backBtn, 255, 0.5f, 0.0f, 0);
    wnd_pos backBtnPos = backBtn->GetPos();
    createBtn->MoveGWnd2(backBtnPos);

    m_IRM.GetResObj<CIFButton>(GDR_BTN_CANCEL, 1)->ShowGWnd(false);

    m_cameraworking->sub_4E6630();

    for (int i = 0; i < size(frames_intro); i++) {
        m_cameraworking->AddKeyframe(i * i, frames_intro[i].position, frames_intro[i].rotation);
    }

    theApp.camera.origin = m_cameraworking->location;
    theApp.camera.rotation_to_world = m_cameraworking->rotation;

    m_cameraworking->float_F0 = 2.0;
    current_state = 0;

}

void CPSCharacterSelect::FUN_008560e0() {

    reinterpret_cast<void(__thiscall *)(CPSCharacterSelect *)>(0x008560e0)(this);
}

void CPSCharacterSelect::FUN_008548d0(bool a1) {

    reinterpret_cast<void(__thiscall *)(CPSCharacterSelect *, bool)>(0x008548d0)(this, a1);
}
void CPSCharacterSelect::FUN_00854860(CIFStatic *obj, unsigned char opacity, float time, float a4, char a5) {

    obj->sub_6526E0(obj->GetN00009BB9(), opacity, time, a4, a5);
}
void CPSCharacterSelect::OnUpdateIMPL()
{
    if(this->m_IRM.GetResObj<CIFWnd>(12, 1)->IsVisible())
    {
        this->m_IRM.GetResObj<CIFWnd>(12, 1)->BringToFront();
    }
    if(this->m_IRM.GetResObj<CIFWnd>(13, 1)->IsVisible())
    {
        this->m_IRM.GetResObj<CIFWnd>(13, 1)->BringToFront();
    }
    if(this->m_IRM.GetResObj<CIFWnd>(14, 1)->IsVisible())
    {
        this->m_IRM.GetResObj<CIFWnd>(14, 1)->BringToFront();
    }
    if(this->m_IRM.GetResObj<CIFWnd>(15, 1)->IsVisible())
    {
        this->m_IRM.GetResObj<CIFWnd>(15, 1)->BringToFront();
    }
    if(this->m_IRM.GetResObj<CIFWnd>(16, 1)->IsVisible())
    {
        this->m_IRM.GetResObj<CIFWnd>(16, 1)->BringToFront();
    }
    if(this->m_IRM.GetResObj<CIFWnd>(18, 1) && this->m_IRM.GetResObj<CIFWnd>(18, 1)->IsVisible())
    {
        CPSMission::m_CharSelectOn=true;
    }


    reinterpret_cast<void (__thiscall *)(CPSCharacterSelect *)>(0x0085ce30)(this);
}
void static_const_intro(void)
{
    Keyframes* intro_start = (Keyframes*)CHARSEL_KEYFRAME_START;

    intro_start->position.x = 486.626f;
    intro_start->position.y = 10.3903f;
    intro_start->position.z = 224.418f;

    intro_start->rotation.x = 0.099325f;
    intro_start->rotation.y = 0.752854f;
    intro_start->rotation.z = 0;

    intro_start->distance = 80.0f;
    intro_start->time = 0; // time is preset and ignored



    Keyframes* intro_end = (Keyframes*)CHARSEL_KEYFRAME_END;

    intro_end->position.x = 502.171f;
    intro_end->position.y = 8.12451f;
    intro_end->position.z = 241.01f;

    intro_end->rotation.x = 0.099325f;
    intro_end->rotation.y = 0.752854f;
    intro_end->rotation.z = 0;

    intro_end->distance = 80.0f;
    intro_end->time = 5.0f; // time is preset and ignored

}

void static_const_create(void) {
    Keyframes* create_1 = (Keyframes*)CHARSEL_KEYFRAME_CREATE_1;

    create_1->position.x = 502.171f;
    create_1->position.y = 8.12451f;
    create_1->position.z = 241.01f;

    create_1->rotation.x = 0.099325f;
    create_1->rotation.y = 0.752854f;
    create_1->rotation.z = 0;

    create_1->distance = 80.0f;
    create_1->time = 0.0f; // time is preset and ignored


    Keyframes* create_2 = (Keyframes*)CHARSEL_KEYFRAME_CREATE_2;

    create_2->position.x = 504.531f;
    create_2->position.y = 8.12451f;
    create_2->position.z = 235.514f;

    create_2->rotation.x = 0.099325f;
    create_2->rotation.y = 1.16525f;
    create_2->rotation.z = 0;

    create_2->distance = 80.0;
    create_2->time = 6.0f; // time is preset and ignored


    Keyframes* create_3 = (Keyframes*)CHARSEL_KEYFRAME_CREATE_3;

    create_3->position.x = 478.134f;
    create_3->position.y = 10.7672f;
    create_3->position.z = 231.172f;

    create_3->rotation.x = 0.099325f;
    create_3->rotation.y = 1.33341f;
    create_3->rotation.z = 0;

    create_3->distance = 80.0f;
    create_3->time = 10.0f; // time is preset and ignored


    Keyframes* create_4 = (Keyframes*)CHARSEL_KEYFRAME_CREATE_4;

    create_4->position.x = 376.72f;
    create_4->position.y = 7.73251f;
    create_4->position.z = 204.31f;

    create_4->rotation.x = 0.8f;
    create_4->rotation.y = 0.8088f;
    create_4->rotation.z = 0;

    create_4->distance = 6.7f;
    create_4->time = 15.0f; // time is preset and ignored
}
void static_const_char_1(void) {
    Character3D* character =  (Character3D*)CHARSEL_CHARACTER_POSITION_1;

    character->location.x = 460.835f;
    character->location.y = 0.626249f;
    character->location.z = 233.131f;

    character->rotation = -0.95493f;

}

void static_const_char_2(void) {
    Character3D* character =  (Character3D*)CHARSEL_CHARACTER_POSITION_2;

    character->location.x = 490.574f;
    character->location.y = 0.985927f;
    character->location.z = 194.903f;

    character->rotation = -0.827606f;

}
int CPSCharacterSelect::client_override_constructor(int id, static_constructor function) {
    DWORD dwProtect = 0;

    if (id < 0) {
        return 0;
    }

    if (id > STATIC_CONSTRUCTOR_LIST_SIZE) {
        return 0;
    }

    static_constructor* list = (static_constructor*)((int)sro_client + STATIC_CONSTRUCTOR_LIST_START);

    //printf("[StaticConst] Have list at %08x\n", list);

    //printf("[StaticConst] Unprotecting %d bytes of memory at %08x\n", sizeof(static_constructor*), &list[id]);

    // Unprotect first
    if (!VirtualProtect(
            (LPVOID)(&(list[id])),
            sizeof(static_constructor*),
            PAGE_EXECUTE_READWRITE,
            &dwProtect)) {

        perror("Failed to unprotect memory\n");
        printf("Failed to unprotect memory\n");
        return 0;
    }

    list[id] = function;

    // aannnd protect
    VirtualProtect(
            (LPVOID)(&(list[id])),
            sizeof(static_constructor*), dwProtect, NULL);

    return 1;
}
void PatchMe(DWORD address, BYTE value)
{
    DWORD oldProtect;
    void *addr = reinterpret_cast<void *>(address);
    if (VirtualProtect((LPVOID)addr, 1, PAGE_READWRITE, &oldProtect) == FALSE)
    {
        throw ("cannot patch function");
        return;
    }
    *reinterpret_cast<BYTE *>(addr) = value;
    VirtualProtect(addr, 1, oldProtect, &oldProtect);
}
void char_select_stuff(void)
{
    //idols start
    //PatchMe(0x400000 + 0x0098ADC6, 0xA0);
    PatchMe(0x400000 + 0x009D7DF0, 0x00);
    PatchMe(0x400000 + 0x009D7DF1, 0x00);
    PatchMe(0x400000 + 0x009D7DF2, 0xA0);
    PatchMe(0x400000 + 0x009D7DF4, 0x00);
    PatchMe(0x400000 + 0x009D7DF5, 0x00);
    PatchMe(0x400000 + 0x009D7DF6, 0xA0);
    PatchMe(0x400000 + 0x009D7DF8, 0x00);
    PatchMe(0x400000 + 0x009D7DF9, 0x00);
    PatchMe(0x400000 + 0x009D7DFA, 0xBE);
    PatchMe(0x400000 + 0x009D7DFC, 0x00);
    PatchMe(0x400000 + 0x009D7DFD, 0x00);
    PatchMe(0x400000 + 0x009D7DFE, 0x50);
    PatchMe(0x400000 + 0x009D7DFF, 0x43);
    PatchMe(0x400000 + 0x009D7E00, 0x00);
    PatchMe(0x400000 + 0x009D7E01, 0x40);
    PatchMe(0x400000 + 0x009D7E02, 0xBE);
    PatchMe(0x400000 + 0x009D7E28, 0x00);
    PatchMe(0x400000 + 0x009D7E29, 0x00);
    PatchMe(0x400000 + 0x009D7E2A, 0x4F);
    PatchMe(0x400000 + 0x009D7E2B, 0x43);
    PatchMe(0x400000 + 0x009D7E7E, 0xBD);
    PatchMe(0x400000 + 0x009D7E84, 0xF0);
    PatchMe(0x400000 + 0x009D7E85, 0x85);
    PatchMe(0x400000 + 0x009D7E86, 0xF7);
    PatchMe(0x400000 + 0x009D7E87, 0x40);
    //idols end
    //idols animations start
    PatchMe(0x400000 + 0x009D7CFC, 0xE3);
    PatchMe(0x400000 + 0x009D7CFD, 0x68);
    PatchMe(0x400000 + 0x009D7CFE, 0x4E);
    PatchMe(0x400000 + 0x009D7CFF, 0x43);
    PatchMe(0x400000 + 0x009D7D00, 0x00);
    PatchMe(0x400000 + 0x009D7D01, 0x00);
    PatchMe(0x400000 + 0x009D7D02, 0xA0);
    PatchMe(0x400000 + 0x009D7D03, 0x41);
    PatchMe(0x400000 + 0x009D7D05, 0x00);
    PatchMe(0x400000 + 0x009D7D06, 0xB9);
    PatchMe(0x400000 + 0x009D7D08, 0xE3);
    PatchMe(0x400000 + 0x009D7D09, 0x68);
    PatchMe(0x400000 + 0x009D7D0A, 0x4E);
    PatchMe(0x400000 + 0x009D7D0B, 0x43);
    PatchMe(0x400000 + 0x009D7D0C, 0x00);
    PatchMe(0x400000 + 0x009D7D0D, 0x00);
    PatchMe(0x400000 + 0x009D7D0E, 0xA0);
    PatchMe(0x400000 + 0x009D7D0F, 0x41);
    PatchMe(0x400000 + 0x009D7D10, 0x00);
    PatchMe(0x400000 + 0x009D7D11, 0x00);
    PatchMe(0x400000 + 0x009D7D12, 0xB9);
    //idols anim end
    //CharSelect Distance
    PatchMe(0x00D8AD3E, (byte)0x70417C87);
    //CharSelect Distance end
    //Region start
    PatchMe(0x400000 + 0x009D7CA6, 0x00);
    PatchMe(0x400000 + 0x009D7CA7, 0x00);
    PatchMe(0x400000 + 0x009D601E, 0x00);
    PatchMe(0x400000 + 0x009D601F, 0x00);
    PatchMe(0x400000 + 0x0045F4FD, 0xBC);
    PatchMe(0x400000 + 0x0045F4FE, 0x5F);

    PatchMe(0x005b542c+1, 0x1);
    PatchMe(0x005b53df+1, 0x1);


    //region end

#ifdef OLD_MAINPOP
    PatchMe(0x400000 + 0x0045C6F5, 0xE9);
	PatchMe(0x400000 + 0x0045C6F6, 0xCA);
	PatchMe(0x400000 + 0x0045C6F7, 0x00);
	PatchMe(0x400000 + 0x0045C6F8, 0x00);
	PatchMe(0x400000 + 0x0045C6F9, 0x00);
	PatchMe(0x400000 + 0x0045C7CD, 0x09);
	PatchMe(0x400000 + 0x002A2901, 0xBC);
	PatchMe(0x400000 + 0x002A2909, 0x50);
	PatchMe(0x400000 + 0x002A290A, 0xFF);
	PatchMe(0x400000 + 0x002A290B, 0xD0);
	PatchMe(0x400000 + 0x002A290C, 0x8B);
	PatchMe(0x400000 + 0x002A290D, 0x44);
	PatchMe(0x400000 + 0x002A290E, 0x24);
	PatchMe(0x400000 + 0x002A290F, 0x2C);
	PatchMe(0x400000 + 0x002A2910, 0x83);
	PatchMe(0x400000 + 0x002A2911, 0xF8);
	PatchMe(0x400000 + 0x002A2912, 0x08);
	PatchMe(0x400000 + 0x002A2913, 0x0F);
	PatchMe(0x400000 + 0x002A2914, 0x82);
	PatchMe(0x400000 + 0x002A2915, 0x85);
	PatchMe(0x400000 + 0x002A2916, 0x00);
	PatchMe(0x400000 + 0x002A2917, 0x00);
	PatchMe(0x400000 + 0x002A2918, 0x00);
	PatchMe(0x400000 + 0x002A2919, 0x90);
	PatchMe(0x400000 + 0x002A291A, 0x90);
	PatchMe(0x400000 + 0x002A291B, 0x90);
	PatchMe(0x400000 + 0x002A291C, 0x90);
	PatchMe(0x400000 + 0x002A291D, 0x90);
	PatchMe(0x400000 + 0x002A291E, 0x90);
	PatchMe(0x400000 + 0x002A291F, 0x90);
	PatchMe(0x400000 + 0x002A2920, 0x90);
	PatchMe(0x400000 + 0x002A2921, 0x90);
	PatchMe(0x400000 + 0x002A2922, 0x90);
	PatchMe(0x400000 + 0x002A2923, 0x90);
	PatchMe(0x400000 + 0x002A2924, 0x90);
	PatchMe(0x400000 + 0x002A2925, 0x90);
	PatchMe(0x400000 + 0x002A2926, 0x90);
	PatchMe(0x400000 + 0x002A2927, 0x90);
	PatchMe(0x400000 + 0x002A2928, 0x90);
	PatchMe(0x400000 + 0x002A2929, 0x90);
	PatchMe(0x400000 + 0x002A292A, 0x90);
	PatchMe(0x400000 + 0x002A292B, 0x90);
	PatchMe(0x400000 + 0x002A292C, 0x90);
	PatchMe(0x400000 + 0x002A292D, 0x90);
	PatchMe(0x400000 + 0x002A292E, 0x90);
	PatchMe(0x400000 + 0x002A292F, 0x90);
	PatchMe(0x400000 + 0x002A2930, 0x90);
	PatchMe(0x400000 + 0x002A2931, 0x90);
	PatchMe(0x400000 + 0x002A2932, 0x90);
	PatchMe(0x400000 + 0x002A2933, 0x90);
	PatchMe(0x400000 + 0x002A2934, 0x90);
	PatchMe(0x400000 + 0x002A2935, 0x90);
	PatchMe(0x400000 + 0x002A2936, 0x90);
	PatchMe(0x400000 + 0x002A2937, 0x90);
	PatchMe(0x400000 + 0x002A2938, 0x90);
	PatchMe(0x400000 + 0x002A2939, 0x90);
	PatchMe(0x400000 + 0x002A293A, 0x90);
	PatchMe(0x400000 + 0x002A293B, 0x90);
	PatchMe(0x400000 + 0x002A293C, 0x90);
	PatchMe(0x400000 + 0x002A293D, 0x90);
	PatchMe(0x400000 + 0x002A293E, 0x90);
	PatchMe(0x400000 + 0x002A293F, 0x90);
	PatchMe(0x400000 + 0x002A2940, 0x90);
	PatchMe(0x400000 + 0x002A2941, 0x90);
	PatchMe(0x400000 + 0x002A2942, 0x90);
	PatchMe(0x400000 + 0x002A2943, 0x90);
	PatchMe(0x400000 + 0x002A2944, 0x90);
	PatchMe(0x400000 + 0x002A2945, 0x90);
	PatchMe(0x400000 + 0x002A2946, 0x90);
	PatchMe(0x400000 + 0x002A2947, 0x90);
	PatchMe(0x400000 + 0x002A2948, 0x90);
	PatchMe(0x400000 + 0x002A2949, 0x90);
	PatchMe(0x400000 + 0x002A294A, 0x90);
	PatchMe(0x400000 + 0x002A294B, 0x90);
	PatchMe(0x400000 + 0x002A294C, 0x90);
	PatchMe(0x400000 + 0x002A294D, 0x90);
	PatchMe(0x400000 + 0x002A294E, 0x90);
	PatchMe(0x400000 + 0x002A294F, 0x90);
	PatchMe(0x400000 + 0x002A2950, 0x90);
	PatchMe(0x400000 + 0x002A2951, 0x90);
	PatchMe(0x400000 + 0x002A2952, 0x90);
	PatchMe(0x400000 + 0x002A2953, 0x90);
	PatchMe(0x400000 + 0x002A2954, 0x90);
	PatchMe(0x400000 + 0x002A2955, 0x90);
	PatchMe(0x400000 + 0x002A2956, 0x90);
	PatchMe(0x400000 + 0x002A2957, 0x90);
	PatchMe(0x400000 + 0x002A2958, 0x90);
	PatchMe(0x400000 + 0x002A2959, 0x90);
	PatchMe(0x400000 + 0x002A295A, 0x90);
	PatchMe(0x400000 + 0x002A295B, 0x90);
	PatchMe(0x400000 + 0x002A295C, 0x90);
	PatchMe(0x400000 + 0x002A295D, 0x90);
	PatchMe(0x400000 + 0x002A295E, 0x90);
	PatchMe(0x400000 + 0x002A295F, 0x90);
	PatchMe(0x400000 + 0x002A2960, 0x90);
	PatchMe(0x400000 + 0x002A2961, 0x90);
	PatchMe(0x400000 + 0x002A2962, 0x90);
	PatchMe(0x400000 + 0x002A2963, 0x90);
	PatchMe(0x400000 + 0x002A2964, 0x90);
	PatchMe(0x400000 + 0x002A2965, 0x90);
	PatchMe(0x400000 + 0x002A2966, 0x90);
	PatchMe(0x400000 + 0x002A2967, 0x90);
	PatchMe(0x400000 + 0x002A2968, 0x90);
	PatchMe(0x400000 + 0x002A2969, 0x90);
	PatchMe(0x400000 + 0x002A296A, 0x90);
	PatchMe(0x400000 + 0x002A296B, 0x90);
	PatchMe(0x400000 + 0x002A296C, 0x90);
	PatchMe(0x400000 + 0x002A296D, 0x90);
	PatchMe(0x400000 + 0x002A296E, 0x90);
	PatchMe(0x400000 + 0x002A296F, 0x90);
	PatchMe(0x400000 + 0x002A2970, 0x90);
	PatchMe(0x400000 + 0x002A2971, 0x90);
	PatchMe(0x400000 + 0x002A2972, 0x90);
	PatchMe(0x400000 + 0x002A2973, 0x90);
	PatchMe(0x400000 + 0x002A2974, 0x90);
	PatchMe(0x400000 + 0x002A2975, 0x90);
	PatchMe(0x400000 + 0x002A2976, 0x90);
	PatchMe(0x400000 + 0x002A2977, 0x90);
	PatchMe(0x400000 + 0x002A2978, 0x90);
	PatchMe(0x400000 + 0x002A2979, 0x90);
	PatchMe(0x400000 + 0x002A297A, 0x90);
	PatchMe(0x400000 + 0x002A297B, 0x90);
	PatchMe(0x400000 + 0x002A297C, 0x90);
	PatchMe(0x400000 + 0x002A297D, 0x90);
	PatchMe(0x400000 + 0x002A297E, 0x90);
	PatchMe(0x400000 + 0x002A297F, 0x90);
	PatchMe(0x400000 + 0x002A2980, 0x90);
	PatchMe(0x400000 + 0x002A2981, 0x90);
	PatchMe(0x400000 + 0x002A2982, 0x90);
	PatchMe(0x400000 + 0x002A2983, 0x90);
	PatchMe(0x400000 + 0x002A2984, 0x90);
	PatchMe(0x400000 + 0x002A2985, 0x90);
	PatchMe(0x400000 + 0x002A2986, 0x90);
	PatchMe(0x400000 + 0x002A2987, 0x90);
	PatchMe(0x400000 + 0x002A2988, 0x90);
	PatchMe(0x400000 + 0x002A2989, 0x90);
	PatchMe(0x400000 + 0x002A298A, 0x90);
	PatchMe(0x400000 + 0x002A298B, 0x90);
#endif
}

void CPSCharacterSelect::char_select_override()
{

    // We override the constructor list
    client_override_constructor(CHARSEL_INTRO, &static_const_intro);
    client_override_constructor(CHARSEL_CREATE, &static_const_create);

    client_override_constructor(CHARSEL_CHARPOS_1, &static_const_char_1);
    client_override_constructor(CHARSEL_CHARPOS_2, &static_const_char_2);


    DWORD dwProtect = 0;
    // Unprotect first
    if (!VirtualProtect(
            (LPVOID)CHARSEL_CHARACTER_POSITION_YOFFSET,
            sizeof(double),
            PAGE_EXECUTE_READWRITE,
            &dwProtect)) {

        perror("Failed to unprotect memory\n");
        printf("Failed to unprotect memory\n");
        return;
    }

    *((double*)(CHARSEL_CHARACTER_POSITION_YOFFSET)) = 0;

    VirtualProtect((LPVOID)CHARSEL_CHARACTER_POSITION_YOFFSET, sizeof(double), dwProtect, NULL);
    char_select_stuff();
}

bool CPSCharacterSelect::OnServerPacketRecv(CMsgStreamBuffer* msg) {
    if (msg->msgid() == 0xB003) //notice
    {
        int Color;
        std::n_string notice;
        *msg >> notice >> Color;
        this->ShowMessage(Convert(notice), Color);
//        wchar_t buffer[255];
//        swprintf_s(buffer,L"%S", notice.c_str());
//        std::n_wstring strmsg(buffer);
//        m_textbox->sub_64F8A0(strmsg, 0, Color, Color, -1, 0, 0);
//        m_textbox->ShowGWnd(true);
//        m_textbox->BringToFront();
        msg->m_currentReadBytes = 0;
    }
    if (msg->msgid() == 0xB888) //notice
    {
        long long notice;
        bool GUIIconTaiXiu;
        bool GUIIconDailyLogin;
        bool GUIIconExTraFeatures;
        bool GUIIconRebot;
        bool GUIIconChest;
        bool GUIIconEvent;
        bool GUIIconLive;
        bool DoubleClickLogin;
        bool XsmbEnable;
        bool LotoEnable;
        *msg >> notice>>GUIIconTaiXiu>>GUIIconDailyLogin>>GUIIconExTraFeatures>>GUIIconRebot>>DoubleClickLogin>>GUIIconChest>>GUIIconEvent>>GUIIconLive >>XsmbEnable>>LotoEnable;

        CPSMission::Icon_TaiXiu = GUIIconTaiXiu;
        CPSMission::Icon_DailyLogin = GUIIconDailyLogin;
        CPSMission::Icon_ExtralFeature = GUIIconExTraFeatures;
        CPSMission::Icon_ReBot = GUIIconRebot;
        CPSMission::Icon_Chest = GUIIconChest;
        CPSMission::Icon_Event = GUIIconEvent;
        CPSMission::Icon_LiveStream = GUIIconLive;
        CPSMission::Double_Click_ToLogin = DoubleClickLogin;
        CPSMission::XSMB_ENABLE = XsmbEnable;
        CPSMission::LOTO_ENABLE = LotoEnable;

        DiscordManager::Instance().Start(notice);
        msg->FlushRemaining();
    }
    if (msg->msgid() == 0xB007) //notice
    {
        BYTE Action;
        BYTE Unk;
        *msg >> Action >> Unk;

        DiscordManager::UpdateState(GAME_STATE::CHARACTER_SELECTION);

        if(Action == 1 && Unk == 1)
            CPSMission::m_CharSelectOn=false;

        if (Action == 2)
        {
            //DiscordManager::Instance().UpdateState(GAME_STATE::CHARACTER_SELECTION);

            const char* hwid = HawidManager::GetHWID();
            std::string hwid_X = HawidManager::Xor(hwid);
            std::string hwid_1 = base64_encode(hwid_X);
            std::string Version = "v263c";
            const char* mac = HawidManager::GetMac();
            const char* serial = HawidManager::GetSerial();
            std::string date = HawidManager::GetDate2();
            const char* date2 = date.c_str();
            std::string macs = mac;
            std::string serials = serial;
            std::string date2s = date2;

            byte v255 = rand() % 2;
            byte v237 = 0;
            byte v118 = 0;

            if (v255 == 1)
            {
                v237 = 237;
            }
            else if (v255 == 2)
            {
                v237 = 220;
            }
            CMsgStreamBuffer packet(0x1789);
            if (!hwid_1.empty())
            {
                packet << v255;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << std::n_string(macs.c_str());
                packet << std::n_string(serials.c_str());
                packet << std::n_string(date2s.c_str());
                packet << std::n_string(Version.c_str());
                packet << std::n_string(hwid_1.c_str());
                SendMsg(packet);
               /* wchar_t buffer[255];
                swprintf_s(buffer,L"STFilter verification success! You may login now.");
                std::n_wstring strmsg(buffer);
                m_textbox->sub_64F8A0(strmsg, 0, 0x00ff00, 0x00ff00, -1, 0, 0);*/


            }
        }
        msg->m_currentReadBytes = 0;
    }

    return reinterpret_cast<int(__thiscall*)(CPSCharacterSelect*, CMsgStreamBuffer*)>(0x0085fc60)(this, msg);
}
wchar_t* CPSCharacterSelect::Convert(std::n_string name)
{
    wchar_t* szName;
    const char* p = name.c_str();
    int nChars = MultiByteToWideChar(CP_ACP, 0, p, -1, NULL, 0);
    szName = new WCHAR[nChars];
    MultiByteToWideChar(CP_ACP, 0, p, -1, (LPWSTR)szName, nChars);
    return szName;
}
