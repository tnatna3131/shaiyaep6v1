#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct BillingItem
    {
        UINT8 type;
        UINT8 typeId;
        UINT8 count;
    };
    #pragma pack(pop)
}
