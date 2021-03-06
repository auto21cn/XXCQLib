// 青云身法
// 权利帮通用特殊轻功之一

inherit SKILL;

mapping *action = ({
([
        "action" : "$n浑不着力，一式「春风得意」，借力而行，向后倒飞了一丈开外。\n",
]),
([
        "action" : "$n一式「一马平川」，身形一晃，前冲七尺，早已脱离了$N的攻势。\n",
]),
([
        "action" : "$n足尖轻点，一式「扶摇直上」，疾冲云霄，$N的眼前竟没有了$n踪迹。\n",
]),
([
        "action" : "$n不慌不忙身形一动，一式「闲庭信步」，几步便让$N的攻击落了空。\n",
]),
([
        "action" : "$n飞身而起，空中几个虚踏接一个翻转，一式「天舞流云」，轻盈的落在了丈外。\n",
]),
([
        "action" : "$n双臂一展如万里鹏翅，一式「鹏程万里」，顺敌之势滑出战圈。\n",
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
        if( (int)me->query("dex") < 20 )
                return notify_fail("你的身形实在太笨重了，不适合练青云步。\n");
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
                return notify_fail("你的体力太差了，不能练习青云步。\n");
        me->receive_damage("qi", 20);
        return 1;
}
