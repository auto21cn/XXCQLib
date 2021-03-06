// feixu-zhang.c 飞絮掌
// 平均damage:90 平均force:90 平均dodge:-10 平均parry:5
// 飞絮掌的特点在于威力较小，招架较易，躲避较难
// By Load

inherit SKILL;

mapping *action = ({
([	"action" : "$N双臂不动，双掌翻飞如春花乍现，踏前一步，一式「绽花迎春」缓缓推向$n。",
	"damage" : 30,
	"parry"  : 10,
	"force"  : 50,
	"lvl"  : 0,
	"dodge"  : -10,
	"skill_name" : "绽花迎春",
	"damage_type" : "瘀伤"
]),
([	"action" : "$N身形微动，欺近$n，左手背后，似「临谷闻香」，右手迅捷的扇向的$n脸颊，待$n伸手去格，却又突然变向。",
	"damage" : 60,
	"parry"  : 5,
	"force"  : 60,
	"lvl"  : 12,
	"dodge"  : -15,
	"skill_name" : "临谷闻香",
	"damage_type" : "瘀伤"
]),
([	"action" : "$N飞身在空，向$n急冲，双臂画圆，一式「艳阳伴夏」，双掌向着$n无可阻挡的拍了下去。",
	"damage" : 80,
	"parry"  : 0,
	"force"  : 70,
	"lvl"  : 24,
	"dodge"  : -5,
	"skill_name" : "艳阳伴夏",
	"damage_type" : "瘀伤"
]),
([	"action" : "$N鬼魅般的闪现在$n的身后，一掌悄然无声的推向$n的身后，对这式「静室听雨」$n似乎毫无察觉。",
	"damage" : 90,
	"parry"  : 15,
	"force"  : 80,
	"lvl"  : 36,
	"dodge"  : 0,
	"skill_name" : "静室听雨",
	"damage_type" : "内伤"
]),
([	"action" : "$N突然加速，在$n周围穿插游走，虚虚实实从四面八方向$n拍出无数的掌影，这一式「落叶知秋」竟令$n无从防起。",
	"damage" : 90,
	"parry"  : 10,
	"force"  : 100,
	"lvl"  : 48,
	"dodge"  : -20,
	"skill_name" : "落叶知秋",
	"damage_type" : "瘀伤"
]),
([	"action" : "$N站立不动，潜运内功，突然一声暴喝，双掌一推，一式「旷野临风」，一股大力携飓风向$n拥去。",
	"damage" : 100,
	"parry"  : 5,
	"force"  : 110,
	"lvl"  : 60,
	"dodge"  : 5,
	"skill_name" : "旷野临风",
	"damage_type" : "内伤"
]),
([	"action" : "$N身形忽高忽低，双掌如刀，掌缘带起阵阵寒意，一式「素雪随冬」向$n周身不断的砍去",
	"damage" : 120,
	"parry"  : 0,
	"force"  : 120,
	"lvl"  : 75,
	"dodge"  : -10,
	"skill_name" : "素雪随冬",
	"damage_type" : "瘀伤"
]),
([	"action" : "$N飞身而起，双掌急摆，幻化为四掌、八掌、十掌、百掌，一式「如絮飞霜」罩向$n全身。",
	"damage" : 150,
	"parry"  : -5,
	"force"  : 130,
	"lvl"  : 90,
	"dodge"  : -20,
	"skill_name" : "如絮飞霜",
	"damage_type" : "瘀伤"
]),
});

int valid_enable(string usage) { return (usage == "strike") || (usage == "parry"); }

int valid_combine(string combo) { return combo=="tiexian-quan"; }

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 100)
		return notify_fail("你的内力不够。\n");
	if ((int)me->query_skill("jiuqu-xinfa", 1) < 20)
		return notify_fail("你的九曲心法火候不够。\n");
	return 1;
}

int practice_skill(object me)
{
	object weapon;

	if (objectp(weapon = me->query_temp("weapon")))
		return notify_fail("练习飞絮掌不能持有任何武器\n");
	if ((int)me->query("neili") < 10)
		return notify_fail("你的内力不足，不能练飞絮掌。\n");
	if ((int)me->query("jingli") < 50)
		return notify_fail("你的精神过于疲劳，无法练习飞絮掌。\n");
	me->add("neili", -5);
	me->add("jingli",-30);
	return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
		level   = (int) me->query_skill("feixu-zhang",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

string perform_action_file(string action)
{
	return __DIR__"feixu-zhang/" + action;
}