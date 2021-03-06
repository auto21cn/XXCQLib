//SKILL : yourenyouyu 游刃有余
//Created by Atlus 1999.7.23.
//

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	if ( me->query_skill("fish-steps",1) < 50 ) return notify_fail("你的「鱼跃龙门步法」还不够纯熟！\n");

	if( !target ) target = offensive_target(me);

	if( !target	||	!target->is_character() ||	!me->is_fighting(target) )
		return notify_fail("「游刃有余」只能对战斗中的对手使用。\n");

	if( target->is_busy() )
		return notify_fail( target->name()+"已经手忙脚乱了！\n");

	message_vision(HIR"$N脚踩连环，使出「游刃有余」，身形如同鲵鱼盘旋成渊，环绕着$n转个不停！\n"NOR,me,target);

	if( random( target->query("combat_exp")/2 ) < me->query("combat_exp") )
	{
		message_vision(WHT"结果$N被扰得眼花潦乱，接应不暇！\n"NOR,target);
		me->add("neili",-200);
		target->start_busy(8);
	}
	else {
		message_vision(WHT"结果$N自己转了个头晕眼花！\n"NOR,me);
		me->add("neili",-100);
		me->start_busy(2);
	}
	return 1; 
}