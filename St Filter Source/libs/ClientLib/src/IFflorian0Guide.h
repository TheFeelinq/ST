#pragma once
#include "IFDecoratedStatic.h"


#define GUIDE_FLORIAN0 13378
struct TitleData
{
    std::n_wstring charname;
    std::n_wstring Title;
    D3DCOLOR titlecolor;
    std::n_wstring NameTitle;
    D3DCOLOR namecolor;
};

class CIFflorian0Guide : public CIFDecoratedStatic
{
	GFX_DECLARE_DYNCREATE(CIFflorian0Guide)



public:

	bool OnCreate(long ln) override;
	int OnMouseLeftUp(int a1, int x, int y) override;
	void OnCIFReady() override;
    void OnUpdate() override;
    int loop;
    int loopcheck;
    int img;

    static std::map<std::n_wstring,TitleData*> TitleDataList;
};
