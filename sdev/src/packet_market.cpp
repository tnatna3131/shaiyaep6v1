#include <util/util.h>
#include "include/main.h"

unsigned u0x486320 = 0x486320;
void __declspec(naked) naked_0x486319()
{
    __asm
    {
        movzx eax,byte ptr[ebp+0x5]
        // ItemMarketType::Vehicle
        cmp eax,0x13
        jge decrement

        original:
        lea ecx,[ebp+0x7]
        jmp u0x486320

        decrement:
        dec eax
        jmp original
    }
}

void hook::packet_market()
{
    // CUser::PacketMarket case 0x1C01
    util::detour((void*)0x486319, naked_0x486319, 7);
}
