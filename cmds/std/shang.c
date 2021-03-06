// shang.c	5段进攻中用来上一步	by winder

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	// 五段进攻的变量定义及赋值，初始化人物战斗位置。
	object target;
	int m_dis, no;

	if( !( me->is_fighting() ) )
		return notify_fail("你没有战斗，不需要进攻。\n");

	if( me->query_temp("guarding") )
		return notify_fail("你目不转睛地盯著对方的动作，不敢有一丝妄动。\n");

	if( me->is_busy() )
		return notify_fail("你上一个动作还没有完成！\n");

	if( me->query_temp("shang") ) 
		return notify_fail("你刚刚抢上了。\n");

	if( me->query_temp("tui") ) 
		return notify_fail("你刚刚退过了。\n");

	me->clean_up_enemy();
	target = me->select_opponent();

	m_dis = me->query_temp("dis");

	if( !arg || arg == "1" )
		no = 1;
	else	if( arg == "2" )
			no = 2;
		else	if( arg == "3" )
				no = 3;
			else	if( arg == "4" )
					no = 4;
				else	return notify_fail("你要抢上几步。\n");

	if( m_dis - no <= 0 )
		return notify_fail("你面前的距离不够了。\n");

	if ( !arg || arg == "1" )
	{
		m_dis -= 1;
		message_vision(HIR"\n$N突然身行一晃，向前抢上一步！\n"NOR, me);
	}
	else	if ( arg =="2" && random(10)>=2 )
		{
			m_dis -= 2;
			message_vision(HIR"\n$N突然身行一晃，向前抢上两步！\n"NOR, me);
		}
		else	if ( arg =="3" && random(10)>=4)
			{
				m_dis -= 3;
				message_vision(HIR"\n$N突然身行一晃，向前抢上三步！\n"NOR, me);
			}
			else	if ( arg =="4" && random(10)>=6 )
				{
					m_dis -= 4;
					message_vision(HIR"\n$N突然身行一晃，向前抢上四步！\n"NOR, me);
				}
				else
					message_vision(HIR"\n$N突然身行一晃，想抢至$n面前！但是$n守的滴水不漏，$N只好退回原地。\n"NOR, me, target);

	me->set_temp("dis", m_dis);
	me->start_busy(1);
	me->set_temp("shang",1);

	call_out("effect_shang", random(8), me);

	return 1;
}

int effect_shang(object me)
{
	me->delete_temp("shang");
	return 1;
}