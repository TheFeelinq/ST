//
// Created by Admin on 11/8/2022.
//

#ifndef SRO_DEVKIT_IFSTBLOODEFFECT_H
#define SRO_DEVKIT_IFSTBLOODEFFECT_H


#include "IFWnd.h"
#include "IFStatic.h"

class CIFSTBloodEffect : public CIFWnd {
GFX_DECLARE_DYNCREATE(CIFSTBloodEffect)
GFX_DECLARE_MESSAGE_MAP(CIFSTBloodEffect)

public:
    CIFSTBloodEffect(void);
    ~CIFSTBloodEffect(void);

    bool OnCreate(long ln) override;
    void DrawBloodEffect();
private:
    int OnVisibleStateChange(int a1, int a2);

public:
    CIFStatic* m_overlay;

};


#endif //SRO_DEVKIT_IFSTBLOODEFFECT_H
