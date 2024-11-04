#pragma once
#include <GlobalHelpersThatHaveNoHomeYet.h>
#include <GFXMainFrame/GWndBase.h>
#include <GFX3DFunction/DrawingHelpers.h>
#include <IFWnd.h>
#include <GInterface.h>
#include <NavMesh/RTNavMeshTerrain.h>
#include <ICPlayer.h>
#include "Skill.h"
#define WM_USEITEM WM_USER + 201
#define WM_USESKILL WM_USER + 202
#define WM_MOVECHAR WM_USER + 230
#define WM_CHOOSEMONSTER WM_USER + 204
#define WM_REBOTSTATUS WM_USER + 300
struct RebotConfig
{
    bool ShowTargetInfo;
    bool ShowTeamer;
    bool ShowAbout;
    bool AttackHostility;
    bool GoBackCentrer;
    bool RequestJoinParty;
    bool AutoBerserk;
    bool AutoHP;
    bool AutoMP;
    bool AutoVigor;
    bool AutoPotion;
    bool AutoPetPotion;
    bool AutoAbnormal;
    bool AutoSpeedScroll;
    bool AutoRidingPetHP;
    bool AutoTransPetHP;
    bool AutoAttackPetHP;
    bool AutoAttackPetHGP;
    bool AutoAttackPetCure;
    bool AutoAttackPetResurrect;
    bool AutoAttackPetPotion;
    bool LureMode;
    bool AcceptRes;
    bool AutoResMember;
    bool AutoBuffMode;
    bool AutoAttackSnowMan;
    bool ResMember;
    bool OnlyResPartyMember;
    bool AttackOtherPlayer;
    int HpPercent;
    int MpPercent;
    int VigorPercent;
    int PetAttackHPPercent;
    int PetAttackHPGPercent;
    int PetRiddingAndTradeHPPercent;
    unsigned __int16 HpItemID;
    unsigned __int16 MpItemID;
    unsigned __int16 VigorItemID;
    unsigned __int16 AbnormalItemID;
    unsigned __int16 SpeedItemID;
    unsigned __int16 PetAttackHPtemID;
    unsigned __int16 PetAttackHPGItemID;
    unsigned __int16 PetAttackCureItemID;
    unsigned __int16 PetAttackResurrectItemID;
    unsigned __int16 PetAttackItemID;
    unsigned __int16 PetHpRiddingAndTradeItemID;
    float RebotRange;
    int FindStatus;
    D3DVECTOR StartPos;
    uregion StartRegion;
    std::vector<std::wstring> Teamer;
    float x1;
    float x2;
    float y1;
    float y2;
    float cercle;
    float cercleX;
    float cercleY;
    float cercleRadius;
    bool CircleShow;
    bool CircleGreenShow;
};

typedef struct _SR_POS
{
    signed char map_x;
    signed char map_y;
    signed char map_z;
    signed char none;
    float x;
    float z;
    float y;
    float d;
}SR_POS, *PSR_POS;
struct ITEM_INFO
{
    SR_POS cur_pos;
    unsigned int item_id;
    unsigned int item_type;
    unsigned int item_cls;
    bool item_pickable;
};
class Rebot {
public:

    Rebot();
    void Render();
    static void AutoPotionForPet();
    static void AutoPotionAndItem();
    static void SelectObject(DWORD32 ObjID);//ѡ��Ŀ��
    static void InviteMember(DWORD32 ObjID);//ѡ��Ŀ��
    static DWORD32 GetSkillIDByQuickIndex(int Index);//ͨ��������õ�����ID
    static boolean TargetIsBuffInUse(DWORD32 SkillID, DWORD32 Target);//�ж�Ŀ���Ƿ����BUFF
    static boolean TargetIsBuffInUse2(DWORD32 SkillID, DWORD32 Target);//�ж�Ŀ���Ƿ����BUFF
    static bool is_skill_inuse(int skill);
    static boolean CastSpell(DWORD32 SkillID, DWORD32 Target);//�ͷż���
    static DWORD32 GetSkillCoolDown(DWORD32 SkillID);//��ȡ������ȴʱ��
    static void HunterWalk( int x, int y );
    static void HunterRandRun( float fBotX, float fBotY, int nRound );
    static RebotConfig Config;
    bool static RebotStart;
    bool static RebotShow;
    std::map<short,CRTNavMeshTerrain*> static CRTNavMeshTerrainAll;
    static CICharactor* SelectObj;
    static CICharactor* SelectObjRes;
    static CICharactor* SelectObjBuff;
    static std::map<short, DWORD> SkillStatus;
    static std::map<short, Skill*> HaveSkill;
    static std::map<short, Skill*> AllSkillOfChar;
    static std::map<short, BuffSkill*> m_SkillBuffList;
    static std::map<std::wstring, BuffSkill*> m_SkillNeedBuffList;
    static std::list<std::wstring> m_CharNeedBuff;
    static HWND GameHWND;
    static std::vector<CIGIDObject*> InvalidObjects;//��Ч�б�
    static std::vector<CIGIDObject*> FirstObjects;//���ȹ����б�
    static CSOItem* GetBackpackItem(int index); //������Ʒ
    static CSOItem* GetEquipmentItem(int index); //װ��
    void GetSkillList(); //װ������
    static void GetSkillInfo(DWORD32 Base, DWORD32 ParentBase);
    static DWORD32 SkillBaseHead;
    static D3DVECTOR GetPatrolPos();
    static int FPatrolDestIndex;
    static float Distance(D3DVECTOR startAirportPos, D3DVECTOR endAirportPos);

    static std::map<std::string, CSOItem> ChatItemInfoList;
    static std::map<std::n_string, CSOItem> CharInfoList1;
    static int get_pet_bytype( int types );
    static void get_itemlist( int* plist );
    static bool get_iteminfo( ITEM_INFO& info, int id );
    static std::list<int> Equipment_TID_List;
    static std::list<int> Equipment_TID_Weapon_List;
    static std::list<int> Equipment_TID_Accsessory_List;
    static std::list<int> Equipment_TID_Heavy_List;
    static std::list<int> Equipment_TID_Clothes_List;
    static std::list<int> Equipment_TID_Light_List;
    static std::list<int> Potion_ObjID_HP_Potion_List; // hp 1->5
    static std::list<int> Potion_ObjID_MP_Potion_List; //mp 1->5
    static std::list<int> Potion_ObjID_Vigor_Potion_List; //mau tim 570-820
    static std::list<int> Potion_ObjID_Universal_Pill_List; //giai doc
    static std::list<int> Potion_ObjID_Return_Scroll_List; //return scroll
    static std::list<int> Potion_ObjID_Coin_List; //token & coin
    static std::list<int> Speed_Scroll_ItemID;
    static std::list<int> Potion_Pet_HP_Tid_List;
    static std::list<int> Potion_Pet_HGP_Tid_List;
    static std::list<int> Potion_Pet_Cure_List;
    static std::list<int> Potion_Pet_Resurrect_List;
    static std::list<int> Potion_Pet_Summon_Trigger_List;

    static CICharactor* FindBaseByUID(DWORD32 ObjectId);

    static void UseBerSerk();


private:

    static DWORD32 GetBuffListBase(DWORD32 Addr);
    static DWORD32 GetQuickBarByIndex(int Index);
    static DWORD32 GetSkillIDWithQuickBarObject(DWORD32 ObjBase);
    static DWORD32 GetSkillCDListBase();

public:
    static DWORD32 GetListBase(); //�ܶ����ݼ��϶���������


    static DWORD _stdcall Main(LPVOID lpParameter);
    static DWORD _stdcall Main2(LPVOID lpParameter);
    static DWORD _stdcall Main3(LPVOID lpParameter);
    static CIObject* GetNearestObj();
    static CIObject* GetNearPartyMember();
    static CIObject* GetNearPartyMemberToBuff(short SkillID);


};