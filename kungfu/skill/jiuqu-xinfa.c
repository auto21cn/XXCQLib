// jiuqu-xinfa 九曲心法
// By Load

inherit FORCE;
#include <ansi.h>

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
	if ((int)me->query_skill("force", 1) < 10)
		return notify_fail("你的基本内功火候还不够，还不能学习九曲心法。\n");

	return 1;
}

int practice_skill(object me)
{
	if ((int)me->query_skill("jiuqu-xinfa", 1) < 180)
		return notify_fail(CYN"你的内功修为不够，还无法自己修炼九曲心法。\n"NOR);
	else
		return notify_fail(CYN"自行修炼九曲心法暂不开放，敬请等待...\n"NOR);
}

string exert_function_file(string func)
{
        return __DIR__"jiuqu-xinfa/" + func;
}