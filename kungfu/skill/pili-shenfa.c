// 霹雳身法
// 权利帮通用特殊轻功之一

inherit SKILL;

mapping *action = ({
([
        "action" : "$n神情一凛，足下生风，一式「平步风雷」早已躲开$N的攻击。\n",
]),
([
        "action" : "$n不顾$N攻势，运起全部功力，一式「玉碎瓦全」，合身扑向$N，吓得$N连忙闪到一旁。\n",
]),
([
        "action" : "$n身形微沉，猛一踏地，一式「一怒冲天」，疾冲云霄，$N的眼前竟没有了$n踪迹。\n",
]),
([
        "action" : "$n不躲不闪，突然大喝一声，正是一式「晴空霹雳」，$N攻势一顿，$n便趁势躲了开去。\n",
]),
([
        "action" : "$n身形一矮，一式「伏虎听风」，贴地而行，避开了$N的锋芒。\n",
])
});

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

int valid_enable(string usage)
{
        return usage == "dodge" ;
}

int valid_learn(object me)
{
        if( (int)me->query("dex") < 15 )
                return notify_fail("你身轻如燕，学这笨重的霹雳身法恐怕不合适。。\n");
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
        if( (int)me->query("qi") < 30 )
                return notify_fail("你的体力太差了，不能练习霹雳身法。\n");
        me->receive_damage("qi", 25);
        return 1;
}

