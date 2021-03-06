// 宠物使用的武功
// By 山猫Adx @ snow 99-12-12

inherit SKILL;

mapping *action = ({
([	"action" : "$n双爪一用力，从$N头顶飞身而过。\n",
	"dodge"  : 10
]),
([	"action" : "$n双腿一越，侧身躲过$N的攻势。\n",
	"dodge"  : 30
]),
([	"action" : "$n伏地一个打滚，闪到$N的身后。\n",
	"dodge"  : 50
]),
});

mapping query_action(object me, object weapon)
{
	int zhaoshu, level;

	zhaoshu = sizeof(action);
	level   = (int) me->query_skill("chongwu-tengnuo");

	if (level < 80 )
		zhaoshu--;

	if (level < 60 )
		zhaoshu--;

	if (level < 40 )
		zhaoshu--;

	return action[random(zhaoshu)];
}

int valid_enable(string usage)
{
	return usage == "dodge" || usage == "move";
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
