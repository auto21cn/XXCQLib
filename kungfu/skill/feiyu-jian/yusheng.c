//SKILL PERFORM yusheng.c 劫后余生
//Modified by Atlus by 1999.10.9

#include <ansi.h>
 
inherit F_SSERVER;

string status_msg(int ratio)
{
	if( ratio==100 ) return HIG "看起来充满活力，一点也不累。" NOR;
	if( ratio > 95 ) return HIG "似乎有些疲惫，但是仍然十分有活力。" NOR;
	if( ratio > 90 ) return HIY "看起来可能有些累了。" NOR;
	if( ratio > 80 ) return HIY "动作似乎开始有点不太灵光，但是仍然有条不紊。" NOR;
	if( ratio > 60 ) return HIY "气喘嘘嘘，看起来状况并不太好。" NOR;
	if( ratio > 40 ) return HIR "似乎十分疲惫，看来需要好好休息了。" NOR;
	if( ratio > 30 ) return HIR "已经一副头重脚轻的模样，正在勉力支撑著不倒下去。" NOR;
	if( ratio > 20 ) return HIR "看起来已经力不从心了。" NOR;
	if( ratio > 10 ) return RED "摇头晃脑、歪歪斜斜地站都站不稳，眼看就要倒在地上。" NOR;
	return RED "已经陷入半昏迷状态，随时都可能摔倒晕去。" NOR;
}

varargs void report_status(object ob)
{
	message_vision( "( $N" + status_msg(
		(int)ob->query("qi") * 100 / (int)ob->query("max_qi") ) 
		+ " )\n", ob);
}

int perform(object me)
{
	string msg;
	object weapon, target;
	object ob;
	int skill, skill2, skill3;

	me->clean_up_enemy();
	target = me->select_opponent();

	skill = (me->query_skill("feiyu-jian",1)+(me->query_skill("sword",1))/2);
	skill2 = (me->query_skill("tianlongforce",1)+(me->query_skill("force",1))/2);
    skill3 = (me->query_skill("fish-steps",1)+(me->query_skill("dodge",1))/2);

	if (!objectp(weapon = me->query_temp("weapon"))
		|| (string)weapon->query("skill_type") != "sword")
			return notify_fail("你手上还没有剑！\n");

	if( !me->is_fighting()|| !living(me) )
	    	return notify_fail("「劫后余生」只能在战斗中使用。\n");

	if( (int)me->query("max_neili") < 1000 )
		return notify_fail("你的内力修为还不够高！\n");

	if( (int)me->query("neili") < 500 )
		return notify_fail("你现在的内力不足！\n");

	if( skill < 150)
		return notify_fail("你剑法的修为不够，不能使用「劫后余生」! \n");

	if( skill2 < 120)
		return notify_fail("你内功修为不够，不能使用「劫后余生」! \n");
   
	if( skill3 < 120)
		return notify_fail("你轻功修为不够，不能使用「劫后余生」! \n");

	if( me->query_skill_mapped("sword") != "feiyu-jian") 
		return notify_fail("你的飞鱼剑法还没准备好，无法使用「劫后余生」！\n");
	
 
	msg = HIY"$N纵身越起，呼啸、转动着，手中"+(string)weapon->query("name")+HIY"发出阵阵青芒，愈来愈盛，最后盖过了眼前所有的光芒，尖啸着攻向$n。\n\n"NOR;
	message_vision(msg, me, target);

	me->clean_up_enemy();
	ob = me->select_opponent();

	COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 0);
	COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 0);
	COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 0);
    COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 0);

	me->add("neili", -300);
	me->start_busy(random(2));

	if(!ob->is_fighting(me)) ob->fight_ob(me);
		return 1;
}
