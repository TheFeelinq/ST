#pragma once

class ItemData {

public:
    void Render();

    void MenuItem();
    void PickAction(int ItemID , int ItemUniqueID,int PetUniqueID);
    void PickAlChemyAction(int ItemID , int ItemUniqueID,int PetUniqueID);
private:
    bool bShow;
};
