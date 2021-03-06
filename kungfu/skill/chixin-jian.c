#include <ansi.h>

inherit SKILL;

mapping *action = ({
   (["skill_name" : "文殊问路",
     "action":     "$N左腿前跨半步,身体前倾,一式『文殊问路』,手中$w横扫向$n的$l",
     "dodge":   10,
     "force" : 300,
     "lvl" : 0,
     "damage_type":  "刺伤"]),
   (["skill_name" : "普贤取宝",
     "action":     "$N左手虚晃,右手$w顺势一招『普贤取宝』,自下而上斩向$n的$l",
     "dodge":   20,
     "force" : 310,
     "lvl" : 10,
     "damage_type":  "刺伤"]),
   (["skill_name" : "弥陀披裟",
     "action":     "$N一招『弥陀披裟』,举$w过肩,在空中划了道半弧,剑风直扫向$n的$l",
     "dodge":   30,
     "force" : 320,
     "lvl" : 20,
     "damage_type":  "刺伤"]),
   (["skill_name" : "金刚朝祖",
     "action":     "$N大喊一声“当心了”，双手举着$w,前跨一步,一招『金刚朝祖』,剑尖疾刺$n的$l",
     "dodge":   40,
     "force" : 345,
     "lvl" : 30,
     "damage_type":  "刺伤"]),
   (["skill_name" : "罗汉扫尘",
     "action":     "$N身形一转,反身一剑,好一招『罗汉扫尘』,剑光一闪,往$n的$l刺去",
     "dodge":   40,
     "force" : 360,
     "lvl" : 40,
     "damage_type":  "刺伤"]),
   (["skill_name" : "观音普渡",
     "action":     "$N上身微晃,手腕疾翻,一式『观音普渡』,剑刃自下而上朝$n的$l挑去",
     "dodge":   30,
     "force" : 380,
     "lvl" : 50,
     "damage_type":  "刺伤"]),
   (["skill_name" : "地藏点卯",
     "action":     "$N纵身跃起丈许,$w凌空画了个大弧,一招『地藏点卯』,自上而下劈向$n的$l",
     "dodge":   40,
     "force" : 400,
     "lvl" : 60,
     "damage_type":  "刺伤"]),
   (["skill_name" : "达摩渡江",
     "action":     "$N身行一顿,使出『达摩渡江』,手中$w对准$n的$l直刺过去",
     "dodge":   30,
     "force" : 430,
     "lvl" : 70,
     "damage_type":  "刺伤"]),
});

int valid_enable(string usage){return usage=="sword" || usage=="parry";}

int valid_learn(object me)
{
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
    level   = (int) me->query_skill("chixin-jian",1);
    for(i = sizeof(action); i > 0; i--)
   if(level > action[i-1]["lvl"])
    return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    if( (int)me->query("qi") < 35)
    return notify_fail("你的体力目前没有办法练习慈心剑。\n");
    me->receive_damage("qi", 15);
    return 1;
}

string perform_action_file(string action)
{
    return __DIR__"chixin-jian/" + action;
}


