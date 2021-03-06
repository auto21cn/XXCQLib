#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>


inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon,ob;
        int skill;
        string msg;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("「雪花剑气」只能在战斗中使用。\n");

        if (!objectp(weapon = me->query_temp("weapon"))
                || (string)weapon->query("skill_type") != "sword")
                return notify_fail("「雪花剑气」必须用剑才能施展。\n");

        if( (int)me->query_skill("xuehua-shenjian", 1) < 120 )
                return notify_fail("你的「雪花剑法」不够娴熟，不会使用「雪花剑气」。\n");

        if( (int)me->query("neili") < 400  ) 
                return notify_fail("你的内力不够。\n");

        skill = me->query_skill("xuehua-shenjian");

        msg = HIW "$N运起素女真气，以气御剑，达到了用剑的最高境界人剑合一,$N使出了惊天动地的"MAG"雪花剑气!\n"NOR;

        message_vision(msg, me, target);

        me->add("neili", -300);

        me->clean_up_enemy();
        ob = me->select_opponent();

        msg = RED"天外飞仙\n"NOR;
        message_vision(msg, me, target);
        COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 2);
        msg = HIW"天外清音\n"NOR;
        message_vision(msg, me, target);
        COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 2);
        msg = BLU"雷动九天\n"NOR;
        message_vision(msg, me, target);
        COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 2);
        msg = HIM"人剑合一\n"NOR;
        message_vision(msg, me, target);
        COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 2);
        
        if( me->is_fighting() ) me->start_busy(3);

        return 1;
}

