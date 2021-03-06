// qizhi.c 长空奇指
 
#include <ansi.h>
 
inherit F_SSERVER;

int perform(object me)
{
	string msg;
	object weapon, target;
	int skill;

	skill = me->query_skill("changkong-zhi",1);

	if( !(me->is_fighting() ))
		return notify_fail("「长空奇指」只能对战斗中的对手使用。\n");
 
	if (objectp(weapon = me->query_temp("weapon")))
		return notify_fail("「长空奇指」必须徒手使用。\n");

	if( skill < 100)
		return notify_fail("你的「长空指」等级不够, 不能使用「长空奇指」！\n");

	if( me->query("neili") < 220 )
		return notify_fail("你的内力不够，无法运用「长空奇指」！\n");
 
	msg = HIC "$N突然纵声长啸，双手接连挥出，带起漫天劲气，闪电般弹出数指。\n"NOR;
	message_vision(msg, me, target);

	me->clean_up_enemy();
	target = me->select_opponent();

	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
//	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
//	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
//	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);

 	me->add("neili", -200);
	me->start_busy(random(3));

	return 1;
}
