#include <strsafe.h>
#include <shaiya/include/common/SConnection.h>
#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/include/CItem.h"
#include "include/shaiya/include/CGameData.h"
#include "include/shaiya/include/CQuest.h"
#include "include/shaiya/include/CQuestData.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/Helpers.h"
#include "include/shaiya/include/ItemInfo.h"
#include "include/shaiya/include/network/game/outgoing/0900.h"
#include "include/shaiya/include/network/gameLog/incoming/0500.h"
using namespace shaiya;

namespace npc_quest
{
    void send_admin_remove(CUser* user, CQuest* quest)
    {
        QuestEndResultOutgoing outgoing{};
        outgoing.questId = quest->questInfo->questId;
        SConnection::Send(&user->connection, &outgoing, sizeof(QuestEndResultOutgoing));
    }

    void send_failure_result(CUser* user, CQuest* quest, uint32_t npcId)
    {
        QuestEndResultOutgoing outgoing{};
        outgoing.npcId = npcId;
        outgoing.questId = quest->questInfo->questId;
        SConnection::Send(&user->connection, &outgoing, sizeof(QuestEndResultOutgoing));
    }

    void send_success_result(CUser* user, CQuest* quest, uint32_t npcId, uint8_t index)
    {
        if (index >= quest->questInfo->results.size())
            return;

        auto& result = quest->questInfo->results[index];
        auto exp = result.exp;

        if (exp)
        {
            auto rate = user->skillAbility.type87QuestExpRate;
            exp = (rate >= 200) ? exp * (rate / 100) : exp;
            CUser::AddExpFromUser(user, 0, exp, true);
        }

        if (result.gold)
        {
            CUser::ChkAddMoneyGet(user, result.gold);
            CUser::SendDBMoney(user);
        }

        GameLogQuestEndResultIncoming log{};
        CUser::SetGameLogMain(user, &log);
        log.questId = quest->questInfo->questId;
        StringCbCopyA(log.questName.data(), log.questName.size(), quest->questInfo->questName.data());
        log.success = true;
        log.gold = result.gold;

        QuestEndResultOutgoing outgoing{};
        outgoing.npcId = npcId;
        outgoing.questId = quest->questInfo->questId;
        outgoing.success = true;
        outgoing.index = index;
        outgoing.exp = exp;
        outgoing.gold = result.gold;

#ifdef SHAIYA_EP6_4_PT
        for (int i = 0; std::cmp_less(i, result.items.size()); ++i)
        {
            int type = result.items[i].type;
            int typeId = result.items[i].typeId;
            int count = result.items[i].count;

            int bag{}, slot{};
            ItemInfo itemInfo{};
            if (CUser::QuestAddItem(user, type, typeId, count, &bag, &slot, &itemInfo))
            {
                outgoing.itemList[i].count = count;
                outgoing.itemList[i].bag = bag;
                outgoing.itemList[i].slot = slot;
                outgoing.itemList[i].type = type;
                outgoing.itemList[i].typeId = typeId;

                log.itemId = itemInfo.itemId;
                log.itemCount = count;
                log.itemName = itemInfo.itemName;
            }
            else
            {
                outgoing.itemList[i].count = 0;
                outgoing.itemList[i].bag = 0;
                outgoing.itemList[i].slot = 0;
                outgoing.itemList[i].type = 0;
                outgoing.itemList[i].typeId = 0;

                log.itemId = 0;
                log.itemCount = 0;
                log.itemName[0] = '\0';
            }

            Helpers::SendGameLog(&log, sizeof(GameLogQuestEndResultIncoming));
        }
#endif

        SConnection::Send(&user->connection, &outgoing, sizeof(QuestEndResultOutgoing));
        CUser::QuestRemove(user, quest, true);
    }
}

unsigned u0x48D237 = 0x48D237;
void __declspec(naked) naked_0x48D1F2()
{
    __asm
    {
        pushad

        push ebp // quest
        push ebx // user
        call npc_quest::send_admin_remove
        add esp,0x8

        popad

        jmp u0x48D237
    }
}

unsigned u0x48DC91 = 0x48DC91;
void __declspec(naked) naked_0x48DC3D()
{
    __asm
    {
        // original
        mov ecx,[esp+0xE0]

        pushad

        push ecx // npcId
        push ebx // quest
        push edi // user
        call npc_quest::send_failure_result
        add esp,0xC

        popad

        jmp u0x48DC91
    }
}

unsigned u0x48E029 = 0x48E029;
void __declspec(naked) naked_0x48DE38()
{
    __asm
    {
        pushad

        mov ecx,[esp+0x114]

        push edx // index
        push ecx // npcId
        push ebx // quest
        push edi // user
        call npc_quest::send_success_result
        add esp,0x10

        popad

        jmp u0x48E029
    }
}

void hook::npc_quest()
{
    // CUser::QuestRemoveAdmin
    util::detour((void*)0x48D1F2, naked_0x48D1F2, 9);
    // CUser::QuestEnd
    util::detour((void*)0x48DC3D, naked_0x48DC3D, 11);
    // CUser::QuestSuccessResult
    util::detour((void*)0x48DE38, naked_0x48DE38, 5);
}
