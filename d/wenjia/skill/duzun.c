// SKILL: duzun.c 惟我毒尊 
// Created by Zeus 1999.5.1
// Modified by Zeus 1999.6.8
// 增加perform 惟我独尊
// 原著武功所有人：无。自创，威力最大。
 
inherit SKILL;

mapping *action = ({
([      "action" : "$N左手护胸，右手变掌，正是一招「惟我毒尊」",
        "damage" : 15,
        "parry"  : -10,
        "force"  : 15,
        "lvl"  : 0,
        "dodge"  : -10,
        "skill_name" : "惟我毒尊",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N一招「买毒还珠」，双手手掌拍出一阵橙雾",
        "damage" : 20,
        "parry"  : -15,
        "force"  : 25,
        "lvl"  : 15,
        "dodge"  : -15,
        "skill_name" : "买毒还珠",
        "damage_type" : "内伤"
]),
([      "action" : "$N一招「穷兵毒武」，左手手掌拍出一阵橙雾，右手手指指尖又飘出一团青雾",
        "damage" : 25,
        "parry"  : -20,
        "force"  : 35,
        "lvl"  : 30,
        "dodge"  : -20,
        "skill_name" : "穷兵毒武",
        "damage_type" : "内伤"
]),
([      "action" : "$N双手平行指出向$n胸前，左手指肺，右手指心，一招「毒心毒肺」",
        "damage" : 35,
        "parry"  : -25,
        "force"  : 45,
        "lvl"  : 45,
        "dodge"  : -25,
        "skill_name" : "毒心毒肺",
        "damage_type" : "内伤"
]),
([	"action" : "$N双手回防，胸缩吸气，一招「毒口喷人」，口中喷出一团气流",
	"damage" : 45,
        "parry"  : -30,
        "force"  : 55,
        "lvl"  : 60,
        "dodge"  : -30,
        "skill_name" : "毒口喷人",
        "damage_type" : "内伤"
]),
([      "action" : "$N右手五指张开，做出一副捧书样，左手指出一团橙雾，正是一招「挑灯夜毒」",
        "damage" : 55,
        "parry"  : -35,
        "force"  : 60,
        "lvl"  : 75,
        "dodge"  : -35,
        "skill_name" : "挑灯夜毒",
        "damage_type" : "内伤"
]),
([      "action" : "$N身形变快，左右手四周乱指，顿时周围布满毒雾，这是一招「寒窗苦毒」",
        "damage" : 65,
        "parry"  : -40,
        "force"  : 65,
        "lvl"  : 90,
        "dodge"  : -40,
        "skill_name" : "寒窗苦毒",
        "damage_type" : "内伤"
]),
([      "action" : "$N使出「毒当一面」，毒物顺着双手手指飞向$n的面前，组成一层毒雾",
        "damage" : 75,
        "parry"  : -45,
        "force"  : 75,
        "lvl"  : 105,
        "dodge"  : -45,
        "skill_name" : "毒当一面",
        "damage_type" : "内伤"
]),
([      "action" : "$N右手从胸前一摸，摸出一团毒素，向$n飞去，一招「毒树一帜」",
        "damage" : 80,
        "parry"  : -50,
        "force"  : 85,
        "lvl"  : 120,
        "dodge"  : -50,
        "skill_name" : "毒树一帜",
        "damage_type" : "内伤"
]),
([      "action" : "$N一招「毒日如年」，手掌竟然发出光芒，光芒射向$n脸上",
        "damage" : 90,
        "parry"  : -55,
        "force"  : 95,
        "lvl"  : 135,
        "dodge"  : -55,
        "skill_name" : "毒日如年",
        "damage_type" : "内伤"
]),
([      "action" : "$N左手摸出一节小木条，右手在木条上一摸，马上向$n掷去，正是一招「毒断专行」",
        "damage" : 100,
        "parry"  : -65,
        "force"  : 90,
        "lvl"  : 150,
        "dodge"  : -65,
        "skill_name" : "毒断专行",
        "damage_type" : "内伤"
]),
([      "action" : "$N双手虚抱圆圈，突然双手向$n的心口指去，这是一招「毒具匠心」",
        "damage" : 130,
        "parry"  : -80,
        "force"  : 100,
        "lvl"  : 175,
        "dodge"  : -80,
        "skill_name" : "毒具匠心",
        "damage_type" : "内伤"
]),
([      "action" : "$N双手不断排出紫雾，接着一招「毒出心裁」，马上向$n的心窝攻去",
        "damage" : 150,
        "parry"  : -100,
        "force"  : 130,
        "lvl"  : 200,
        "dodge"  : -100,
        "skill_name" : "毒出心裁",
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
        if ((int)me->query("max_neili") < 1000)
                return notify_fail("「惟我毒尊」需要很深厚的内力!\n");
        if ((int)me->query_skill("lphand", 1) < 100)
                return notify_fail("「惟我毒尊」需要很熟练的「施毒手法」!\n");
        if ((int)me->query_skill("zhixin", 1) < 100)
                return notify_fail("「惟我毒尊」需要很深厚的内功!\n");
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
                return notify_fail("「惟我毒尊」是用「施毒手法」放毒的，不是用武器放毒的!\n");
        if ((int)me->query("qi") < 50)
                return notify_fail("在疲劳的时候练习「惟我毒尊」是没有用的!\n");
        me->add("qi",-40);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"duzun/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        victim->apply_condition("duzun_poison", random(me->query_skill("duzun",1)/10) + 1 + victim->query_condition("duzun_poison"));
}
