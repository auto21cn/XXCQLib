// tianyu-bufa.c 天羽步法

inherit SKILL;
#include <ansi.h>

mapping *action = ({
([      "action" : "$n一式「单燕南飞」，左脚脚尖垫起，右脚凌空发力，身体如行云流水般滑出丈余。\n",
        "dodge"  : 15
]),
([      "action" : "$n一式「一叶障目」，身行旋转，双脚跋地而起，顿时闪过了$N的凌厉攻势。\n",
        "dodge"  : 25
]),
([      "action" : "$n一式「分身幻影」，左右双足凌空踢出数脚，顿时落到$N的上空。\n",
        "dodge"  : 35
]),
([  "action" :     "$n，突然间身行前扑，象利箭般的冲向$N，令$N手无足措。\n",
        "dodge"  : 45
]),
([  "action" :    "$n一式「余音绕梁」，真气布满全身，围着$N急速旋转，令$N手忙脚乱，$n已落到几丈远的地方。\n",
        "dodge"  : 60
]),
([      "action" : "$n双足凌空点地，在剌剌风声中，从$N头顶横跃而过。\n",
        "dodge"  : 75
]),
([      "action" : "$n一式「燕子回头」，借力身行上飘，霎时间躲过$N的凌厉攻势。\n",
        "dodge"  : 90
]),
([ "action" : "$n身体如陀螺般急转，气流形成一个个漩涡，令$N陷身其间。\n",
        "dodge"  : 100
])
});

mapping query_action(object me, object weapon)
{
        int zhaoshu, level;

        zhaoshu = sizeof(action);
        level   = (int) me->query_skill("tianyu-bufa");

        if (level < 60 )
                zhaoshu--;

        if (level < 50 )
                zhaoshu--;

        if (level < 40 )
                zhaoshu--;
        if (random(me->query_skill("dodge")) > 100 &&
            me->query_skill("force") > 100 &&
            me->query("neili") > 1000) {
            me->add("neili",-5);
            return (["action" : HIW"$n身形斗转，脚步越转越快，陡然踏出「天羽步法」之奥妙，身形一晃\n已经绕到$N身后,令$N防不胜防!\n"NOR,
                     "dodge"  : 500
                          ]); 
            }
 
        return action[random(zhaoshu)];
}

int valid_enable(string usage)
{
        return usage == "dodge"||"move";
}

int valid_learn(object me)
{
        return 1;
}

string query_dodge_msg(string limb)
{
        object me, ob;
        mapping action;

        me = this_player();
        action = query_action(me, ob);

        return action["action"];
}
int practice_skill(object me)
{
        if( (int)me->query("jingli") < 40 )
                return notify_fail("你的精力太差了，不能练天羽步法。\n");
        me->add("jingli", -30);
        return 1;
}
