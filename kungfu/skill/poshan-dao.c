// poshan-dao.c 破山刀

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N握紧手中$w一招「破阵一刀」点向$n的$l",
        "force" : 50,
        "dodge" : 40,
        "damage" : 20,
        "lvl"    : 0,
        "skill_name" : "破阵一刀", 
        "damage_type" : "割伤"
]),
([      "action" : "$N向前跨上一步，手中$w使出「破魔一刀」砍向$n的喉部",
        "force" : 90,
        "dodge" : 80,
        "damage" : 50,
        "lvl"    : 20,
        "skill_name" : "破魔一刀",
        "damage_type" : "割伤"
]),
([      "action" : "只见$N抡起手中的$w，使出「破妖一刀」万点金光直劈$n",
        "force" : 90,
        "dodge" : 70,
        "damage" : 60,
        "lvl"    : 40,
        "skill_name" : "破妖一刀",
        "damage_type" : "劈伤"
]),
([      "action" : "$N使出「破立一刀」，手中$w如刮起狂风一般闪烁不定，割向$n",
        "force" : 200,
        "dodge" : 80,
        "damage" : 65,
        "lvl"    : 80,
        "skill_name" : "破立一刀",
        "damage_type" : "割伤"
]),
([      "action" : "$N随手使出刀法之奥义「破旧一刀」，手中$w如鬼魅一般铺天盖地的砍向$n",
        "force" : 300,
        "dodge" : 90,
        "damage" : 90,
        "lvl"    : 100,
        "skill_name" : "「破旧一刀」",
        "damage_type" : "割伤"
]),
([      "action" : HIY"$N使出破山刀法之最终绝技[1;36m「破势一刀」[0m,[1;33m手中$w犹如蛟龙一般劈向$n[0m"NOR,
        "force" : 400,
        "dodge" : 100,
        "damage" : 350,
        "lvl"    : 150,
        "skill_name" : "HIY「破势一刀」"NOR,
        "damage_type" : "割伤"
]),
});


int valid_enable(string usage) { return (usage == "blade") || (usage == "parry"); }

int valid_learn(object me)
{
        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("你对调理气息的火候不够，无法学「破山刀法」。\n");
        if ((int)me->query("max_neili") < 300)
                return notify_fail("你的内力太弱，无法练「破山刀法」。\n");
        if ((int)me->query("shen") < 10000)
        	return notify_fail("用破山刀法时要满腔正气，否则会反受其害。\n");
        return 1;
}


string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
	level   = (int) me->query_skill("poshan-dao",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/4)];
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "blade")
                return notify_fail("你使用的武器不对。\n");
        if ((int)me->query("qi") < 50)
                return notify_fail("你的体力不够练「破山刀法」。\n");
        if ((int)me->query("neili") < 50)
                return notify_fail("你的内力不够练「破山刀法」。\n");
        me->receive_damage("qi", 15);
        return 1;
}
string perform_action_file(string action)
{
        return __DIR__"poshan-dao/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	if( damage_bonus < 100 ) return 0;
    if(me->query("douzhi")<1)
      return 0;

        if( random(damage_bonus/2) > victim->query_str() ) {
               if ( (( (int)victim->query("shen") - (int)me->query("shen") ) > 50000) && ( (int)me->query("shen") < 0 )  )
			{
				me->add("douzhi",-30);
				message_vision("$N骇然发现手中的兵器竟然受到对方正气的吸引而不听使唤了。$N斗志下降了！\n",me);              
				return 1;
			}
                victim->receive_wound("qi", (damage_bonus - 100) / 2 );
                return RED "只见$n一个不留神，被$N的刀砍的血肉横飞！\n"NOR;
        }
}


