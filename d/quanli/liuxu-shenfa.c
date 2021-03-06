// liuxu-shenfa.c
//by mulan

inherit SKILL;

string *dodge_msg = ({
"$n比风吹柳，柳梢稍动的刹那，像水面初漾的起波纹的瞬间，还要快!\n",
"就在这刹那，$N只觉头上衣衫一闪，一样东西，“唆”地经过,原来是$n。\n",
"$n倏然一反，正面向$N。然后又是一反，遂而一正，一正、一反，又一正一反，反反正正、正正反反，不知转了\n
 多少次，在短短不到十尺之距离中，如此旋转着但极快疾地欺近$N！\n",
"$n的人，也化作了柳丝飞絮，$N激飞，$n的人也飘起。\n",
"$n好象已无生机。但$n忽然粘在$N的武器上。整个人贴在$W上、附在$W身。全身轻似柳!\n",
"$n的身子，似腐朽了一般，又似柳絮，强力的劲风打过去，不过激起荡荡而飘，全失去了效用。\n",
"$n的神情与身影，如韦睿临阵，轻袍缓带，乘舆坐椅，轻舒慢捻，是武学中至高境界：\n
 以缓赶急，以慢打快，以后夺先，以静制动。\n",

});

int valid_enable(string usage) 
{ 
	return (usage == "dodge") ; 
}

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( (int)me->query("qi") < 100 )
                return notify_fail("你的体力太差了，不能练凌波微步。\n");
        me->receive_damage("qi", 80);
        return 1;
}

