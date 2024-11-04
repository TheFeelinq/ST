//
// Created by Admin on 27/11/2021.
//

#ifndef SRO_DEVKIT_PETFILTER_H
#define SRO_DEVKIT_PETFILTER_H
#include <imgui/imgui.h>
#include <IFSTCustomTitle.h>
#include <IFflorian0Guide.h>

class PetFilter {
public:
    void Render();
    void PickAlChemyAction(int ItemID, int ItemUniqueID, int PetUniqueID) ;
    void PickAction(int ItemID, int ItemUniqueID , int PetUniqueID) ;
};


#endif //SRO_DEVKIT_PETFILTER_H
