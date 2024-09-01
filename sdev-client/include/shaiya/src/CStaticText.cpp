#include "include/static.h"
#include "include/shaiya/include/CStaticText.h"
using namespace shaiya;

SStaticText* CStaticText::Create(const char* text)
{
    typedef SStaticText* (__thiscall* LPFN)(CStaticText*, const char*);
    return (*(LPFN)0x57C280)(g_var->camera.staticText, text);
}

void CStaticText::Draw(SStaticText* staticText, long x, long y, float z, D3DCOLOR color)
{
    typedef void(__thiscall* LPFN)(CStaticText*, SStaticText*, long, long, float, D3DCOLOR);
    (*(LPFN)0x57CA20)(g_var->camera.staticText, staticText, x, y, z, color);
}

long CStaticText::GetTextWidth(const char* text)
{
    typedef long(__thiscall* LPFN)(CStaticText*, const char*);
    return (*(LPFN)0x57CC70)(g_var->camera.staticText, text);
}
