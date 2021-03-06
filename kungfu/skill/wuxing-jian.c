// wuxing-jian.c

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : BLU"$N好像就算准$n会向哪一个部位打来似的，每一出剑，就挑开了$n的武器"NOR,
        "force" : 60,
        "dodge" : 20,
        "parry" : 10,
        "damage" : 50+random(100)/10,
        "lvl" : 0,
        "damage_type" : "刺伤"
]),
([      "action" : BLU"$N目光收缩，已变得如剑般的锋利。一道极其尖锐的厉风，向$n飞袭而来"NOR,
        "force" : 70,
        "dodge" : 15,
        "parry" : 10,
        "damage" : 50+random(100)/5,
        "lvl" : 4,
        "damage_type" : "刺伤"
]),
([      "action" : BLU"$N的千万点剑锋都不见了。只剩下$w。剑快而急、准。$n发觉时，已避不开。$w已至咽喉。"NOR,
        "force" : 80,
        "dodge" : 15,
        "parry" : 10,
        "damage" : 80+random(100)/3,
        "lvl" : 9,
        "damage_type" : "刺伤"
]),
([      "action" : BLU"$N忽抬左手，把袖子一遮，就在$n的剑尖，刺中了袖子时，$N的右手忽然多了五柄剑，刺向$n的肚子。"NOR,
        "force" : 90,
        "dodge" : 15,
        "parry" : 10,
        "damage" : 80+random(100)/2,
        "lvl" : 14,
        "damage_type" : "刺伤"
]),
([      "action" : BLU"$N的脸色变了，人剑一合，就要飞贯过来。再在这时，$N手中又多了一柄剑!"NOR,
        "force" : 100,
        "dodge" : 15,
        "parry" : 15,
        "damage" : 80+random(100),
        "lvl" : 19,
        "damage_type" : "刺伤"
]),
([      "action" : BLU"$N的$w，却比铁枪还烈，钢杖还直，向$n直刺出去，从千变万幻，已到了毫无变化。"NOR,
        "force" : 110,
        "dodge" : 15,
        "parry" : 15,
        "damage" : 100+random(200)/5,
        "lvl" : 24,
        "damage_type" : "刺伤"
]),
([      "action" : BLU"$N手中突然又多了一柄剑。$w。这把$w一出，$n便败象显现。$n完全接不下剑招，一直败退。"NOR,
        "force" : 120,
        "dodge" : 10,
        "parry" : 15,
        "damage" : 100+random(200)/2,
        "lvl" : 29,
        "damage_type" : "刺伤"
]),
});


int valid_enable(string usage)
{ return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 500)
                return notify_fail("你的内力不够。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("wuxing-jian",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];

}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
            || (string)weapon->query("skill_type") != "sword")
           return notify_fail("你使用的武器不对。\n");
        if ((int)me->query("qi") < 100)
           return notify_fail("你的体力不够练无形剑法。\n");
        me->receive_damage("qi", 50);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"wuxing-jian/" + action;
}
