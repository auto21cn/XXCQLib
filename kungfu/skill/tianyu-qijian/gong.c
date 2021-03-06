// 玉石俱焚 gong.c
//Write by godzilla 99.11.10

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;

        if( !target )
        target = offensive_target(me);
        if(!me->query("lingwu_perform"))
                return notify_fail("你还没有领悟其绝招。\n");
        if( !target || !target->is_character()
           || !me->is_fighting(target) || !living(target) )
                return notify_fail("「玉石俱焚」只能在战斗中使用。\n");
        if( (int)me->query("int") < 25 )
                return notify_fail("天羽奇剑关键在于一个“悟”字，你悟性不够不能使用玉石俱焚！\n");
        if (!objectp(weapon = me->query_temp("weapon"))
		|| (string)weapon->query("skill_type") != "sword")
		return notify_fail("你使用的武器不对。\n");
	if( (int)me->query("max_neili") < 1200 )
                return notify_fail("你现在内力不足，使不出玉石俱焚！\n");     
        if( (int)me->query("neili") < 200 )
                return notify_fail("你现在内力不足，使不出玉石俱焚！\n");
        if( me->query_temp("tianyu_qijian") )
                return notify_fail("你刚使完「天羽奇剑」的绝招，目前气血翻涌，无法再次运用！\n");
        msg = HIW "\n$N手中之剑叮呤不绝，一股真气围绕剑身，剑未出，气势已不可御，天下第一功招\n----「"+BLINK+HIR+"玉石俱焚"+NOR+HIW+"」已然出手，剑风犹如万马脱缰般的直逼$n而去！\n"NOR;        
        me->set_temp("tianyu_qijian", 1);
         if (random((int)me->query("combat_exp")) > random(target->query("combat_exp") ) )
        {                     
                damage = (int)me->query_skill("tianyu-qijian", 1); 
                damage = damage*2 + random(damage);
                msg += HIR"$p被$P这一招攻得毫无还手之力，只听“哧”的一声，$p的鲜血已溅满全身！\n" NOR;
                message_vision(msg,me,target);
                call_out("perform2",0, me,target);
                call_out("remove_effect",me->query_con()/2, me); 
                target->receive_damage("qi", damage);
                target->receive_wound("qi", damage/2);
                me->start_busy(1);
                me->add("neili", -150);    
                } 
        else {
                me->start_busy(2);
                target->start_busy(1);
                me->add("neili", -100);
                msg +=HIY"$p忽然感觉到$P欲出剑的气势，竟无可比拟。当机立断，翻了出去。\n"NOR;
                message_vision(msg, me, target);
                call_out("remove_effect", me->query_con()/6, me);
        }
        return 1;
}

int perform2(object me, object target)
{
        int damage;
        string msg;
        msg = HIW "\n$N上招为完，第二剑已经刺出，剑更快，气更盛，好一招玉石俱焚！\n"NOR;
         if(me->query_int()>= random(50))
        {
            
                me->start_busy(1);
                target->start_busy(1);
                me->add("neili", -300);
                damage = (int)me->query_skill("tianyu-qijian", 1);                
                damage = damage*5 + random(damage)*2;
                msg +=HIR"只听“哧”的一声，$n已经中招摇摇欲坠了！\n"NOR;
                message_vision(msg, me, target);
                damage += random(damage);
                target->receive_damage("qi", damage);
                target->receive_wound("qi", damage/2);
                }
                else
                {
                msg +=HIY"$n见剑气扑来，当机立断，立即翻了出去!\n"NOR;
                message_vision(msg, me, target);	
                me->start_busy(2);
                target->start_busy(1);
                me->add("neili", -100);
                }	
       return 1;
}

void remove_effect(object me)
{
        if (!me) 
        return;
        me->delete_temp("tianyu_qijian");
        tell_object(me, HIR"\n你经过一段时间调气养息，又可以使用「天羽奇剑」的绝招了。\n"NOR); 
}
