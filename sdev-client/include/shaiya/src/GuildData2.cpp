#include "include/shaiya/include/GuildData2.h"
using namespace shaiya;

GuildData2* GuildData2::Find(ULONG guildId)
{
    typedef GuildData2* (__thiscall* LPFN)(void*, ULONG);
    return (*(LPFN)0x4446E0)((void*)0x22AF6DC, guildId);
}
