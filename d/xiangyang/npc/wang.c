// huoji. ҩ�̻��

inherit NPC;
#include <ansi.h>

void create()
{
    set_name("��С��", ({ "wang", "wang xiaoer", "xiaoer"}));
	set("str", 20);
	set("gender", "����");
	set("age", 27);
	set("long", "����һ���ǳ���׳�������ˣ����ƺ����Ṧ��\n");
	set("max_qi",350);
	set("eff_qi",350);
	set("qi",350);
	set("combat_exp", 2000);
	set("attitude", "friendly");

	setup();
	carry_object("/clone/misc/cloth")->wear();
}

#include "/d/quanli/npc/die_quest.c"