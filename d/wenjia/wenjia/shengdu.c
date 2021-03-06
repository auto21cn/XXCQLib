// SKILL: shengdu.c 声毒
// Created by Zeus 1999.4.30
// Modified by Zeus 1999.6.8
// 修改武功威力。
// 原著武功所有人：温文人。
 
inherit SKILL;

mapping *action = ({
([	"action" : "$N弹起手中的琵琶，用「宫」调弹起了一曲「阳春古曲」。",
//	"parry_action" : "",
	"damage" : 10,
	"parry"  : 0,
	"force"  : 10,
	"lvl"  : 0,
	"dodge"  : 0,
	"skill_name" : "阳春古曲",
        "damage_type" : "内伤"
]),
([	"action" : "$N的手指一拨，竟然用「变宫」调弹起了「十面埋伏」。",
//	"parry_action" : "",
	"damage" : 20,
	"parry"  : -10,
	"force"  : 20,
	"lvl"  : 15,
	"dodge"  : -10,
	"skill_name" : "十面埋伏",
        "damage_type" : "内伤"
]),
([	"action" : "$N将手中的古琴平放，随着手指波动，正是用「商」调弹出的「高山流水」。",
//	"parry_action" : "",
	"damage" : 40,
	"parry"  : -20,
	"force"  : 40,
	"lvl"  : 30,
	"dodge"  : -20,
	"skill_name" : "高山流水",
        "damage_type" : "内伤"
]),
([	"action" : "$N的手指在古琴的弦上波动，一曲「平沙落雁」正是用「角」调演奏出来。",
//	"parry_action" : "",
	"damage" : 40,
	"parry"  : -30,
	"force"  : 60,
	"lvl"  : 45,
	"dodge"  : -30,
	"skill_name" : "平沙落雁",
        "damage_type" : "内伤"
]),
([      "action" : "只看到$N的手指放在古琴上，也没动，正是用「徵」调演奏的「阳关三叠」",
//	"parry_action" : "",
	"damage" : 40,
	"parry"  : -40,
	"force"  : 80,
	"lvl"  : 60,
	"dodge"  : -40,
	"skill_name" : "阳关三叠",
        "damage_type" : "内伤"
]),
([	"action" : "$N从怀里摸出一个东西，却是没见过的东西，这时一曲用「变徵」调的「胡笳十八拍」响了起来。",
//	"parry_action" : "",
	"damage" : 100,
	"parry"  : -60,
	"force"  : 80,
	"lvl"  : 100,
	"dodge"  : -50,
	"skill_name" : "胡笳十八拍",
        "damage_type" : "内伤"
]),
([	"action" : "$N从怀里拿出一样$n没见过的乐器，其实$n也无法确定那是否乐器，只因它上面有两根弦，$N用「羽」调演奏出了一曲失传已久的「广陵散」。",
//	"parry_action" : "",
	"damage" : 120,
	"parry"  : -80,
	"force"  : 100,
	"lvl"  : 130,
	"dodge"  : -70,
	"skill_name" : "广陵散",
        "damage_type" : "内伤"
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
        if ((int)me->query("max_neili") < 500)
                return notify_fail("内力不够深厚怎样把毒放出去!\n");
        if ((int)me->query_skill("lphand", 1) < 50)
                return notify_fail("「施毒手法」不够深厚如何施毒!\n");
        if ((int)me->query_skill("zhixin", 1) < 50)
                return notify_fail("「温故知新」火候不够如何施出有威力的毒!\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
		level   = (int) me->query_skill("shengdu",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if (objectp(weapon = me->query_temp("weapon")))
                return notify_fail("「声毒」是用「施毒手法」施毒的，不能有武器!\n");
        if ((int)me->query("jingli") < 40)
        return notify_fail("歇一会吧，这样练是不会有效果的!\n");
        me->add("jingli",-30);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"shengdu/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        if( me->query_skill("shengdu",1) > 50 )
                victim->apply_condition("shengdu_poison", random(me->query_skill("shengdu",1)/10) + 1 + victim->query_condition("shengdu_poison"));
}
