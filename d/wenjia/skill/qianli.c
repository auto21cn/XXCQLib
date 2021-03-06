// SKILL: qianli.c 毒行千里 温家特殊身法
// Created by Zeus 1999.5.1
// Modified by Zeus 1999.5.28
// 修改威力
// 原著武功所有人：无。自创。

inherit SKILL;

mapping *action = ({
([	"action" : "$n双手叉腰，腰部扭动,一式「毒钓江雪」，从$N的凌厉攻势中“穿”了出来。\n",
]),
([	"action" : "$n双手同时攻势加强，一式「毒立寒秋」，$n的身体乍停在$N面前，$N正觉得奇怪，$n的身影又转到了$N背后。\n",
]),
([	"action" : "$n一式「毒善其身」，脸色严肃，身体向斜右飘出，$N的攻势又空了。\n",
]),
([	"action" : "$n身体向后弯曲，左手攻势乍停，右手攻势凌厉，一式「万里毒行」，$n佯攻反退，人早已闪在了一边。\n",
]),
([	"action" : "$n左手手掌朝天、右手手掌朝地，弯腰隆背，一式「毒来毒往」，身体出现在$N的背后。\n",
]),
});

mapping query_action(object me, object weapon)
{
	return action[random(sizeof(action))];
}

int valid_enable(string usage)
{
	return usage == "dodge";
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
	if( (int)me->query("qi") < 40 )
		return notify_fail("体力太差了，再练都不会练好的!\n");
	me->receive_damage("qi", 20);
	return 1;
}
