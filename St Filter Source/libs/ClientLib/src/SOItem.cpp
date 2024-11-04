#include "SOItem.h"
#include "ObjectData.h"
#include "GlobalDataManager.h"


ObjectData* CSOItem::GetObjectData(void)
{
    return reinterpret_cast<ObjectData*(__thiscall*)(CSOItem*)>(0x008BA440)(this);
}
int CSOItem::GetItemId() const {
    return dwObjID;
}
const CItemData *CSOItem::GetItemData() const {
    const CItemData *data = NULL;

    if (dwObjID != 0) {
        data = g_CGlobalDataManager->GetItemData(dwObjID);
    }

    return data;
}
int CSOItem::GetQuantity() const {
    return m_quantity;
}
void CSOItem::CreateObject()
{
    reinterpret_cast<void (__thiscall *)(CSOItem *)>(0x008bef90)(this);
}
void CSOItem::DestructorObject()
{
    reinterpret_cast<void (__thiscall *)(CSOItem *)>(0x008bedd0)(this);
}