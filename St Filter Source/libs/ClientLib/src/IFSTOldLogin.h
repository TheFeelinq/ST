//
// Created by Admin on 25/6/2021.
//

#ifndef SRO_DEVKIT_IFSTOLDLOGIN_H
#define SRO_DEVKIT_IFSTOLDLOGIN_H


#include "IFButton.h"

class IFSTOldLogin {
public:
    void NewWindows();
    static void Initialize();
    CIFButton* m_mybutton;
};


#endif //SRO_DEVKIT_IFSTOLDLOGIN_H
