// 风吹草动
// bye jfeng 江枫
#include <ansi.h>
inherit F_SSERVER;
int perform(object me, object target)
{
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("风吹草动只能对战斗中的对手使用。\n");
        if((int)me->query_skill("strike") < 100)
                return notify_fail("你的基本掌法火候不够，无法使用风吹草动。\n");
        if((int)me->query_skill("zhuifeng-zhang",1) < 100)
                return notify_fail("你的追风掌火候不够，无法使用风吹草动。\n");
        if((int)me->query_skill("zhixin",1) < 100)
                return notify_fail("你的温故知新火候不够，无法使用风吹草动。\n");
        if( me->query("max_neili") < 500 || me->query("neili") < 700 )
                return notify_fail("你的内力修为不够，无法使用风吹草动！\n");
        message_vision(HIR"$N凌空跃起,大喝一声，双掌齐发，排山倒海的劲气卷向$n！！！\n"NOR, me, target);
        me->add("neili", -200);
        me->add_temp("apply/strength", 2*(int)me->query("str") );
        me->add_temp("apply/dexerity", 2*(int)me->query("dex") );
        COMBAT_D->do_attack(me, target);
        me->add_temp("apply/strength", -2*(int)me->query("str") );
        me->add_temp("apply/dexerity", -2*(int)me->query("dex") );
        me->start_busy(4);
        return 1;
}
