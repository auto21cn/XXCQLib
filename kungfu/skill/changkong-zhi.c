// changkon-zhi.c 长空神指

inherit SKILL;

mapping *action = ({
([	"action" : "$N右手突然平直伸出，五指猛然弹出，拂向$n的$l",
	"damage" : 100,
	"damage_type" : "瘀伤"
]),
([	"action" : "$N突然转身，五指自左向右带着凌厉的指气拂向$n的$l",
	"damage" : 150,
	"damage_type" : "刺伤"
]),
([	"action" : "$N侧身抬臂，手臂自下而上向$n胸前要穴拂去",
	"damage" : 200,
	"damage_type" : "割伤"
]),
([	"action" : "$N身如陀螺急转不停，两手不断弹出全无停顿，无数劲气直奔$n而来",
	"damage" : 250,
	"damage_type" : "刺伤"
]),
([      "action" : "$N犹如泰山巍然不动，双臂却闪电挥出，袭向$n周身大穴，",
        "damage" : 300,
        "damage_type" : "刺伤"
]),
});

int valid_enable(string usage) { return (usage == "finger") || (usage == "parry"); }

int valid_combine(string combo) { return combo=="tianyu-qijian"; }

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 200)
		return notify_fail("你的内力不够。\n");
	if ((int)me->query_skill("tianyu-qigong", 1) < 150)
		return notify_fail("你的天羽奇功火候不够。\n");
	return 1;
}

mapping query_action(object me, object weapon)
{
	return action[random(sizeof(action))];
}

int practice_skill(object me)
{
	object weapon;

	if (objectp(weapon = me->query_temp("weapon")))
		return notify_fail("练习长空神指不能持有武器\n");
	if ((int)me->query("neili") < 60)
		return notify_fail("你的内力不够练长空神指。\n");
    me->add("neili",-40);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"changkong-zhi/" + action;
}
