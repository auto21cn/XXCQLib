// SKILL: bupangguan.c 袖手不旁观
// Created by Zeus 1999.5.11
// Modified by Zeus 1999.5.11
// 
// 
inherit SKILL;

mapping *action = ({
([	"action" : "$N身形向前猛冲，双手急动，使出一招「见义勇为」。",
//	"parry_action" : "",
	"damage" : 50,
	"parry"  : 10,
	"force"  : 20,
	"lvl"  : 0,
	"dodge"  : 20,
	"skill_name" : "见义勇为",
        "damage_type" : "瘀伤"
]),
([	"action" : "$N右手做出一个拔刀的动作，使出「拔刀相助」，身子向前急冲。",
//	"parry_action" : "",
	"damage" : 50,
	"parry"  : 10,
	"force"  : 20,
	"lvl"  : 20,
	"dodge"  : 20,
	"skill_name" : "拔刀相助",
        "damage_type" : "瘀伤"
]),
([	"action" : "$N身子的攻势突然减慢，右手向前拍出几掌，正是一招「打抱不平」。",
//	"parry_action" : "",
	"damage" : 50,
	"parry"  : 10,
	"force"  : 20,
	"lvl"  : 40,
	"dodge"  : 20,
	"skill_name" : "打抱不平",
        "damage_type" : "瘀伤"
]),
([	"action" : "$N的双眼闪烁出青光，一招「冷眼不旁观」使出，攻势顿时凌厉起来。",
//	"parry_action" : "",
	"damage" : 70,
	"parry"  : 30,
	"force"  : 40,
	"lvl"  : 60,
	"dodge"  : 50,
	"skill_name" : "冷眼不旁观",
        "damage_type" : "瘀伤"
]),
([	"action" : "$N将上升之中的身子转向$n，双手拍出几团青雾，正是一招「不作壁上观」。",
//	"parry_action" : "",
	"damage" : 70,
	"parry"  : 30,
	"force"  : 40,
	"lvl"  : 80,
	"dodge"  : 50,
	"skill_name" : "不作壁上观",
        "damage_type" : "瘀伤"
]),
([	"action" : "$N的身子刚要坐下，突然弹起，使出「坐视要救」，双掌向$n拍去。",
//	"parry_action" : "",
	"damage" : 70,
	"parry"  : 30,
	"force"  : 40,
	"lvl"  : 100,
	"dodge"  : 50,
	"skill_name" : "坐视要救",
        "damage_type" : "瘀伤"
]),
});

int valid_enable(string usage) { return (usage == "lphand") || (usage == "parry");  }


string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 200)
                return notify_fail("你的内力不够。\n");
        if ((int)me->query_skill("zhixin", 1) < 20)
                return notify_fail("你的「温故知新」火候不够。\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
		level   = (int) me->query_skill("duzi-du",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if (objectp(weapon = me->query_temp("weapon")))
                return notify_fail("练习「袖手不旁观」不能持有武器\n");
	if ((int)me->query("qi") < 60)
		return notify_fail("你太累了，还是歇一会再练吧。。\n");
	me->add("qi",-30);
        return 1;
}
