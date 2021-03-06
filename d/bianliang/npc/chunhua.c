// huoji. 药铺伙计

inherit NPC;

void create()
{
	set_name("孟春花", ({ "meng chunhua", "meng", "chunhua"}));
	set("str", 20);
	set("gender", "女性");
	set("title", "华清池老板娘");
	set("age", 45);
	set("long", "她是一个很能干的女人，每天在这里招呼客人和阻止“走错了门”的人。\n");
	set("combat_exp", 250);
	set("attitude", "friendly");

	setup();
	carry_object("/clone/misc/cloth")->wear();
}

void init()
{
	object ob;

	::init();
	if( interactive(ob = this_player()) && !is_fighting() ) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}

void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;
	say( "孟春花迎上来道：这位" + RANK_D->query_respect(ob)
				+ "快请进，洗个澡好舒服的。\n");
}