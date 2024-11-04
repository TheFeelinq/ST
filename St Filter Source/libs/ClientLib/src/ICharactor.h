#pragma once

#include <ghidra/undefined.h>
#include "IGIDObject.h"
#include "ClassLink.h"
#include "Test/Test.h"
#include <set>
#include "ICharactor_Class1.h"
#include "ICharactor_Class2.h"
#include "ICharactor_Class3.h"
#include "ICharactor_Class4.h"
#include "Data/CharacterData.h"

enum TRIJOB_TYPE : char { /* Job Type of the Player */
    TRIJOB_HUNTER = 3,
    TRIJOB_NOJOB = 4,
    TRIJOB_THIEF = 2,
    TRIJOB_TRADER = 1

};
struct SStatusEffectData {
    int Param1;
    undefined4 Param2;
    undefined4 Param3;
    undefined4 Param4;

};


class CICharactor : public CIGIDObject {
    friend CClassLink<CICharactor>;
public:
    /// \address 009cf1b0
    void Func_15(int param_1, float *param_2) override;
    void Func_15_impl(int param_1, float *param_2);

    /// \address 009cbb90
    void SetName(const std::n_wstring &name, undefined4 show) override;
    virtual void Func_34();

    virtual void Func_35();

    virtual const CCharacterData::SData &Func_36();

    virtual void Func_37();

    virtual void Func_38();

    virtual void Func_39();

    virtual void Func_40();

    virtual void Func_41();

    virtual void Func_42();

    virtual TRIJOB_TYPE GetJobType();

    virtual void SetJobType(TRIJOB_TYPE type);

    virtual void Func_45();

    virtual void Func_46();

    virtual void Func_47();

    virtual void Func_48();

    virtual void Func_49();

    virtual void Func_50();

    virtual void Func_51();

    virtual void Func_52();

    virtual void Func_53();

    virtual void Func_54();


    /// \brief Display the given text message above the entity for a certain amount of time.
    /// \address 009c77c0
    /// \param message The message to be displayed
    /// \param color Color of the letters being displayed
    void ShowMessageAboveEntity(const std::n_wstring &message, D3DCOLOR color);
    unsigned int GetMaxHp() const;

    unsigned int GetCurrentMp() const;

    unsigned int GetMaxMp() const;

    /// \address 009c7880
    unsigned int FUN_009c7880() const;

    DWORD GetObjEffect();
    int GetJobTypes();
    void MakeEffect(UINT32 effectID);
    void RemoveEffect(UINT32 effectID);
public:
    undefined field_0x254;
    undefined field_0x255;
    undefined field_0x256;
    undefined field_0x257;
    undefined field_0x258;
    undefined field_0x259;
    undefined field_0x25a;
    undefined field_0x25b;
    undefined field_0x25c;
    undefined field_0x25d;
    undefined field_0x25e;
    undefined field_0x25f;
    undefined4 field_0x260;
    undefined4 field_0x264;
    undefined4 field_0x268;
    undefined field_0x26c;
    undefined field_0x26d;
    undefined field_0x26e;
    undefined field_0x26f;
    undefined field_0x270;
    undefined1 field_0x271;
    undefined field_0x272;
    undefined field_0x273;
    CClassLink<CICharactor> classLink;
    std::list<void*> decolist;
    std::list<void*> field_0x290;
    undefined4 m_timeOfCreation;
    undefined4 field_0x2a0;
    undefined4 field_0x2a4;
    undefined1 field_0x2a8;
    undefined1 field_0x2a9;
    undefined field_0x2aa;
    undefined field_0x2ab;
    undefined4 field_0x2ac;
    undefined4 field_0x2b0;
    std::set<CIEntity*> field_0x2b4;
    undefined1 field_0x2c0;
    undefined1 field_0x2c1;
    undefined1 field_0x2c2;
    undefined1 field_0x2c3;
    unsigned int m_illness; //illness
public:
    std::map<int, SStatusEffectData> field_0x2c8; // so luong buff
private:
    undefined field_0x2d4;
    undefined field_0x2d5;
    undefined field_0x2d6;
    undefined field_0x2d7;
    undefined4 field_0x2d8;
    undefined4 field_0x2dc;
    undefined4 field_0x2e0;
    undefined1 field_0x2e4;
    undefined field_0x2e5;
    undefined field_0x2e6;
    undefined field_0x2e7;
    undefined field_0x2e8[0x40];
    undefined field_0x328[0x28];
    float field_0x350;
    float field_0x354;
    undefined field_0x358;
    undefined field_0x359;
    undefined field_0x35a;
    undefined field_0x35b;
    undefined field_0x35c;
    undefined field_0x35d;
    undefined field_0x35e;
    undefined field_0x35f;
    undefined field_0x360;
    undefined field_0x361;
    undefined field_0x362;
    undefined field_0x363;
    undefined field_0x364;
    undefined field_0x365;
    undefined field_0x366;
    undefined field_0x367;
    undefined1 field_0x368;
    undefined field_0x369;
    undefined field_0x36a;
    undefined field_0x36b;
    undefined field_0x36c;
    undefined field_0x36d;
    undefined field_0x36e;
    undefined field_0x36f;
    undefined field_0x370;
    undefined field_0x371;
    undefined field_0x372;
    undefined field_0x373;
    undefined field_0x374;
    undefined field_0x375;
    undefined field_0x376;
    undefined field_0x377;
    undefined field_0x378;
    undefined field_0x379;
    undefined field_0x37a;
    undefined field_0x37b;
    undefined field_0x37c;
    undefined field_0x37d;
    undefined field_0x37e;
    undefined field_0x37f;
    undefined field_0x380;
    undefined field_0x381;
    undefined field_0x382;
    undefined field_0x383;
    undefined field_0x384;
    undefined field_0x385;
    undefined field_0x386;
    undefined field_0x387;
    undefined field_0x388;
    undefined field_0x389;
    undefined field_0x38a;
    undefined field_0x38b;
    undefined field_0x38c;
    undefined field_0x38d;
    undefined field_0x38e;
    undefined field_0x38f;
    undefined field_0x390;
    undefined field_0x391;
    undefined field_0x392;
    undefined field_0x393;
    undefined field_0x394;
    undefined field_0x395;
    undefined field_0x396;
    undefined field_0x397;
    undefined field_0x398;
    undefined field_0x399;
    undefined field_0x39a;
    undefined field_0x39b;
    undefined field_0x39c;
    undefined field_0x39d;
    undefined field_0x39e;
    undefined field_0x39f;
    undefined field_0x3a0;
    undefined field_0x3a1;
    undefined field_0x3a2;
    undefined field_0x3a3;
    undefined field_0x3a4;
    undefined field_0x3a5;
    undefined field_0x3a6;
    undefined field_0x3a7;
    undefined field_0x3a8;
    undefined field_0x3a9;
    undefined field_0x3aa;
    undefined field_0x3ab;
    undefined field_0x3ac;
    undefined field_0x3ad;
    undefined field_0x3ae;
    undefined field_0x3af;
    undefined field_0x3b0;
    undefined field_0x3b1;
    undefined field_0x3b2;
    undefined field_0x3b3;
    undefined field_0x3b4;
    undefined field_0x3b5;
    undefined field_0x3b6;
    undefined field_0x3b7;
    undefined field_0x3b8;
    undefined field_0x3b9;
    undefined field_0x3ba;
    undefined field_0x3bb;
    undefined field_0x3bc;
    undefined field_0x3bd;
    undefined field_0x3be;
    undefined field_0x3bf;
    undefined field_0x3c0;
    undefined field_0x3c1;
    undefined field_0x3c2;
    undefined field_0x3c3;
    undefined field_0x3c4;
    undefined field_0x3c5;
    undefined field_0x3c6;
    undefined field_0x3c7;
    undefined field_0x3c8;
    undefined field_0x3c9;
    undefined field_0x3ca;
    undefined field_0x3cb;
    undefined field_0x3cc;
    undefined field_0x3cd;
    undefined field_0x3ce;
    undefined field_0x3cf;
    undefined field_0x3d0;
    undefined field_0x3d1;
    undefined field_0x3d2;
    undefined field_0x3d3;
    undefined field_0x3d4;
    undefined field_0x3d5;
    undefined field_0x3d6;
    undefined field_0x3d7;
    undefined field_0x3d8;
    undefined field_0x3d9;
    undefined field_0x3da;
    undefined field_0x3db;
    undefined field_0x3dc;
    undefined field_0x3dd;
    undefined field_0x3de;
    undefined field_0x3df;
    undefined field_0x3e0;
    undefined field_0x3e1;
    undefined field_0x3e2;
    undefined field_0x3e3;
    undefined field_0x3e4;
    undefined field_0x3e5;
    undefined field_0x3e6;
    undefined field_0x3e7;
    undefined field_0x3e8;
    undefined field_0x3e9;
    undefined field_0x3ea;
    undefined field_0x3eb;
    undefined field_0x3ec;
    undefined field_0x3ed;
    undefined field_0x3ee;
    undefined field_0x3ef;
    undefined field_0x3f0;
    undefined field_0x3f1;
    undefined field_0x3f2;
    undefined field_0x3f3;
    undefined field_0x3f4;
    undefined field_0x3f5;
    undefined field_0x3f6;
    undefined field_0x3f7;
    undefined field_0x3f8;
    undefined field_0x3f9;
    undefined field_0x3fa;
    undefined field_0x3fb;
    undefined field_0x3fc;
    undefined field_0x3fd;
    undefined field_0x3fe;
    undefined field_0x3ff;
    undefined field_0x400;
    undefined field_0x401;
    undefined field_0x402;
    undefined field_0x403;
    undefined field_0x404;
    undefined field_0x405;
    undefined field_0x406;
    undefined field_0x407;
    undefined field_0x408;
    undefined field_0x409;
    undefined field_0x40b;
    undefined field_0x40c;
    undefined field_0x40a;
    undefined field_0x40d;
    undefined field_0x40e;
    undefined field_0x40f;
    undefined field_0x410;
    undefined field_0x411;
    undefined field_0x412;
    undefined field_0x413;
    undefined field_0x414;
    undefined field_0x415;
    undefined field_0x416;
    undefined field_0x417;
    undefined field_0x418;
    undefined field_0x419;
    undefined field_0x41a;
    undefined field_0x41b;
    undefined field_0x41c;
    undefined field_0x41d;
    undefined field_0x41e;
    undefined field_0x41f;
    undefined field_0x420;
    undefined field_0x421;
    undefined field_0x422;
    undefined field_0x423;
    undefined field_0x424;
    undefined field_0x425;
    undefined field_0x426;
    undefined field_0x427;
    undefined field_0x428;
    undefined field_0x429;
    undefined field_0x42a;
    undefined field_0x42b;
    undefined field_0x42c;
    undefined field_0x42d;
    undefined field_0x42e;
    undefined field_0x42f;
    undefined field_0x430;
    undefined field_0x431;
    undefined field_0x432;
    undefined field_0x433;
    undefined field_0x434;
    undefined field_0x435;
    undefined field_0x436;
    undefined field_0x437;
    undefined field_0x438;
    undefined field_0x439;
    undefined field_0x43a;
    undefined field_0x43b;
    undefined field_0x43c;
    undefined field_0x43d;
    undefined field_0x43e;
    undefined field_0x43f;
    undefined1 field_0x440;
    undefined1 field_0x441;
    undefined field_0x442;
    undefined field_0x443;
    float field_0x444;
    undefined1 field_0x448;
    undefined field_0x449;
    undefined field_0x44a;
    undefined field_0x44b;
    float field_0x44c;
public:
    unsigned int m_petCurrentHp; //0x0450
    unsigned int m_mpCurrent; //0x0454
    unsigned int m_hpMax; //0x0458
    unsigned int m_mpMax; //0x045C
    unsigned int m_hpCurrent; //0x0460

    undefined4 field_0x464;
    undefined4 field_0x468;
    undefined4 field_0x46c;
    undefined field_0x470;
    undefined1 field_0x471;
    undefined field_0x472;
    undefined field_0x473;
    CGFontTexture m_textureMessageAbove;
    undefined field_0x4dc;
    undefined field_0x4dd;
    undefined field_0x4de;
    undefined field_0x4df;
    undefined4 field_0x4e0;
    undefined4 field_0x4e4;
    undefined field_0x4e8;
    undefined field_0x4e9;
    undefined field_0x4ea;
    undefined field_0x4eb;
    undefined field_0x4ec;
    undefined field_0x4ed;
    undefined field_0x4ee;
    undefined field_0x4ef;
    float m_renderY; //0x04F0
    float m_renderX; //0x04F4
    float m_renderDepth; //0x04F8

    undefined1 field_0x4fc;
    undefined field_0x4fd;
    undefined field_0x4fe;
    undefined field_0x4ff;
    std::set<char> field_0x500;
    undefined1 field_0x50c;
    TRIJOB_TYPE b_JobType; /* Created by retype action */
    undefined1 field_0x50e;
    undefined field_0x50f;
    int m_valueDerivedFromRand;
    undefined4 field_0x514;
    undefined4 field_0x518;
    undefined field_0x51c;
    undefined field_0x51d;
    undefined field_0x51e;
    undefined field_0x51f;
    undefined field_0x520;
    undefined field_0x521;
    undefined field_0x522;
    undefined field_0x523;
    undefined field_0x524;
    undefined field_0x525;
    undefined field_0x526;
    undefined field_0x527;
    undefined field_0x528;
    undefined field_0x529;
    undefined field_0x52a;
    undefined field_0x52b;
    CICharactor_Class1 field_0x52c[15];
    undefined field_0x658;
    undefined field_0x659;
    undefined field_0x65a;
    undefined field_0x65b;

    short Status; // = 2 dead // 265 dung im // 521 chay // 269 danh quai // 65 ngoi // 5 buff // 2313 bi quai danh // 17 - bi nga
    undefined field_0x65e;
    undefined field_0x65f;
    undefined4 field_0x660;
    undefined4 field_0x664;
    undefined4 field_0x668;
    float field_0x66C; //19.200 mac dinh (char speed)
    float field_0x670; //60.00 mac dinh (char speed)
    undefined m_sub2[0xA8]; /* Created by retype action */
    undefined field_0x71c;
    undefined field_0x71d;
    undefined field_0x71e;
    undefined field_0x71f;
    undefined field_0x720;
    undefined field_0x721;
    undefined field_0x722;
    undefined field_0x723;
    undefined field_0x724;
    undefined field_0x725;
    undefined field_0x726;
    undefined field_0x727;
    undefined4 field_0x728;
    float field_0x72c;
    float field_0x730;
    float field_0x734;
    float field_0x738;
    undefined4 field_0x73c;
    float field_0x740;
    float field_0x744;
    float field_0x748;
    undefined4 field_0x74c;
    undefined1 field_0x750;
    undefined field_0x751;
    undefined field_0x752;
    undefined field_0x753;
    int m_effectId; //0x754
    undefined1 field_0x758;
    undefined1 field_0x759;
    undefined1 field_0x75a;
    undefined1 field_0x75b;
    undefined1 field_0x75c;
    undefined field_0x75d;
    undefined field_0x75e;
    undefined field_0x75f;
    undefined4 field_0x760;
    unsigned char m_hwanLevel; /* According to Sector1337 */
    undefined field_0x765;
    undefined field_0x766;
    undefined field_0x767;
    undefined4 field_0x768;
    undefined4 field_0x76c;
    undefined1 field_0x770;
    undefined field_0x771;
    undefined field_0x772;
    undefined field_0x773;
    undefined4 field_0x774;
    undefined4 field_0x778;
    undefined4 field_0x77c;
    undefined4 field_0x780;
    undefined1 field_0x784;
    undefined1 field_0x785;
    undefined field_0x786;
    undefined field_0x787;
    undefined field_0x788;
    undefined field_0x789;
    undefined field_0x78a;
    undefined field_0x78b;

BEGIN_FIXTURE()
        ENSURE_SIZE(0x78c)
        ENSURE_OFFSET(classLink, 0x274)
        ENSURE_OFFSET(decolist, 0x284)
        ENSURE_OFFSET(m_illness, 0x2c4)
        ENSURE_OFFSET(m_mpCurrent, 0x0454)
        ENSURE_OFFSET(m_hpMax, 0x0458)
        ENSURE_OFFSET(m_mpMax, 0x045C)
        ENSURE_OFFSET(m_hpCurrent, 0x0460)

        ENSURE_OFFSET(m_textureMessageAbove, 0x474)
        ENSURE_OFFSET(m_renderY, 0x4F0)
        ENSURE_OFFSET(m_renderX, 0x4F4)
        ENSURE_OFFSET(m_renderDepth, 0x4F8)

        ENSURE_OFFSET(b_JobType, 0x50d)
        ENSURE_OFFSET(field_0x66C, 0x66C)
        ENSURE_OFFSET(field_0x670, 0x670)
        ENSURE_OFFSET(m_effectId, 0x754)
    END_FIXTURE()
    RUN_FIXTURE(CICharactor)
};
