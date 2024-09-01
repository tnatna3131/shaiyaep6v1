#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/CraftName.h>
#include <shaiya/include/common/Gems.h>
#include <shaiya/include/common/MakeType.h>
#include <shaiya/include/common/SNode.h>
#include "include/shaiya/include/SVector.h"

namespace shaiya
{
    struct CZone;
    struct ItemInfo;

    enum struct ItemDropType : UINT8
    {
        User = 1,
        Mob
    };

    #pragma pack(push, 1)
    struct CItem
    {
        SNode node;                //0x00
        SVector zonePos;           //0x08
        ULONG zoneItemId;          //0x14
        CZone* zone;               //0x18
        UINT32 zoneCellX;          //0x1C
        UINT32 zoneCellZ;          //0x20
        PAD(12);
        ItemInfo* itemInfo;        //0x30
        PAD(4);
        UINT64 uniqueId;           //0x38
        UINT8 type;                //0x40
        UINT8 typeId;              //0x41
        UINT8 count;               //0x42
        PAD(1);
        UINT16 quality;            //0x44
        Gems gems;                 //0x46
        CraftName craftName;       //0x4C
        PAD(3);
        ULONG makeTime;            //0x64
        MakeType makeType;         //0x68
        PAD(3);
        DWORD enablePickTick;      //0x6C
        ULONG enablePickId;        //0x70
        ULONG enablePickPartyId;   //0x74
        ItemDropType dropType;     //0x78
        PAD(3);
        // user->id, mobId (e.g., 835)
        ULONG dropId;              //0x7C
        // type 26 (gold)
        UINT32 dropMoney;          //0x80
        UINT16 craftStrength;      //0x84
        UINT16 craftDexterity;     //0x86
        UINT16 craftReaction;      //0x88
        UINT16 craftIntelligence;  //0x8A
        UINT16 craftWisdom;        //0x8C
        UINT16 craftLuck;          //0x8E
        // value * 100
        UINT16 craftHealth;        //0x90
        // value * 100
        UINT16 craftMana;          //0x92
        // value * 100
        UINT16 craftStamina;       //0x94
        UINT16 craftAttackPower;   //0x96
        UINT16 craftAbsorption;    //0x98
        PAD(2);
        // cash shop
        UINT32 purchaseNumber;     //0x9C
        // 0xA0

        static char GetEnchantStep(CItem* item/*edx*/);
        static int GetGemCount(CItem* item/*ecx*/);
        static int GetGemSlot(CItem* item/*ecx*/);
        static void InitCraftExpansion(CItem* item/*eax*/);
        /*itemInfo->itemRealType == 22 or 23 or 25*/
        static bool IsAccessory(CItem* item/*eax*/);
        /*itemInfo->itemRealType >= 1 and <= 25*/
        static bool IsEquipment(CItem* item/*eax*/);
        static bool IsEquipSex(CItem* item/*eax*/, int bySex/*ecx*/);
        /*itemInfo->type == 43*/
        static bool IsEtin(CItem* item/*eax*/);
        /*itemInfo->itemRealType == 27*/
        static bool IsQuest(CItem* item/*eax*/);
        /*itemInfo->itemRealType == 1 or 3 or 7 or 9*/
        static bool IsOneHandWeapon(CItem* item/*eax*/);
        /*itemInfo->itemRealType == 19*/
        static bool IsShield(CItem* item/*eax*/);
        /*itemInfo->itemRealType >= 1 and <= 15*/
        static bool IsWeapon(CItem* item/*eax*/);
        static void ReGenerationCraftExpansion(CItem* item/*esi*/, BOOL compose);
    };
    #pragma pack(pop)

    static_assert(sizeof(CItem) == 0xA0);
}
