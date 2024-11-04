#include "IFEquipment.h"
#include "IFSlotWithHelp.h"
#include "GInterface.h"


CSOItem* CIFEquipment::GetEquipmentObjectBySlot(BYTE SlotIndex)
{
    return reinterpret_cast<CSOItem*(__thiscall*)(CIFEquipment*, BYTE)>(0x006AB6E0)(this, SlotIndex);
}

bool CIFEquipment::OnCreateIMPL(long ln) {


    bool b = reinterpret_cast<bool (__thiscall *)(CIFEquipment *, long)>(0x006ac1c0)(this, ln);
    RECT rect_m_itempoint_title = {80, 270, 20, 15};
    RECT rect_m_itempoint = {80, 290, 20, 15};
    CIFStatic * m_itempoint_title = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect_m_itempoint_title, 11112, 0);
    m_itempoint = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect_m_itempoint, 11113, 0);
    int color = D3DCOLOR_ARGB(255, 0, 255, 0);
    m_itempoint_title->SetText(L"Item Point");
    m_itempoint_title->SetTextColor(color);
    m_itempoint_title->BringToFront();
    m_itempoint_title->ShowGWnd(true);
    m_itempoint->SetText(L"10000");
    m_itempoint->BringToFront();
    m_itempoint->SetTextColor(color);
    m_itempoint->ShowGWnd(true);

    return b;
}
void CIFEquipment::OnUpdateIMPL()
{
    int itempoint0 = 0;
    int itempoint1 = 0;
    int itempoint2 = 0;
    int itempoint3 = 0;
    int itempoint4 = 0;
    int itempoint5 = 0;
    int itempoint6 = 0;
    int itempoint7 = 0;
    int itempoint9 = 0;
    int itempoint10 = 0;
    int itempoint11 = 0;
    int itempoint12 = 0;
    if(g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(0) &&
       g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(0)->dwObjID != 0)
    {
        CSOItem* myitem = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(0);
        if(myitem && myitem != 0 && myitem != NULL)
        {
            int dmii0 = myitem->GetObjectData()->Rarity;
            int rqlevel0 = myitem->GetObjectData()->ReqLevel1;
            int otplevel0 = myitem->OptLevel;
            itempoint0 = otplevel0+rqlevel0+(dmii0*3);
        } else
        {
            itempoint0 = 0;
        }
    } else
    {
        itempoint0 = 0;
    }

    if(g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(1) &&
       g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(1)->dwObjID != 0)
    {
        CSOItem* myitem1 = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(1);
        if(myitem1 && myitem1 != 0 && myitem1 != NULL)
        {
            int dmii1 = myitem1->GetObjectData()->Rarity;
            int rqlevel1 = myitem1->GetObjectData()->ReqLevel1;
            int otplevel1 = myitem1->OptLevel;
            itempoint1 = otplevel1+rqlevel1+(dmii1*3);
        } else
        {
            itempoint1 = 0;
        }
    } else
    {
        itempoint1 = 0;
    }
    if(g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(2) &&
       g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(2)->dwObjID != 0)
    {
        CSOItem* myitem2 = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(2);
        if(myitem2 && myitem2 != 0 && myitem2 != NULL)
        {
            int dmii2 = myitem2->GetObjectData()->Rarity;
            int rqlevel2 = myitem2->GetObjectData()->ReqLevel1;
            int otplevel2 = myitem2->OptLevel;
            itempoint2 = otplevel2+rqlevel2+(dmii2*3);
        } else
        {
            itempoint2 = 0;
        }
    } else
    {
        itempoint2 = 0;
    }

    if(g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(3) &&
       g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(3)->dwObjID != 0)
    {
        CSOItem* myitem3 = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(3);
        if(myitem3 && myitem3 != 0 && myitem3 != NULL)
        {
            int dmii3 = myitem3->GetObjectData()->Rarity;
            int rqlevel3 = myitem3->GetObjectData()->ReqLevel1;
            int otplevel3 = myitem3->OptLevel;
            itempoint3 = otplevel3+rqlevel3+(dmii3*3);
        } else
        {
            itempoint3 = 0;
        }
    } else
    {
        itempoint3 = 0;
    }

    if(g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(4) &&
       g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(4)->dwObjID != 0)
    {
        CSOItem* myitem4 = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(4);
        if(myitem4 && myitem4 != 0 && myitem4 != NULL)
        {
            int dmii4 = myitem4->GetObjectData()->Rarity;
            int rqlevel4 = myitem4->GetObjectData()->ReqLevel1;
            int otplevel4 = myitem4->OptLevel;
            itempoint4 = otplevel4+rqlevel4+(dmii4*3);
        } else
        {
            itempoint4 = 0;
        }
    } else
    {
        itempoint4 = 0;
    }


    if(g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(5) &&
       g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(5)->dwObjID != 0)
    {
        CSOItem* myitem5 = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(5);
        if(myitem5 && myitem5 != 0 && myitem5 != NULL)
        {
            int dmii5 = myitem5->GetObjectData()->Rarity;
            int rqlevel5 = myitem5->GetObjectData()->ReqLevel1;
            int otplevel5 = myitem5->OptLevel;
            itempoint5 = otplevel5+rqlevel5+(dmii5*3);
        } else
        {
            itempoint5 = 0;
        }
    } else
    {
        itempoint5 = 0;
    }

    if(g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(6) &&
       g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(6)->dwObjID != 0)
    {
        CSOItem* myitem6 = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(6);
        if(myitem6 && myitem6 != 0 && myitem6 != NULL)
        {
            int dmii6 = myitem6->GetObjectData()->Rarity;
            int rqlevel6 = myitem6->GetObjectData()->ReqLevel1;
            int otplevel6 = myitem6->OptLevel;
            itempoint6 = otplevel6+rqlevel6+(dmii6*3);
        } else
        {
            itempoint6 = 0;
        }
    } else
    {
        itempoint6 = 0;
    }

    if(g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(7) &&
       g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(7)->dwObjID != 0)
    {
        CSOItem* myitem7 = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(7);
        if(myitem7 && myitem7 != 0 && myitem7 != NULL)
        {
            int dmii7 = myitem7->GetObjectData()->Rarity;
            int rqlevel7 = myitem7->GetObjectData()->ReqLevel1;
            int otplevel7 = myitem7->OptLevel;
            itempoint7 = otplevel7+rqlevel7+(dmii7*3);
        } else
        {
            itempoint7 = 0;
        }
    } else
    {
        itempoint7 = 0;
    }


    if(g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(9) &&
       g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(9)->dwObjID != 0)
    {
        CSOItem* myitem9 = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(9);
        if(myitem9 && myitem9 != 0 && myitem9 != NULL)
        {
            int dmii9 = myitem9->GetObjectData()->Rarity;
            int rqlevel9 = myitem9->GetObjectData()->ReqLevel1;
            int otplevel9 = myitem9->OptLevel;
            itempoint9 = otplevel9+rqlevel9+(dmii9*3);
        } else
        {
            itempoint9 = 0;
        }
    } else
    {
        itempoint9 = 0;
    }

    if(g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(10) &&
       g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(10)->dwObjID != 0)
    {
        CSOItem* myitem10 = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(10);
       if(myitem10 && myitem10 != 0 && myitem10 != NULL)
       {
           int dmii10 = myitem10->GetObjectData()->Rarity;
           int rqlevel10 = myitem10->GetObjectData()->ReqLevel1;
           int otplevel10 = myitem10->OptLevel;
           itempoint10 = otplevel10+rqlevel10+(dmii10*3);
       } else
       {
           itempoint10 = 0;
       }
    } else
    {
        itempoint10 = 0;
    }

    if(g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(11) &&
       g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(11)->dwObjID != 0)
    {
        CSOItem* myitem11 = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(11);
        if(myitem11 && myitem11 != 0 && myitem11 != NULL)
        {
            int dmii11 = myitem11->GetObjectData()->Rarity;
            int rqlevel11 = myitem11->GetObjectData()->ReqLevel1;
            int otplevel11 = myitem11->OptLevel;
            itempoint11 = otplevel11+rqlevel11+(dmii11*3);
        } else
        {
            itempoint11 = 0;
        }
    } else
    {
        itempoint11 = 0;
    }

    if(g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(12) &&
       g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(12)->dwObjID != 0)
    {
        CSOItem* myitem12 = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(12);
        if(myitem12 && myitem12 != 0 && myitem12 != NULL)
        {
            int dmii12 = myitem12->GetObjectData()->Rarity;
            int rqlevel12 = myitem12->GetObjectData()->ReqLevel1;
            int otplevel12 = myitem12->OptLevel;
            itempoint12 = otplevel12+rqlevel12+(dmii12*3);
        } else
        {
            itempoint12 = 0;
        }
    } else
    {
        itempoint12 = 0;
    }

    int itempointtotal = itempoint0+itempoint1+itempoint2+itempoint3+itempoint4+itempoint5+itempoint6+itempoint7+itempoint9+itempoint10+itempoint11+itempoint12;
    wchar_t buffer[255];
    swprintf_s(buffer, L"%d", itempointtotal);
    m_itempoint -> SetText(buffer);

    reinterpret_cast<void (__thiscall *)(CIFEquipment *)>(0x006ab6b0)(this);
}