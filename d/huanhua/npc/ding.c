// ding.c 家丁

inherit NPC;

int ask_baishi();

void create()
{
	set_name("家丁", ({ "jia ding", "ding" }));
	set("age", 25);
	set("gender", "男性");
	set("long", "他是一个精壮的青年男子，每日里就做一些端茶倒水、打扫庭厨的工作。\n");
	set("attitude", "peaceful");

	set("str", 24);
	set("dex", 16);
	set("combat_exp", 10000);
	set("shen_type", 1);

	set_skill("strike", 40);
	set_skill("dodge", 40);
	set_skill("parry", 40);
	set_skill("force", 40);
	set_temp("apply/attack", 40);
	set_temp("apply/defense", 40);
	set_temp("apply/damage", 20);
	set_temp("apply/armor", 40);

	setup();

	carry_object(__DIR__"obj/liangongfu")->wear();
}