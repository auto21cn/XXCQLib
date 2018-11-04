// literate.c

#include <ansi.h>
inherit SKILL;

string type() { return "knowledge"; }

void skill_improved(object me)
{
	if(me->query("shen")<0) {
		tell_object(me,HIR"你从心底冒出一股恶念：练！练！练！我要毒死天下所有的人！\n"NOR);
		me->add("shen", -(me->query_skill("healing",1)));
	} else {
       tell_object(me,HIM"你从心底升起一股意念：学！学！学！我要学会治病救人！\n"NOR);
		me->add("shen", (me->query_skill("healing",1)));
	}
}

int valid_learn(object me)
{ return 1; }
