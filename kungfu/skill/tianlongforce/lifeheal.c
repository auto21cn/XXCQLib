// lifeheal.c
// from jiuyang-shengong

#include <ansi.h>

int exert(object me, object target)
{
	if( !target )
		return notify_fail("你要用真气为谁疗伤？\n");
	
	if( me->is_fighting() || target->is_fighting())
		return notify_fail("战斗中无法运功疗伤！不要命了?\n");

	if( (int)me->query("max_neili") < 500 )
		return notify_fail("你的内力修为不够。\n");

	if( (int)me->query("neili") < 250 )
		return notify_fail("你的真气不够。\n");

	if( (int)target->query("eff_qi") < (int)target->query("max_qi") / 4 )
		return notify_fail( target->name() +
			"已经受了严重的内伤，你再输真气会将其震死的！\n");
        if( me == target ) {
                return notify_fail("你想替自己疗伤，可是运功的方法不对。\n");
				}
	else {message_vision(
		HIY "$N盘膝坐下,运起金刚天龙神功，将手掌轻轻贴在$n背心，缓缓地将真气输入$n体内....\n"
		    "$n只觉一股真气从背心源源输入体内，瞬间流遍全身各大穴位。\n"NOR,
		me, target );
	}
	target->receive_curing("qi", 30 + (int)me->query_skill("tianlongforce")/3 );
	target->add("qi", 30 + (int)me->query_skill("tianlongforce")/3 );
	if( (int)target->query("qi") > (int)target->query("eff_qi") ) target->set("qi", (int)target->query("eff_qi"));

	me->add("neili", -150);
	me->set("jiali", 0);

	return 1;
}
