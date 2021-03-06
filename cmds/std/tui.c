// tui.c	5段进攻中用来退一步	by winder

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	// 五段进攻的变量定义及赋值，初始化人物战斗位置。
	object target;
	int m_dis, no, distance;

	if( !( me->is_fighting() ) )
		return notify_fail("你没有战斗，不需要退防。\n");

	if( me->query_temp("guarding") )
		return notify_fail("你目不转睛地盯著对方的动作，不敢有一丝妄动。\n");

	if( me->is_busy() )
		return notify_fail("你上一个动作还没有完成！\n");

	if( me->query_temp("tui") ) 
		return notify_fail("你刚刚退过了。\n");

	if( me->query_temp("shang") ) 
		return notify_fail("你刚刚抢上了。\n");

	me->clean_up_enemy();
	target = me->select_opponent();

	if ( !environment(me)->query("length") || environment(me)->query("length") <= 0 )
		if ( !environment(me)->query("piazza") )
			if ( !environment(me)->query("outdoors") )
				distance = 5;
			else
				distance = 7;
		else
			distance = 11;
	else
	{
		distance = environment(me)->query("length");
		if ( distance >= 20 )
			distance = 19;
		else	if ( intp(distance/2) )
				distance -= 1;
	}

	m_dis = me->query_temp("dis");

	if( !arg || arg == "1" )
		no = 1;
	else	if( arg == "2" )
			no = 2;
		else	if( arg == "3" )
				no = 3;
			else	if( arg == "4" )
					no = 4;
				else	return notify_fail("你要退后几步。\n");

	if( ( distance - m_dis ) < no )
		return notify_fail("你后面的距离不够了。\n");

	if ( !arg || arg == "1" )
	{
		m_dis += 1;
		message_vision(HIR"\n$N突然虚晃一招，向后疾退一步！\n"NOR, me);
	}
	else	if ( arg =="2" && random(10)>=2 )
		{
			m_dis += 2;
			message_vision(HIR"\n$N突然虚晃一招，向后疾退两步！\n"NOR, me);
		}
		else	if ( arg =="3" && random(10)>=4 )
			{
				m_dis += 3;
				message_vision(HIR"\n$N突然虚晃一招，向后疾退三步！\n"NOR, me);
			}
			else	if ( arg =="4" && random(10)>=6 )
				{
					m_dis += 4;
					message_vision(HIR"\n$N突然虚晃一招，向后疾退四步！\n"NOR, me);
				}
				else
					message_vision(HIR"\n$N突然虚晃一招，想向后跳开几步！但是$n攻势凌厉，$N忙于招架无法得逞。\n"NOR, me, target);

	me->set_temp("dis", m_dis);
	me->start_busy(1);
	me->set_temp("tui",1);

	call_out("effect_tui", random(4), me);

	return 1;
}

int effect_tui(object me)
{
	me->delete_temp("tui");
	return 1;
}