//
// Created by Admin on 27/11/2021.
//

#include "PetFilter.h"
#include "GlobalDataManager.h"
#include "Rebot.h"
#include "EntityManagerClient.h"
#include <algorithm>
#include <ctime>
#include <Data/ItemData.h>
#include <IFSTPetFilter.h>

time_t LastSendTimex;
void PetFilter::PickAlChemyAction(int ItemID, int ItemUniqueID, int PetUniqueID) {

    static const CItemData *data = NULL;
    data = g_CGlobalDataManager->GetItemData(ItemID);

    if( data->TID==5612 && g_pCGInterface->GetPetFilterGUI()->IsALChemyStoneRedChecked())
    {
        if((time(NULL) - LastSendTimex > 0.5)) {

            NEWMSG(0x70C5)
                pReq << PetUniqueID;
                pReq << (byte)8;
                pReq << ItemUniqueID;
            SENDMSG()
            LastSendTimex = time(NULL);
            return;
        }
    }
    if( data->TID==3564 && g_pCGInterface->GetPetFilterGUI()->IsALChemyStoneBlueChecked() ||
        data->TID==15853 && g_pCGInterface->GetPetFilterGUI()->IsALChemyStoneBlueChecked())
    {
        if((time(NULL) - LastSendTimex > 0.5)) {

            NEWMSG(0x70C5)
                pReq << PetUniqueID;
                pReq << (byte)8;
                pReq << ItemUniqueID;
            SENDMSG()
            LastSendTimex = time(NULL);
            return;
        }
    }
    if( data->TID==7660 && g_pCGInterface->GetPetFilterGUI()->IsALChemyTabletBlueChecked() ||  data->TID==7660 && g_pCGInterface->GetPetFilterGUI()->IsALChemyTabletRedChecked())
    {
        if((time(NULL) - LastSendTimex > 0.5)) {

            NEWMSG(0x70C5)
                pReq << PetUniqueID;
                pReq << (byte)8;
                pReq << ItemUniqueID;
            SENDMSG()
            LastSendTimex = time(NULL);
            return;
        }
    }


}
void PetFilter::PickAction(int ItemID, int ItemUniqueID , int PetUniqueID) {

    static const CItemData *data = NULL;
    data = g_CGlobalDataManager->GetItemData(ItemID);

    if(g_pCGInterface->GetPetFilterGUI()->IsEQWeaponChecked())
    {
        std::list<int>::iterator it = std::find(Rebot::Equipment_TID_Weapon_List.begin(), Rebot::Equipment_TID_Weapon_List.end(), data->TID);
        if(it != Rebot::Equipment_TID_Weapon_List.end())
        {
            printf("pick weapon equipment\n");
            if((time(NULL) - LastSendTimex > 0.5)) {

                NEWMSG(0x70C5)
                    pReq << PetUniqueID;
                    pReq << (byte)8;
                    pReq << ItemUniqueID;
                SENDMSG()
                LastSendTimex = time(NULL);
                return;
            }

        }

    }
    if(g_pCGInterface->GetPetFilterGUI()->IsEQAccsessoryChecked())
    {

        std::list<int>::iterator it = std::find(Rebot::Equipment_TID_Accsessory_List.begin(), Rebot::Equipment_TID_Accsessory_List.end(), data->TID);
        if(it != Rebot::Equipment_TID_Accsessory_List.end())
        {
            printf("pick Accsessory equipment\n");
            if((time(NULL) - LastSendTimex > 0.5)) {

                NEWMSG(0x70C5)
                    pReq << PetUniqueID;
                    pReq << (byte)8;
                    pReq << ItemUniqueID;
                SENDMSG()
                LastSendTimex = time(NULL);
                return;
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
                    printf("pick male equipment\n");
                    if((time(NULL) - LastSendTimex > 0.5)) {

                        NEWMSG(0x70C5)
                            pReq << PetUniqueID;
                            pReq << (byte)8;
                            pReq << ItemUniqueID;
                        SENDMSG()
                        LastSendTimex = time(NULL);
                        return;
                    }

                }

            }
            if(g_pCGInterface->GetPetFilterGUI()->IsEQFeMaleChecked())
            {

                if(data->m_reqGender==0)
                {
                    printf("pick female equipment\n");
                    if((time(NULL) - LastSendTimex > 0.5)) {

                        NEWMSG(0x70C5)
                            pReq << PetUniqueID;
                            pReq << (byte)8;
                            pReq << ItemUniqueID;
                        SENDMSG()
                        LastSendTimex = time(NULL);
                        return;
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
                    printf("pick male equipment\n");
                    if((time(NULL) - LastSendTimex > 0.5)) {

                        NEWMSG(0x70C5)
                            pReq << PetUniqueID;
                            pReq << (byte)8;
                            pReq << ItemUniqueID;
                        SENDMSG()
                        LastSendTimex = time(NULL);
                        return;
                    }

                }

            }
            if(g_pCGInterface->GetPetFilterGUI()->IsEQFeMaleChecked())
            {

                if(data->m_reqGender==0)
                {
                    printf("pick female equipment\n");
                    if((time(NULL) - LastSendTimex > 0.5)) {

                        NEWMSG(0x70C5)
                            pReq << PetUniqueID;
                            pReq << (byte)8;
                            pReq << ItemUniqueID;
                        SENDMSG()
                        LastSendTimex = time(NULL);
                        return;
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
                    printf("pick male equipment\n");
                    if((time(NULL) - LastSendTimex > 0.5)) {

                        NEWMSG(0x70C5)
                            pReq << PetUniqueID;
                            pReq << (byte)8;
                            pReq << ItemUniqueID;
                        SENDMSG()
                        LastSendTimex = time(NULL);
                        return;
                    }

                }

            }
            if(g_pCGInterface->GetPetFilterGUI()->IsEQFeMaleChecked())
            {

                if(data->m_reqGender==0)
                {
                    printf("pick female equipment\n");
                    if((time(NULL) - LastSendTimex > 0.5)) {

                        NEWMSG(0x70C5)
                            pReq << PetUniqueID;
                            pReq << (byte)8;
                            pReq << ItemUniqueID;
                        SENDMSG()
                        LastSendTimex = time(NULL);
                        return;
                    }

                }

            }

        }

    }
}
void PetFilter::Render() {
    if(!g_pCICPlayer)
        return;
    if(!g_pCGInterface->GetPetFilterGUI()->SwitchPetFilter)
        return;

    for (std::map<int, CIObject *>::iterator it = g_pGfxEttManager->entities.begin();
         it != g_pGfxEttManager->entities.end(); ++it) {

        if (!strcmp(it->second->GetRuntimeClass()->m_lpszClassName, "CIItem")) {

            int petBase = Rebot::get_pet_bytype(2);
            if (0 != petBase && 0 != *(DWORD32*)(petBase + 0x04))
            {
                int uniqueid = *(DWORD32*)(petBase + 0x04); //petuniqueid
                int nItems[1024] = { 0 };
                Rebot::get_itemlist(nItems);

                for (int i = 0; i < 1024; i ++)
                {
                    ITEM_INFO ii = { 0 };
                    if (0 != nItems[i] && Rebot::get_iteminfo(ii, nItems[i]))
                    {
                        if (ii.item_pickable)
                        {

                            static const CItemData *data = NULL;
                            if(data = g_CGlobalDataManager->GetItemData(ii.item_type))
                            {
                                /*   ImGui::LabelText("CodeName", "%ls", data->m_codeName128.c_str());
                                    ImGui::LabelText("m_id", "%d", data->m_id);
                                    ImGui::LabelText("TID", "%d", data->TID);
                                    ImGui::LabelText("m_itemClass", "%d", data->m_itemClass);
                                    ImGui::LabelText("UniqueID", "%d", ii.item_id);
                                    ImGui::LabelText("m_reqLevel1", "%d", data->m_reqLevel1);
                                    ImGui::LabelText("m_reqLevelType1", "%d", data->m_reqLevelType1);
                                    ImGui::LabelText("m_reqLevel2", "%d", data->m_reqLevel2);
                                    ImGui::LabelText("m_reqLevelType2", "%d", data->m_reqLevelType2);
                                    ImGui::LabelText("m_scale", "%d", data->m_scale);
                                    ImGui::LabelText("m_bcHeight", "%d", data->m_bcHeight);
                                    ImGui::LabelText("m_bcRadius", "%d", data->m_bcRadius);
                                    ImGui::LabelText("m_eventId", "%d", data->m_eventId);
                                    ImGui::LabelText("m_reqGender", "%d", data->m_reqGender);
                                    ImGui::LabelText("m_param1", "%d", data->m_param1);*/


                                //ImGui::LabelText("UniqueID", "%d", ii.item_id);
                                //ImGui::LabelText("ITEMID", "%d", ii.item_type);
                                if( data->m_id==23 && g_pCGInterface->GetPetFilterGUI()->IsPotionVigorGrainChecked())
                                {
                                    if((time(NULL) - LastSendTimex > 0.5)) {

                                        NEWMSG(0x70C5)
                                            pReq << uniqueid;
                                            pReq << (byte)8;
                                            pReq << ii.item_id;
                                        SENDMSG()
                                        LastSendTimex = time(NULL);
                                        return;
                                    }

                                }
                                if( data->m_id==9 && g_pCGInterface->GetPetFilterGUI()->IsPotionHpGrainChecked())
                                {
                                    if((time(NULL) - LastSendTimex > 0.5)) {

                                        NEWMSG(0x70C5)
                                            pReq << uniqueid;
                                            pReq << (byte)8;
                                            pReq << ii.item_id;
                                        SENDMSG()
                                        LastSendTimex = time(NULL);
                                        return;
                                    }

                                }
                                if( data->m_id==16 && g_pCGInterface->GetPetFilterGUI()->IsPotionMpGrainChecked())
                                {
                                    if((time(NULL) - LastSendTimex > 0.5)) {

                                        NEWMSG(0x70C5)
                                            pReq << uniqueid;
                                            pReq << (byte)8;
                                            pReq << ii.item_id;
                                        SENDMSG()
                                        LastSendTimex = time(NULL);
                                        return;

                                    }

                                }
                                if( data->m_id==62 && g_pCGInterface->GetPetFilterGUI()->IsPotionArrowsChecked())
                                {
                                    if((time(NULL) - LastSendTimex > 0.5)) {

                                        NEWMSG(0x70C5)
                                            pReq << uniqueid;
                                            pReq << (byte)8;
                                            pReq << ii.item_id;
                                        SENDMSG()
                                        LastSendTimex = time(NULL);
                                        return;
                                    }

                                }
                                if( data->m_id==10383 && g_pCGInterface->GetPetFilterGUI()->IsPotionBoltsChecked())
                                {
                                    if((time(NULL) - LastSendTimex > 0.5)) {

                                        NEWMSG(0x70C5)
                                            pReq << uniqueid;
                                            pReq << (byte)8;
                                            pReq << ii.item_id;
                                        SENDMSG()
                                        LastSendTimex = time(NULL);
                                        return;
                                    }

                                }
                                if(g_pCGInterface->GetPetFilterGUI()->IsPotionHpChecked())
                                {
                                    std::list<int>::iterator it = std::find(Rebot::Potion_ObjID_HP_Potion_List.begin(), Rebot::Potion_ObjID_HP_Potion_List.end(), data->m_id);
                                    if(it != Rebot::Potion_ObjID_HP_Potion_List.end())
                                    {
                                        if((time(NULL) - LastSendTimex > 0.5)) {

                                            NEWMSG(0x70C5)
                                                pReq << uniqueid;
                                                pReq << (byte)8;
                                                pReq << ii.item_id;
                                            SENDMSG()
                                            LastSendTimex = time(NULL);
                                            return;
                                        }

                                    }

                                }
                                if(g_pCGInterface->GetPetFilterGUI()->IsPotionMpChecked())
                                {
                                    std::list<int>::iterator it = std::find(Rebot::Potion_ObjID_MP_Potion_List.begin(), Rebot::Potion_ObjID_MP_Potion_List.end(), data->m_id);
                                    if(it != Rebot::Potion_ObjID_MP_Potion_List.end())
                                    {
                                        if((time(NULL) - LastSendTimex > 0.5)) {

                                            NEWMSG(0x70C5)
                                                pReq << uniqueid;
                                                pReq << (byte)8;
                                                pReq << ii.item_id;
                                            SENDMSG()
                                            LastSendTimex = time(NULL);
                                            return;
                                        }

                                    }

                                }
                                if(g_pCGInterface->GetPetFilterGUI()->IsPotionVigorChecked())
                                {
                                    std::list<int>::iterator it = std::find(Rebot::Potion_ObjID_Vigor_Potion_List.begin(), Rebot::Potion_ObjID_Vigor_Potion_List.end(), data->m_id);
                                    if(it != Rebot::Potion_ObjID_Vigor_Potion_List.end())
                                    {
                                        if((time(NULL) - LastSendTimex > 0.5)) {

                                            NEWMSG(0x70C5)
                                                pReq << uniqueid;
                                                pReq << (byte)8;
                                                pReq << ii.item_id;
                                            SENDMSG()
                                            LastSendTimex = time(NULL);
                                            return;
                                        }

                                    }

                                }
                                if(g_pCGInterface->GetPetFilterGUI()->IsPotionUniversalPillChecked())
                                {
                                    std::list<int>::iterator it = std::find(Rebot::Potion_ObjID_Universal_Pill_List.begin(), Rebot::Potion_ObjID_Universal_Pill_List.end(), data->m_id);
                                    if(it != Rebot::Potion_ObjID_Universal_Pill_List.end())
                                    {
                                        if((time(NULL) - LastSendTimex > 0.5)) {

                                            NEWMSG(0x70C5)
                                                pReq << uniqueid;
                                                pReq << (byte)8;
                                                pReq << ii.item_id;
                                            SENDMSG()
                                            LastSendTimex = time(NULL);
                                            return;
                                        }

                                    }

                                }
                                if(g_pCGInterface->GetPetFilterGUI()->IsPotionReturnScrollChecked())
                                {
                                    std::list<int>::iterator it = std::find(Rebot::Potion_ObjID_Return_Scroll_List.begin(), Rebot::Potion_ObjID_Return_Scroll_List.end(), data->m_id);
                                    if(it != Rebot::Potion_ObjID_Return_Scroll_List.end())
                                    {
                                        if((time(NULL) - LastSendTimex > 0.5)) {

                                            NEWMSG(0x70C5)
                                                pReq << uniqueid;
                                                pReq << (byte)8;
                                                pReq << ii.item_id;
                                            SENDMSG()
                                            LastSendTimex = time(NULL);
                                            return;
                                        }

                                    }

                                }
                                if(g_pCGInterface->GetPetFilterGUI()->IsPotionCoinChecked())
                                {
                                    std::list<int>::iterator it = std::find(Rebot::Potion_ObjID_Coin_List.begin(), Rebot::Potion_ObjID_Coin_List.end(), data->m_id);
                                    if(it != Rebot::Potion_ObjID_Coin_List.end())
                                    {
                                        if((time(NULL) - LastSendTimex > 0.5)) {

                                            NEWMSG(0x70C5)
                                                pReq << uniqueid;
                                                pReq << (byte)8;
                                                pReq << ii.item_id;
                                            SENDMSG()
                                            LastSendTimex = time(NULL);
                                            return;
                                        }

                                    }

                                }
                                if( data->TID==3436 &&data->m_param1== 100663296 && g_pCGInterface->GetPetFilterGUI()->IsALChemyElixirWeaponChecked())
                                {
                                    if((time(NULL) - LastSendTimex > 0.5)) {

                                        NEWMSG(0x70C5)
                                            pReq << uniqueid;
                                            pReq << (byte)8;
                                            pReq << ii.item_id;
                                        SENDMSG()
                                        LastSendTimex = time(NULL);
                                        return;
                                    }

                                }
                                if( data->TID==3436 &&data->m_param1== 67108864 && g_pCGInterface->GetPetFilterGUI()->IsALChemyElixirShieldChecked())
                                {
                                    if((time(NULL) - LastSendTimex > 0.5)) {

                                        NEWMSG(0x70C5)
                                            pReq << uniqueid;
                                            pReq << (byte)8;
                                            pReq << ii.item_id;
                                        SENDMSG()
                                        LastSendTimex = time(NULL);
                                        return;
                                    }

                                }
                                if( data->TID==3436 &&data->m_param1== 16909056 && g_pCGInterface->GetPetFilterGUI()->IsALChemyElixirProtectorChecked())
                                {
                                    if((time(NULL) - LastSendTimex > 0.5)) {

                                        NEWMSG(0x70C5)
                                            pReq << uniqueid;
                                            pReq << (byte)8;
                                            pReq << ii.item_id;
                                        SENDMSG()
                                        LastSendTimex = time(NULL);
                                        return;
                                    }

                                }
                                if( data->TID==3436 &&data->m_param1== 83886080 && g_pCGInterface->GetPetFilterGUI()->IsALChemyElixirAccessoryChecked())
                                {
                                    if((time(NULL) - LastSendTimex > 0.5)) {

                                        NEWMSG(0x70C5)
                                            pReq << uniqueid;
                                            pReq << (byte)8;
                                            pReq << ii.item_id;
                                        SENDMSG()
                                        LastSendTimex = time(NULL);
                                        return;
                                    }

                                }
                                if( data->TID==9708 && g_pCGInterface->GetPetFilterGUI()->IsALChemyMaterialChecked() && data->m_itemClass ==1)
                                {
                                    if((time(NULL) - LastSendTimex > 0.5)) {

                                        NEWMSG(0x70C5)
                                            pReq << uniqueid;
                                            pReq << (byte)8;
                                            pReq << ii.item_id;
                                        SENDMSG()
                                        LastSendTimex = time(NULL);
                                        return;
                                    }

                                }
                                if(g_pCGInterface->GetPetFilterGUI()->IsALChemyDegree01Checked() && data->m_itemClass ==1)
                                {
                                    PickAlChemyAction(ii.item_type, ii.item_id,uniqueid);

                                }
                                if(g_pCGInterface->GetPetFilterGUI()->IsALChemyDegree02Checked() && data->m_itemClass ==2)
                                {
                                    PickAlChemyAction(ii.item_type, ii.item_id,uniqueid);

                                }
                                if(g_pCGInterface->GetPetFilterGUI()->IsALChemyDegree03Checked() && data->m_itemClass ==3)
                                {
                                    PickAlChemyAction(ii.item_type, ii.item_id,uniqueid);

                                }
                                if(g_pCGInterface->GetPetFilterGUI()->IsALChemyDegree04Checked() && data->m_itemClass ==4)
                                {
                                    PickAlChemyAction(ii.item_type, ii.item_id,uniqueid);

                                }
                                if(g_pCGInterface->GetPetFilterGUI()->IsALChemyDegree05Checked() && data->m_itemClass ==5)
                                {
                                    PickAlChemyAction(ii.item_type, ii.item_id,uniqueid);

                                }
                                if(g_pCGInterface->GetPetFilterGUI()->IsALChemyDegree06Checked() && data->m_itemClass ==6)
                                {
                                    PickAlChemyAction(ii.item_type, ii.item_id,uniqueid);

                                }
                                if(g_pCGInterface->GetPetFilterGUI()->IsALChemyDegree07Checked() && data->m_itemClass ==7)
                                {
                                    PickAlChemyAction(ii.item_type, ii.item_id,uniqueid);

                                }
                                if(g_pCGInterface->GetPetFilterGUI()->IsALChemyDegree08Checked() && data->m_itemClass ==8)
                                {
                                    PickAlChemyAction(ii.item_type, ii.item_id,uniqueid);

                                }
                                if(g_pCGInterface->GetPetFilterGUI()->IsALChemyDegree09Checked() && data->m_itemClass ==9)
                                {
                                    PickAlChemyAction(ii.item_type, ii.item_id,uniqueid);

                                }
                                if(g_pCGInterface->GetPetFilterGUI()->IsALChemyDegree10Checked() && data->m_itemClass ==10)
                                {
                                    PickAlChemyAction(ii.item_type, ii.item_id,uniqueid);

                                }
                                if(g_pCGInterface->GetPetFilterGUI()->IsALChemyDegree11Checked() && data->m_itemClass ==11)
                                {
                                    PickAlChemyAction(ii.item_type, ii.item_id,uniqueid);

                                }
                                if(g_pCGInterface->GetPetFilterGUI()->IsALChemyDegree12Checked() && data->m_itemClass ==12)
                                {
                                    PickAlChemyAction(ii.item_type, ii.item_id,uniqueid);

                                }
                                if(g_pCGInterface->GetPetFilterGUI()->IsALChemyDegree13Checked() && data->m_itemClass ==13)
                                {
                                    PickAlChemyAction(ii.item_type, ii.item_id,uniqueid);

                                }
                                if(g_pCGInterface->GetPetFilterGUI()->IsALChemyDegree14Checked() && data->m_itemClass ==14)
                                {
                                    PickAlChemyAction(ii.item_type, ii.item_id,uniqueid);

                                }
                                if(g_pCGInterface->GetPetFilterGUI()->IsALChemyDegree15Checked() && data->m_itemClass ==15)
                                {
                                    PickAlChemyAction(ii.item_type, ii.item_id,uniqueid);

                                }
                                if (!Rebot::Equipment_TID_List.empty())
                                {

                                    std::list<int>::iterator it = std::find(Rebot::Equipment_TID_List.begin(), Rebot::Equipment_TID_List.end(), data->TID);
                                    if(it != Rebot::Equipment_TID_List.end())
                                    {
                                        if(g_pCGInterface->GetPetFilterGUI()->IsEQDegree01Checked() && data->m_itemClass <= 3)
                                        {
                                            PickAction(ii.item_type, ii.item_id,uniqueid);

                                        }
                                        if(g_pCGInterface->GetPetFilterGUI()->IsEQDegree02Checked() && data->m_itemClass <= 6 && data->m_itemClass >= 4)
                                        {
                                            PickAction(ii.item_type, ii.item_id,uniqueid);

                                        }
                                        if(g_pCGInterface->GetPetFilterGUI()->IsEQDegree03Checked() && data->m_itemClass <= 9 && data->m_itemClass >= 7)
                                        {
                                            PickAction(ii.item_type, ii.item_id,uniqueid);

                                        }
                                        if(g_pCGInterface->GetPetFilterGUI()->IsEQDegree04Checked() && data->m_itemClass <= 12 && data->m_itemClass >= 10)
                                        {
                                            PickAction(ii.item_type, ii.item_id,uniqueid);

                                        }
                                        if(g_pCGInterface->GetPetFilterGUI()->IsEQDegree05Checked() && data->m_itemClass <= 15 && data->m_itemClass >= 13)
                                        {
                                            PickAction(ii.item_type, ii.item_id,uniqueid);

                                        }
                                        if(g_pCGInterface->GetPetFilterGUI()->IsEQDegree06Checked() && data->m_itemClass <= 18 && data->m_itemClass >= 16)
                                        {
                                            PickAction(ii.item_type, ii.item_id,uniqueid);

                                        }
                                        if(g_pCGInterface->GetPetFilterGUI()->IsEQDegree07Checked() && data->m_itemClass <= 21 && data->m_itemClass >= 19)
                                        {
                                            PickAction(ii.item_type, ii.item_id,uniqueid);

                                        }
                                        if(g_pCGInterface->GetPetFilterGUI()->IsEQDegree08Checked() && data->m_itemClass <= 24 && data->m_itemClass >= 22)
                                        {
                                            PickAction(ii.item_type, ii.item_id,uniqueid);

                                        }
                                        if(g_pCGInterface->GetPetFilterGUI()->IsEQDegree09Checked() && data->m_itemClass <= 27 && data->m_itemClass >= 25)
                                        {
                                            PickAction(ii.item_type, ii.item_id,uniqueid);

                                        }
                                        if(g_pCGInterface->GetPetFilterGUI()->IsEQDegree10Checked() && data->m_itemClass <= 30 && data->m_itemClass >= 28)
                                        {
                                            PickAction(ii.item_type, ii.item_id,uniqueid);

                                        }
                                        if(g_pCGInterface->GetPetFilterGUI()->IsEQDegree11Checked() && data->m_itemClass <= 33 && data->m_itemClass >= 31)
                                        {
                                            PickAction(ii.item_type, ii.item_id,uniqueid);

                                        }
                                        if(g_pCGInterface->GetPetFilterGUI()->IsEQDegree12Checked() && data->m_itemClass <= 36 && data->m_itemClass >= 34)
                                        {
                                            PickAction(ii.item_type, ii.item_id,uniqueid);

                                        }
                                        if(g_pCGInterface->GetPetFilterGUI()->IsEQDegree13Checked() && data->m_itemClass <= 39 && data->m_itemClass >= 37)
                                        {
                                            PickAction(ii.item_type, ii.item_id,uniqueid);

                                        }
                                        if(g_pCGInterface->GetPetFilterGUI()->IsEQDegree14Checked() && data->m_itemClass <= 42 && data->m_itemClass >= 40)
                                        {
                                            PickAction(ii.item_type, ii.item_id,uniqueid);

                                        }
                                        if(g_pCGInterface->GetPetFilterGUI()->IsEQDegree15Checked() && data->m_itemClass <= 45 && data->m_itemClass >= 43)
                                        {
                                            PickAction(ii.item_type, ii.item_id,uniqueid);

                                        }
                                    }
                                }
                            }
                        }
                    }
                }

            }
        }
    }
}
