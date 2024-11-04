#pragma once

#include "IFStatic.h"

class CIFDecoratedStatic : public CIFStatic
{
	GFX_DECLARE_DYNAMIC_EXISTING(CIFDecoratedStatic, 0x00EE94F8)

public:
	bool OnCreate(long ln) override;
	void OnUpdate() override;
	void OnTimer(int) override;

	void RenderMyself() override;

	void OnCIFReady() override;
	virtual bool Func_52();

public:
	CIFDecoratedStatic();
	virtual ~CIFDecoratedStatic();

protected:
	void set_N00009BDD(char a1);
	void set_N00009C18(char a1);
protected:
	void set_N00009BD4(char a1);
	void set_N00009BD3(int a1);
    void set_N00009BDC(int a1);
	void sub_634470(std::n_string a1);
    void set_wndsize(int w , int h);
    void set_N00009BFD(std::n_string a1);
    void  set_field_394(int a1);
	void sub_633990();
    void sub_634300();
    std::n_string FUN_00633940();

public:
	int m_uniqueid; //0x0380
	int N00009BD3; //0x0384
	char N00009BD4; //0x0388
	char pad_0389[3]; //0x0389
	int N00009BD5; //0x038C
	int N00009BD8; //0x0390
    int field_394; //0x0394
	int N00009BDC; //0x0398
	char N00009BDD; //0x039C
	char N00009C18; //0x039D
	char pad_039E[2]; //0x039E
	float field_3a0;// 0x03a0
    float field_3a4;// 0x03a4
    float field_3a8;// 0x03a8
    float field_3ac;// 0x03ac
    char pad_03b0[8]; //0x03b0
    float field_3b8;// 0x03b8
    float field_3bc;// 0x03bc
    float field_3c0;// 0x03c0
    float field_3c4;// 0x03c4
    float field_3c8;// 0x03c8
    char pad_03cc[4]; //0x03cc
    float field_3d0;// 0x03d0
    float field_3d4;// 0x03d4
    float field_3d8;// 0x03d8
    float field_3dc;// 0x03dc
    float field_3e0;// 0x03e0
    float field_3e4;// 0x03e4
    float field_3e8;// 0x03e8
    float field_3ec;// 0x03ec
    float field_3f0;// 0x03f0
    float field_3f4;// 0x03f4
    char pad_03f8[4]; //0x03f8
    float field_3fc;// 0x03fc
	int N00009BFC; //0x0400
	std::n_string N00009BFD; //0x0404

    BEGIN_FIXTURE()
        ENSURE_SIZE(1056)
        ENSURE_OFFSET(m_uniqueid, 0x0380)
        ENSURE_OFFSET(N00009BD3, 0x0384)
        ENSURE_OFFSET(N00009BD4, 0x0388)
        ENSURE_OFFSET(field_3fc, 0x03fc)
        ENSURE_OFFSET(N00009BFC, 0x0400)
    END_FIXTURE()
    RUN_FIXTURE(CIFDecoratedStatic)
};
