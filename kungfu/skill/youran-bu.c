// youran-bu.c  

#include <ansi.h>
inherit SKILL;
string *dodge_msg = ({
    HIM "$n漫不经心的向左迈出一步，刚好避过了这个凌厉的攻势。\n"NOR,
     YEL"可是$n恰巧往右走了一步，躲过了这一招。\n"NOR,
        WHT "但是$n身形飘忽，轻轻一纵，早已避开。\n"NOR,
         HIC"$n身随意转，倏地往一旁挪开了三尺，避过了这一招。\n"NOR,
       CYN "可是$n侧身一让，结果这一招扑了个空。\n"NOR,
       HIY "却见$n足不点地，往旁窜开数尺，躲了开去。\n"NOR,
         HIW"$n身形微晃，有惊无险地避开了这一招。\n"NOR,
});

int valid_enable(string usage) { return (usage == "dodge") || (usage == "move"); }

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( (int)me->query("qi") < 40 )
                return notify_fail("你的体力太差了，无法悠然来往。\n");
        me->receive_damage("qi", 20);
        return 1;
}

