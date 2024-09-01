#include "include/shaiya/include/CMob.h"
#include "include/shaiya/include/SkillInfo.h"
using namespace shaiya;

void CMob::UseSkill(CMob* mob/*edi*/, ULONG time, CUser* user/*edx*/, SkillInfo* info/*eax*/)
{
    Address u0x4B9280 = 0x4B9280;

    __asm
    {
        push time
        mov eax,info
        mov edx,user
        mov edi,mob
        call u0x4B9280
    }
}

void CMob::SendLogBossMob(CMob* mob/*edx*/, UINT byAction, const char* text3/*edi*/, const char* text4, ULONG damage)
{
    Address u0x4B62C0 = 0x4B62C0;

    __asm
    {
        push damage
        push text4
        push byAction

        lea edi,[text3]
        mov edx,mob
        call u0x4B62C0
    }
}

void CMob::SetAttack(CMob* mob/*esi*/)
{
    Address u0x4A0DB0 = 0x4A0DB0;

    __asm
    {
        mov esi,mob
        call u0x4A0DB0
    }
}

void CMob::SetSkillAbility(CMob* mob/*edx*/, int _type/*ecx*/, int value/*eax*/)
{
    Address u0x4B5A70 = 0x4B5A70;

    __asm
    {
        mov eax,value
        mov ecx,_type
        mov edx,mob
        call u0x4B5A70
    }
}

void CMob::SetStatus(CMob* mob/*eax*/, int status/*ecx*/)
{
    Address u0x4A12C0 = 0x4A12C0;

    __asm
    {
        mov ecx,status
        mov eax,mob
        call u0x4A12C0
    }
}
