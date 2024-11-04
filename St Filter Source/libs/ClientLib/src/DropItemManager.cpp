//
// Created by Admin on 16/8/2022.
//

#include <algorithm>
#include "DropItemManager.h"
#include <ctime>
time_t LastPickSendTime;
void PickAlChemyAction(const CItemData *data , int PetUniqueID , int ItemUniqueID) {

    if( data->TID==5612 && g_pCGInterface->GetPetFilterGUI()->IsALChemyStoneRedChecked())
    {
        if ((time(NULL) - LastPickSendTime > 0.4)) {

            NEWMSG(0x70C5)
                pReq << PetUniqueID;
                pReq << (byte) 8;
                pReq << ItemUniqueID;
            SENDMSG()
            LastPickSendTime = time(NULL);

        }
    }
    if( data->TID==3564 && g_pCGInterface->GetPetFilterGUI()->IsALChemyStoneBlueChecked() ||
        data->TID==15853 && g_pCGInterface->GetPetFilterGUI()->IsALChemyStoneBlueChecked() ||
        data->TID==15852 && g_pCGInterface->GetPetFilterGUI()->IsALChemyStoneBlueChecked())
    {
        if ((time(NULL) - LastPickSendTime > 0.4)) {

            NEWMSG(0x70C5)
                pReq << PetUniqueID;
                pReq << (byte) 8;
                pReq << ItemUniqueID;
            SENDMSG()
            LastPickSendTime = time(NULL);

        }
    }
    if( data->TID==7660 && g_pCGInterface->GetPetFilterGUI()->IsALChemyTabletBlueChecked() ||  data->TID==7660 && g_pCGInterface->GetPetFilterGUI()->IsALChemyTabletRedChecked())
    {
        if ((time(NULL) - LastPickSendTime > 0.4)) {

            NEWMSG(0x70C5)
                pReq << PetUniqueID;
                pReq << (byte) 8;
                pReq << ItemUniqueID;
            SENDMSG()
            LastPickSendTime = time(NULL);

        }
    }

}
void PickAction(const CItemData *data , int PetUniqueID , int ItemUniqueID) {

    if(g_pCGInterface->GetPetFilterGUI()->IsEQWeaponChecked())
    {
        std::list<int>::iterator it = std::find(Rebot::Equipment_TID_Weapon_List.begin(), Rebot::Equipment_TID_Weapon_List.end(), data->TID);
        if(it != Rebot::Equipment_TID_Weapon_List.end())
        {
            if ((time(NULL) - LastPickSendTime > 0.4)) {

                NEWMSG(0x70C5)
                    pReq << PetUniqueID;
                    pReq << (byte) 8;
                    pReq << ItemUniqueID;
                SENDMSG()
                LastPickSendTime = time(NULL);

            }
        }

    }
    if(g_pCGInterface->GetPetFilterGUI()->IsEQAccsessoryChecked())
    {

        std::list<int>::iterator it = std::find(Rebot::Equipment_TID_Accsessory_List.begin(), Rebot::Equipment_TID_Accsessory_List.end(), data->TID);
        if(it != Rebot::Equipment_TID_Accsessory_List.end())
        {
            if ((time(NULL) - LastPickSendTime > 0.4)) {

                NEWMSG(0x70C5)
                    pReq << PetUniqueID;
                    pReq << (byte) 8;
                    pReq << ItemUniqueID;
                SENDMSG()
                LastPickSendTime = time(NULL);

            }
        }

    }
    if(g_pCGInterface->GetPetFilterGUI()->IsEQHeavyChecked())
    {

        std::list<int>::iterator it = std::find(Rebot::Equipment_TID_Heavy_List.begin(), Rebot::Equipment_TID_Heavy_List.end(), data->TID);
        if(it != Rebot::Equipment_TID_Heavy_List.end())
        {
            if(g_pCGInterface->GetPetFilterGUI()->IsEQMaleChecked())
            {

                if(data->m_reqGender==1)
                {
                    if ((time(NULL) - LastPickSendTime > 0.4)) {

                        NEWMSG(0x70C5)
                            pReq << PetUniqueID;
                            pReq << (byte) 8;
                            pReq << ItemUniqueID;
                        SENDMSG()
                        LastPickSendTime = time(NULL);

                    }
                }

            }
            if(g_pCGInterface->GetPetFilterGUI()->IsEQFeMaleChecked())
            {

                if(data->m_reqGender==0)
                {
                    if ((time(NULL) - LastPickSendTime > 0.4)) {

                        NEWMSG(0x70C5)
                            pReq << PetUniqueID;
                            pReq << (byte) 8;
                            pReq << ItemUniqueID;
                        SENDMSG()
                        LastPickSendTime = time(NULL);

                    }
                }

            }

        }

    }
    if(g_pCGInterface->GetPetFilterGUI()->IsEQLightChecked())
    {

        std::list<int>::iterator it = std::find(Rebot::Equipment_TID_Light_List.begin(), Rebot::Equipment_TID_Light_List.end(), data->TID);
        if(it != Rebot::Equipment_TID_Light_List.end())
        {
            if(g_pCGInterface->GetPetFilterGUI()->IsEQMaleChecked())
            {

                if(data->m_reqGender==1)
                {
                    if ((time(NULL) - LastPickSendTime > 0.4)) {

                        NEWMSG(0x70C5)
                            pReq << PetUniqueID;
                            pReq << (byte) 8;
                            pReq << ItemUniqueID;
                        SENDMSG()
                        LastPickSendTime = time(NULL);

                    }
                }

            }
            if(g_pCGInterface->GetPetFilterGUI()->IsEQFeMaleChecked())
            {

                if(data->m_reqGender==0)
                {
                    if ((time(NULL) - LastPickSendTime > 0.4)) {

                        NEWMSG(0x70C5)
                            pReq << PetUniqueID;
                            pReq << (byte) 8;
                            pReq << ItemUniqueID;
                        SENDMSG()
                        LastPickSendTime = time(NULL);

                    }
                }

            }
        }

    }
    if(g_pCGInterface->GetPetFilterGUI()->IsEQClothesChecked())
    {

        std::list<int>::iterator it = std::find(Rebot::Equipment_TID_Clothes_List.begin(), Rebot::Equipment_TID_Clothes_List.end(), data->TID);
        if(it != Rebot::Equipment_TID_Clothes_List.end())
        {
            if(g_pCGInterface->GetPetFilterGUI()->IsEQMaleChecked())
            {

                if(data->m_reqGender==1)
                {
                    if ((time(NULL) - LastPickSendTime > 0.4)) {

                        NEWMSG(0x70C5)
                            pReq << PetUniqueID;
                            pReq << (byte) 8;
                            pReq << ItemUniqueID;
                        SENDMSG()
                        LastPickSendTime = time(NULL);

                    }
                }

            }
            if(g_pCGInterface->GetPetFilterGUI()->IsEQFeMaleChecked())
            {

                if(data->m_reqGender==0)
                {
                    if ((time(NULL) - LastPickSendTime > 0.4)) {

                        NEWMSG(0x70C5)
                            pReq << PetUniqueID;
                            pReq << (byte) 8;
                            pReq << ItemUniqueID;
                        SENDMSG()
                        LastPickSendTime = time(NULL);

                    }
                }

            }

        }

    }
}
int CDropItemManager::sub_8AF7F0(char a2,UINT16 PetRegionID,int PetPosition,DWORD a5)
{

    if(g_pCGInterface->GetPetFilterGUI()->SwitchPetFilter)
    {
        int PetUniqueID = *(int *) ((DWORD32) (PetPosition - 0x6C0) + 0xF8);

        //printf(" a2 %d, a3 %d, a4 %p,a5 %d \n", a2,PetRegionID,PetPosition,a5);

        for (std::map<int, CIObject *>::iterator it = g_pGfxEttManager->entities.begin();
             it != g_pGfxEttManager->entities.end(); ++it) {

            //TODO REPLACE STRING COMPARISON WITH isSame Function
            if (it->second->IsSame(GFX_RUNTIME_CLASS(CIItem))) {
                /* WE KINDA REPLACING THE FUNCTION, THIS FUNCTION IS BOOLEAN RETURNS 0 OR 1.
                IT ITERATES THROUGH THE DROPPED ITEMS AND FINDS ONE BASED AT YOUR PET SETTINGS.
                THE ITEM IS BEING RESERVED AT ANOTHER REGISTER THOUGH. SO RETURNING 1. YOU COMMITING THAT YOU FOUND AN ITEM,
                THE GAME WILL CRASH AT THIS CASE. SO WE ALWAYS RETURN 0 SO THAT ITEM NOT FOUND.

                TODO::// FILTERING THE ITEM BASED AT PET SETTINGS && NEW SETTINGS
                AFTER THAT YOU WOULD SEND THE PICK PACKET, KEEP IN MIND THAT THIS FUNCTION IS BEING CALLED AS LONG AS YOU HAVE A PICK PET SPAWNED.
                SO AT THIS POINT YOU WILL HAVE TO BLOCK THIS FUNCTION UNTIL YOU RECEIVE A RESPOND FROM SERVER */
                CIItem* item = (CIItem*) it->second;

                int ItemUniqueID = *(int *) ((int) (it->second) + 0xF8); //item uniqueid
                int refObjID = *(int *) ((int) (it->second) + 0x21C); //item refobjid

                static const CItemData *data = NULL;
                data = g_CGlobalDataManager->GetItemData(refObjID);

                //printf(" ItemUniqueID %d, m_bPickAbbilty %d, hasOwner %d,SomeCheckForPlayerOwnerName %d \n", ItemUniqueID,item->m_bPickAbbilty,item->hasOwner,item->SomeCheckForPlayerOwnerName);
                if(!ItemUniqueID)
                    continue;
                if(!data || data == NULL)
                    continue;
                if (MEMUTIL_READ_BY_PTR_OFFSET(it->second, 0x28C, bool))
                    continue;
                if(item->hasOwner)
                {
                    if(item->SomeCheckForPlayerOwnerName != *(int *) ((int) (g_pCICPlayer)) + 0x2094);
                    continue;
                }

                if (data->m_id == 23 && g_pCGInterface->GetPetFilterGUI()->IsPotionVigorGrainChecked()) {
                    if ((time(NULL) - LastPickSendTime > 0.4)) {

                        NEWMSG(0x70C5)
                            pReq << PetUniqueID;
                            pReq << (byte) 8;
                            pReq << ItemUniqueID;
                        SENDMSG()
                        LastPickSendTime = time(NULL);

                    }
                }
                if (data->m_id == 9 && g_pCGInterface->GetPetFilterGUI()->IsPotionHpGrainChecked()) {
                    if ((time(NULL) - LastPickSendTime > 0.4)) {

                        NEWMSG(0x70C5)
                            pReq << PetUniqueID;
                            pReq << (byte) 8;
                            pReq << ItemUniqueID;
                        SENDMSG()
                        LastPickSendTime = time(NULL);

                    }
                }
                if (data->m_id == 16 && g_pCGInterface->GetPetFilterGUI()->IsPotionMpGrainChecked()) {
                    if ((time(NULL) - LastPickSendTime > 0.4)) {

                        NEWMSG(0x70C5)
                            pReq << PetUniqueID;
                            pReq << (byte) 8;
                            pReq << ItemUniqueID;
                        SENDMSG()
                        LastPickSendTime = time(NULL);

                    }
                }
                if (data->m_id == 62 && g_pCGInterface->GetPetFilterGUI()->IsPotionArrowsChecked()) {
                    if ((time(NULL) - LastPickSendTime > 0.4)) {

                        NEWMSG(0x70C5)
                            pReq << PetUniqueID;
                            pReq << (byte) 8;
                            pReq << ItemUniqueID;
                        SENDMSG()
                        LastPickSendTime = time(NULL);

                    }
                }
                if (data->m_id == 10383 && g_pCGInterface->GetPetFilterGUI()->IsPotionBoltsChecked()) {
                    if ((time(NULL) - LastPickSendTime > 0.4)) {

                        NEWMSG(0x70C5)
                            pReq << PetUniqueID;
                            pReq << (byte) 8;
                            pReq << ItemUniqueID;
                        SENDMSG()
                        LastPickSendTime = time(NULL);

                    }
                }
                if (g_pCGInterface->GetPetFilterGUI()->IsPotionHpChecked()) {
                    std::list<int>::iterator it = std::find(Rebot::Potion_ObjID_HP_Potion_List.begin(),
                                                            Rebot::Potion_ObjID_HP_Potion_List.end(),
                                                            data->TID);
                    if (it != Rebot::Potion_ObjID_HP_Potion_List.end()) {
                        if ((time(NULL) - LastPickSendTime > 0.4)) {

                            NEWMSG(0x70C5)
                                pReq << PetUniqueID;
                                pReq << (byte) 8;
                                pReq << ItemUniqueID;
                            SENDMSG()
                            LastPickSendTime = time(NULL);

                        }
                    }

                }
                if (g_pCGInterface->GetPetFilterGUI()->IsPotionMpChecked()) {
                    std::list<int>::iterator it = std::find(Rebot::Potion_ObjID_MP_Potion_List.begin(),
                                                            Rebot::Potion_ObjID_MP_Potion_List.end(),
                                                            data->TID);
                    if (it != Rebot::Potion_ObjID_MP_Potion_List.end()) {
                        if ((time(NULL) - LastPickSendTime > 0.4)) {

                            NEWMSG(0x70C5)
                                pReq << PetUniqueID;
                                pReq << (byte) 8;
                                pReq << ItemUniqueID;
                            SENDMSG()
                            LastPickSendTime = time(NULL);

                        }
                    }

                }
                if (g_pCGInterface->GetPetFilterGUI()->IsPotionVigorChecked()) {
                    std::list<int>::iterator it = std::find(
                            Rebot::Potion_ObjID_Vigor_Potion_List.begin(),
                            Rebot::Potion_ObjID_Vigor_Potion_List.end(), data->TID);
                    if (it != Rebot::Potion_ObjID_Vigor_Potion_List.end()) {
                        if ((time(NULL) - LastPickSendTime > 0.4)) {

                            NEWMSG(0x70C5)
                                pReq << PetUniqueID;
                                pReq << (byte) 8;
                                pReq << ItemUniqueID;
                            SENDMSG()
                            LastPickSendTime = time(NULL);

                        }
                    }

                }
                if (g_pCGInterface->GetPetFilterGUI()->IsPotionUniversalPillChecked()) {
                    std::list<int>::iterator it = std::find(
                            Rebot::Potion_ObjID_Universal_Pill_List.begin(),
                            Rebot::Potion_ObjID_Universal_Pill_List.end(), data->TID);
                    if (it != Rebot::Potion_ObjID_Universal_Pill_List.end()) {
                        if ((time(NULL) - LastPickSendTime > 0.4)) {

                            NEWMSG(0x70C5)
                                pReq << PetUniqueID;
                                pReq << (byte) 8;
                                pReq << ItemUniqueID;
                            SENDMSG()
                            LastPickSendTime = time(NULL);

                        }
                    }

                }
                if (g_pCGInterface->GetPetFilterGUI()->IsPotionReturnScrollChecked()) {
                    std::list<int>::iterator it = std::find(
                            Rebot::Potion_ObjID_Return_Scroll_List.begin(),
                            Rebot::Potion_ObjID_Return_Scroll_List.end(), data->m_id);
                    if (it != Rebot::Potion_ObjID_Return_Scroll_List.end()) {
                        if ((time(NULL) - LastPickSendTime > 0.4)) {

                            NEWMSG(0x70C5)
                                pReq << PetUniqueID;
                                pReq << (byte) 8;
                                pReq << ItemUniqueID;
                            SENDMSG()
                            LastPickSendTime = time(NULL);

                        }
                    }

                }
                if (g_pCGInterface->GetPetFilterGUI()->IsPotionCoinChecked()) {
                    std::list<int>::iterator it = std::find(Rebot::Potion_ObjID_Coin_List.begin(),
                                                            Rebot::Potion_ObjID_Coin_List.end(),
                                                            data->m_id);
                    if (it != Rebot::Potion_ObjID_Coin_List.end()) {
                        if ((time(NULL) - LastPickSendTime > 0.4)) {

                            NEWMSG(0x70C5)
                                pReq << PetUniqueID;
                                pReq << (byte) 8;
                                pReq << ItemUniqueID;
                            SENDMSG()
                            LastPickSendTime = time(NULL);

                        }
                    }

                }
                if (data->TID == 3436 && data->m_param1 == 100663296 &&
                    g_pCGInterface->GetPetFilterGUI()->IsALChemyElixirWeaponChecked()) {
                    if ((time(NULL) - LastPickSendTime > 0.4)) {

                        NEWMSG(0x70C5)
                            pReq << PetUniqueID;
                            pReq << (byte) 8;
                            pReq << ItemUniqueID;
                        SENDMSG()
                        LastPickSendTime = time(NULL);

                    }
                }
                if (data->TID == 3436 && data->m_param1 == 67108864 &&
                    g_pCGInterface->GetPetFilterGUI()->IsALChemyElixirShieldChecked()) {
                    if ((time(NULL) - LastPickSendTime > 0.4)) {

                        NEWMSG(0x70C5)
                            pReq << PetUniqueID;
                            pReq << (byte) 8;
                            pReq << ItemUniqueID;
                        SENDMSG()
                        LastPickSendTime = time(NULL);

                    }
                }
                if (data->TID == 3436 && data->m_param1 == 16909056 &&
                    g_pCGInterface->GetPetFilterGUI()->IsALChemyElixirProtectorChecked()) {
                    if ((time(NULL) - LastPickSendTime > 0.4)) {

                        NEWMSG(0x70C5)
                            pReq << PetUniqueID;
                            pReq << (byte) 8;
                            pReq << ItemUniqueID;
                        SENDMSG()
                        LastPickSendTime = time(NULL);

                    }
                }
                if (data->TID == 3436 && data->m_param1 == 83886080 &&
                    g_pCGInterface->GetPetFilterGUI()->IsALChemyElixirAccessoryChecked()) {
                    if ((time(NULL) - LastPickSendTime > 0.4)) {

                        NEWMSG(0x70C5)
                            pReq << PetUniqueID;
                            pReq << (byte) 8;
                            pReq << ItemUniqueID;
                        SENDMSG()
                        LastPickSendTime = time(NULL);

                    }
                }
                if (data->TID == 9708 && g_pCGInterface->GetPetFilterGUI()->IsALChemyMaterialChecked() &&
                    data->m_itemClass == 1) {
                    if ((time(NULL) - LastPickSendTime > 0.4)) {

                        NEWMSG(0x70C5)
                            pReq << PetUniqueID;
                            pReq << (byte) 8;
                            pReq << ItemUniqueID;
                        SENDMSG()
                        LastPickSendTime = time(NULL);

                    }
                }
                if ((data->m_id == 1 || data->m_id == 2 || data->m_id == 3) && g_pCGInterface->GetPetFilterGUI()->IsGoldChecked()) {
                    if ((time(NULL) - LastPickSendTime > 0.4)) {

                        NEWMSG(0x70C5)
                            pReq << PetUniqueID;
                            pReq << (byte) 8;
                            pReq << ItemUniqueID;
                        SENDMSG()
                        LastPickSendTime = time(NULL);

                    }
                }
                if (g_pCGInterface->GetPetFilterGUI()->IsALChemyDegree01Checked() &&
                    data->m_itemClass == 1) {
                    PickAlChemyAction(data,PetUniqueID,ItemUniqueID);

                }
                if (g_pCGInterface->GetPetFilterGUI()->IsALChemyDegree02Checked() &&
                    data->m_itemClass == 2) {
                    PickAlChemyAction(data,PetUniqueID,ItemUniqueID);

                }
                if (g_pCGInterface->GetPetFilterGUI()->IsALChemyDegree03Checked() &&
                    data->m_itemClass == 3) {
                    PickAlChemyAction(data,PetUniqueID,ItemUniqueID);

                }
                if (g_pCGInterface->GetPetFilterGUI()->IsALChemyDegree04Checked() &&
                    data->m_itemClass == 4) {
                    PickAlChemyAction(data,PetUniqueID,ItemUniqueID);
                }
                if (g_pCGInterface->GetPetFilterGUI()->IsALChemyDegree05Checked() &&
                    data->m_itemClass == 5) {
                    PickAlChemyAction(data,PetUniqueID,ItemUniqueID);
                }
                if (g_pCGInterface->GetPetFilterGUI()->IsALChemyDegree06Checked() &&
                    data->m_itemClass == 6) {
                    PickAlChemyAction(data,PetUniqueID,ItemUniqueID);
                }
                if (g_pCGInterface->GetPetFilterGUI()->IsALChemyDegree07Checked() &&
                    data->m_itemClass == 7) {
                    PickAlChemyAction(data,PetUniqueID,ItemUniqueID);
                }
                if (g_pCGInterface->GetPetFilterGUI()->IsALChemyDegree08Checked() &&
                    data->m_itemClass == 8) {
                    PickAlChemyAction(data,PetUniqueID,ItemUniqueID);
                }
                if (g_pCGInterface->GetPetFilterGUI()->IsALChemyDegree09Checked() &&
                    data->m_itemClass == 9) {
                    PickAlChemyAction(data,PetUniqueID,ItemUniqueID);
                }
                if (g_pCGInterface->GetPetFilterGUI()->IsALChemyDegree10Checked() &&
                    data->m_itemClass == 10) {
                    PickAlChemyAction(data,PetUniqueID,ItemUniqueID);
                }
                if (g_pCGInterface->GetPetFilterGUI()->IsALChemyDegree11Checked() &&
                    data->m_itemClass == 11) {
                    PickAlChemyAction(data,PetUniqueID,ItemUniqueID);
                }
                if (g_pCGInterface->GetPetFilterGUI()->IsALChemyDegree12Checked() &&
                    data->m_itemClass == 12) {
                    PickAlChemyAction(data,PetUniqueID,ItemUniqueID);
                }
                if (g_pCGInterface->GetPetFilterGUI()->IsALChemyDegree13Checked() &&
                    data->m_itemClass == 13) {
                    PickAlChemyAction(data,PetUniqueID,ItemUniqueID);
                }
                if (g_pCGInterface->GetPetFilterGUI()->IsALChemyDegree14Checked() &&
                    data->m_itemClass == 14) {
                    PickAlChemyAction(data,PetUniqueID,ItemUniqueID);
                }
                if (g_pCGInterface->GetPetFilterGUI()->IsALChemyDegree15Checked() &&
                    data->m_itemClass == 15) {
                    PickAlChemyAction(data,PetUniqueID,ItemUniqueID);
                }
                if (!Rebot::Equipment_TID_List.empty()) {

                    std::list<int>::iterator it = std::find(Rebot::Equipment_TID_List.begin(),
                                                            Rebot::Equipment_TID_List.end(), data->TID);
                    if (it != Rebot::Equipment_TID_List.end()) {
                        if (g_pCGInterface->GetPetFilterGUI()->IsEQDegree01Checked() &&
                            data->m_itemClass <= 3) {
                            PickAction(data,PetUniqueID,ItemUniqueID);

                        }
                        if (g_pCGInterface->GetPetFilterGUI()->IsEQDegree02Checked() &&
                            data->m_itemClass <= 6 && data->m_itemClass >= 4) {
                            PickAction(data,PetUniqueID,ItemUniqueID);
                        }
                        if (g_pCGInterface->GetPetFilterGUI()->IsEQDegree03Checked() &&
                            data->m_itemClass <= 9 && data->m_itemClass >= 7) {
                            PickAction(data,PetUniqueID,ItemUniqueID);
                        }
                        if (g_pCGInterface->GetPetFilterGUI()->IsEQDegree04Checked() &&
                            data->m_itemClass <= 12 && data->m_itemClass >= 10) {
                            PickAction(data,PetUniqueID,ItemUniqueID);
                        }
                        if (g_pCGInterface->GetPetFilterGUI()->IsEQDegree05Checked() &&
                            data->m_itemClass <= 15 && data->m_itemClass >= 13) {
                            PickAction(data,PetUniqueID,ItemUniqueID);
                        }
                        if (g_pCGInterface->GetPetFilterGUI()->IsEQDegree06Checked() &&
                            data->m_itemClass <= 18 && data->m_itemClass >= 16) {
                            PickAction(data,PetUniqueID,ItemUniqueID);
                        }
                        if (g_pCGInterface->GetPetFilterGUI()->IsEQDegree07Checked() &&
                            data->m_itemClass <= 21 && data->m_itemClass >= 19) {
                            PickAction(data,PetUniqueID,ItemUniqueID);
                        }
                        if (g_pCGInterface->GetPetFilterGUI()->IsEQDegree08Checked() &&
                            data->m_itemClass <= 24 && data->m_itemClass >= 22) {
                            PickAction(data,PetUniqueID,ItemUniqueID);
                        }
                        if (g_pCGInterface->GetPetFilterGUI()->IsEQDegree09Checked() &&
                            data->m_itemClass <= 27 && data->m_itemClass >= 25) {
                            PickAction(data,PetUniqueID,ItemUniqueID);
                        }
                        if (g_pCGInterface->GetPetFilterGUI()->IsEQDegree10Checked() &&
                            data->m_itemClass <= 30 && data->m_itemClass >= 28) {
                            PickAction(data,PetUniqueID,ItemUniqueID);
                        }
                        if (g_pCGInterface->GetPetFilterGUI()->IsEQDegree11Checked() &&
                            data->m_itemClass <= 33 && data->m_itemClass >= 31) {
                            PickAction(data,PetUniqueID,ItemUniqueID);
                        }
                        if (g_pCGInterface->GetPetFilterGUI()->IsEQDegree12Checked() &&
                            data->m_itemClass <= 36 && data->m_itemClass >= 34) {
                            PickAction(data,PetUniqueID,ItemUniqueID);
                        }
                        if (g_pCGInterface->GetPetFilterGUI()->IsEQDegree13Checked() &&
                            data->m_itemClass <= 39 && data->m_itemClass >= 37) {
                            PickAction(data,PetUniqueID,ItemUniqueID);
                        }
                        if (g_pCGInterface->GetPetFilterGUI()->IsEQDegree14Checked() &&
                            data->m_itemClass <= 42 && data->m_itemClass >= 40) {
                            PickAction(data,PetUniqueID,ItemUniqueID);
                        }
                        if (g_pCGInterface->GetPetFilterGUI()->IsEQDegree15Checked() &&
                            data->m_itemClass <= 45 && data->m_itemClass >= 43) {
                            PickAction(data,PetUniqueID,ItemUniqueID);
                        }
                    }
                }

                continue;
            }
            //return 0;
        }
        return 0;
    }
    else
        return reinterpret_cast<bool(__thiscall*)(CDropItemManager*, char,UINT16,int,DWORD)>(0x008AF7F0)(this, a2,PetRegionID,PetPosition,a5);
}