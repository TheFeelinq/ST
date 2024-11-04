#include "Rebot.h"
#include <GFX3DFunction/GFXVideo3d.h>
#include <GFX3DFunction/DrawingHelpers.h>
#include <imgui/imgui.h>
#include "../../../DevKit_DLL/src/Util.h"
#include "CPSMission.h"
#include "ICMonster.h"
#include "PartyData.h"
#include "CharacterDependentData.h"
#include "IFPlayerMiniInfo.h"
#include "GameDataExt.h"
#include <EntityManagerClient.h>
#include <NavMesh/RTNavMesh.h>
#include <NavMesh/SNavMeshInst.h>
#include <algorithm>
#include <BSLib/multibyte.h>
#include <GlobalDataManager.h>
#include <TextStringManager.h>
#include <ctime>
#include <GFXMainFrame/Controler.h>

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)


int Rebot::FPatrolDestIndex=0;
bool Rebot::RebotStart = false;
bool Rebot::RebotShow = false;
std::map<short, Skill*> Rebot::HaveSkill;
std::map<short, Skill*> Rebot::AllSkillOfChar;
std::list<std::wstring> Rebot::m_CharNeedBuff;
std::map<short, BuffSkill*> Rebot::m_SkillBuffList;
std::map<std::wstring, BuffSkill*> Rebot::m_SkillNeedBuffList;
DWORD32 Rebot::SkillBaseHead;
HWND Rebot::GameHWND=0;
RebotConfig Rebot::Config = {};
CICharactor* Rebot::SelectObj=0;
CICharactor* Rebot::SelectObjRes=0;
CICharactor* Rebot::SelectObjBuff=0;
std::map<short,CRTNavMeshTerrain*>  Rebot::CRTNavMeshTerrainAll;
std::map<short, DWORD> Rebot::SkillStatus;
////std::map<DWORD32, bool> Rebot::SkillStatus;
std::vector<CIGIDObject*>  Rebot::InvalidObjects;
std::vector<CIGIDObject*>  Rebot::FirstObjects;
std::map<std::string, CSOItem> Rebot::ChatItemInfoList;
std::map<std::n_string, CSOItem> Rebot::CharInfoList1;
std::list<int> Rebot::Equipment_TID_List;
std::list<int> Rebot::Equipment_TID_Weapon_List;
std::list<int> Rebot::Equipment_TID_Accsessory_List;
std::list<int> Rebot::Equipment_TID_Heavy_List;
std::list<int> Rebot::Equipment_TID_Clothes_List;
std::list<int> Rebot::Equipment_TID_Light_List;
std::list<int> Rebot::Potion_ObjID_HP_Potion_List;
std::list<int> Rebot::Potion_ObjID_MP_Potion_List;
std::list<int> Rebot::Potion_ObjID_Vigor_Potion_List;
std::list<int> Rebot::Potion_ObjID_Universal_Pill_List;
std::list<int> Rebot::Potion_ObjID_Return_Scroll_List;
std::list<int> Rebot::Potion_ObjID_Coin_List;
std::list<int> Rebot::Speed_Scroll_ItemID;
std::list<int> Rebot::Potion_Pet_HP_Tid_List;
std::list<int> Rebot::Potion_Pet_HGP_Tid_List;
std::list<int> Rebot::Potion_Pet_Cure_List;
std::list<int> Rebot::Potion_Pet_Resurrect_List;
std::list<int> Rebot::Potion_Pet_Summon_Trigger_List;
Rebot::Rebot() {
    Rebot::Config.RebotRange = 100.0;
    Rebot::Config.FindStatus = 0;
    Rebot::Config.GoBackCentrer= false;
    Rebot::Config.AttackHostility=true;
    Rebot::Config.RequestJoinParty= true;
    Rebot::Config.AutoBerserk=false;
    Rebot::Config.AutoHP=false;
    Rebot::Config.AutoMP=false;
    Rebot::Config.AutoVigor=false;
    Rebot::Config.AutoPotion=false;
    Rebot::Config.AutoPetPotion=false;
    Rebot::Config.AutoSpeedScroll=false;
    Rebot::Config.AutoRidingPetHP=false;
    Rebot::Config.AutoTransPetHP=false;
    Rebot::Config.AutoAttackPetHP=false;
    Rebot::Config.AutoAttackPetHGP=false;
    Rebot::Config.AutoAttackPetCure=false;
    Rebot::Config.AutoAttackPetResurrect=false;
    Rebot::Config.AutoAttackPetPotion=false;

    Rebot::Config.LureMode=false;
    Rebot::Config.AutoBuffMode=false;
    Rebot::Config.AutoAttackSnowMan= true;
    Rebot::Config.AcceptRes=false;
    Rebot::Config.ResMember=false;
    Rebot::Config.OnlyResPartyMember=true;
    Rebot::Config.AutoResMember= false;
    Rebot::Config.AttackOtherPlayer= false;
    Rebot::Config.HpPercent = 0;
    Rebot::Config.MpPercent = 0;
    Rebot::Config.VigorPercent = 0;
    Rebot::Config.HpItemID=0;
    Rebot::Config.MpItemID = 0;
    Rebot::Config.VigorItemID = 0;
    Rebot::Config.AbnormalItemID = 0;
    Rebot::Config.SpeedItemID = 0;
    Rebot::Config.PetAttackHPtemID = 0;
    Rebot::Config.PetAttackHPGItemID = 0;
    Rebot::Config.PetAttackCureItemID = 0;
    Rebot::Config.PetAttackResurrectItemID = 0;
    Rebot::Config.PetAttackItemID = 0;

    Rebot::Config.x1 = 0;
    Rebot::Config.x2 = 0;
    Rebot::Config.y1 = 0;
    Rebot::Config.y2 = 0;
    Rebot::Config.cercle = -47;
    Rebot::Config.cercleX = 321;
    Rebot::Config.cercleY = 202;
    Rebot::Config.cercleRadius = 176;
    Rebot::Config.CircleShow = false;
    Rebot::Config.CircleGreenShow = false;

    Rebot::RebotStart=false;
    Rebot::SelectObj = 0;
    CreateThread(NULL, 0, Rebot::Main, NULL, 0, NULL);
    CreateThread(NULL, 0, Rebot::Main2, NULL, 0, NULL);
    CreateThread(NULL, 0, Rebot::Main3, NULL, 0, NULL);
    //CreateThread(NULL, 0, Rebot::Main4, NULL, 0, NULL);
   // CreateThread(NULL, 0, CNavigationDeadreckon::AutoMove, NULL, 0, NULL);
//    CreateThread(NULL, 0, KeyDown, NULL, 0, NULL);
}

int Rebot::get_pet_bytype( int types )
{
    int i = 0;
    int TempAddr = 0;
    byte Sign1 = 0, Sign2 = 0;
    int	PetEDX = 0, PetEBX = 0, PetEAX = 0;
    TempAddr = (DWORD32)g_pCICPlayer;
    TempAddr = *(DWORD32*)(TempAddr + 0x20D4);
    TempAddr = *(DWORD32*)(TempAddr + 0x08);
    PetEDX = *(DWORD32*)(TempAddr);
    //printf("PetEDX %p\n",PetEDX);
    PetEBX = *(DWORD32*)(PetEDX + 0x10);
    //printf("PetEDX %p\n",PetEBX);
    Sign1 = *(DWORD32*)(PetEBX + 0x14);
    while (Sign1 != types && i ++ < 5)
    {
        PetEAX = *(DWORD32*)(PetEDX + 0x08);
        Sign2 = *(BYTE *)(PetEAX + 0x15);
        if (Sign2 != 0)
        {
            PetEAX = *(DWORD32*)(PetEDX + 0x04);
        }
        PetEDX = PetEAX;
        PetEBX = *(DWORD32*)(PetEDX + 0x10);
        Sign1 = *(BYTE *)(PetEBX + 0x14);
    }
    if (types != Sign1)
    {
        return 0;
    }

    return PetEBX;
}
void Rebot::get_itemlist( int* plist )
{
    int nPos = 0;
    DWORD dwAddr = *(DWORD32*)(0x00EC4AE4);
    while (0 != dwAddr)
    {
        if (0x0C == (*(DWORD32*)(dwAddr + 0x1A0) & 0x0C))
        {
            plist[nPos] = *(DWORD32*)(dwAddr + 0x1C);
            nPos ++;
        }

        // next
        dwAddr = *(DWORD32*)(dwAddr + 0x0C);
    }
}
bool Rebot::get_iteminfo( ITEM_INFO& info, int id )
{
    DWORD dwItem = 0;
    DWORD dwAddr = *(DWORD32*)(0x00EC4AE4);
    while (0 != dwAddr)
    {
        if (id == *(DWORD32*)(dwAddr + 0x1C))
        {
            dwItem = dwAddr;
        }

        // next
        dwAddr = *(DWORD32*)(dwAddr + 0x0C);
    }

    if (0 != dwItem)
    {
        // info

        info.item_id   = *(DWORD32*)(dwItem + 0x1C);
        info.item_type = *(DWORD32*)(dwItem + 0x140);
        info.item_cls  = *(DWORD32*)(dwItem + 0x1A0);
        info.item_pickable = (0 == *(BYTE *)(dwItem + 0x178));
        return true;
    }

    return false;
}
void Rebot::SelectObject(DWORD32 ObjId) {
    if (ObjId == 0) {
        return;
    }
    NEWMSG(0x7045)
        pReq.Write(&ObjId, 4);
    SENDMSG()
}
void Rebot::InviteMember(DWORD32 ObjId) {
    if (ObjId == 0) {
        return;
    }
    byte Action = 0x5;
    NEWMSG(0x7060)
        pReq.Write(&ObjId, 4);
        pReq.Write(&Action, 1);
    SENDMSG()
}
DWORD32 Rebot::GetSkillIDByQuickIndex(int Index) {
    if(g_pCGInterface && g_pCGInterface != 0 )
    {
        if(g_pCGInterface->GetUnderMenuBar())
        {
            if(g_pCGInterface->GetUnderMenuBar()->m_slots[Index] && g_pCGInterface->GetUnderMenuBar()->m_slots[Index] != 0)
            {
                if(g_pCGInterface->GetUnderMenuBar()->m_slots[Index]->m_main_slot->Type == 12 && g_pCGInterface->GetUnderMenuBar()->m_slots[Index]->m_main_slot->SlotType == 73)
                    return  g_pCGInterface->GetUnderMenuBar()->m_slots[Index]->m_main_slot->m_SkillID;
                else
                    return 0;
            }
            else
                return 0;
        }
        else
            return 0;
    }
    else
        return 0;


}
DWORD32 Rebot::GetSkillCoolDown(DWORD32 SkillID) {
   // printf("GetSkillCoolDown start\r\n");
    DWORD32 dwListBase = *(DWORD32*)GetSkillCDListBase();
    DWORD32 Base = dwListBase;
    while (1)
    {
        Base=*(DWORD32*)Base;
        if (Base == 0)
            return 0;
        if (Base == dwListBase)
            return 0;
        if (SkillID == *(DWORD32*)(Base + 0x8)) {
            return  *(DWORD32*)(Base + 0x14);
        }
    }
   // printf("GetSkillCoolDown end\r\n");
    return 0;
}
boolean Rebot::TargetIsBuffInUse(DWORD32 SkillID, DWORD32 Target) {
    DWORD32 dwListBase = GetBuffListBase(Target);
    if(dwListBase != 0)
    {
        DWORD32 Base = dwListBase;
        while (1)
        {
            Base = *(DWORD32*)(Base);
            if (Base == 0)
                return false;
            if (Base == dwListBase)
                return false;
            if (SkillID == *(DWORD32*)(*(DWORD32*)(Base + 0x8) + 0x5C)) {
                return true;
            }
        }
    }
    return false;
}
boolean Rebot::TargetIsBuffInUse2(DWORD32 SkillID, DWORD32 Target) {
    DWORD32 dwListBase = GetBuffListBase(Target);
    if(dwListBase != 0)
    {
        DWORD32 Base = dwListBase;
        while (1)
        {
            Base = *(DWORD32*)(Base);
            if (Base == 0)
                return false;
            if (Base == dwListBase)
                return false;
            if (SkillID == *(DWORD32*)(*(DWORD32*)(Base + 0x8) + 0x5C)) {
                return true;
            }
        }
    }
    return false;
}
DWORD32 Rebot::GetBuffListBase(DWORD32 Addr) {
    if(g_pCICPlayer)
        return *(DWORD32*)(Addr + 0x288);
    else
        return 0;
}
DWORD32 Rebot::GetSkillCDListBase() {
   // printf("GetSkillCDListBaseCD start :%X\r\n", *(DWORD32*)(((DWORD32)g_pCGInterface) + 0x778) + 0xC);
    return *(DWORD32*)(((DWORD32)g_pCGInterface)+0x778)+0xC;
}
boolean Rebot::CastSpell(DWORD32 SkillID, DWORD32 Target=0) {
    if (SkillID == 0)
        return false;

    NEWMSG(0x7074)
        if (Target == 0) {
            pReq << (byte)1;
            pReq << (byte)4;
            pReq << (WORD)SkillID;
            pReq << (byte)0;
            pReq << (WORD)0;
        }
        else {

            pReq << (byte)1;
            pReq << (byte)4;
            pReq << (WORD)SkillID;
            pReq << (WORD)0;
            pReq << (byte)1;
            pReq << Target;
        }
    SENDMSG()
    return true;
}
float Rebot::Distance(D3DVECTOR startAirportPos, D3DVECTOR endAirportPos)
{
    float dis = sqrt(pow(startAirportPos.x - endAirportPos.x, 2) + pow(startAirportPos.y - endAirportPos.y, 2) + pow(startAirportPos.z - endAirportPos.z, 2));
    return fabs(dis);
}
CIObject* Rebot::GetNearPartyMemberToBuff(short SkillID){

    CIObject *TempObj = 0;

    std::map<int, CIObject*> entities = g_pGfxEttManager->entities;
    for (std::map<int, CIObject*>::iterator it = entities.begin();
         it != entities.end(); ++it) {
        if (!strcmp(it->second->GetRuntimeClass()->m_lpszClassName, "CICUser")) {
//            int HP = ((CICharactor*)it->second)->HP;
//            int MAXHP = ((CICharactor*)it->second)->MAXHP;
            short Status = ((CICharactor*)it->second)->Status;//0x2 or 0x18
            if (std::count(Rebot::InvalidObjects.begin(), Rebot::InvalidObjects.end(), it->second)) {
                continue;
            }

            if (((CICharactor*)it->second)->GetUniqueID() == 0 || Status == 0x2||  Status == 0x18|| ObjIntersect(g_pCICPlayer, it->second)) {
                continue;
            }
            D3DVECTOR TagLocation = it->second->GetLocation();
            GetSilkPos(it->second->GetRegion(), TagLocation);
            //if the distance between starting pos , monster greater than range , just ignore it
            if (Rebot::Distance(TagLocation, GetSilkPosD3D(Rebot::Config.StartRegion, Rebot::Config.StartPos)) > Rebot::Config.RebotRange) {
                continue;
            }
            if(SkillID>0)
            {
                if (Rebot::TargetIsBuffInUse(SkillID, (DWORD32)it->second))
                {
                    continue;
                }
            }
            if (!strcmp(it->second->GetRuntimeClass()->m_lpszClassName, "CICUser")) {
                {
                        TempObj = it->second;
                }
            }
        }
    }
    return TempObj;
}
CIObject* Rebot::GetNearPartyMember(){

    CIObject *TempObj = 0;

    std::map<int, CIObject*> entities = g_pGfxEttManager->entities;
    for (std::map<int, CIObject*>::iterator it = entities.begin();
         it != entities.end(); ++it) {
        if (!strcmp(it->second->GetRuntimeClass()->m_lpszClassName, "CICUser")) {
            short Status = ((CICharactor*)it->second)->Status;//0x2 or 0x18
            //if (std::count(Rebot::InvalidObjects.begin(), Rebot::InvalidObjects.end(), it->second)) {
            //    continue;
            //}

            if (((CICharactor*)it->second)->GetUniqueID() == 0 || Status == 0x18 || Status != 0x2||  ObjIntersect(g_pCICPlayer, it->second)) {
                continue;
            }
            D3DVECTOR TagLocation = it->second->GetLocation();
            GetSilkPos(it->second->GetRegion(), TagLocation);
            //if the distance between starting pos , monster greater than range , just ignore it
            if (Rebot::Distance(TagLocation, GetSilkPosD3D(Rebot::Config.StartRegion, Rebot::Config.StartPos)) > Rebot::Config.RebotRange) {
                continue;
            }
            if (!strcmp(it->second->GetRuntimeClass()->m_lpszClassName, "CICUser")) {
                if (((CICharactor*)it->second)->Status == 2) {
                    const SPartyData &partyData = g_CCharacterDependentData.GetPartyData();
                    for (size_t i = 0; i < partyData.NumberOfMembers; ++i)
                    {
                        const SPartyMemberData &memberData = g_CCharacterDependentData.GetPartyMemberData(i);
                        if (wcscmp(memberData.m_charactername.c_str(), ((CICharactor*)it->second)->GetName().c_str()) == 0)
                        {
                            TempObj = it->second;
                        }
                        else continue;
                    }
                }
                else continue;
            }
        }
    }
    return TempObj;
}
CIObject* Rebot::GetNearestObj(){

    CIObject *TempObj = 0;

    std::map<int, CIObject*> entities = g_pGfxEttManager->entities;
    for (std::map<int, CIObject*>::iterator it = entities.begin();
         it != entities.end(); ++it) {
        if (!strcmp(it->second->GetRuntimeClass()->m_lpszClassName, "CICMonster")||
            !strcmp(it->second->GetRuntimeClass()->m_lpszClassName, "CICUser")) {
//            int HP = ((CICharactor*)it->second)->HP;
//            int MAXHP = ((CICharactor*)it->second)->MAXHP;
            short Status = ((CICharactor*)it->second)->Status;//0x2 or 0x18

//            wchar_t* HPT = new wchar_t[100];
//            wsprintfW(HPT, L"<%d/%d>", HP, MAXHP);
//            ((CICharactor*)it->second)->ShowMessageAboveEntity(HPT,0xFFFFFF);

            short Level = *(short*)((DWORD32)it->second + 0x7AC);//0 Normal 1 = champion 3 rare 4 Giant
            if (std::count(Rebot::InvalidObjects.begin(), Rebot::InvalidObjects.end(), it->second)) {
                continue;
            }

            if (((CICharactor*)it->second)->GetUniqueID() == 0 || Status == 0x18 || Status == 2|| ObjIntersect(g_pCICPlayer, it->second)) {
                continue;
            }

            D3DVECTOR TagLocation = it->second->GetLocation();
            GetSilkPos(it->second->GetRegion(), TagLocation);
            //if the distance between starting pos , monster greater than range , just ignore it
            if (Rebot::Distance(TagLocation, GetSilkPosD3D(Rebot::Config.StartRegion, Rebot::Config.StartPos)) > Rebot::Config.RebotRange) {
                continue;
            }
            if(Rebot::Config.AutoAttackSnowMan)
            {
                int mobID = *(int *) ((int) (it->second) + 0x21C);
               if(mobID == 28811 || mobID >= 36034 && mobID <= 36054)
                   continue;
            }
            if(Rebot::Config.LureMode)
            {
                short Statuss = ((CICMonster*)it->second)->Status;//0x2 or 0x18
                if (((CICMonster*)it->second)->GetUniqueID() == 0 || Statuss == 269 || Statuss == 0x2313 || Statuss == 0x2317) {
                    TempObj=0;
                    continue;
                }
                if (Rebot::Distance(TagLocation, GetSilkPosD3D(Rebot::Config.StartRegion, Rebot::Config.StartPos)) < 70) {
                    continue;
                }
            }
            if(Rebot::Config.AttackHostility)
            {
               if(Level == 3)
                   TempObj = it->second;
               else if (Level == 4)
                   TempObj = it->second;
            }
            if (TempObj == 0) {
                if (!strcmp(it->second->GetRuntimeClass()->m_lpszClassName, "CICUser")) {
                    if ((((CICharactor*)it->second)->GetNameColor() == 0xFFFF58FE || ((CICharactor*)it->second)->GetNameColor() == 0xFFFF6262) && Rebot::Config.AttackOtherPlayer ) {
                        TempObj = it->second;
                    }
                    else {
                        continue;
                    }

                }
                TempObj = it->second;
            }

            D3DVECTOR MyLocation = g_pCICPlayer->GetLocation();
            D3DVECTOR SelectLocation = TempObj->GetLocation();
            GetSilkPos(TempObj->GetRegion(), SelectLocation);

            double TagDis = Rebot::Distance(MyLocation, TagLocation);
            double SelectDis = Rebot::Distance(MyLocation, SelectLocation);
            //give attacking priority type ?
            if ((((CICharactor*)it->second)->GetNameColor() == 0xFFFF58EE || ((CICharactor*)it->second)->GetNameColor() == 0xFFFF6262) && TagDis < 500 && Rebot::Config.AttackOtherPlayer) {
                //normal player
                TempObj = it->second;
            }else if (Level != 0 && Level != 1 && TagDis<500&& !strcmp(it->second->GetRuntimeClass()->m_lpszClassName, "CICMonster")) {
                TempObj = it->second;

            }else if (TagDis < SelectDis&& !strcmp(it->second->GetRuntimeClass()->m_lpszClassName, "CICMonster")) {
                TempObj=it->second;
            }
        }
    }
    return TempObj;
}
CICharactor* Rebot::FindBaseByUID(DWORD32 ObjectId) {
    return GetCharacterObjectByID_MAYBE(ObjectId);
}
DWORD32 Rebot::GetListBase() {
    DWORD32 addr = 0;
    addr = (DWORD32)g_pCGInterface;
    addr = *(DWORD32*)(addr + 0x36C + 0x4); //370
    addr = *(DWORD32*)(addr + 0x4);
    addr = *(DWORD32*)(addr);
    addr = *(DWORD32*)(addr + 0x8);
    addr = *(DWORD32*)(addr + 0x8);
    addr = *(DWORD32*)(addr + 0x10);
    printf("%d",addr);
    return addr;
}
void Rebot::UseBerSerk() {

    NEWMSG(0x70A7)
        pReq << (byte)1;
    SENDMSG()
}
void Rebot::GetSkillList() {

    DWORD32 addr = GetListBase();
    addr = *(DWORD32*)(addr + 0x7C4);
    addr = addr + 0x36C+0xC; //=0x37c
    addr = *(DWORD32*)(addr + 0x4);
    SkillBaseHead = addr;
    addr = *(DWORD32*)(addr);
    GetSkillInfo(addr,0);
}
CSOItem* Rebot::GetBackpackItem(int index) {
    DWORD32 addr = GetListBase();;
    addr = *(DWORD32*)(addr + 0x7BC);
    addr = *(DWORD32*)(addr + 0x3A0);
    return (CSOItem*)*(DWORD32*)(addr+index*4);
}

CSOItem* Rebot::GetEquipmentItem(int index) {
    DWORD32 addr = GetListBase();;
    addr = *(DWORD32*)(addr + 0x7C0);
    addr = addr + 0xF10;
    return (CSOItem*)(addr+index*0x1D0);
}

void Rebot::GetSkillInfo(DWORD32 Base, DWORD32 ParentBase) {
    DWORD32 BaseAddr=  *(DWORD32*)(Base+0x10);
    int SkillID = *(DWORD32*)(BaseAddr);
    if (SkillID != 0) {
        //0x6C Preparation time 0x70 Action time
        DWORD32 DescriptAddr = *(DWORD32*)(BaseAddr + 8)+0x774;
        const std::n_wstring* name= g_CTextStringManager->GetString((const wchar_t*)*(DWORD32*)(DescriptAddr + 0x128));
        HaveSkill[SkillID] = new Skill;
        HaveSkill[SkillID]->SkillName = acp_n_encode(name);
        HaveSkill[SkillID]->TargetRequired = *(BYTE*)(DescriptAddr + 0x98);
        HaveSkill[SkillID]->Param1 = *(int*)(DescriptAddr + 0x1B0);
        HaveSkill[SkillID]->Param8 = *(int*)(DescriptAddr + 0x194);
/*
        printf("SkillName:%s\r\n", acp_n_encode(name).c_str());
        printf("Descriptionadd:%p\r\n", DescriptAddr);
        printf("TargetRequired:%d\r\n", *(BYTE*)(DescriptAddr + 0x98));
        printf("Param1:%d\r\n", *(DWORD32*)(DescriptAddr + 0x1B0));
        printf("Param8:%d\r\n", *(DWORD32*)(DescriptAddr + 0x194));*/
    }
    DWORD32 N1 = *(DWORD32*)(Base + 0x0);
    DWORD32 N2 = *(DWORD32*)(Base + 0x4);
    DWORD32 N3 = *(DWORD32*)(Base + 0x8);
    if (N1!= SkillBaseHead && N1!=0 && N1!=ParentBase) {
        GetSkillInfo(N1,Base);
    }
    if (N2 != SkillBaseHead && N2 != 0 && N2 != ParentBase) {
        GetSkillInfo(N2, Base);
    }
    if (N3 != SkillBaseHead && N3 != 0 && N3 != ParentBase) {
        GetSkillInfo(N3, Base);
    }

}
D3DVECTOR Rebot::GetPatrolPos() {


    D3DVECTOR CenterLocation = Config.StartPos;
    //printf("xxxx0 %f,%f,%f\r\n", CenterLocation.x, CenterLocation.y, CenterLocation.z);
    SilkPosToSimplePos(Config.StartPos, Config.StartRegion);
    //printf("xxxx1 %f,%f,%f\r\n", CenterLocation.x, CenterLocation.y, CenterLocation.z);
    FPatrolDestIndex++;
    if (FPatrolDestIndex > 3) {
        FPatrolDestIndex = 0;
    }
    int angle = FPatrolDestIndex * 90;
    if (false) {
        //À­¹Ö×ø±êµã ÔÝÊ±Î´Ð´
    }
    else {
        //Ñ°¹Ö×ø±êµã
        CenterLocation.x = ceil(cos((angle) * (3.1415926 / 180)) * (Config.RebotRange) + CenterLocation.x);
        CenterLocation.z = ceil(sin((angle) * (3.1415926 / 180)) * (Config.RebotRange) + CenterLocation.z);
        //printf("xxxx2 %f,%f,%f\r\n", CenterLocation.x, CenterLocation.y, CenterLocation.z);
        return CenterLocation;
    }

}
////////////////UI

void Rebot::Render() {
    try
    {

        if (!g_pCICPlayer)
            return;
        if (ImGui::BeginTabBar("", ImGuiTabBarFlags_None))
        {
            if (ImGui::BeginTabItem("Menu"))
            {

                ImGui::SameLine();

                ImGui::PushItemWidth(400);
                ImGui::SliderFloat("1", &Rebot::Config.x1, -1000.0f, 1000.0f, "x1 = %.2f");
                ImGui::Separator();
                ImGui::SliderFloat("2", &Rebot::Config.x2, -1000.0f, 1000.0f, "x2 = %.2f");
                ImGui::Separator();
                ImGui::SliderFloat("3", &Rebot::Config.y1, -1000.0f, 1000.0f, "y1 = %.2f");
                ImGui::Separator();
                ImGui::SliderFloat("4", &Rebot::Config.y2, -1000.0f, 1000.0f, "y2 = %.2f");
                ImGui::Separator();
                ImGui::SliderFloat("5", &Rebot::Config.cercle, -1000.0f, 1000.0f, "cercle = %.2f");
                ImGui::Separator();
                ImGui::SliderFloat("6", &Rebot::Config.cercleX, -1000.0f, 1000.0f, "cercleX = %.2f");
                ImGui::Separator();
                ImGui::SliderFloat("7", &Rebot::Config.cercleY, -1000.0f, 1000.0f, "cercleY = %.2f");
                ImGui::Separator();
                ImGui::SliderFloat("8", &Rebot::Config.cercleRadius, -1000.0f, 1000.0f, "cercleRadius = %.2f");
                ImGui::Separator();
                ImGui::EndTabItem();
            }


            ImGui::EndTabBar();
        }
        ImGui::End();


    }
    catch (const std::exception&)
    {
        SelectObj = 0;
    }

}

void Rebot::HunterRandRun( float fBotX, float fBotY, int nRound )
{
    GUID guid;
    int newX = (int)fBotX;
    int newY = (int)fBotY;
    CoCreateGuid(&guid);

    if (0 == nRound)
    {
        nRound = 10;
    }
    if (guid.Data4[0] % 2)
    {
        newX += guid.Data2 % nRound;
    }
    else
    {
        newX -= guid.Data2 % nRound;
    }
    if (guid.Data4[1] % 2)
    {
        newY += guid.Data3 % nRound;
    }
    else
    {
        newY -= guid.Data3 % nRound;
    }

    HunterWalk(newX, newY);
}
void Rebot::HunterWalk( int x, int y )
{
    NEWMSG(0x7021)
        pReq << (byte)1;
        pReq << (short)(-32752);
        pReq << (int)(x);
        pReq << (int)(57.5);
        pReq << (int)(y);
    SENDMSG()
   // printf("mx %d ,my %d, x %d,y %d,z %d\r\n",mx,my, xx, 0, yy);

}
void WalkTo(long X, long Y, short Z)
{
    long xPos = 0;
    long yPos = 0;

    if (X > 0 && Y > 0)
    {
        xPos = (X % 192) * 10;
        yPos = (Y % 192) * 10;
    }
    else if (X < 0 && Y < 0)
    {
        xPos = (192 + (X % 192)) * 10;
        yPos = (192 + (Y % 192)) * 10;
    }
    else if (X < 0 && Y > 0)
    {
        xPos = (192 + (X % 192)) * 10;
        yPos = (Y % 192) * 10;
    }
    else if (X > 0 && Y < 0)
    {
        xPos = (X % 192) * 10;
        yPos = (192 + (Y % 192)) * 10;
    }

    byte xSector = (byte)((X - xPos / 10) / 192 + 135);
    byte ySector = (byte)((Y - yPos / 10) / 192 + 92);

    xPos = (X - ((xSector - 0x87) * 0xC0)) * 0x0A;
    yPos = (Y - ((ySector - 0x5C) * 0xC0)) * 0x0A;

    NEWMSG(0x7021)
    if (xSector == 1)
    {
        ySector++;

        //Recalculate X, Y coordinates
        xPos = (X - ((xSector - 0x87) * 0xC0)) * 0x0A;
        yPos = (Y - ((ySector - 0x5C) * 0xC0)) * 0x0A;

        pReq << (byte)1;

        pReq << (byte)1;
        pReq << (byte)(128);
        pReq << (short)(xPos);
        pReq << (short)(Z);
        pReq << (short)(yPos);

    }
    else
    {
        pReq << (byte)1;
        pReq << (byte)(xSector);
        pReq << (byte)(ySector);
        pReq << (short)(xPos);
        pReq << (short)(Z);
        pReq << (short)(yPos);

    }

    SENDMSG()
}
time_t LastSendTimePetPotion;
time_t LastSendTimePetTradePotion;
time_t LastSendTimePetRidingPotion;

time_t lastClickTime2;
time_t lastClickTime3;
time_t lastClickTime6;
time_t lastClickTime8;

time_t lastClickTime10;
time_t lastClickTime11;
time_t lastClickTime12;
time_t lastClickTime13;
time_t lastClickTime14;
void Rebot::AutoPotionAndItem()
{
    if(g_pCICPlayer)
    {

        if(Rebot::Config.AutoBerserk && g_pCICPlayer->m_zerkPoint==5 && g_pCICPlayer && Rebot::RebotStart)
        {
            if((time(NULL) - lastClickTime2 > 1)) {

                NEWMSG(0x70A7)
                    pReq << (byte)1;
                SENDMSG()
                lastClickTime2 = time(NULL);
            }
        }

/*        if(Rebot::Config.AutoAttackPetResurrect && Rebot::Config.PetAttackResurrectItemID != 0 && Rebot::Config.PetAttackItemID > 0 && Rebot::Config.AutoPetPotion)
        {
            CIFSlotWithHelp* pSlot;
            CIFInventory* pInventory = g_pCGInterface->GetMainPopup()->GetInventory();
            BYTE PetDiedSlot;
            for (int i = 0; i <  g_pCICPlayer->m_inventorySize; i++)
            {
                pSlot = *reinterpret_cast<CIFSlotWithHelp**>(pInventory->pSlots + (i * 4));
                if(pSlot->ItemInfo)
                {
                    *//*if ( pSlot->ItemInfo->GetItemData()->m_id == Rebot::Config.PetAttackItemID && pSlot->ItemInfo->m_petStatus == 4)
                    {
                        PetDiedSlot = pSlot->UniqueID()- 100 + 0xD;
                        if((time(NULL) - lastClickTime3 > 1)) {
                            CMsgStreamBuffer buf(0x704C);
                            buf << (byte)(CIFflorian0Guide::CIFSTMacroAutoHuntGUI->PET_RESURRECT_SLOT+ 0xD);
                            buf << (UINT16)(0x30ec) ;
                            buf << (byte)(PetDiedSlot) ;
                            SendMsg(buf);
                            lastClickTime6 = time(NULL);
                        }
                        break;
                    }
                    if ( pSlot->ItemInfo->GetItemData()->m_id == Rebot::Config.PetAttackItemID && pSlot->ItemInfo->m_petStatus == 3 && !Rebot::get_pet_bytype(3))
                    {
                        PetDiedSlot = pSlot->UniqueID()- 100 + 0xD;
                        if((time(NULL) - lastClickTime3 > 3)) {
                            CMsgStreamBuffer buf2(0x704C);
                            buf2 << (byte)(PetDiedSlot);
                            buf2 << (UINT16)(pSlot->ItemInfo->GetItemData()->TID) ;
                            SendMsg(buf2);
                            lastClickTime6 = time(NULL);
                        }
                        break;
                    }*//*
                    break;
                }
            }
        }*/
    }

    if(Rebot::Config.AutoHP && Rebot::Config.AutoPotion &&  Rebot::Config.HpItemID != 0 &&  ((((float)g_pCICPlayer->m_hpCurrent/(float)g_pCICPlayer->m_hpMax) * 100) < Rebot::Config.HpPercent)  && g_pCICPlayer  && g_pCICPlayer->Status !=2)
    {
        CIFSlotWithHelp* pSlot;
        CIFInventory* pInventory = g_pCGInterface->GetMainPopup()->GetInventory();
        if(pInventory)
        {
            for (int i = 0; i <  g_pCICPlayer->m_inventorySize; i++)
            {
                pSlot = *reinterpret_cast<CIFSlotWithHelp**>(pInventory->pSlots + (i * 4));
                if(pSlot->ItemInfo && pSlot)
                {
                    if ( pSlot->ItemInfo->GetItemData()->m_id == Rebot::Config.HpItemID)
                    {
                        if((time(NULL) - lastClickTime11 > 0.5)) {

                            CMsgStreamBuffer buf(0x704C);
                            buf << (byte)(pSlot->UniqueID()- 100 + 0xD);
                            buf << (UINT16)(pSlot->ItemInfo->GetItemData()->TID) ;
                            SendMsg(buf);
                            lastClickTime11 = time(NULL);
                        }
                        break;
                    }
                }
            }
        }

    }
    if(Rebot::Config.AutoMP && Rebot::Config.AutoPotion &&  Rebot::Config.MpItemID != 0 && ((((float)g_pCICPlayer->m_mpCurrent/(float)g_pCICPlayer->m_mpMax) * 100) < Rebot::Config.MpPercent)  && g_pCICPlayer && g_pCICPlayer->Status !=2)
    {
        CIFSlotWithHelp* pSlot;
        CIFInventory* pInventory = g_pCGInterface->GetMainPopup()->GetInventory();
        if(pInventory)
        {
            for (int i = 0; i < g_pCICPlayer->m_inventorySize; i++)
            {
                pSlot = *reinterpret_cast<CIFSlotWithHelp**>(pInventory->pSlots + (i * 4));
                if(pSlot->ItemInfo && pSlot)
                {
                    if ( pSlot->ItemInfo->GetItemData()->m_id == Rebot::Config.MpItemID)
                    {
                        if((time(NULL) - lastClickTime12 > 0.5)) {

                            CMsgStreamBuffer buf(0x704C);
                            buf << (byte)(pSlot->UniqueID()- 100 + 0xD);
                            buf << (UINT16)(pSlot->ItemInfo->GetItemData()->TID) ;
                            SendMsg(buf);
                            lastClickTime12 = time(NULL);
                        }
                        break;
                    }
                }
            }
        }

    }
    if(Rebot::Config.AutoAbnormal && Rebot::Config.AutoPotion &&  Rebot::Config.AbnormalItemID != 0 && 0 < g_pCICPlayer->m_illness && g_pCICPlayer->m_illness < 0x7FFFFFFF  && g_pCICPlayer && g_pCICPlayer->Status !=2)
    {
        CIFSlotWithHelp* pSlot;
        CIFInventory* pInventory = g_pCGInterface->GetMainPopup()->GetInventory();
        if(pInventory)
        {
            for (int i = 0; i < g_pCICPlayer->m_inventorySize; i++)
            {
                pSlot = *reinterpret_cast<CIFSlotWithHelp**>(pInventory->pSlots + (i * 4));
                if(pSlot->ItemInfo && pSlot)
                {
                    if ( pSlot->ItemInfo->GetItemData()->m_id == Rebot::Config.AbnormalItemID)
                    {
                        if((time(NULL) - lastClickTime13 > 0.5)) {

                            CMsgStreamBuffer buf(0x704C);
                            buf << (byte)(pSlot->UniqueID()- 100 + 0xD);
                            buf << (UINT16)(pSlot->ItemInfo->GetItemData()->TID) ;
                            SendMsg(buf);
                            lastClickTime13 = time(NULL);
                        }
                        break;
                    }
                }
            }
        }

    }
    if(Rebot::Config.AutoSpeedScroll && Rebot::Config.AutoPotion &&  Rebot::Config.SpeedItemID != 0 && (int)g_pCICPlayer->field_0x670 <= 60 && g_pCICPlayer && g_pCICPlayer->Status !=2)
    {
        CIFSlotWithHelp* pSlot;
        CIFInventory* pInventory = g_pCGInterface->GetMainPopup()->GetInventory();
        if(pInventory)
        {
            for (int i = 0; i < g_pCICPlayer->m_inventorySize; i++)
            {
                pSlot = *reinterpret_cast<CIFSlotWithHelp**>(pInventory->pSlots + (i * 4));
                if(pSlot->ItemInfo && pSlot)
                {
                    if ( pSlot->ItemInfo->GetItemData()->m_id == Rebot::Config.SpeedItemID)
                    {
                        if((time(NULL) - lastClickTime3 > 0.5)) {

                            CMsgStreamBuffer buf(0x704C);
                            buf << (byte)(pSlot->UniqueID()- 100 + 0xD);
                            buf << (UINT16)(pSlot->ItemInfo->GetItemData()->TID) ;
                            SendMsg(buf);
                            lastClickTime3 = time(NULL);
                        }
                        break;
                    }
                }
            }
        }

    }

    if((Rebot::Config.AutoVigor && Rebot::Config.AutoPotion && Rebot::Config.VigorItemID != 0 &&  ((((float)g_pCICPlayer->m_hpCurrent/(float)g_pCICPlayer->m_hpMax) * 100) < Rebot::Config.VigorPercent)  && g_pCICPlayer  && g_pCICPlayer->Status !=2)
       ||(Rebot::Config.AutoVigor && Rebot::Config.AutoPotion && Rebot::Config.VigorItemID != 0 &&  ((((float)g_pCICPlayer->m_mpCurrent/(float)g_pCICPlayer->m_mpMax) * 100) < Rebot::Config.VigorPercent)  && g_pCICPlayer  && g_pCICPlayer->Status !=2))
    {
        CIFSlotWithHelp* pSlot;
        CIFInventory* pInventory = g_pCGInterface->GetMainPopup()->GetInventory();
        if(pInventory)
        {
            for (int i = 0; i < g_pCICPlayer->m_inventorySize; i++)
            {
                pSlot = *reinterpret_cast<CIFSlotWithHelp**>(pInventory->pSlots + (i * 4));
                if(pSlot->ItemInfo && pSlot)
                {
                    if ( pSlot->ItemInfo->GetItemData()->m_id == Rebot::Config.VigorItemID)
                    {
                        if((time(NULL) - lastClickTime6 > 0.5)) {

                            CMsgStreamBuffer buf(0x704C);
                            buf << (byte)(pSlot->UniqueID()- 100 + 0xD);
                            buf << (UINT16)(pSlot->ItemInfo->GetItemData()->TID) ;
                            SendMsg(buf);
                            lastClickTime6 = time(NULL);
                        }
                        break;
                    }
                }
            }
        }

    }
/////////////////
    if(g_pCGInterface->GetExtraFeatureGUI()->SetAutoRessurect  && g_pCICPlayer && g_pCICPlayer->Status==2)
    {
        if((time(NULL) - lastClickTime10 > 7)) {
            g_pCGInterface->GetCIFSTEffectGUI()->SetRessuretTime(5);
            lastClickTime10 = time(NULL);
        }
    }
    if(g_pCGInterface->GetExtraFeatureGUI()->SetAutoBerserkerPotion  && g_pCICPlayer && g_pCICPlayer->m_zerkPoint < 5)
    {
        CIFSlotWithHelp* pSlot;
        CIFInventory* pInventory = g_pCGInterface->GetMainPopup()->GetInventory();
        if(pInventory)
        {
            for (int i = 0; i < g_pCICPlayer->m_inventorySize; i++)
            {
                pSlot = *reinterpret_cast<CIFSlotWithHelp**>(pInventory->pSlots + (i * 4));
                if(pSlot->ItemInfo && pSlot->ItemInfo != 0  && pSlot)
                {
                    if ( pSlot->ItemInfo->GetObjectData()->TID == 16620)
                    {
                        if(pSlot->ItemInfo->m_quantity == 1)
                        {
                            g_pCGInterface->GetExtraFeatureGUI()->m_slot6->FUN_006871d0(0);
                            g_pCGInterface->GetExtraFeatureGUI()->m_slot6->TB_Func_13("", 1, 1);
                            g_pCGInterface->GetExtraFeatureGUI()->SetAutoBerserkerPotion = false;
                            g_pCGInterface->GetExtraFeatureGUI()->m_btn8->SetText(TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP12"));
                        }
                        else
                        {
                            g_pCGInterface->GetExtraFeatureGUI()-> m_berserker_potion_slot = pSlot->UniqueID()- 100 + 0xD;

                            if((time(NULL) - lastClickTime14 > 3)) {
                                CMsgStreamBuffer buf(0x704C);
                                buf << (byte)g_pCGInterface->GetExtraFeatureGUI()-> m_berserker_potion_slot;
                                buf << pSlot->ItemInfo->GetObjectData()->TID ;
                                SendMsg(buf);
                                lastClickTime14 = time(NULL);
                            }
                            break;
                        }

                    }
                }

            }
        }

    }
    if(g_pCGInterface->GetExtraFeatureGUI()->SetAutoABS && !Rebot::TargetIsBuffInUse2(3110,(DWORD32)g_pCICPlayer) && g_pCICPlayer && g_pCICPlayer->Status != 2)
    {
        CIFSlotWithHelp* pSlot;
        CIFInventory* pInventory = g_pCGInterface->GetMainPopup()->GetInventory();
        if(pInventory)
        {
            for (int i = 0; i < g_pCICPlayer->m_inventorySize; i++)
            {
                pSlot = *reinterpret_cast<CIFSlotWithHelp**>(pInventory->pSlots + (i * 4));
                if(pSlot->ItemInfo && pSlot->ItemInfo != 0  && pSlot)
                {
                    if ( pSlot->ItemInfo->GetObjectData()->ObjID == 3768)
                    {
                        if(pSlot->ItemInfo->m_quantity == 1)
                        {
                            g_pCGInterface->GetExtraFeatureGUI()->m_slot1->FUN_006871d0(0);
                            g_pCGInterface->GetExtraFeatureGUI()->m_slot1->TB_Func_13("", 1, 1);
                            g_pCGInterface->GetExtraFeatureGUI()->SetAutoABS = false;
                            g_pCGInterface->GetExtraFeatureGUI()->m_btn1->SetText(TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP12"));
                        }
                        else
                        {
                            g_pCGInterface->GetExtraFeatureGUI()-> m_dame_abs_slot = pSlot->UniqueID()- 100 + 0xD;
                            if((time(NULL) - lastClickTime8 > 3)) {
                                CMsgStreamBuffer buf(0x704C);
                                buf << (byte)g_pCGInterface->GetExtraFeatureGUI()-> m_dame_abs_slot;
                                buf << (UINT16)0x0EED ;
                                SendMsg(buf);
                                lastClickTime8 = time(NULL);
                            }
                            break;
                        }

                    }
                }

            }
        }

    }
    if(g_pCGInterface->GetExtraFeatureGUI()->SetAutoINC  && !Rebot::TargetIsBuffInUse2(3109,(DWORD32)g_pCICPlayer) && g_pCICPlayer && g_pCICPlayer->Status != 2)
    {
        CIFSlotWithHelp* pSlot;
        CIFInventory* pInventory = g_pCGInterface->GetMainPopup()->GetInventory();
        if(pInventory)
        {
            for (int i = 0; i < g_pCICPlayer->m_inventorySize; i++)
            {
                pSlot = *reinterpret_cast<CIFSlotWithHelp**>(pInventory->pSlots + (i * 4));
                if(pSlot->ItemInfo && pSlot->ItemInfo != 0  && pSlot)
                {
                    if ( pSlot->ItemInfo->GetObjectData()->ObjID == 3767)
                    {
                        if(pSlot->ItemInfo->m_quantity == 1)
                        {
                            g_pCGInterface->GetExtraFeatureGUI()->m_slot2->FUN_006871d0(0);
                            g_pCGInterface->GetExtraFeatureGUI()->m_slot2->TB_Func_13("", 1, 1);
                            g_pCGInterface->GetExtraFeatureGUI()->SetAutoINC = false;
                            g_pCGInterface->GetExtraFeatureGUI()->m_btn2->SetText(TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP12"));
                        }
                        else
                        {
                            g_pCGInterface->GetExtraFeatureGUI()-> m_dame_inc_slot = pSlot->UniqueID()- 100 + 0xD;

                            if((time(NULL) - lastClickTime8 > 4)) {
                                CMsgStreamBuffer buf(0x704C);
                                buf << (byte)g_pCGInterface->GetExtraFeatureGUI()-> m_dame_inc_slot;
                                buf << (UINT16)0x0EED ;
                                SendMsg(buf);
                                lastClickTime8 = time(NULL);
                            }
                            break;
                        }
                    }
                }

            }
        }

    }

    if(g_pCGInterface->GetExtraFeatureGUI()->SetAutoABSbubble && g_pCICPlayer  && g_pCICPlayer->Status != 2 && !Rebot::TargetIsBuffInUse2(31154,(DWORD32)g_pCICPlayer )
       && !Rebot::TargetIsBuffInUse2(31166,(DWORD32)g_pCICPlayer) && !Rebot::TargetIsBuffInUse2(31170,(DWORD32)g_pCICPlayer)
       && !Rebot::TargetIsBuffInUse2(31158,(DWORD32)g_pCICPlayer) && !Rebot::TargetIsBuffInUse2(31162,(DWORD32)g_pCICPlayer)
       && !Rebot::TargetIsBuffInUse2(31174,(DWORD32)g_pCICPlayer))
    {
        for (int i = 0; i < g_pCICPlayer->m_inventorySize; i++)
        {
            CIFSlotWithHelp* pSlot;
            CIFInventory* pInventory = g_pCGInterface->GetMainPopup()->GetInventory();
            if(pInventory)
            {
                pSlot = *reinterpret_cast<CIFSlotWithHelp**>(pInventory->pSlots + (i * 4));
                if(pSlot->ItemInfo && pSlot->ItemInfo != 0  && pSlot)
                {
                    if ( (pSlot->ItemInfo->GetObjectData()->ObjID == 24394 ||
                          pSlot->ItemInfo->GetObjectData()->ObjID == 24390||
                          pSlot->ItemInfo->GetObjectData()->ObjID == 24386||
                          pSlot->ItemInfo->GetObjectData()->ObjID == 24402))
                    {
                        if(pSlot->ItemInfo->m_quantity == 1)
                        {
                            g_pCGInterface->GetExtraFeatureGUI()->m_slot3->FUN_006871d0(0);
                            g_pCGInterface->GetExtraFeatureGUI()->m_slot3->TB_Func_13("", 1, 1);
                            g_pCGInterface->GetExtraFeatureGUI()->SetAutoABSbubble = false;
                            g_pCGInterface->GetExtraFeatureGUI()->m_btn3->SetText(TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP12"));
                        }
                        else
                        {
                            g_pCGInterface->GetExtraFeatureGUI()-> m_dame_absorbbubble_slot = pSlot->UniqueID()- 100 + 0xD;
                            if((time(NULL) - lastClickTime8 > 5)) {
                                CMsgStreamBuffer buf(0x704C);
                                buf << (byte)g_pCGInterface->GetExtraFeatureGUI()-> m_dame_absorbbubble_slot;
                                buf << (UINT16)0x0EED ;
                                SendMsg(buf);
                                lastClickTime8 = time(NULL);
                            }
                            break;
                        }

                    }
                }
            }
        }

    }
    if(g_pCGInterface->GetExtraFeatureGUI()->SetAutoINCbubble && g_pCICPlayer  && g_pCICPlayer->Status != 2 && !Rebot::TargetIsBuffInUse2(31153,(DWORD32)g_pCICPlayer)
       && !Rebot::TargetIsBuffInUse2(31165,(DWORD32)g_pCICPlayer) && !Rebot::TargetIsBuffInUse2(31161,(DWORD32)g_pCICPlayer)
       && !Rebot::TargetIsBuffInUse2(31157,(DWORD32)g_pCICPlayer) && !Rebot::TargetIsBuffInUse2(31169,(DWORD32)g_pCICPlayer)
       && !Rebot::TargetIsBuffInUse2(31173,(DWORD32)g_pCICPlayer))
    {
        CIFSlotWithHelp* pSlot;
        CIFInventory* pInventory = g_pCGInterface->GetMainPopup()->GetInventory();
        if(pInventory)
        {
            for (int i = 0; i < g_pCICPlayer->m_inventorySize; i++)
            {
                pSlot = *reinterpret_cast<CIFSlotWithHelp**>(pInventory->pSlots + (i * 4));
                if(pSlot->ItemInfo && pSlot->ItemInfo != 0  && pSlot)
                {
                    if ( (pSlot->ItemInfo->GetObjectData()->ObjID == 24393 ||
                          pSlot->ItemInfo->GetObjectData()->ObjID == 24389||
                          pSlot->ItemInfo->GetObjectData()->ObjID == 24385||
                          pSlot->ItemInfo->GetObjectData()->ObjID == 24401) )
                    {
                        if(pSlot->ItemInfo->m_quantity == 1)
                        {
                            g_pCGInterface->GetExtraFeatureGUI()->m_slot4->FUN_006871d0(0);
                            g_pCGInterface->GetExtraFeatureGUI()->m_slot4->TB_Func_13("", 1, 1);
                            g_pCGInterface->GetExtraFeatureGUI()->SetAutoINCbubble = false;
                            g_pCGInterface->GetExtraFeatureGUI()->m_btn4->SetText(TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP12"));
                        }
                        else
                        {
                            g_pCGInterface->GetExtraFeatureGUI()-> m_dame_Increasebubble_slot = pSlot->UniqueID()- 100 + 0xD;
                            if((time(NULL) - lastClickTime8 > 6)) {
                                CMsgStreamBuffer buf(0x704C);
                                buf << (byte)g_pCGInterface->GetExtraFeatureGUI()-> m_dame_Increasebubble_slot;
                                buf << (UINT16)0x0EED ;
                                SendMsg(buf);
                                lastClickTime8 = time(NULL);
                            }
                            break;
                        }

                    }
                }

            }
        }

    }
    //////////////////////////
}
void Rebot::AutoPotionForPet()
{
    if(Rebot::Config.AutoAttackPetPotion && Rebot::Config.PetAttackItemID > 0 && Rebot::Config.AutoPetPotion && g_pCICPlayer)
    {
        if(Rebot::get_pet_bytype(3))
        {
            int petAttackBase = Rebot::get_pet_bytype(3);
            if (0 != petAttackBase && 0 != *(DWORD32*)(petAttackBase + 0x04))
            {
                int uniqueid = *(DWORD32*)(petAttackBase + 0x04); //petuniqueid
                //printf("petAttackBase %p \n",petAttackBase);

                CICharactor * MyPetAttack = GetCharacterObjectByID_MAYBE(uniqueid);
                if(MyPetAttack && MyPetAttack != NULL)
                {

                    //int HP = *(DWORD32*)(petAttackBase + 0x08);
                    //int HGP = *(DWORD32*)(petAttackBase + 0x10);
                    //printf("petAttackBase %d \n",petAttackBase);
                    //printf("MyPetAttack %d \n",MyPetAttack);
                    //printf("PetUniqueID %d HP %d MAX %d HGP %d ILLNESS %d \n",uniqueid,MyPetAttack->m_petCurrentHp,MyPetAttack->GetSData()->m_health,HGP ,MyPetAttack->m_illness);

                    CIFPlayerMiniInfo *COSInfo = reinterpret_cast<CIFPlayerMiniInfo *>(g_pCGInterface->m_IRM.GetResObj(11, 1));
                    if (COSInfo && COSInfo->IsVisible())
                    {
                        //if(COSInfo->m_IRM.GetResObj<CIFPetMiniInfo>(100, 1)->IsVisible())
                        {
                            CIFPetMiniInfo* PetXX = COSInfo->m_IRM.GetResObj<CIFPetMiniInfo>(100, 1);
                            CIFGauge* HPPercent = PetXX->m_IRM.GetResObj<CIFGauge>(10, 1);
                            CIFGauge* HGPPercent = PetXX->m_IRM.GetResObj<CIFGauge>(11, 1);
                            //printf("m_valueBg %f m_valueFg %f \n",HGPPercent->m_valueBg,HGPPercent->m_valueFg);
                            if(Rebot::Config.AutoAttackPetHP && Rebot::Config.PetAttackHPtemID != 0 &&   ((HPPercent->m_valueBg * 100) < Rebot::Config.PetAttackHPPercent))
                            {
                                CIFSlotWithHelp* pSlot;
                                CIFInventory* pInventory = g_pCGInterface->GetMainPopup()->GetInventory();
                                if(pInventory)
                                {
                                    for (int i = 0; i <  g_pCICPlayer->m_inventorySize; i++)
                                    {
                                        pSlot = *reinterpret_cast<CIFSlotWithHelp**>(pInventory->pSlots + (i * 4));
                                        if(pSlot->ItemInfo  && pSlot)
                                        {
                                            if ( pSlot->ItemInfo->GetItemData()->m_id == Rebot::Config.PetAttackHPtemID)
                                            {
                                                if((time(NULL) - LastSendTimePetPotion > 1)) {

                                                    CMsgStreamBuffer buf(0x704C);
                                                    buf << (byte)(pSlot->UniqueID()- 100 + 0xD);
                                                    buf << (UINT16)(pSlot->ItemInfo->GetItemData()->TID) ;
                                                    buf << (UINT32)(uniqueid) ;
                                                    SendMsg(buf);
                                                    LastSendTimePetPotion = time(NULL);
                                                }
                                                break;
                                            }
                                        }
                                    }
                                }

                            }
                            if(Rebot::Config.AutoAttackPetHGP && Rebot::Config.PetAttackHPGItemID != 0 &&  ((HGPPercent->m_valueBg * 100) < Rebot::Config.PetAttackHPGPercent))
                            {
                                CIFSlotWithHelp* pSlot;
                                CIFInventory* pInventory = g_pCGInterface->GetMainPopup()->GetInventory();
                                if(pInventory)
                                {
                                    for (int i = 0; i <  g_pCICPlayer->m_inventorySize; i++)
                                    {
                                        pSlot = *reinterpret_cast<CIFSlotWithHelp**>(pInventory->pSlots + (i * 4));
                                        if(pSlot->ItemInfo  && pSlot)
                                        {
                                            if ( pSlot->ItemInfo->GetItemData()->m_id == Rebot::Config.PetAttackHPGItemID)
                                            {
                                                if((time(NULL) - LastSendTimePetPotion > 1)) {

                                                    CMsgStreamBuffer buf(0x704C);
                                                    buf << (byte)(pSlot->UniqueID()- 100 + 0xD);
                                                    buf << (UINT16)(pSlot->ItemInfo->GetItemData()->TID) ;
                                                    buf << (UINT32)(uniqueid) ;
                                                    SendMsg(buf);
                                                    LastSendTimePetPotion = time(NULL);
                                                }
                                                break;
                                            }
                                        }
                                    }
                                }

                            }
                        }
                    }
                    if(Rebot::Config.AutoAttackPetCure && Rebot::Config.PetAttackCureItemID != 0 && MyPetAttack->m_illness > 0)
                    {
                        CIFSlotWithHelp* pSlot;
                        CIFInventory* pInventory = g_pCGInterface->GetMainPopup()->GetInventory();
                        if(pInventory)
                        {
                            for (int i = 0; i <  g_pCICPlayer->m_inventorySize; i++)
                            {
                                pSlot = *reinterpret_cast<CIFSlotWithHelp**>(pInventory->pSlots + (i * 4));
                                if(pSlot->ItemInfo  && pSlot)
                                {
                                    if ( pSlot->ItemInfo->GetItemData()->m_id == Rebot::Config.PetAttackCureItemID)
                                    {
                                        if((time(NULL) - LastSendTimePetPotion > 1)) {

                                            CMsgStreamBuffer buf(0x704C);
                                            buf << (byte)(pSlot->UniqueID()- 100 + 0xD);
                                            buf << (UINT16)(pSlot->ItemInfo->GetItemData()->TID) ;
                                            buf << (UINT32)(uniqueid) ;
                                            SendMsg(buf);
                                            LastSendTimePetPotion = time(NULL);
                                        }
                                        break;
                                    }
                                }
                            }
                        }

                    }
                }

            }
        }
    }
    if(Rebot::Config.AutoTransPetHP && Rebot::Config.AutoPetPotion && g_pCICPlayer)
    {
        if(Rebot::get_pet_bytype(1))
        {
            int petTradeBase = Rebot::get_pet_bytype(1); // trade pet
            if (0 != petTradeBase && 0 != *(DWORD32 *) (petTradeBase + 0x04)) {
                int uniqueid = *(DWORD32 *) (petTradeBase + 0x04); //petuniqueid
                CICharactor *MyPetTrade = GetCharacterObjectByID_MAYBE(uniqueid);
                if (MyPetTrade && MyPetTrade != NULL) {
                    int HP = *(DWORD32 *) (petTradeBase + 0x08);
                    int MAXHP = *(DWORD32 *) (petTradeBase + 0x0C);
                    //printf("PetUniqueID %d HP %d MAX %d \n",uniqueid,HP,MAXHP);
                    if (Rebot::Config.AutoTransPetHP && Rebot::Config.PetHpRiddingAndTradeItemID != 0 &&
                        ((((float) HP / (float) MAXHP) * 100) < Rebot::Config.PetRiddingAndTradeHPPercent) ) {
                        CIFSlotWithHelp *pSlot;
                        CIFInventory *pInventory = g_pCGInterface->GetMainPopup()->GetInventory();
                        if(pInventory)
                        {
                            for (int i = 0; i < g_pCICPlayer->m_inventorySize; i++) {
                                pSlot = *reinterpret_cast<CIFSlotWithHelp **>(pInventory->pSlots + (i * 4));
                                if (pSlot->ItemInfo  && pSlot) {
                                    if (pSlot->ItemInfo->GetItemData()->m_id ==
                                        Rebot::Config.PetHpRiddingAndTradeItemID) {
                                        if ((time(NULL) - LastSendTimePetTradePotion > 2)) {

                                            CMsgStreamBuffer buf(0x704C);
                                            buf << (byte) (pSlot->UniqueID() - 100 + 0xD);
                                            buf << (UINT16) (pSlot->ItemInfo->GetItemData()->TID);
                                            buf << (UINT32) (uniqueid);
                                            SendMsg(buf);
                                            LastSendTimePetTradePotion = time(NULL);
                                        }
                                        break;
                                    }
                                }
                            }
                        }

                    }
                }

            }
        }
    }
    if(Rebot::Config.AutoRidingPetHP && Rebot::Config.AutoPetPotion && g_pCICPlayer)
    {
        if(Rebot::get_pet_bytype(0))
        {
            int petRiddingBase = Rebot::get_pet_bytype(0);
            if (0 != petRiddingBase && 0 != *(DWORD32*)(petRiddingBase + 0x04)) {
                int uniqueid = *(DWORD32 *) (petRiddingBase + 0x04); //petuniqueid
                CICharactor *MyPetRidding = GetCharacterObjectByID_MAYBE(uniqueid);
                if (MyPetRidding && MyPetRidding != NULL) {
                    int HP = *(DWORD32 *) (petRiddingBase + 0x08);
                    int MAXHP = *(DWORD32 *) (petRiddingBase + 0x0C);
                    //printf("PetUniqueID %d HP %d MAX %d \n",uniqueid,HP,MAXHP);
                    if (Rebot::Config.AutoRidingPetHP &&  Rebot::Config.PetHpRiddingAndTradeItemID != 0 &&
                        ((((float) HP / (float) MAXHP) * 100) < Rebot::Config.PetRiddingAndTradeHPPercent)) {
                        CIFSlotWithHelp *pSlot;
                        CIFInventory *pInventory = g_pCGInterface->GetMainPopup()->GetInventory();
                        if(pInventory)
                        {
                            for (int i = 0; i < g_pCICPlayer->m_inventorySize; i++) {
                                pSlot = *reinterpret_cast<CIFSlotWithHelp **>(pInventory->pSlots + (i * 4));
                                if (pSlot->ItemInfo  && pSlot) {
                                    if (pSlot->ItemInfo->GetItemData()->m_id == Rebot::Config.PetHpRiddingAndTradeItemID) {
                                        if ((time(NULL) - LastSendTimePetRidingPotion > 2)) {

                                            CMsgStreamBuffer buf(0x704C);
                                            buf << (byte) (pSlot->UniqueID() - 100 + 0xD);
                                            buf << (UINT16) (pSlot->ItemInfo->GetItemData()->TID);
                                            buf << (UINT32) (uniqueid);
                                            SendMsg(buf);
                                            LastSendTimePetRidingPotion = time(NULL);
                                        }
                                        break;
                                    }
                                }
                            }
                        }

                    }
                }
            }

        }
    }
}
time_t lastClickTime5;
DWORD _stdcall Rebot::Main(LPVOID lpParameter) {
    int FPatrolDestIndexs;
    int MonsterCount;
    while (1)
    {
        if (!Rebot::RebotStart) {
            Sleep(500);
            continue;
        }
        if (!g_pCICPlayer || g_pCICPlayer == 0) {
            Sleep(3000);
            continue;
        }
        if (!g_pCGInterface || g_pCGInterface == 0) {
            Sleep(3000);
            continue;
        }
        if (TownRegion.find(g_pCICPlayer->GetRegion().r) != TownRegion.end())
        {
            Sleep(500);
            continue;
        }
        if (DimenSionalRegion.find(g_pCICPlayer->GetRegion().r) != DimenSionalRegion.end())
        {
            Sleep(500);
            continue;
        }
        if (g_pCICPlayer->Status == 2) {
            if(Config.AcceptRes)
            {
                Sleep(500);
                continue;
            }
            else
            {
                Rebot::RebotStart=false;
                g_pCGInterface->GetCIFSTMacroGUI()->btn2->TB_Func_13("interface\\macro\\macro_icon_hunting_off.ddj", 1, 1);
                g_pCGInterface->ShowMessage_Quest(TSM_GETTEXTPTR("UIIT_ST_MACRO_TOOLTIP4"));
                Sleep(500);
                continue;
             }
        }
        if(Rebot::Config.OnlyResPartyMember && Rebot::Config.AutoResMember)
        {
            if (Rebot::SelectObjRes) {
                D3DVECTOR SelectLocation = Rebot::SelectObjRes->GetLocation();
                GetSilkPos(Rebot::SelectObjRes->GetRegion(), SelectLocation);
                double SelectDis = Rebot::Distance(g_pCICPlayer->GetLocation(), SelectLocation);
                short Status = Rebot::SelectObjRes->Status;//0x2 or 0x18   //17���� 265վ��  521�� 65����
                if (Rebot::SelectObjRes->GetUniqueID()==0 || Status == 0x18 || SelectDis > 500 || ObjIntersect(g_pCICPlayer, Rebot::SelectObjRes)) {
                    Rebot::SelectObjRes = 0;
                }
                else if (Rebot::Distance(SelectLocation, GetSilkPosD3D(Rebot::Config.StartRegion, Rebot::Config.StartPos)) > Rebot::Config.RebotRange) {
                    Rebot::SelectObjRes = 0;
                }
            }
            if (!Rebot::SelectObjRes) {
                Rebot::SelectObjRes = (CICharactor*)Rebot::GetNearPartyMember();
            }
            if (Rebot::SelectObjRes && Rebot::SelectObjRes->GetUniqueID() != 0 && Rebot::SelectObjRes->Status == 0x2 && Rebot::SelectObjRes->Status != 0x18 ) {
                for (size_t i = 21; i <= 30; i++)
                {
                    DWORD32 SkillID = Rebot::GetSkillIDByQuickIndex(i);
                    if (Rebot::HaveSkill[SkillID] && SkillID != 0) {
                        if (Rebot::HaveSkill[SkillID]->Param1 == 0) {
                            if (Rebot::HaveSkill[SkillID]->TargetRequired &&Rebot::HaveSkill[SkillID]->TargetEtc_SelectDeadBody){
                                if (SendMessageA(Rebot::GameHWND, WM_USESKILL, SkillID, Rebot::SelectObjRes->GetUniqueID()))
                                {
                                    break;
                                }
                            }

                        }
                    }
                }
                Rebot::SelectObjRes = 0;
                Sleep(500);
                continue;
            }

        }
        if(Rebot::Config.AutoBuffMode )
        {
             for (size_t i = 21; i <= 30; i++)
             {
                 DWORD32 SkillID = Rebot::GetSkillIDByQuickIndex(i);
                     if (Rebot::HaveSkill[SkillID] && SkillID != 0)
                     {
                         if (Rebot::HaveSkill[SkillID]->Param1 == 3 || Rebot::HaveSkill[SkillID]->Param3 == 63 || Rebot::HaveSkill[SkillID]->Param2 == 1751474540 || Rebot::HaveSkill[SkillID]->Param2 == 6645362 )
                         {
                             if (Rebot::HaveSkill[SkillID]->TargetRequired)
                             {
                                 Rebot::SelectObjBuff = (CICharactor*)Rebot::GetNearPartyMemberToBuff(SkillID);
                                 if(Rebot::SelectObjBuff && Rebot::SelectObjBuff->GetUniqueID() != 0 && Rebot::SelectObjBuff->Status != 0x2 && Rebot::SelectObjBuff->Status != 0x18)
                                 {
                                     if (Rebot::m_SkillNeedBuffList[Rebot::SelectObjBuff->GetName().c_str()])
                                     {
                                         for(std::list<short >::iterator itr = Rebot::m_SkillNeedBuffList[Rebot::SelectObjBuff->GetName().c_str()]->m_SkillNeedBuff.begin(); itr != Rebot::m_SkillNeedBuffList[Rebot::SelectObjBuff->GetName().c_str()]->m_SkillNeedBuff.end(); ++itr)
                                         {
                                             if (*itr==SkillID)
                                             {
                                                 if (!Rebot::TargetIsBuffInUse(SkillID, (DWORD32)Rebot::SelectObjBuff)) {
                                                     if (SendMessageA(Rebot::GameHWND, WM_USESKILL, SkillID, Rebot::SelectObjBuff->GetUniqueID())) {
                                                         break;
                                                     }
                                                 }
                                             }

                                         }
                                     }

                                 }
                             }
                         }
                     }
             }
        }
    if (Rebot::SelectObj) {
            D3DVECTOR SelectLocation = Rebot::SelectObj->GetLocation();
            GetSilkPos(Rebot::SelectObj->GetRegion(), SelectLocation);
            double SelectDis = Rebot::Distance(g_pCICPlayer->GetLocation(), SelectLocation);
            short Status = Rebot::SelectObj->Status;//0x2 or 0x18   //17���� 265վ��  521�� 65����
            if (Rebot::SelectObj->GetUniqueID()==0||Status == 2 || Status == 0x18 || SelectDis > 500 || ObjIntersect(g_pCICPlayer, Rebot::SelectObj)) {
                Rebot::SelectObj = 0;
            }
                else if (Rebot::Distance(SelectLocation, GetSilkPosD3D(Rebot::Config.StartRegion, Rebot::Config.StartPos)) > Rebot::Config.RebotRange) {
                Rebot::SelectObj = 0;
            }
    }
    if (!Rebot::SelectObj) {
        Rebot::SelectObj = (CICharactor*)Rebot::GetNearestObj();
        Rebot::InvalidObjects.clear();
    }
    if (Rebot::SelectObj && Rebot::SelectObj->GetUniqueID() != 0 && Rebot::SelectObj->Status != 0x2 && Rebot::SelectObj->Status != 0x18 && g_pCGInterface) {
        if (Rebot::SelectObj->GetUniqueID() != g_pCGInterface->Get_SelectedObjectId()) {
        SendMessageA(Rebot::GameHWND, WM_CHOOSEMONSTER, Rebot::SelectObj->GetUniqueID(), 0);
        }

        for (size_t i = 1; i <= 20; i++)
        {
            DWORD32 SkillID = Rebot::GetSkillIDByQuickIndex(i);
            //printf("SkillID:::::%d\r\n", SkillID);
            if (Rebot::HaveSkill[SkillID] && SkillID != 0) {
           // printf("SkillID%d,Param1:%d\r\n", SkillID, HaveSkill[SkillID]->Param1);
           // printf("SkillID%d,Param8:%d\r\n", SkillID, HaveSkill[SkillID]->Param8);

                if (Rebot::HaveSkill[SkillID]->Param1 == 3) {
                    if (Rebot::HaveSkill[SkillID]->TargetRequired){
                       /* if(Rebot::HaveSkill[SkillID]->Param4 == 1500 && Rebot::HaveSkill[SkillID]->Param5 > 0)
                        {

                        }*/
                    }
                    else{
                        if (!Rebot::TargetIsBuffInUse(SkillID, (DWORD32)g_pCICPlayer)) {
                            if (SendMessageA(Rebot::GameHWND, WM_USESKILL, SkillID, 0)) {
                                break;
                            }
                        }
                    }
                }
                else {
                    if (Rebot::HaveSkill[SkillID]->Param8 == 25697) {
                        if (Rebot::SelectObj&&Rebot::SelectObj->Status == 17) {
                            if (SendMessageA(Rebot::GameHWND, WM_USESKILL, SkillID, Rebot::SelectObj->GetUniqueID())) {
                             break;
                            }
                        }
                    }
                    else if (Rebot::SelectObj && Rebot::SelectObj->Status != 17) {
                        if (SendMessageA(Rebot::GameHWND, WM_USESKILL, SkillID, Rebot::SelectObj->GetUniqueID())) {
                            break;
                        }
                    }
                }
            }
            else{
                if(Rebot::Config.LureMode)
                {
                    if ( g_pCICPlayer->Status== 269) {
                        Rebot::SelectObj=0;
                        MonsterCount++;
                        if(MonsterCount>2)
                        {
                            MonsterCount=0;
                            SendMessageA(Rebot::GameHWND, WM_MOVECHAR, (DWORD32)&PatrolRegions, (DWORD32)&CenterLocations);
                            Sleep(3000);
                        }
                    }
                }
                if (!Rebot::TargetIsBuffInUse(SkillID, (DWORD32)g_pCICPlayer)) {

                            if (SendMessageA(Rebot::GameHWND, WM_USESKILL, SkillID, 0)) {
                            break;
                            }
                        //param4 1919250793 shield req
                        //param8 1919250793 shield req
                }
            }
        }
    }
    else {
        if (g_pCICPlayer->Status == 265) {
            if (!Rebot::Config.GoBackCentrer) {
                    if((time(NULL) - lastClickTime5 > 2)) {
                        D3DVECTOR CenterLocation = CenterLocations;
                        uregion PatrolRegion = PatrolRegions;
                        FPatrolDestIndexs++;
                        if (FPatrolDestIndexs > 3) {
                            FPatrolDestIndex = 0;
                        }
                        int angle = FPatrolDestIndexs * 90;
                        CenterLocation.x = ceil(cos((angle) * (3.1415926 / 180)) * (Config.RebotRange) + CenterLocation.x);
                        CenterLocation.z = ceil(sin((angle) * (3.1415926 / 180)) * (Config.RebotRange) + CenterLocation.z);
                        SendMessageA(Rebot::GameHWND, WM_MOVECHAR, (DWORD32)&PatrolRegion, (DWORD32)&CenterLocation);
                        lastClickTime5 = time(NULL);
                    }
            }
            else {
                if (Rebot::Distance(g_pCICPlayer->GetLocation(), GetSilkPosD3D(Config.StartRegion, Config.StartPos)) > 50) {
                    if((time(NULL) - lastClickTime5 > 2)) {
                        SendMessageA(Rebot::GameHWND, WM_MOVECHAR, (DWORD32)&PatrolRegions, (DWORD32)&CenterLocations);
                        lastClickTime5 = time(NULL);
                    }
                }
            }
            Sleep(500);
        }
    }
    Sleep(200);
    }
}

DWORD _stdcall Rebot::Main2(LPVOID lpParameter) {
    while (1)
    {
        if(!Rebot::Config.AutoPetPotion)
        {
            Sleep(1000);
            continue;
        }
        if (!g_pCICPlayer || g_pCICPlayer == 0) {
            Sleep(3000);
            continue;
        }
        if (g_pCICPlayer->Status==2) {
            Sleep(2000);
            continue;
        }
         AutoPotionForPet();
         Sleep(200);
    }
}
DWORD _stdcall Rebot::Main3(LPVOID lpParameter) {
    while (1)
    {
        if (!g_pCICPlayer || g_pCICPlayer == 0) {
            Sleep(3000);
                continue;
            }
            AutoPotionAndItem();
        Sleep(200);
    }
}
