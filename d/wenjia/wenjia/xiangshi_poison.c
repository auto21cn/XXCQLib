// Condition: xiangshi_poison.c 相识蜂雨中状态
// Created by Zeus 1999.4.30
// Modified by Zeus 1999.6.9
// 
// 

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
        if( duration < 1 )  {
                tell_object(me, GRN "你觉得呼吸畅顺，身上的也不再疼痛。\n"+CYN+"你中的「相识蜂雨中」已经发作完了。\n" NOR );
                return 0;
        }

        if( !living(me) ) {
                message("vision", me->name() + "浑身颤抖，痛苦地哼了一声。\n", environment(me), me);
        }
        else {
                tell_object(me, RED "忽然觉得全身皮肤像给蜜蜂刺一样痛，并且突然呼吸困难。\n"+RED+"你中的「相识蜂雨中」发作了！\n" NOR );
                message("vision", RED + me->name() + "的呼吸变得困难，身子开始颤抖。\n",environment(me), me);
        }

        me->receive_wound("qi",random(200-me->query_con()-me->query_dex()));
        me->receive_wound("jing", random(200-me->query_con()-me->query_dex());

        me->apply_condition("xiangshi_poison", duration - 1);

        if ( (int)me->query_temp("powerup") ) {
                me->add_temp("apply/attack", - (int)(me->query_skill("force")/3));
                me->add_temp("apply/dodge", - (int)(me->query_skill("force")/3));
                me->delete_temp("powerup");
        }

        if( duration < 1 )  {
                tell_object(me, GRN "你觉得身上的也不再疼痛。\n"+CYN+"你中的「相识风雨中」已经发作完了。\n" NOR );
                return 0;
        }

        return CND_CONTINUE;
}
