#include "Util.h"

#include <sys/stat.h>

#include <memory/hook.h>

#include "hooks/Hooks.h"
#include "hooks/GFXVideo3d_Hook.h"
#include "hooks/CGame_Hook.h"

#include "hooks/WndProc_Hook.h"

#include <GInterface.h>

//#include <NetProcessIn.h>
//#include <NetProcessSecond.h>
//#include <NetProcessThird.h>

#include <BSLib/Debug.h>
#include <PSCharacterSelect.h>
#include <GFX3DFunction/DrawingHelpers.h>
#include <NavMesh/RTNavMeshTerrain.h>
#include <Rebot.h>
#include <NetProcessIn.h>
#include <NetProcessSecond.h>
#include <NetProcessThird.h>
#include <CPSTitle.h>
#include <IFCOSSetup.h>
#include <IFPartyMatchReqJoin.h>
#include <IFMessageBox.h>
#include <ICMonster.h>
#include <GFX3DFunction/RStateMgr.h>
#include <NIFGuildWnd.h>
#include <GlobalDataManager.h>
#include <IFMagicStateBoard.h>
#include <IFPlayerMiniInfo.h>
#include <IFPartyMatch.h>
#include <NIFWorldMap.h>
#include <GameDataExt.h>
#include <algorithm>
#include <DropItemManager.h>
#include "QuickStart.h"



std::vector<const CGfxRuntimeClass *> register_objects;
std::vector<overrideFnPtr> override_objects;

QuickStart quickstart;

void Setup() {
#ifdef CONFIG_DEBUG_CONSOLE
   // AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONIN$", "r", stdin);
#endif

    vftableHook(0x00E0963C, 17, addr_from_this(&CGFXVideo3D_Hook::CreateThingsHook));
    vftableHook(0x00E0963C, 26, addr_from_this(&CGFXVideo3D_Hook::EndSceneHook));
    vftableHook(0x00E0963C, 20, addr_from_this(&CGFXVideo3D_Hook::SetSizeHook));

    vftableHook(0x00db95a4, 10, addr_from_this(&CGInterface::OnCreateIMPL));
    replaceAddr(0x00d7110a + 1, addr_from_this(&CGInterface::OnKeyDown));
    replaceOffset(0x0078b6ce, addr_from_this(&CGInterface::OnEscapePressed));

    vftableHook(0x00de2e7c, 15, addr_from_this(&CICUser::Func_15_impl));
    vftableHook(0x00de256c, 15, addr_from_this(&CICharactor::Func_15_impl));
    vftableHook(0x00de2c24, 15, addr_from_this(&CICPlayer::Func_15_impl));
    //vftableHook(0x00de26c4, 15, addr_from_this(&CICMonster::Func_15_impl));

    //vftableHook(0x00dd811c, 10, addr_from_this(&CPSCharacterSelect::OnCreateIMPL));




    //`replaceAddr(0x00dd8134, addr_from_this(&CPSCharacterSelect::OnServerPacketRecv));
    replaceAddr(0x00dd814c, addr_from_this(&CPSCharacterSelect::OnUpdateIMPL));

    //replaceAddr(0x00da7a94, addr_from_this(&CIFPlayerInfo::OnCreateIMPL));
    //replaceAddr(0x00da7a9c, addr_from_this(&CIFPlayerInfo::OnUpdateIMPL));


    replaceAddr(0x00dbb174, addr_from_this(&CIFCOSSetup::OnCreateIMPL));
    replaceAddr(0x00dbb17c, addr_from_this(&CIFCOSSetup::OnUpdateIMPL));

    replaceAddr(0x00db41ac, addr_from_this(&CIFPartyMatchReqJoin::OnCreateIMPL));
    replaceAddr(0x00db41b4, addr_from_this(&CIFPartyMatchReqJoin::OnUpdateIMPL));

    replaceAddr(0x00da9248, addr_from_this(&CIFPartySlot::OnMouseLeftUpIMPL));
    replaceAddr(0x00da8f0c, addr_from_this(&CIFParty::OnCreateIMPL));
    replaceAddr(0x00da8f14, addr_from_this(&CIFParty::OnUpdateIMPL));
    replaceAddr(0x00db37cc, addr_from_this(&CIFPartyMatch::OnUpdateIMPL));
    replaceAddr(0x00db37e4, addr_from_this(&CIFPartyMatch::OnMouseLeftUpIMPL));
    replaceAddr(0x00db4304, addr_from_this(&CIFPartyMatchSlot::OnUpdateIMPL));
    replaceAddr(0x00db42fc, addr_from_this(&CIFPartyMatchSlot::OnCreateIMPL));


    //pick pet filter
    replaceOffset(0x008AFCF9,addr_from_this(&CDropItemManager::sub_8AF7F0));

    replaceAddr(0x00da6f04, addr_from_this(&CIFEquipment::OnCreateIMPL));
    replaceAddr(0x00da6f0c, addr_from_this(&CIFEquipment::OnUpdateIMPL));

    //replaceAddr(0x00da1918, addr_from_this(&CIFSlotWithHelp::RenderMyselfIMPL));

    //replaceAddr(0x00da190c, addr_from_this(&CIFSlotWithHelp::OnCreateIMPL));
    //replaceAddr(0x00da4f5c, addr_from_this(&CNIFWorldMap::OnCreateIMPL));
    //replaceAddr(0x00da4f64, addr_from_this(&CNIFWorldMap::OnUpdateIMPL));
    replaceAddr(0x00d99bc8, addr_from_this(&CNIFWorldMap::RenderMyselfIMPL));
    //replaceAddr(0x00da4f68, addr_from_this(&CNIFWorldMap::RenderMyselfIMPL));
    //replaceAddr(0x00d6a130 + 1, addr_from_this(&CNIFWorldMap::FUN_00620f70));

    //replaceAddr(0x00d9ba78, addr_from_this(&CIFMessageBox::OnCloseWndIMPL));
    //replaceAddr(0x00d9ba28, addr_from_this(&CIFMessageBox::ShowGWndIMPL));

    //replaceAddr(0x00d92884, addr_from_this(&CNIFGuildWnd::OnCreateIMPL));
    //replaceAddr(0x00d9288c, addr_from_this(&CNIFGuildWnd::OnUpdateIMPL));

    //replaceAddr(0x00dd058c, addr_from_this(&CIFMagicStateBoard::OnCreateIMPL));
    //replaceAddr(0x00dd0594, addr_from_this(&CIFMagicStateBoard::OnUpdateIMPL));


    //replaceAddr(0x00dbd4f4, addr_from_this(&CIFPlayerMiniInfo::OnCreateIMPL));
    //replaceAddr(0x00dbd4fc, addr_from_this(&CIFPlayerMiniInfo::OnUpdateIMPL));


    replaceAddr(0x00831337 + 4, (int) &WndProcHook);


    placeHook(0x0065c6f0, addr_from_this(&CAlramGuideMgrWnd::GetGuide));

    replaceOffset(0x008491d1, addr_from_this(&CGame_Hook::LoadGameOption));

    replaceOffset(0x00832a11, addr_from_this(&CGame_Hook::InitGameAssets_Impl));
    replaceOffset(0x008774f4, (int)&WriteToChatWindow);
    replaceOffset(0x00877b5c, (int)&WriteToChatWindow);
    replaceAddr(0x00dd92d4, addr_from_this(&CPSTitle::OnServerPacketRecv));
    placeHook(0x007a9bd0, addr_from_this(&CIFChatViewer::ShowHideControls));

    //replaceOffset(0x009ded0d, addr_from_this(&CRStateMgr::FUN_00470060));
    //replaceOffset(0x0084c9bf, addr_from_this(&CNetProcessIn::RegisterPacketHandlers));
    //replaceOffset(0x00898656, addr_from_this(&CNetProcessSecond::RegisterPacketHandlers));
    //replaceOffset(0x008a4876, addr_from_this(&CNetProcessThird::RegisterPacketHandlers));

    // placeHook(0x0049d620, Put);

    quickstart.Setup();

    // Start Discord rich presence

#ifdef CONFIG_DEBUG_REDIRECT_PUTDUMP
    replaceAddr(0x00832927 + 1, (int) &DebugPrintCallback);
#endif // CONFIG_DEBUG_REDIRECT_PUTDUMP

#ifdef CONFIG_TRANSLATIONS_DEBUG
    placeHook(0x008C9C30, addr_from_this(&CTextStringManager::GetString));
#endif // CONFIG_TRANSLATIONS_DEBUG

#ifdef CONFIG_CHATVIEWER
    replaceOffset(0x008774f4, (int)&WriteToChatWindow);
    replaceOffset(0x00877b5c, (int)&WriteToChatWindow);

    placeHook(0x007a9bd0, addr_from_this(&CIFChatViewer::ShowHideControls));
#endif // CONFIG_CHATVIEWER

}
void AddRegion() {
    RocRegion.insert(21617);
    RocRegion.insert(21618);
    RocRegion.insert(21619);
    RocRegion.insert(21620);
    RocRegion.insert(21621);
    RocRegion.insert(21866);
    RocRegion.insert(21867);
    RocRegion.insert(21868);
    RocRegion.insert(21869);
    RocRegion.insert(21870);
    RocRegion.insert(21871);
    RocRegion.insert(21872);
    RocRegion.insert(21873);
    RocRegion.insert(21874);
    RocRegion.insert(21875);
    RocRegion.insert(21876);
    RocRegion.insert(21877);
    RocRegion.insert(22122);
    RocRegion.insert(22123);
    RocRegion.insert(22124);
    RocRegion.insert(22125);
    RocRegion.insert(22126);
    RocRegion.insert(22127);
    RocRegion.insert(22128);
    RocRegion.insert(22129);
    RocRegion.insert(22130);
    RocRegion.insert(22131);
    RocRegion.insert(22132);
    RocRegion.insert(22133);
    RocRegion.insert(22134);
    RocRegion.insert(22377);
    RocRegion.insert(22378);
    RocRegion.insert(22379);
    RocRegion.insert(22380);
    RocRegion.insert(22381);
    RocRegion.insert(22382);
    RocRegion.insert(22383);
    RocRegion.insert(22384);
    RocRegion.insert(22385);
    RocRegion.insert(22386);
    RocRegion.insert(22387);
    RocRegion.insert(22388);
    RocRegion.insert(22389);
    RocRegion.insert(22390);
    RocRegion.insert(22633);
    RocRegion.insert(22634);
    RocRegion.insert(22635);
    RocRegion.insert(22636);
    RocRegion.insert(22637);
    RocRegion.insert(22638);
    RocRegion.insert(22639);
    RocRegion.insert(22640);
    RocRegion.insert(22641);
    RocRegion.insert(22642);
    RocRegion.insert(22643);
    RocRegion.insert(22644);
    RocRegion.insert(22645);
    RocRegion.insert(22889);
    RocRegion.insert(22890);
    RocRegion.insert(22891);
    RocRegion.insert(22892);
    RocRegion.insert(22893);
    RocRegion.insert(22894);
    RocRegion.insert(22895);
    RocRegion.insert(22896);
    RocRegion.insert(22897);
    RocRegion.insert(22898);
    RocRegion.insert(22899);
    RocRegion.insert(22900);
    RocRegion.insert(22901);
    RocRegion.insert(23144);
    RocRegion.insert(23145);
    RocRegion.insert(23146);
    RocRegion.insert(23147);
    RocRegion.insert(23148);
    RocRegion.insert(23149);
    RocRegion.insert(23150);
    RocRegion.insert(23151);
    RocRegion.insert(23152);
    RocRegion.insert(23153);
    RocRegion.insert(23154);
    RocRegion.insert(23155);
    RocRegion.insert(23156);
    RocRegion.insert(23157);
    RocRegion.insert(23158);
    RocRegion.insert(23400);
    RocRegion.insert(23401);
    RocRegion.insert(23402);
    RocRegion.insert(23403);
    RocRegion.insert(23404);
    RocRegion.insert(23405);
    RocRegion.insert(23406);
    RocRegion.insert(23407);
    RocRegion.insert(23408);
    RocRegion.insert(23409);
    RocRegion.insert(23410);
    RocRegion.insert(23411);
    RocRegion.insert(23412);
    RocRegion.insert(23413);
    RocRegion.insert(23414);
    RocRegion.insert(23656);
    RocRegion.insert(23657);
    RocRegion.insert(23658);
    RocRegion.insert(23659);
    RocRegion.insert(23660);
    RocRegion.insert(23661);
    RocRegion.insert(23662);
    RocRegion.insert(23663);
    RocRegion.insert(23664);
    RocRegion.insert(23665);
    RocRegion.insert(23666);
    RocRegion.insert(23667);
    RocRegion.insert(23668);
    RocRegion.insert(23669);
    RocRegion.insert(23670);
    RocRegion.insert(23912);
    RocRegion.insert(23913);
    RocRegion.insert(23914);
    RocRegion.insert(23915);
    RocRegion.insert(23916);
    RocRegion.insert(23917);
    RocRegion.insert(23918);
    RocRegion.insert(23919);
    RocRegion.insert(23920);
    RocRegion.insert(23921);
    RocRegion.insert(23922);
    RocRegion.insert(23923);
    RocRegion.insert(23924);
    RocRegion.insert(23925);
    RocRegion.insert(24168);
    RocRegion.insert(24169);
    RocRegion.insert(24170);
    RocRegion.insert(24171);
    RocRegion.insert(24172);
    RocRegion.insert(24173);
    RocRegion.insert(24174);
    RocRegion.insert(24175);
    RocRegion.insert(24176);
    RocRegion.insert(24177);
    RocRegion.insert(24178);
    RocRegion.insert(24179);
    RocRegion.insert(24180);
    RocRegion.insert(24181);
    RocRegion.insert(24182);
    RocRegion.insert(24424);
    RocRegion.insert(24425);
    RocRegion.insert(24426);
    RocRegion.insert(24427);
    RocRegion.insert(24428);
    RocRegion.insert(24429);
    RocRegion.insert(24430);
    RocRegion.insert(24431);
    RocRegion.insert(24432);
    RocRegion.insert(24433);
    RocRegion.insert(24434);
    RocRegion.insert(24435);
    RocRegion.insert(24436);
    RocRegion.insert(24437);
    RocRegion.insert(24438);
    RocRegion.insert(24680);
    RocRegion.insert(24681);
    RocRegion.insert(24682);
    RocRegion.insert(24683);
    RocRegion.insert(24684);
    RocRegion.insert(24685);
    RocRegion.insert(24686);
    RocRegion.insert(24687);
    RocRegion.insert(24688);
    RocRegion.insert(24689);
    RocRegion.insert(24690);
    RocRegion.insert(24691);
    RocRegion.insert(24692);
    RocRegion.insert(24693);
    RocRegion.insert(24936);
    RocRegion.insert(24937);
    RocRegion.insert(24938);
    RocRegion.insert(24939);
    RocRegion.insert(24940);
    RocRegion.insert(24941);
    RocRegion.insert(24942);
    RocRegion.insert(24943);
    RocRegion.insert(24944);
    RocRegion.insert(24945);
    RocRegion.insert(24946);
    RocRegion.insert(24947);
    RocRegion.insert(24948);
    RocRegion.insert(24949);
    RocRegion.insert(25194);
    RocRegion.insert(25195);
    RocRegion.insert(25196);
    RocRegion.insert(25197);
    RocRegion.insert(25200);
    RocRegion.insert(25201);
    RocRegion.insert(25202);
    RocRegion.insert(25203);
    RocRegion.insert(25532);
    RocRegion.insert(25533);
    RocRegion.insert(25788);
    RocRegion.insert(25789);
    RocRegion.insert(25790);
    RocRegion.insert(25792);
    RocRegion.insert(26044);
    RocRegion.insert(26045);
    RocRegion.insert(26046);
    RocRegion.insert(26300);
    RocRegion.insert(26301);
    RocRegion.insert(26302);

    DimenSionalRegion.insert(22763);
    DimenSionalRegion.insert(22764);
    DimenSionalRegion.insert(22765);
    DimenSionalRegion.insert(22766);
    DimenSionalRegion.insert(22767);
    DimenSionalRegion.insert(22768);
    DimenSionalRegion.insert(22769);
    DimenSionalRegion.insert(22770);
    DimenSionalRegion.insert(22771);
    DimenSionalRegion.insert(22772);
    DimenSionalRegion.insert(22773);
    DimenSionalRegion.insert(22774);
    DimenSionalRegion.insert(22775);
    DimenSionalRegion.insert(23019);
    DimenSionalRegion.insert(23020);
    DimenSionalRegion.insert(23021);
    DimenSionalRegion.insert(23022);
    DimenSionalRegion.insert(23023);
    DimenSionalRegion.insert(23024);
    DimenSionalRegion.insert(23025);
    DimenSionalRegion.insert(23026);
    DimenSionalRegion.insert(23027);
    DimenSionalRegion.insert(23028);
    DimenSionalRegion.insert(23029);
    DimenSionalRegion.insert(23030);
    DimenSionalRegion.insert(23031);
    DimenSionalRegion.insert(23275);
    DimenSionalRegion.insert(23276);
    DimenSionalRegion.insert(23277);
    DimenSionalRegion.insert(23278);
    DimenSionalRegion.insert(23279);
    DimenSionalRegion.insert(23280);
    DimenSionalRegion.insert(23281);
    DimenSionalRegion.insert(23282);
    DimenSionalRegion.insert(23283);
    DimenSionalRegion.insert(23284);
    DimenSionalRegion.insert(23285);
    DimenSionalRegion.insert(23286);
    DimenSionalRegion.insert(23287);
    DimenSionalRegion.insert(23531);
    DimenSionalRegion.insert(23532);
    DimenSionalRegion.insert(23533);
    DimenSionalRegion.insert(23534);
    DimenSionalRegion.insert(23535);
    DimenSionalRegion.insert(23536);
    DimenSionalRegion.insert(23537);
    DimenSionalRegion.insert(23538);
    DimenSionalRegion.insert(23539);
    DimenSionalRegion.insert(23540);
    DimenSionalRegion.insert(23541);
    DimenSionalRegion.insert(23542);
    DimenSionalRegion.insert(23543);
    DimenSionalRegion.insert(23787);
    DimenSionalRegion.insert(23788);
    DimenSionalRegion.insert(23789);
    DimenSionalRegion.insert(23790);
    DimenSionalRegion.insert(23791);
    DimenSionalRegion.insert(23792);
    DimenSionalRegion.insert(23793);
    DimenSionalRegion.insert(23794);
    DimenSionalRegion.insert(23795);
    DimenSionalRegion.insert(23796);
    DimenSionalRegion.insert(23797);
    DimenSionalRegion.insert(23798);
    DimenSionalRegion.insert(23799);
    DimenSionalRegion.insert(24043);
    DimenSionalRegion.insert(24044);
    DimenSionalRegion.insert(24045);
    DimenSionalRegion.insert(24046);
    DimenSionalRegion.insert(24047);
    DimenSionalRegion.insert(24048);
    DimenSionalRegion.insert(24049);
    DimenSionalRegion.insert(24050);
    DimenSionalRegion.insert(24051);
    DimenSionalRegion.insert(24052);
    DimenSionalRegion.insert(24053);
    DimenSionalRegion.insert(24054);
    DimenSionalRegion.insert(24055);
    DimenSionalRegion.insert(24299);
    DimenSionalRegion.insert(24300);
    DimenSionalRegion.insert(24301);
    DimenSionalRegion.insert(24302);
    DimenSionalRegion.insert(24303);
    DimenSionalRegion.insert(24304);
    DimenSionalRegion.insert(24305);
    DimenSionalRegion.insert(24306);
    DimenSionalRegion.insert(24307);
    DimenSionalRegion.insert(24308);
    DimenSionalRegion.insert(24309);
    DimenSionalRegion.insert(24310);
    DimenSionalRegion.insert(24311);
    DimenSionalRegion.insert(24555);
    DimenSionalRegion.insert(24556);
    DimenSionalRegion.insert(24557);
    DimenSionalRegion.insert(24558);
    DimenSionalRegion.insert(24559);
    DimenSionalRegion.insert(24560);
    DimenSionalRegion.insert(24561);
    DimenSionalRegion.insert(24562);
    DimenSionalRegion.insert(24563);
    DimenSionalRegion.insert(24564);
    DimenSionalRegion.insert(24565);
    DimenSionalRegion.insert(24566);
    DimenSionalRegion.insert(24567);
}
bool DoesFileExists(const std::string &name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

void RegisterObject(const CGfxRuntimeClass *obj) {
    register_objects.push_back(obj);
}

void OverrideObject(overrideFnPtr fn) {
    override_objects.push_back(fn);
}

void InstallRuntimeClasses(CGame *) {
    // Replace Create & Delete for existing classes
    // Note: We can't just inject existing objects like we would do with new objects.
    //       Joymax uses == on GFX_RUNTIME_CLASS(), so we would end up breaking this comparison

    for (std::vector<const CGfxRuntimeClass *>::const_iterator it = register_objects.begin();
         it != register_objects.end(); ++it) {
        reinterpret_cast<void (__thiscall *)(const CGfxRuntimeClass *, const char *, void *, void *,const CGfxRuntimeClass *, size_t, int)>(0x00B9C9C0)(*it,(*it)->m_lpszClassName, (*it)->m_pfnCreateObject, (*it)->m_pfnDeleteObject, (*it)->m_pBaseClass, (*it)->m_nObjectSize, 0);
    }

    for (std::vector<overrideFnPtr>::const_iterator it = override_objects.begin(); it != override_objects.end(); ++it) {
        (*it)();
    }
}
void SilkPosToSimplePos(D3DVECTOR& location, uregion region) {
    //r x= z
    //r y=x
    if (region.single.x != 0x80) {
        location.x = region.single.y * 1920 + location.x;
        location.z = region.single.x * 1920 + location.z;
    }
}
void SimplePosToSilkPos(D3DVECTOR& location, uregion& region) {
    if (region.single.x != 0x80) {
        region.single.x = location.z / 1920;
        region.single.y = location.x / 1920;
        location.x = (int)location.x % 1920;
        location.z = (int)location.z % 1920;

    }
}
void GetSilkPos(uregion dis, D3DVECTOR& location) {
    float offsetZ=0,offsetX = 0;
    offsetX = abs((g_pCICPlayer->GetRegion().single.y - dis.single.y) * 1920);
    offsetZ = abs((g_pCICPlayer->GetRegion().single.x - dis.single.x) * 1920);
    if (g_pCICPlayer->GetRegion().single.y - dis.single.y < 0) {
        location.x = location.x + offsetX;
    }
    else if(g_pCICPlayer->GetRegion().single.y - dis.single.y > 0) {

        location.x = location.x-offsetX;
    }
    if (g_pCICPlayer->GetRegion().single.x - dis.single.x< 0) {
        location.z = location.z + offsetZ;

    }
    else if(g_pCICPlayer->GetRegion().single.x - dis.single.x > 0) {
        location.z = location.z-offsetZ;
    }
}
D3DVECTOR GetSilkPosD3D(uregion dis, D3DVECTOR location) {
    float offsetZ = 0, offsetX = 0;
    offsetX = abs((g_pCICPlayer->GetRegion().single.y - dis.single.y) * 1920);
    offsetZ = abs((g_pCICPlayer->GetRegion().single.x - dis.single.x) * 1920);
    if (g_pCICPlayer->GetRegion().single.y - dis.single.y < 0) {
        location.x = location.x + offsetX;
    }
    else if (g_pCICPlayer->GetRegion().single.y - dis.single.y > 0) {

        location.x = location.x - offsetX;
    }
    if (g_pCICPlayer->GetRegion().single.x - dis.single.x < 0) {
        location.z = location.z + offsetZ;

    }
    else if (g_pCICPlayer->GetRegion().single.x - dis.single.x > 0) {
        location.z = location.z - offsetZ;
    }
    return location;
}

double determinant(double v1, double v2, double v3, double v4)  // ÐÐÁÐÊ½
{
    return (v1 * v4 - v2 * v3);
}

bool intersect(D3DXVECTOR2 aa, D3DXVECTOR2 bb, D3DXVECTOR2 cc, D3DXVECTOR2 dd)
{
    double delta = determinant(bb.x - aa.x, cc.x - dd.x, bb.y - aa.y, cc.y - dd.y);
    if (delta <= (1e-6) && delta >= -(1e-6))  // delta=0£¬±íÊ¾Á½Ïß¶ÎÖØºÏ»òÆ½ÐÐ
    {
        return false;
    }
    double namenda = determinant(cc.x - aa.x, cc.x - dd.x, cc.y - aa.y, cc.y - dd.y) / delta;
    if (namenda > 1 || namenda < 0)
    {
        return false;
    }
    double miu = determinant(bb.x - aa.x, cc.x - aa.x, bb.y - aa.y, cc.y - aa.y) / delta;
    if (miu > 1 || miu < 0)
    {
        return false;
    }
    return true;
}
bool ObjIntersect(CIObject* Src, CIObject* Dis)
{
    /*   LocationInfo l1 = { 0, 0, 0, 0 };
       l1.pos = Src->GetLocation();
       l1.region = Src->GetRegion();
       l1.field_0 = Src->m_navcell;
       l1.field_1 = Src->m_object_under_foot;
       LocationInfo l2 = { 0, 0, 0,0 };
       l1.pos = Dis->GetLocation();
       l1.region = Dis->GetRegion();

       return !g_CRegionManagerBody.SomethingWithMapCollision_MAYBE(1, 1, &l1, &l2, 0, g_pCICPlayer);*/
    CGFXVideo3d* gfx = CGFXVideo3d::get();

    for (std::map<short, CRTNavMeshTerrain*>::iterator mit = Rebot::CRTNavMeshTerrainAll.begin();
         mit != Rebot::CRTNavMeshTerrainAll.end(); ++mit)
    {
        CRTNavMeshTerrain* m_pNavmesh = mit->second;
        BYTE bHIGH, bLow;
        bHIGH = m_pNavmesh->m_Region >> 8;
        bLow = m_pNavmesh->m_Region & 0xFF;
        //printf("%d,%d,%d\r\n",m_pNavmesh->m_Region, bHIGH,bLow);
        uregion reg;
        reg.single.x = bHIGH;
        reg.single.y = bLow;
        for (std::vector<SNavMeshInst*>::iterator it = m_pNavmesh->m_sObjList.begin();
             it != m_pNavmesh->m_sObjList.end(); ++it) {
            SNavMeshInst* pInst = *it;
            CRTNavMeshObj* pObj = pInst->m_pObject;
            const D3DXVECTOR3& offset = pInst->m_sObj.Offset;
            float yaw = -pInst->m_sObj.Yaw;

            for (std::vector<PrimNavMeshEdge>::iterator it = pObj->m_GlobalEdges.begin();

                 it != pObj->m_GlobalEdges.end(); ++it) {
                PrimNavMeshEdge& edge = *it;
                if (edge.btFlag == EDGE_FLAG_BLOCKED) {
                    D3DXVECTOR3 p1, p2, p1_2d, p2_2d, p3_2d, p4_2d;
                    p1 = edge.AssocVertex[0]->Position;
                    rotatey(p1, yaw);
                    p1 += offset;


                    p2 = edge.AssocVertex[1]->Position;
                    rotatey(p2, yaw);
                    p2 += offset;

                    D3DXVECTOR2 aa, bb, cc, dd;

                    D3DXVECTOR3 a3 = Src->GetLocation();
                    D3DXVECTOR3 b3 = Dis->GetLocation();
                    GetSilkPos(reg, p1);
                    GetSilkPos(reg, p2);
                    GetSilkPos(Src->GetRegion(), a3);
                    GetSilkPos(Dis->GetRegion(), b3);
                    aa.x = a3.x, aa.y = a3.z,
                    bb.x = b3.x, bb.y = b3.z,
                    cc.x = p1.x, cc.y = p1.z,
                    dd.x = p2.x, dd.y = p2.z;
                    if (intersect(aa, bb, cc, dd)) {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}
bool ObjIntersect(uregion SrcRegion, D3DVECTOR SrcLocation, uregion TargetRegion, D3DVECTOR TargetLocation)
{
    /*   LocationInfo l1 = { 0, 0, 0, 0 };
       l1.pos = Src->GetLocation();
       l1.region = Src->GetRegion();
       l1.field_0 = Src->m_navcell;
       l1.field_1 = Src->m_object_under_foot;
       LocationInfo l2 = { 0, 0, 0,0 };
       l1.pos = Dis->GetLocation();
       l1.region = Dis->GetRegion();

       return !g_CRegionManagerBody.SomethingWithMapCollision_MAYBE(1, 1, &l1, &l2, 0, g_pCICPlayer);*/
    CGFXVideo3d* gfx = CGFXVideo3d::get();

    for (std::map<short, CRTNavMeshTerrain*>::iterator mit = Rebot::CRTNavMeshTerrainAll.begin();
         mit != Rebot::CRTNavMeshTerrainAll.end(); ++mit)
    {
        CRTNavMeshTerrain* m_pNavmesh = mit->second;
        BYTE bHIGH, bLow;
        bHIGH = m_pNavmesh->m_Region >> 8;
        bLow = m_pNavmesh->m_Region & 0xFF;
        //printf("%d,%d,%d\r\n",m_pNavmesh->m_Region, bHIGH,bLow);
        uregion reg;
        reg.single.x = bHIGH;
        reg.single.y = bLow;
        for (std::vector<SNavMeshInst*>::iterator it = m_pNavmesh->m_sObjList.begin();
             it != m_pNavmesh->m_sObjList.end(); ++it) {
            SNavMeshInst* pInst = *it;
            CRTNavMeshObj* pObj = pInst->m_pObject;
            const D3DXVECTOR3& offset = pInst->m_sObj.Offset;
            float yaw = -pInst->m_sObj.Yaw;

            for (std::vector<PrimNavMeshEdge>::iterator it = pObj->m_GlobalEdges.begin();

                 it != pObj->m_GlobalEdges.end(); ++it) {
                PrimNavMeshEdge& edge = *it;
                if (edge.btFlag == EDGE_FLAG_BLOCKED) {
                    D3DXVECTOR3 p1, p2, p1_2d, p2_2d, p3_2d, p4_2d;
                    p1 = edge.AssocVertex[0]->Position;
                    rotatey(p1, yaw);
                    p1 += offset;


                    p2 = edge.AssocVertex[1]->Position;
                    rotatey(p2, yaw);
                    p2 += offset;

                    D3DXVECTOR2 aa, bb, cc, dd;

                    GetSilkPos(reg, p1);
                    GetSilkPos(reg, p2);
                    GetSilkPos(SrcRegion, SrcLocation);
                    GetSilkPos(TargetRegion,TargetLocation);
                    aa.x = SrcLocation.x, aa.y = SrcLocation.z,
                    bb.x = TargetLocation.x, bb.y = TargetLocation.z,
                    cc.x = p1.x, cc.y = p1.z,
                    dd.x = p2.x, dd.y = p2.z;
                    if (intersect(aa, bb, cc, dd)) {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}
std::string string_To_UTF8(const std::string& str)
{
    int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

    wchar_t* pwBuf = new wchar_t[nwLen + 1];//һ��Ҫ��1����Ȼ�����β��
    ZeroMemory(pwBuf, nwLen * 2 + 2);

    ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

    int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

    char* pBuf = new char[nLen + 1];
    ZeroMemory(pBuf, nLen + 1);

    ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

    std::string retStr(pBuf);

    delete[]pwBuf;
    delete[]pBuf;

    pwBuf = NULL;
    pBuf = NULL;

    return retStr;
}


std::deque<int> unicode_to_utf8(int charcode)
{
    std::deque<int> d;
    if (charcode < 128)
    {
        d.push_back(charcode);
    }
    else
    {
        int first_bits = 6;
        const int other_bits = 6;
        int first_val = 0xC0;
        int t = 0;
        while (charcode >= (1 << first_bits))
        {
            {
                t = 128 | (charcode & ((1 << other_bits)-1));
                charcode >>= other_bits;
                first_val |= 1 << (first_bits);
                first_bits--;
            }
            d.push_front(t);
        }
        t = first_val | charcode;
        d.push_front(t);
    }
    return d;
}


int utf8_to_unicode(std::deque<int> &coded)
{
    int charcode = 0;
    int t = coded.front();
    coded.pop_front();
    if (t < 128)
    {
        return t;
    }
    int high_bit_mask = (1 << 6) -1;
    int high_bit_shift = 0;
    int total_bits = 0;
    const int other_bits = 6;
    while((t & 0xC0) == 0xC0)
    {
        t <<= 1;
        t &= 0xff;
        total_bits += 6;
        high_bit_mask >>= 1;
        high_bit_shift++;
        charcode <<= other_bits;
        charcode |= coded.front() & ((1 << other_bits)-1);
        coded.pop_front();
    }
    charcode |= ((t >> high_bit_shift) & high_bit_mask) << total_bits;
    return charcode;
}

void showhideEmoji(bool Show,int Index,int totalIndexes,int width,int height,int usedIndexes,std::string emoji,int emojiIndex)
{


    int fakeIndex = 0;
    if(usedIndexes < totalIndexes)
    {
        fakeIndex = Index + totalIndexes - usedIndexes;
        height = height + (fakeIndex)*14;
    }
    else
        height = height + (Index)*14;
    for (std::map<int, CIFCustomRankSlot*>::iterator it = chatSlots.begin();
         it != chatSlots.end(); ++it) {
        if(it->first == Index +201)
        {
            if(Show)
            {
                it->second->ShowGWnd(true);
                switch(emojiIndex)
                {
                    case 0:
                        it->second->m_custom_label1->SetGWndSize(16,16);
                        it->second->m_custom_label1->MoveGWnd(width,height);
                        it->second->m_custom_label1->ShowGWnd(true);
                        it->second->m_custom_label1->TB_Func_13x(emoji,0,0);
                        break;
                    case 1:
                        it->second->m_custom_label2->SetGWndSize(16,16);

                        it->second->m_custom_label2->MoveGWnd(width,height);
                        it->second->m_custom_label2->ShowGWnd(true);
                        it->second->m_custom_label2->TB_Func_13x(emoji,0,0);
                        break;
                    case 2:
                        it->second->m_custom_label3->SetGWndSize(16,16);

                        it->second->m_custom_label3->MoveGWnd(width,height);
                        it->second->m_custom_label3->ShowGWnd(true);
                        it->second->m_custom_label3->TB_Func_13x(emoji,0,0);
                        break;
                    case 3:
                        it->second->m_custom_label4->SetGWndSize(16,16);

                        it->second->m_custom_label4->MoveGWnd(width,height);
                        it->second->m_custom_label4->ShowGWnd(true);
                        it->second->m_custom_label4->TB_Func_13x(emoji,0,0);
                        break;
                    case 4:
                        it->second->m_custom_label5->SetGWndSize(16,16);

                        it->second->m_custom_label5->MoveGWnd(width,height);
                        it->second->m_custom_label5->ShowGWnd(true);
                        it->second->m_custom_label5->TB_Func_13x(emoji,0,0);
                        break;
                }
                break;
            }
            else
            {
                it->second->m_custom_label1->ShowGWnd(false);
                it->second->m_custom_label2->ShowGWnd(false);
                it->second->m_custom_label3->ShowGWnd(false);
                it->second->m_custom_label4->ShowGWnd(false);
                it->second->m_custom_label5->ShowGWnd(false);

            }

        }
    }
}
void hideEmojis()
{
    for (std::map<int, CIFCustomRankSlot*>::iterator it = chatSlots.begin();
         it != chatSlots.end(); ++it) {
        it->second->showEmojis(false);
    }

}
bool isRendered = false;
void renderchatStatics(CIFChatViewer* chatView)
{
    if(!isRendered && chatView && chatView->IsVisible())
    {
        isRendered = true;
        emojiList.insert(std::pair<std::string, std::string>(":P","interface\\emoji\\tongue.ddj"));
        emojiList.insert(std::pair<std::string, std::string>(":D","interface\\emoji\\smile2.ddj"));
        emojiList.insert(std::pair<std::string, std::string>(":)","interface\\emoji\\smile1.ddj"));
        emojiList.insert(std::pair<std::string, std::string>(":S","interface\\emoji\\sleepy.ddj"));
        emojiList.insert(std::pair<std::string, std::string>(":(","interface\\emoji\\sad.ddj"));
        emojiList.insert(std::pair<std::string, std::string>(":o","interface\\emoji\\ooo.ddj"));
        emojiList.insert(std::pair<std::string, std::string>(":O","interface\\emoji\\mouth.ddj"));
        emojiList.insert(std::pair<std::string, std::string>(":L","interface\\emoji\\laugh.ddj"));
        emojiList.insert(std::pair<std::string, std::string>(":k","interface\\emoji\\kekw.ddj"));
        emojiList.insert(std::pair<std::string, std::string>(":I","interface\\emoji\\instagram.ddj"));
        emojiList.insert(std::pair<std::string, std::string>(":h","interface\\emoji\\huh.ddj"));
        emojiList.insert(std::pair<std::string, std::string>("<3","interface\\emoji\\heart.ddj"));
        emojiList.insert(std::pair<std::string, std::string>(":C","interface\\emoji\\corona.ddj"));
        emojiList.insert(std::pair<std::string, std::string>(":f","interface\\emoji\\facebook.ddj"));
        emojiList.insert(std::pair<std::string, std::string>(":d","interface\\emoji\\discord.ddj"));
        emojiList.insert(std::pair<std::string, std::string>(":b","interface\\emoji\\boii.ddj"));
        emojiList.insert(std::pair<std::string, std::string>(":A","interface\\emoji\\angry.ddj"));
        RECT onlineRect = { 18,74,24,24 };
        CIFCustomRankSlot*  emojiLine1 = (CIFCustomRankSlot*)CGWnd::CreateInstance(chatView, GFX_RUNTIME_CLASS(CIFCustomRankSlot), onlineRect, 201, 0);
        CIFCustomRankSlot*  emojiLine2 = (CIFCustomRankSlot*)CGWnd::CreateInstance(chatView, GFX_RUNTIME_CLASS(CIFCustomRankSlot), onlineRect, 202, 0);
        CIFCustomRankSlot*  emojiLine3 = (CIFCustomRankSlot*)CGWnd::CreateInstance(chatView, GFX_RUNTIME_CLASS(CIFCustomRankSlot), onlineRect, 203, 0);
        CIFCustomRankSlot*  emojiLine4 = (CIFCustomRankSlot*)CGWnd::CreateInstance(chatView, GFX_RUNTIME_CLASS(CIFCustomRankSlot), onlineRect, 204, 0);
        CIFCustomRankSlot*  emojiLine5 = (CIFCustomRankSlot*)CGWnd::CreateInstance(chatView, GFX_RUNTIME_CLASS(CIFCustomRankSlot), onlineRect, 205, 0);
        CIFCustomRankSlot*  emojiLine6 = (CIFCustomRankSlot*)CGWnd::CreateInstance(chatView, GFX_RUNTIME_CLASS(CIFCustomRankSlot), onlineRect, 206, 0);
        CIFCustomRankSlot*  emojiLine7 = (CIFCustomRankSlot*)CGWnd::CreateInstance(chatView, GFX_RUNTIME_CLASS(CIFCustomRankSlot), onlineRect, 207, 0);
        CIFCustomRankSlot*  emojiLine8 = (CIFCustomRankSlot*)CGWnd::CreateInstance(chatView, GFX_RUNTIME_CLASS(CIFCustomRankSlot), onlineRect, 208, 0);
        CIFCustomRankSlot*  emojiLine9 = (CIFCustomRankSlot*)CGWnd::CreateInstance(chatView, GFX_RUNTIME_CLASS(CIFCustomRankSlot), onlineRect, 209, 0);
        CIFCustomRankSlot*  emojiLine10 = (CIFCustomRankSlot*)CGWnd::CreateInstance(chatView, GFX_RUNTIME_CLASS(CIFCustomRankSlot), onlineRect, 210, 0);
        CIFCustomRankSlot*  emojiLine11 = (CIFCustomRankSlot*)CGWnd::CreateInstance(chatView, GFX_RUNTIME_CLASS(CIFCustomRankSlot), onlineRect, 211, 0);
        CIFCustomRankSlot*  emojiLine12 = (CIFCustomRankSlot*)CGWnd::CreateInstance(chatView, GFX_RUNTIME_CLASS(CIFCustomRankSlot), onlineRect, 212, 0);
        CIFCustomRankSlot*  emojiLine13 = (CIFCustomRankSlot*)CGWnd::CreateInstance(chatView, GFX_RUNTIME_CLASS(CIFCustomRankSlot), onlineRect, 213, 0);
        CIFCustomRankSlot*  emojiLine14 = (CIFCustomRankSlot*)CGWnd::CreateInstance(chatView, GFX_RUNTIME_CLASS(CIFCustomRankSlot), onlineRect, 214, 0);
        CIFCustomRankSlot*  emojiLine15 = (CIFCustomRankSlot*)CGWnd::CreateInstance(chatView, GFX_RUNTIME_CLASS(CIFCustomRankSlot), onlineRect, 215, 0);
        CIFCustomRankSlot*  emojiLine16 = (CIFCustomRankSlot*)CGWnd::CreateInstance(chatView, GFX_RUNTIME_CLASS(CIFCustomRankSlot), onlineRect, 216, 0);
        CIFCustomRankSlot*  emojiLine17 = (CIFCustomRankSlot*)CGWnd::CreateInstance(chatView, GFX_RUNTIME_CLASS(CIFCustomRankSlot), onlineRect, 217, 0);
        CIFCustomRankSlot*  emojiLine18 = (CIFCustomRankSlot*)CGWnd::CreateInstance(chatView, GFX_RUNTIME_CLASS(CIFCustomRankSlot), onlineRect, 218, 0);
        CIFCustomRankSlot*  emojiLine19 = (CIFCustomRankSlot*)CGWnd::CreateInstance(chatView, GFX_RUNTIME_CLASS(CIFCustomRankSlot), onlineRect, 219, 0);
        CIFCustomRankSlot*  emojiLine20 = (CIFCustomRankSlot*)CGWnd::CreateInstance(chatView, GFX_RUNTIME_CLASS(CIFCustomRankSlot), onlineRect, 220, 0);
        CIFCustomRankSlot*  emojiLine21 = (CIFCustomRankSlot*)CGWnd::CreateInstance(chatView, GFX_RUNTIME_CLASS(CIFCustomRankSlot), onlineRect, 221, 0);
        CIFCustomRankSlot*  emojiLine22 = (CIFCustomRankSlot*)CGWnd::CreateInstance(chatView, GFX_RUNTIME_CLASS(CIFCustomRankSlot), onlineRect, 222, 0);
        CIFCustomRankSlot*  emojiLine23 = (CIFCustomRankSlot*)CGWnd::CreateInstance(chatView, GFX_RUNTIME_CLASS(CIFCustomRankSlot), onlineRect, 223, 0);
        CIFCustomRankSlot*  emojiLine24 = (CIFCustomRankSlot*)CGWnd::CreateInstance(chatView, GFX_RUNTIME_CLASS(CIFCustomRankSlot), onlineRect, 224, 0);
        //no clue why isn't working //map instead
        //        for(int i =201; i<=224;i++)
//        {
//            CIFWnd *emojiLine = chatView->m_IRM.GetResObj<CIFWnd>(i, 1);
//            if(emojiLine)
//            {
//                printf("000000\n");
//            }
//        }
        chatSlots.insert(std::pair<int, CIFCustomRankSlot*>(201,emojiLine1));
        chatSlots.insert(std::pair<int, CIFCustomRankSlot*>(202,emojiLine2));
        chatSlots.insert(std::pair<int, CIFCustomRankSlot*>(203,emojiLine3));
        chatSlots.insert(std::pair<int, CIFCustomRankSlot*>(204,emojiLine4));
        chatSlots.insert(std::pair<int, CIFCustomRankSlot*>(205,emojiLine5));
        chatSlots.insert(std::pair<int, CIFCustomRankSlot*>(206,emojiLine6));
        chatSlots.insert(std::pair<int, CIFCustomRankSlot*>(207,emojiLine7));
        chatSlots.insert(std::pair<int, CIFCustomRankSlot*>(208,emojiLine8));
        chatSlots.insert(std::pair<int, CIFCustomRankSlot*>(209,emojiLine9));
        chatSlots.insert(std::pair<int, CIFCustomRankSlot*>(210,emojiLine10));
        chatSlots.insert(std::pair<int, CIFCustomRankSlot*>(211,emojiLine11));
        chatSlots.insert(std::pair<int, CIFCustomRankSlot*>(212,emojiLine12));
        chatSlots.insert(std::pair<int, CIFCustomRankSlot*>(213,emojiLine13));
        chatSlots.insert(std::pair<int, CIFCustomRankSlot*>(214,emojiLine14));
        chatSlots.insert(std::pair<int, CIFCustomRankSlot*>(215,emojiLine15));
        chatSlots.insert(std::pair<int, CIFCustomRankSlot*>(216,emojiLine16));
        chatSlots.insert(std::pair<int, CIFCustomRankSlot*>(217,emojiLine17));
        chatSlots.insert(std::pair<int, CIFCustomRankSlot*>(218,emojiLine18));
        chatSlots.insert(std::pair<int, CIFCustomRankSlot*>(219,emojiLine19));
        chatSlots.insert(std::pair<int, CIFCustomRankSlot*>(220,emojiLine20));
        chatSlots.insert(std::pair<int, CIFCustomRankSlot*>(221,emojiLine21));
        chatSlots.insert(std::pair<int, CIFCustomRankSlot*>(222,emojiLine22));
        chatSlots.insert(std::pair<int, CIFCustomRankSlot*>(223,emojiLine23));
        chatSlots.insert(std::pair<int, CIFCustomRankSlot*>(224,emojiLine24));
        hideEmojis();
    }
}
int getstringWidth(std::n_wstring str,CIFListCtrl* pList,std::string emojiCode,int index)
{
    std::n_wstring tempStr;
    CIFListCtrl::SLineOfText* tempLine;
    int Width=0;
    std::n_wstring tempText = str.substr(0, index);
    if(pList)
    {
        tempLine = pList->GetTextByIndex(0);
        if(tempLine)
        {
            CGFontTexture* cgFont = tempLine->m_font;
            if(cgFont)
            {
                cgFont->GetText(&tempStr);
                cgFont->sub_8B3B60(&tempText);
                Width = cgFont->GetDimensions().width;
                cgFont->sub_8B3B60(&tempStr);
            }
        }
    }
    return Width;
}
std::wstring get_string(std::wstring res) {

    //????????

    int r = res.find('\r\n');
    while (r != std::wstring::npos)
    {
        if (r != std::wstring::npos)
        {
            res.replace(r, 1, L"");
            r = res.find('\r\n');
        }
    }

    //?????????

    res.erase(std::remove_if(res.begin(), res.end(), ::isspace), res.end());

    return res;

}
std::wstring ReadFromClipBoard()
{
    ::OpenClipboard(theApp.GetHWnd());
    HANDLE hClipMemory = ::GetClipboardData(CF_TEXT);
    DWORD dwLength = GlobalSize(hClipMemory);
    LPBYTE lpClipMemory = (LPBYTE)GlobalLock(hClipMemory);
    std::wstring rtnstr = get_string(acp_decode((char*)lpClipMemory, dwLength));
    GlobalUnlock(hClipMemory);
    ::CloseClipboard();

    return rtnstr;
}

void emojiHandler()
{
    //todo make a copy of chatBox to remove the emojiCodes
    //todo remove renderchatStatics and replace it with initiate function
    //todo hook d3d instead ? causing some crashs rofl
    CIFChatViewer* chatView = (CIFChatViewer*)g_pCGInterface->m_IRM.GetResObj(1, 1);
    CIFListCtrl::SLineOfText* line;
    std::n_wstring str,tempStr;
    if(chatView && chatView->IsVisible())
    {
        renderchatStatics(chatView);
        CIFTextBox* chatBox = (CIFTextBox*)chatView->m_IRM.GetResObj(30, 1);
        if(!chatBox || !chatBox->IsVisible())
        {
            for(int i=16;i<=19;i++)
            {
                chatBox = (CIFTextBox*)chatView->m_IRM.GetResObj(i, 1);
                if(chatBox && chatBox->IsVisible())
                    break;
            }
        }
        if(chatBox && chatBox->IsVisible())
        {
            CIFListCtrl* pList = chatView->m_CurrentActiveChatlist;
            if(pList)
            {
                int totalIndexes = *(int*)((int)pList + 0x3A4);
                int firstAppearIndexAlt = *(int*)((int)pList + 0x380);
                int renderReferenceAlt = pList->GetNumberOfItems() - totalIndexes;
                //todo replace it with events
                if(firstAppearIndexAlt != firstAppearIndex || renderReferenceAlt !=renderReference)
                {
                    firstAppearIndex = firstAppearIndexAlt;
                    renderReference = renderReferenceAlt;
                    if(chatView->GetSize().height < 50)
                        hideEmojis();
                    else {
                        for (int i = firstAppearIndexAlt; i < firstAppearIndexAlt + totalIndexes; i++) {
                            showhideEmoji(false, i - firstAppearIndexAlt, totalIndexes,
                                          0,
                                          0, pList->GetNumberOfItems(), "",0);
                            bool found = false;
                            line = pList->GetTextByIndex(i);
                            if (line) {
                                int k =0;
                                line->m_font->GetText(&str);
                                if (!str.empty()) {
                                    for (std::map<string, string>::iterator it = emojiList.begin();
                                         it != emojiList.end(); ++it) {
                                        if (str.rfind(TO_WSTRING(it->first).c_str()) != std::string::npos) {
                                            for (int j = 0; j < str.length(); j++) {
                                                if(k ==5)
                                                    break;
                                                if (str.substr(j, TO_WSTRING(it->first).length()) == TO_WSTRING(it->first).c_str()) {
                                                    std::n_wstring charBefore = str.substr(j - 1, 1);
                                                    std::n_wstring charAfter = str.substr(j + 2, 1);
                                                    if ((charBefore == L" " || charBefore == L":") &&
                                                        (charAfter == L" " || charAfter.empty())) {
                                                        int width = getstringWidth(str, pList, it->first,j);
                                                        showhideEmoji(true, i - firstAppearIndexAlt, totalIndexes,
                                                                      chatBox->GetPos().x + width,
                                                                      chatBox->GetPos().y, pList->GetNumberOfItems(), it->second,k);
                                                        k++;
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
        }
    }
}
