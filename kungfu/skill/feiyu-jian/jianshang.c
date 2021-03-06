// jianshang.c 剑伤

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
	string msg;
	object weapon;

	if( !target ) target = offensive_target(me);

	if( !target || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("[剑伤]只能对战斗中的对手使用。\n");

	if (!objectp(weapon = me->query_temp("weapon"))
		|| (string)weapon->query("skill_type") != "sword")
			return notify_fail("你手上还没有剑！\n");	
		
        if( (int)me->query_skill("feiyu-jian", 1) < 80 )
		return notify_fail("你的飞鱼剑法不够娴熟，不能使用「剑伤」。\n");
	                        
        if( (int)me->query("neili", 1) < 200 )
		return notify_fail("你现在内力太弱，不能使用「剑伤」。\n");
		
		if ((int)this_player()->query("eff_qi") == 
                    (int)this_player()->query("max_qi"))
                return notify_fail("你现在很健康，不需要使用「剑伤」。\n");	
	
	message_vision(
	HIY "$N使出飞鱼剑法中的一式［剑伤］，竟用剑在自己的伤口上划了几下！\n" NOR,
	               me);
	
	me->add("eff_qi", ((int)this_player()->query("max_qi")/10));
	me->add("neili", -200);
    me->add("qi", -((int)this_player()->query("max_qi")/10));
	if( (int)me->query("eff_qi") > (int)me->query("max_qi") ) me->set("eff_qi", (int)me->query("max_qi"));
    return 1;
}

