// heal.c

#include <ansi.h>

int exert(object me, object target)
{
	if( me->is_fighting() )
		return notify_fail("战斗中运功疗伤？找死吗？\n");

	if (me->is_busy())
		return notify_fail("你正忙着其他事，怎么疗伤？\n");

	if ((int)me->query_skill("jiuqu-xinfa", 1) < 40)
		return notify_fail("你的九曲心法修为还不够。\n");
	if( (int)me->query("neili") < 50 ) 
		return notify_fail("你的真气不够。\n");
	if ((int)me->query("eff_qi") > ((int)me->query("max_qi")-1))
		return notify_fail("你不需要疗伤。\n");

	if( (int)me->query("eff_qi") < (int)me->query("max_qi") / 2 )
		return notify_fail("你的经脉受损，根本无法引导真气运行周身！\n");

	write( HIW "你盘膝而坐，默运九曲心法，运一股丹田之气游走周身，开始疗伤。\n" NOR);
	message("vision",
		HIY + me->name() + "盘膝跌坐，默运神功，突然“哇”的一声喷出一蓬黑血，脸色看起来似乎好了许多。\n" NOR,
		environment(me), me);

	me->receive_curing("qi", 10 + (int)me->query_skill("force")/5 );
	me->add("neili", -50);
	me->set("jiali", 0);

	return 1;
}
