#pragma once

#include "GFXMainFrame/IEntity.h"
#include <d3d9.h>

#include "GlobalHelpersThatHaveNoHomeYet.h"
#include "AnimationCallback.h"
#include "CObjAnimation.h"
#include "ClassLink.h"

class CIObject : public CIEntity, public CAnimationCallback {
GFX_DECLARE_DYNAMIC_EXISTING(CIObject, 0x00eef6b0);

public:
    /// \address 009c4860
    CIObject();
    /// \address 009c4980
    ~CIObject();


    /// \address 009c4230
    virtual void Func_14();

    /// \address 004df110
    virtual void Func_15(int param_1, float *param_2);

    /// \address 004df120
    virtual void Func_16();

    /// \address 004df130
    virtual float Func_17();

    uregion GetRegion() const;

    D3DVECTOR GetLocation() const;

private:
    undefined field_0x58;
    undefined field_0x59;
    undefined field_0x5a;
    undefined field_0x5b;
    undefined field_0x5c;
    undefined field_0x5d;
    undefined field_0x5e;
    undefined field_0x5f;
    CClassLink<CIObject> m_classLink;
    undefined4 field_0x70;
public:
    class CRTNavCellQuad* m_navcell; //0x0074
    void* m_object_under_foot; //0x0078
    uregion region;  //0x007C
    D3DVECTOR location;  //0x0080
    float rotation; //0x008C
    D3DVECTOR loc_camera_center;
public:
    CCObjAnimation *m_CCObjAnimation_MAYBE;
private:
    float field_0xa0;
    float field_0xa4;
    float field_0xa8;
    float field_0xac;
    float field_0xb0;
    float field_0xb4;
    undefined4 field_0xb8;
    undefined1 field_0xbc;
    undefined1 field_0xbd;
    undefined field_0xbe;
    undefined field_0xbf;
    float field_0xc0;
    float field_0xc4;
    float field_0xc8;
    undefined4 field_0xcc;
    float field_0xd0;
    undefined4 field_0xd4;
    undefined1 field_0xd8;
    undefined field_0xd9;
    undefined field_0xda;
    undefined field_0xdb;


BEGIN_FIXTURE()
        ENSURE_SIZE(0xdc)
        ENSURE_OFFSET(m_classLink, 0x60)
        ENSURE_OFFSET(region, 0x7c)
        ENSURE_OFFSET(location, 0x80)
        ENSURE_OFFSET(rotation, 0x8C)
        ENSURE_OFFSET(loc_camera_center, 0x90)
        ENSURE_OFFSET(m_CCObjAnimation_MAYBE, 0x9c)
    END_FIXTURE()

    RUN_FIXTURE(CIObject)
};