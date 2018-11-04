// powerup.c


#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me);

int exert(object me, object target)
{
	
	if( target != me )
        return notify_fail("你只能对自己有效。\n");
        if( (int)me->query("neili") < 1000  )
        return notify_fail("你的内力不够。\n");
        if((int)me->query("max_neili") < 1500  )
        return notify_fail("你的内力不够。\n");
        if( me->query_skill("tianyu-qigong",1)<180)
        return notify_fail("你天羽奇功还不纯熟，不能用九弧震日的绝招。\n");
        if( (int)me->query_temp("powerup") )
        return notify_fail("你已经在运功中了。\n");
        if(me->query("family/family_name")!="天羽派")
        return notify_fail("你不能使用九弧震日。\n");
        if(me->is_fighting())
        {
        	me->add("neili", -300);
                message_vision(HIR "$N微一凝神，运起九弧震日的真气，一股气流旋流全身。\n" NOR, me);
               me->add_temp("str", 10);
                me->set_temp("powerup", 1);
                me->add_temp("num", 1);
                remove_call_out("number_2");
                call_out("number_2",6,me);
                return 1;
        }
        else
        {
        	return notify_fail("九弧震日只能在战斗中使用。\n");
        }	
       
}
int number_2()
{
	object me=this_player();
	int i=(int)me->query_temp("num");
	if(i>9)
	{
		remove_call_out("end_powerup");        
        	call_out("end_powerup",1,me,i);
        	return 1;
        }	
        if(me->is_fighting())
        {
        	message_vision(HIR "只听$N全身骨骼啪啪做响，第"HIC+chinese_number((int)me->query_temp("num"))+HIR"道九弧震日的真气，排山倒海般的向敌人涌了过去。\n" NOR, me);
               me->add_temp("str", 10);
        	me->add_temp("num", 1);
	        call_out("number_2",6,me);
	        return 1;
	 }
	 else
	 {
	    
        	call_out("end_powerup",1,me,i);
        	return 1;
         }	       
}
void end_powerup(object me,int i)
{
    int m=i*10;	
              me->add_temp("str", -m);
    me->delete_temp("num");
    me->delete_temp("powerup");
    tell_object(me, HIR"你的天羽奇功--九弧震日运行完毕，缓缓的将内力收回丹田。\n"NOR);
}

