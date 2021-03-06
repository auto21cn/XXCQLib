// heal.c

#include <ansi.h>

int exert(object me, object target)
{
        if( me->is_fighting() )
                return notify_fail("战斗中运功疗伤？找死吗？\n");

        if (me->is_busy())
                return notify_fail("你正忙着其他事，怎么疗伤？\n");

        if ((int)me->query_skill("jiuqu-xinfa", 1) < 25)
                return notify_fail("你的玄天修为还不够。\n");
        if( (int)me->query("neili") < 50 ) 
                return notify_fail("你的真气不够。\n");
        if ((int)me->query("eff_qi") > ((int)me->query("max_qi")-1))
                return notify_fail("你不需要疗伤。\n");

        if( (int)me->query("eff_qi") < (int)me->query("max_qi") / 2 )
                return notify_fail("你的经脉受损，根本无法引导真气运行周身！\n");

        write( HIW "你盘膝跌坐，左手运真力疾点周身穴道，同时运玄天心法企图打通受损的经脉。\n" NOR);
        write( HIW "突然一股真气突破受损穴道，直冲天庭，你感到一股暖融融的感觉，伤势也好了许多。\n" NOR);
        message("vision",
                HIM + me->name() + "盘膝跌坐，左手运真力疾点周身穴道，过了半柱香功夫，脸色看起来似乎好了些。\n" NOR,
                environment(me), me);

        me->receive_curing("qi", 10 + (int)me->query_skill("force")/4 );
        me->add("neili", -50);
        me->set("jiali", 0);

        return 1;
}
