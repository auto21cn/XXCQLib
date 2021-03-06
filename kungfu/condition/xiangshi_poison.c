// Condition: xiangshi_poison.c 相识蜂雨中状态
// Created by Zeus 1999.4.30
// Modified by Zeus 1999.4.30
// 
// 

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
        if( duration < 1 ) return 0;
        if( !living(me) ) {
                message("vision", me->name() + "浑身颤抖，痛苦地哼了一声。\n", environment(me), me);
        }
        else {
                tell_object(me, HIB "忽然觉得全身皮肤像给蜜蜂刺一样痛，并且突然呼吸困难，你中的相识蜂雨中发作了！\n" NOR );
                message("vision", me->name() + "的身子突然晃了两晃，牙关格格地响了起来。\n",environment(me), me);
        }
        me->receive_wound("qi",30 + random(10));
        me->receive_wound("jing", 10);
        me->apply_condition("xiangshi_poison", duration - 1);
        if ( (int)me->query_temp("powerup") ) 
           { me->add_temp("apply/attack", - (int)(me->query_skill("force")/3));
	     me->add_temp("apply/dodge", - (int)(me->query_skill("force")/3));
	     me->delete_temp("powerup");  }

       if( duration < 1 ) return 0;
       return CND_CONTINUE;
}
