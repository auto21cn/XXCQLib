// Npc: /d/shaolin/npc/seng-bing3.c
// Date: YZC 96/01/19

#include <ansi.h>

inherit NPC;

void create()
{
	set_name("守寺僧兵", ({
		"seng bing",
		"seng",
		"bing",
	}));
	set("long",
		"他是一位身材高大的壮年僧人，两臂粗壮，膀阔腰圆。他手持兵\n"
		"刃，身穿一袭灰布镶边袈裟，似乎有一身武艺。\n"
	);

	set("gender", "男性");
	set("attitude", "peaceful");
	set("class", "bonze");

	set("age", 40);
	set("shen_type", 1);
	set("str", 25);
	set("int", 20);
	set("con", 20);
	set("dex", 25);
	set("bac", 25);
	set("max_qi", 700);
	set("qi", 700);
	set("max_jingli", 500);
	set("jingli", 500);
	set("neili", 500);
	set("max_neili", 500);
	set("jiaji", 50);
	set("combat_exp", 20000);
	set("score", 1);

	set_skill("force", 60);
	set_skill("banruo-changong", 60);
	set_skill("dodge", 60);
	set_skill("shaolin-shenfa", 60);
	set_skill("cuff", 60);
	set_skill("luohan-quan", 60);
	set_skill("parry", 60);
	set_skill("blade", 60);
	set_skill("buddha", 60);
	set_skill("cibei-dao", 60);

	map_skill("force", "banruo-changong");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("cuff", "luohan-quan");
	map_skill("parry", "cibei-dao");
	map_skill("blade", "cibei-dao");

	prepare_skill("cuff", "luohan-quan");

	setup();

	carry_object(__DIR__"obj/jiedao")->wield();
	carry_object(__DIR__"obj/huijiasha")->wear();

	create_family("少林派", 37, "弟子");
}

void init()
{
	object me, ob;
	mapping fam;

	::init();

	ob = this_player();
	me = this_object();
	
	if (interactive(ob) 
	&& !environment(ob)->query("no_fight")
	&& !present("yingxiong ling", ob) 
	&& ( (fam = ob->query("family")) && fam["family_name"] != "少林派" ) )
	{
		if( !ob->query_temp("warned") ) {
			command("say 你是谁？！怎么闯到少林寺里来了？！");
			command("say 快给我速速离开，下次看到决不轻饶！");
			ob->set_temp("warned", 1);
		}
		else if( ob->query_temp("stay") < 10 ) ob->add_temp("stay", 1);
		else {
			command("say 大胆狂徒，竟敢闯到少林寺里来撒野！！！\n");
			me->set_leader(ob);
			remove_call_out("kill_ob");
			call_out("kill_ob", 1, ob); 
		}
	}       

}
