// sworm_poison.c
// by mulan

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
   if( duration < 1 ) return 0;
   if( !living(me) ) {
      message("vision", me->name() + "凄惨地哼了一声。\n", environment(me), me);
   }
   else {
      tell_object(me, HIW "忽然觉得全身奇痒难忍，你中的蛊毒发作了！\n" NOR );
      message("vision", me->name() + HIB"突然倒在地上，双手在身上一阵乱抓。\n"NOR,
            environment(me), me);
   }
      me->receive_wound("qi",30 + random(10));
      me->receive_wound("jingli", 20);
      me->apply_condition("sworm_poison", duration - 1);
      if ( (int)me->query_temp("powerup") ) 
         { me->add_temp("apply/attack", - (int)(me->query_skill("force")/3));
	     me->add_temp("apply/dodge", - (int)(me->query_skill("force")/3));
	     me->delete_temp("powerup");  }

   if( duration < 1 ) return 0;
   return CND_CONTINUE;
}
