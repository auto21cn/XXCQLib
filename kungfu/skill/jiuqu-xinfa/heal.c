// heal.c

#include <ansi.h>

int exert(object me, object target)
{
	if( me->is_fighting() )
		return notify_fail("ս�����˹����ˣ�������\n");

	if (me->is_busy())
		return notify_fail("����æ�������£���ô���ˣ�\n");

	if ((int)me->query_skill("jiuqu-xinfa", 1) < 40)
		return notify_fail("��ľ����ķ���Ϊ��������\n");
	if( (int)me->query("neili") < 50 ) 
		return notify_fail("�������������\n");
	if ((int)me->query("eff_qi") > ((int)me->query("max_qi")-1))
		return notify_fail("�㲻��Ҫ���ˡ�\n");

	if( (int)me->query("eff_qi") < (int)me->query("max_qi") / 2 )
		return notify_fail("��ľ������𣬸����޷�������������������\n");

	write( HIW "����ϥ������Ĭ�˾����ķ�����һ�ɵ���֮��������������ʼ���ˡ�\n" NOR);
	message("vision",
		HIY + me->name() + "��ϥ������Ĭ���񹦣�ͻȻ���ۡ���һ�����һ���Ѫ����ɫ�������ƺ��������ࡣ\n" NOR,
		environment(me), me);

	me->receive_curing("qi", 10 + (int)me->query_skill("force")/5 );
	me->add("neili", -50);
	me->set("jiali", 0);

	return 1;
}