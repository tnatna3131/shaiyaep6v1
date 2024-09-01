#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Country.h>
#include <shaiya/include/common/Family.h>
#include <shaiya/include/common/Gems.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/Job.h>
#include <shaiya/include/common/Sex.h>

namespace shaiya
{
    struct CItem;
    struct SConnection;

    using Inventory = Array<Array<CItem*, 24>, 6>;
    using Warehouse = Array<CItem*, 240>;
    using StoredPointItems = Warehouse;

    #pragma pack(push, 1)
    struct Equipment
    {
        Array<UINT8, 8> type;
        Array<UINT8, 8> typeId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct EquipmentEx
    {
        Array<UINT8, 24> type;
        Array<UINT8, 24> typeId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct Character
    {
        ULONG id;               //0x00
        ULONG regDate;          //0x04
        UINT8 slot;             //0x08
        Family family;          //0x09
        Grow grow;              //0x0A
        UINT8 hair;             //0x0B
        UINT8 face;             //0x0C
        UINT8 size;             //0x0D
        Job job;                //0x0E
        Sex sex;                //0x0F
        UINT16 level;           //0x10
        UINT16 strength;        //0x12
        UINT16 dexterity;       //0x14
        UINT16 reaction;        //0x16
        UINT16 intelligence;    //0x18
        UINT16 wisdom;          //0x1A
        UINT16 luck;            //0x1C
        UINT16 health;          //0x1E
        UINT16 mana;            //0x20
        UINT16 stamina;         //0x22
        UINT16 mapId;           //0x24
        PAD(2);
        ULONG deleteDate;       //0x28
        Equipment equipment;    //0x2C
        CloakBadge cloakBadge;  //0x3C
        CharArray<21> name;     //0x42
        PAD(1);
        bool nameChange;        //0x58
        PAD(3);
        // 0x5C
    };
    #pragma pack(pop)

    using CharacterList = Array<Character, 5>;

    #pragma pack(push, 1)
    struct ProductItem
    {
        PAD(4);
        CharArray<21> productCode;  //0x04
        PAD(3);
        ULONG purchaseDate;         //0x1C
        UINT32 itemPrice;           //0x20
        // 0x24
    };
    #pragma pack(pop)

    using ProductLog = Array<ProductItem, 10>;

    #pragma pack(push, 1)
    struct CUser
    {
        PAD(56);
        ULONG userId;                   //0x38
        UINT32 serverId;                //0x3C
        CharArray<32> username;         //0x40
        ULONG charId;                   //0x60
        UINT8 slot;                     //0x64
        Country country;                //0x65
        Grow maxGrow;                   //0x66
        Family family;                  //0x67
        Grow grow;                      //0x68
        UINT8 hair;                     //0x69
        UINT8 face;                     //0x6A
        UINT8 size;                     //0x6B
        Job job;                        //0x6C
        Sex sex;                        //0x6D
        UINT16 level;                   //0x6E
        UINT16 statPoint;               //0x70
        UINT16 skillPoint;              //0x72
        UINT32 exp;                     //0x74
        UINT32 money;                   //0x78
        UINT32 bankMoney;               //0x7C
        UINT32 kills;                   //0x80
        UINT32 deaths;                  //0x84
        UINT32 victories;               //0x88
        UINT32 defeats;                 //0x8C
        UINT16 killLv;                  //0x90
        PAD(2);
        UINT16 deathLv;                 //0x94
        PAD(2);
        UINT16 mapId;                   //0x98
        UINT16 direction;               //0x9A
        float posX;                     //0x9C
        float posY;                     //0xA0
        float posZ;                     //0xA4
        UINT16 honor;                   //0xA8
        INT16 vg;                       //0xAA
        UINT8 cg;                       //0xAC
        UINT8 og;                       //0xAD
        UINT16 ig;                      //0xAE
        UINT16 strength;                //0xB0
        UINT16 dexterity;               //0xB2
        UINT16 intelligence;            //0xB4
        UINT16 wisdom;                  //0xB6
        UINT16 reaction;                //0xB8
        UINT16 luck;                    //0xBA
        UINT16 health;                  //0xBC
        UINT16 mana;                    //0xBE
        UINT16 stamina;                 //0xC0
        PAD(6);
        CharArray<21> charName;         //0xC8
        PAD(3);
        Inventory inventory;            //0xE0
        Warehouse warehouse;            //0x320
        // 0x6E0
        PAD(13452);
        CharacterList characterList;    //0x3B6C
        // 0x3D38
        PAD(17236);
        CharArray<21> newCharName;      //0x808C
        // 0x80A1
        PAD(83);
        UINT32 points;                  //0x80F4
        ProductLog productLog;          //0x80F8
        CharArray<21> giftTargetName;   //0x8260
        CharArray<21> giftProductCode;  //0x8275
        PAD(2);
        UINT32 giftItemPrice;           //0x828C
        ULONG giftPurchaseDate;         //0x8290
        UINT32 giftPurchaseNumber;      //0x8294
        StoredPointItems giftItems;     //0x8298
        ULONG purchaseTargetId;         //0x8658
        UINT32 purchaseNumber;          //0x865C
        PAD(408);
        SConnection* connection;        //0x87F8
        PAD(92);
        // 0x8858

        // custom
        Array<EquipmentEx, 5> equipmentEx;
    };
    #pragma pack(pop)

    //static_assert(sizeof(CUser) == 0x8858);
    static_assert(sizeof(CUser) == 0x8948);
}
