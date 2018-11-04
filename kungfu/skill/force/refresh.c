// regenerate.c

//inherit SSERVER;

int exert(object me, object target)
{
	int n, q;

	q = (int)me->query("eff_jingli") - (int)me->query("jingli");
	if (q < 10)
		return notify_fail("你现在精力充沛。\n");
                 if (me->query("neili")<20)
                            return notify_fail("你的内力不够。\n");
	n = (q / ((int)me->query_skill("force") / 3)) * 30;

	if (n < 20)
		n = 20;

	if ((int)me->query("neili") < n) 
	{
		q = q * (int)me->query("neili") / n;
		n = (int)me->query("neili");
	}

	me->add("neili", -n);
	me->receive_heal("jingli", q);
	
        message_vision("$N深深吸了几口气，精神看起来好多了。\n", me);

        if( me->is_fighting() ) me->start_busy(1);
	
	return 1;
}

