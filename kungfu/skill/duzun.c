// SKILL: duzun.c 惟我毒尊 温家的特殊基本武功
// Created by Zeus 1999.5.1
// Modified by Zeus 1999.5.7
// 
// 
inherit SKILL;

mapping *action = ({
([	"action" : "$N左手护胸，右手变掌，正是一招「万毒起头难」",
	"damage" : 5,
	"parry"  : -20,
	"force"  : 10,
	"lvl"  : 0,
	"dodge"  : 5,
	"skill_name" : "万毒起头难",
        "damage_type" : "瘀伤"
]),
([	"action" : "$N一招「小毒初成」，双手手掌拍出一阵橙雾",
	"damage" : 10,
	"parry"  : -15,
	"force"  : 15,
	"lvl"  : 7,
	"dodge"  : 10,
	"skill_name" : "小毒初成",
        "damage_type" : "内伤"
]),
([	"action" : "$N一招「毒中毒」，左手手掌拍出一阵橙雾，右手手指指尖又飘出一团青雾",
	"damage" : 15,
	"parry"  : -10,
	"force"  : 20,
	"lvl"  : 14,
	"dodge"  : 15,
	"skill_name" : "毒中毒",
        "damage_type" : "内伤"
]),
([	"action" : "$N双手平行指出向$n胸前，左手指肺，右手指心，一招「毒心毒肺」",
	"damage" : 15,
	"parry"  : -10,
	"force"  : 20,
	"lvl"  : 21,
	"dodge"  : 15,
	"skill_name" : "毒心毒肺",
        "damage_type" : "刺伤"
]),
([	"action" : "$N双手回防，胸缩吸气，一招「毒口喷人」，口中喷出一团气流",
	"damage" : 20,
	"parry"  : -5,
	"force"  : 25,
	"lvl"  : 28,
	"dodge"  : 20,
	"skill_name" : "毒口喷人",
        "damage_type" : "内伤"
]),
([	"action" : "$N右手五指张开，做出一副捧书样，左手指出一团橙雾，正是一招「挑灯夜毒」",
	"damage" : 20,
	"parry"  : -5,
	"force"  : 25,
	"lvl"  : 35,
	"dodge"  : 20,
	"skill_name" : "挑灯夜毒",
        "damage_type" : "内伤"
]),
([	"action" : "$N身形变快，左右手四周乱指，顿时周围布满毒雾，这是一招「寒窗苦毒」",
	"damage" : 25,
	"parry"  : 0,
	"force"  : 30,
	"lvl"  : 42,
	"dodge"  : 25,
	"skill_name" : "寒窗苦毒",
        "damage_type" : "内伤"
]),
([	"action" : "$N使出「毒挡一面」，毒物顺着双手手指飞向$n的面前，组成一层毒雾",
	"damage" : 35,
	"parry"  : 0,
	"force"  : 30,
	"lvl"  : 49,
	"dodge"  : 30,
	"skill_name" : "毒挡一面",
        "damage_type" : "内伤"
]),
([	"action" : "$N右手从胸前一摸，摸出一团毒素，向$n飞去，一招「毒素一掷」",
	"damage" : 40,
	"parry"  : 10,
	"force"  : 35,
	"lvl"  : 56,
	"dodge"  : 35,
	"skill_name" : "毒素一掷",
        "damage_type" : "内伤"
]),
([	"action" : "$N一招「毒日入脸」，手掌竟然发出光芒，光芒射向$n脸上",
	"damage" : 45,
	"parry"  : 15,
	"force"  : 40,
	"lvl"  : 63,
	"dodge"  : 40,
	"skill_name" : "毒日入脸",
        "damage_type" : "刺伤"
]),
([	"action" : "$N左手摸出一节小木条，右手在木条上一摸，马上向$n掷去，正是一招「毒端钻心」",
	"damage" : 50,
	"parry"  : 20,
	"force"  : 45,
	"lvl"  : 70,
	"dodge"  : 50,
	"skill_name" : "毒端钻心",
        "damage_type" : "刺伤"
]),
([	"action" : "$N双手虚抱圆圈，突然双手向$n的心口指去，这是一招「毒聚将心」",
	"damage" : 60,
	"parry"  : 30,
	"force"  : 55,
	"lvl"  : 77,
	"dodge"  : 60,
	"skill_name" : "毒聚将心",
        "damage_type" : "内伤"
]),
([	"action" : "$N双手不断排出紫雾，接着一招「毒出心拆」，马上向$n的心窝攻去",
	"damage" : 70,
	"parry"  : 40,
	"force"  : 70,
	"lvl"  : 85,
	"dodge"  : 80,
	"skill_name" : "毒出心拆",
        "damage_type" : "内伤"
]),
});

int valid_enable(string usage) { return (usage == "lphand"); }


string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 50)
                return notify_fail("你的内力不够。\n");
        if ((int)me->query_skill("zhixin", 1) < 20)
                return notify_fail("你的「温故知新」火候不够。\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
		level   = (int) me->query_skill("duzun",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if (objectp(weapon = me->query_temp("weapon")))
                return notify_fail("练习「惟我毒尊」不能持有武器\n");
	if ((int)me->query("qi") < 40)
		return notify_fail("你太累了，还是歇一会再练吧。。\n");
	me->add("qi",-20);
        return 1;
}
