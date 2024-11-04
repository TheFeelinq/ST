#pragma once

#include "BSLib/BSLib.h"
#include <Game.h>
#include <deque>
#include <IFChatViewer.h>
void Setup();
void AddRegion();
bool DoesFileExists(const std::string &name);

void InstallRuntimeClasses(CGame *);

void RegisterObject(const CGfxRuntimeClass *);

typedef void(*overrideFnPtr)();

extern std::vector<overrideFnPtr> override_objects;

template<typename T, int address>
void OverrideRtClassAt() {
    CGfxRuntimeClass *rt = (CGfxRuntimeClass *) address;

    rt->m_pfnCreateObject = T::CreateObject;
    rt->m_pfnDeleteObject = T::DeleteObject;
}

template<typename T, int address>
void OverrideObject() {
    override_objects.push_back(&OverrideRtClassAt<T, address>);
}
void SilkPosToSimplePos(D3DVECTOR& location, uregion region);
void SimplePosToSilkPos(D3DVECTOR& location, uregion& region);
void GetSilkPos(uregion dis, D3DVECTOR& location);
D3DVECTOR GetSilkPosD3D(uregion dis, D3DVECTOR location);
double determinant(double v1, double v2, double v3, double v4);
bool intersect(D3DXVECTOR2 aa, D3DXVECTOR2 bb, D3DXVECTOR2 cc, D3DXVECTOR2 dd);
bool ObjIntersect(uregion SrcRegion, D3DVECTOR SrcLocation, uregion TargetRegion, D3DVECTOR TargetLocation);
bool ObjIntersect(CIObject* Src, CIObject* Dis);
std::string string_To_UTF8(const std::string& str);
std::deque<int> unicode_to_utf8(int charcode);
int utf8_to_unicode(std::deque<int> &coded);
void renderchatStatics(CIFChatViewer* chatView);
int getstringWidth(std::n_wstring str,CIFListCtrl* pList,std::string emojiCode,int index);
void hideEmojis();
void emojiHandler();
std::wstring ReadFromClipBoard();
std::wstring get_string(std::wstring res);
void setlangEng();
void showhideEmoji(bool Show,int Index,int totalIndexes,int width,int height,int usedIndexes,std::string emoji,int emojiIndex);