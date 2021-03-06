// NPC 掌柜
// By 山猫Adx 16:53 99-10-25

#include <ansi.h>
inherit NPC;

int ask_me();

void create()
{
	set_name("唐讹化", ({ "tang ehua", "tang", "ehua" }) );
	set("title", HIB"药王谷"NOR+HIC"医师"NOR);
	set("long", "他是回春堂的坐堂老医师，负责给看病。\n" );
	set("gender", "男性" );
	set("age", 52);
	set("combat_exp", 100);
	set("attitude", "friendly");

        set("inquiry", ([
		"heal" : (: ask_me :),
        ]));

	setup();
        add_money("silver", 5);
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{	
	object ob = this_player();

	::init();
	if( interactive(ob) && !is_fighting() )
	{
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}

int greeting(object ob)
{

	if((string)ob->query("party/party_name")==HIB"药王谷"NOR) {
		command("say 这位兄弟辛苦了，快请进！\n");
		return 1;}
	else {
	switch( random(4) ) {
		case 0:
			command("bow "+ob->query("id"));
			break;
		case 1:
			command("nod "+ob->query("id"));
			break;
		case 2:
			command("hi "+ob->query("id"));
			break;
		case 3:
			command("welcome "+ob->query("id"));
			break;
		}
	}
}

int ask_me()
{
	object me;
	int i, obj;

	me = this_player();
	i = (me->query("max_qi")-me->query("eff_qi"));
	obj = me->query("max_qi");

	if(!me->query_temp("heal")) {
		command("say "+RANK_D->query_respect(me)+
			"你先交诊金"+MONEY_D->price_str(i*10)+"吧！\n");
		return 1;
	}
	me->delete_temp("heal");
	me->set("eff_qi", obj);
	me->set("qi", obj);
	message_vision ("唐讹化为$N把了把脉，拿出一根银针在$N穴位上扎了几下。\n", me);
	command("say 你的伤好得差不多了！");
	return 1;
}

int accept_object(object me, object ob)
{
	int i=(me->query("max_qi")-me->query("eff_qi"));

	if(i<5) i=5;

	command("smile");
	command("say 呵呵，多谢这位" + RANK_D->query_respect(me) + " ！");

	if( ob->query("money_id") ) 
	{
		if(ob->value() < (i*10))
		{
			command("say 这位给的未免少了点。");
			return 1;
		}
		else
		{
			me->set_temp("heal",1);
			command("say 好我收下了！");
			return 1;
		}
	}
	return 1;
}
