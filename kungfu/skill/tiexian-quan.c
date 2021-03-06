// tiexian-quan.c 铁线拳
// 平均damage:120 平均force:90 平均dodge:5 平均parry:-5
// 铁线拳的特点在于威力较大，招架较难，躲避较易
// By Load

inherit SKILL;

mapping *action = ({
([	"action" : "$N左臂横扫，右拳带着锐器破空之声直击而出，一式「横冲直撞」，照$n的$l打去。",
	"damage" : 60,
	"parry"  : -5,
	"force"  : 50,
	"lvl"  : 0,
	"dodge"  : 10,
	"skill_name" : "横冲直撞",
	"damage_type" : "瘀伤"
]),
([	"action" : "$N飞起一丈高，一式「石破天惊」，双手和拳，带一道霹雳，朝$n当头砸了下去。",
	"damage" : 70,
	"parry"  : 5,
	"force"  : 60,
	"lvl"  : 12,
	"dodge"  : -5,
	"skill_name" : "石破天惊",
	"damage_type" : "瘀伤"
]),
([	"action" : "$N右拳护胸，左臂平伸，一式「铁索横江」，脚下声雷，疾步向$n撞了过去。",
	"damage" : 90,
	"parry"  : -5,
	"force"  : 70,
	"lvl"  : 24,
	"dodge"  : 10,
	"skill_name" : "铁索横江",
	"damage_type" : "瘀伤"
]),
([	"action" : "$N舒臂吸气，丹田凝力，一声暴喝，真如「春雷乍响」，$n一楞之间，$N的拳头已然攻到了面前。",
	"damage" : 100,
	"parry"  : -15,
	"force"  : 80,
	"lvl"  : 36,
	"dodge"  : 0,
	"skill_name" : "春雷乍响",
	"damage_type" : "瘀伤"
]),
([	"action" : "$N左脚猛一顿地，向前跨上一步，一式「山崩地裂」，双拳一前一后，朝$n攻了出去。",
	"damage" : 120,
	"parry"  : 0,
	"force"  : 100,
	"lvl"  : 48,
	"dodge"  : 10,
	"skill_name" : "山崩地裂",
	"damage_type" : "瘀伤"
]),
([	"action" : "$N一式「巨浪排空」，双拳快收快放，自上下左右如雨点般的砸向$n的$l。",
	"damage" : 140,
	"parry"  : 5,
	"force"  : 110,
	"lvl"  : 60,
	"dodge"  : 5,
	"skill_name" : "巨浪排空",
	"damage_type" : "瘀伤"
]),
([	"action" : "$N双足顿地，如大鹏鸟般飞身而起，拳脚并用，一式「落地生根」，向$n飞落下去。",
	"damage" : 180,
	"parry"  : -5,
	"force"  : 120,
	"lvl"  : 75,
	"dodge"  : 5,
	"skill_name" : "落地生根",
	"damage_type" : "瘀伤"
]),
([	"action" : "$N猿臂轻展，身形暴涨，平地风雷，一拳击出，天地为之变色，真个「无坚不摧」，无往不克。",
	"damage" : 200,
	"parry"  : -20,
	"force"  : 130,
	"lvl"  : 90,
	"dodge"  : 5,
	"skill_name" : "无坚不摧",
	"damage_type" : "瘀伤"
]),
});

int valid_enable(string usage) { return (usage == "cuff") || (usage == "parry"); }

int valid_combine(string combo) { return combo=="feixu-zhang"; }

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 300)
		return notify_fail("你的内力不够。\n");
	if ((int)me->query_skill("jiuqu-xinfa", 1) < 40)
		return notify_fail("你的九曲心法火候不够。\n");
	return 1;
}

int practice_skill(object me)
{
	object weapon;

	if (objectp(weapon = me->query_temp("weapon")))
		return notify_fail("练习铁线拳不能持有武器\n");
	if ((int)me->query("neili") < 40)
		return notify_fail("你的内力不够练铁线拳。\n");
	if ((int)me->query("jingli") < 60)
		return notify_fail("你精神过于疲劳，无法练习铁线拳。\n");
	me->add("neili", -20);
	me->add("jingli",-30);
	return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
		level   = (int) me->query_skill("tiexian-quan",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

string perform_action_file(string action)
{
	return __DIR__"tiexian-quan/" + action;
}
