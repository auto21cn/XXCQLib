// zuida.c 少林醉棍 [八仙醉打]

#include <ansi.h>

inherit F_SSERVER;

void remove_effect(object me, int amount1);

int perform(object me)
{
	object weapon, target;
  	string msg;
	int count1, cnt, skill,ap ,dp;
	
	me->clean_up_enemy();
	target = me->select_opponent();

	if( !me->is_fighting() )
	    return notify_fail("「八仙醉打」只能在战斗中使用。\n");

	if (!objectp(weapon = me->query_temp("weapon"))
		|| (string)weapon->query("skill_type") != "club")
			return notify_fail("你使用的武器不对。\n");

	if( (int)me->query_temp("zuida") ) 
		return notify_fail("你已经在运功中了。\n");

	if( (int)me->query_str() < 25 )
		return notify_fail("你的臂力不够，目前不能使用此绝技! \n");

	if( me->query_skill_mapped("force") != "banruo-changong"
		&& me->query_skill_mapped("force") != "wuxiang-shengong") 
		return notify_fail("你没有激发少林内功，无法使用「醉仙望月」！\n");
	if( (int)me->query_skill("force") < 100)
		return notify_fail("你的少林内功修为不够，不能使用「醉仙望月」！\n");

	if( (int)me->query_skill("club") < 120)
		return notify_fail("你的棍法修为不够，不能使用「醉仙望月」! \n");

	if( (int)me->query("neili") < 300 ||(int)me->query("max_neili") < 500 )
		return notify_fail("你的真气不足！\n");
	
	msg = HIY "突然$N步伐一变「醉仙望月」，双目瞟天，脚下几个踉跄乎上乎下乎左乎右，，变得更加不可捉摸。\n" NOR;
	
   	message_vision(msg, me, target);
	skill = me->query_skill("zui-gun",1);
	cnt =(int)( (int)me->query_condition("drunk") / 30 );
	count1 = me->query("dex") * cnt;

	me->add_temp("dex", count1);
	me->set_temp("zuida", 1);

	me->start_call_out( (: call_other, __FILE__, "remove_effect", me, count1 :), skill /6 );

	me->add("neili", -150);

	ap = ((me->query("combat_exp"))*(me->query_dex()));
	dp = ((target->query("combat_exp"))*(target->query_dex()))/2;
	if( dp < 1 )
		dp = 1;
	if( random(ap) > dp)
	{
		msg = HIW "$n只觉自己身前身后都是$N的影子，竟然不知道该向那里进攻了。\n" NOR;
		message_vision(msg, me, target);
		target->start_busy( 1 + (int)me->query_condition("drunk") / 30);
		me->add("neili", -150);
	}
	else
	{
		msg = HIC "$n急忙跃后一步，仔细观察$N的步法，总算没有被搅得手忙脚乱。\n" NOR;
		message_vision(msg, me, target);
	}
   	return 1;
}

void remove_effect(object me, int amount1)
{
	if ( (int)me->query_temp("zuida") ) 
	{
		me->add_temp("dex", -amount1);
		me->delete_temp("zuida");
		message_vision(HIY "$N醉态一收，步法也恢复了正常。\n" NOR,me);
		me->start_busy(3);
	}
}