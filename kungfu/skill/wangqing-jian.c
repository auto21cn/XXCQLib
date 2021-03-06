// wangqing-jian.c
// by mulan

#include <ansi.h>
inherit SKILL;

mapping *action = ({
	([	"name":		"天意诀",
                "action":       "$N使出忘情剑法中的"+HIY"「天意诀」"NOR+"$N已仿佛与天融合在一起，在刹那间便是苍苍天穹，永无底止，也没有感情。",
		"dodge":	50,
		"parry" :	100,
		"force":	170,
        "damage" :  100,
		"damage_type":	"刺伤"
	]),
	([	"name":		"地势诀",
             "action":       "$N使出忘情剑法中的"+HIW"「地势诀」"NOR+"，$N立时觑出死角，觅得虚隙，乘机而入",
		"dodge":	100,
		"parry" :	200,
		"force" : 	200,
        "damage":   150,
		"damage_type":	"刺伤"
	]),
	([	"name":		"君王诀",
		"action":	"$N举剑齐眉，容庄神凝，$w剑尖凝在半空，遥指$n。使出忘情剑法中的"+HIR"「君王诀」"NOR,
                "dodge":	100,
                "parry" :	200,
		"force":	170,
        "damage" :  200,
		"damage_type":	"刺伤"
	]),
	([	"name":		"亲思诀",
		"action":	"$N使出忘情剑法中的"+HIB"「亲思诀」"NOR+"，以一些声音、手势、音乐、景象吸引住$n，以惊人数倍的内力，使$n坠入了往事尘烟之中",
		"dodge":	100,
		"parry" :	200,
		"force" : 	200,
        "damage":   250,
		"damage_type":	"刺伤"
	]),
	([	"name":		"金断诀",
		"action":	"$N使出忘情剑法中的"+HIC"「金断诀」"NOR+"，倏地一个箭步就抢过去，一伸手，就摘下背后的$w，“玎玎”两声，一剑削出，",
		"dodge":	100,
		"parry" :	200,
		"force" : 	300,
                "damage":       250,
		"damage_type":	"刺伤"
	]),
	([	"name":		"日明诀",
		"action":	"$N只觉一股共天地久长的浩气，自心中激游全身，使出忘情剑法中的"+BLU"「日明诀」"NOR+"，飞袭$n",
		"dodge":	100,
		"parry" :	200,
		"force" : 	350,
                "damage":       300,
		"damage_type":	"刺伤"
	]),
	([	"name":		"风流诀",
		"action":	"$n只觉有一股强大的压力，铺天盖地的涌压而来，额上隐然有汗，正是忘情剑法中的「风流诀」",
		"dodge":	100,
		"parry" :	200,
		"force" : 	400,
                "damage":       350,
		"damage_type":	"刺伤"
	]),
	([	"name":		"云翳诀",
		"action":	"$n刚要刺出，忽然觉得凤涌云动，反被$N一剑自顶至胯，串了进去,   中了"+HIG"「云翳诀」"NOR,
		"dodge":	100,
		"parry" :	200,
		"force" : 	400,
                "damage":       400,
		"damage_type":	"刺伤"
	]),
});

int valid_learn(object me)
{
        return notify_fail("忘情剑法只能靠研读忘情天书来提高!。\n");

}

int valid_enable(string usage)
{
	return usage=="sword" || usage=="parry" || usage=="dodge";
}

mapping query_action(object me, object weapon)
{
	return action[random(sizeof(action))];
}

int practice_skill(object me)
{
	write("忘情剑法不能练。\n");
	return 1;
}

int valid_effect(object me, object weapon, string name, int skill)
{
}

int effective_level() { return 25;}

string *dodge_msg = ({
       "$n人如大鸟般跃起，平飞掠出，轻轻一点，宛似飞燕在天空一折，又掠了出去。\n",
       "$n身未回，身形却地倒飞而出，宛若流星，斜挂纵落。\n",
       "$n一点，又疾地冲天而起，去势劲急，$n在骄阳下映耀，犹如孔雀开屏，破空而去。\n",
       "就在这一霎眼间，$n倏然不见了，一阵凤掠过，扬柳飞送。\n",
	"$n施展了“忘情天书”中的“月映”法，在月色寒光中消失了。\n",   
       "剑割微风，造成急卷的气流割体,$n轻如落叶，已飘到$N背后。正是以"+HIW"“风流”"NOR+"一诀\n",
});

string *parry_msg = ({
       "$n以"+MAG"「师教诀」"NOR+"之势，竟随在$N之后,竟让$N产生一种错觉.\n",
      "$n在这刹那间，身体变得如一根朽木。在这瞬间将所有的穴道全部闭死.正是"+HIM"「木顽诀」NOR\n",
       "$n运用"+CYN"「水逝诀」"NOR+"在$n周围激起了无数串水柱，$N的武器全打在水墙上，都无法透过.\n",
	"$n仗着遥远的火光摇晃，以"+RED"「火延诀」"NOR+"之势，掩人眼目,急闪一旁.\n",
	"$n用"+YEL"「土掩诀」"NOR+"迅速的在地上掘开洞,$n不见了\n",
});

string *unarmed_parry_msg = ({
       "$n使动$v，在身前布起了一道铜墙铁壁，封住了$N的攻势。\n",
	"$n一抖手中的$v，护住了全身。\n",
	"$n将$v往地上一刺，$v反弹起来，刚好直刺$N的双臂。\n",
	"$n举剑静立，一股内力从剑梢透出，逼开了$N。\n",
});

string query_parry_msg(object weapon)
{
        if( weapon )
                return parry_msg[random(sizeof(parry_msg))];
        else
                return unarmed_parry_msg[random(sizeof(unarmed_parry_msg))];
}

string query_dodge_msg(string limb)
{
    return dodge_msg[random(sizeof(dodge_msg))];
}


string perform_action_file(string action)
{
        return __DIR__"wangqing-jian/" + action;
}


