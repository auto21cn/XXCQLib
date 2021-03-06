// tongren.c 铜人
// by Load

inherit NPC;

void create()
{

	set_name("铜人", ({"tong ren","tong","ren",}));
	set("long",
		"他是一位身穿黄布袈裟的青年僧人。脸上稚气未脱，身手却已相\n"
		"当矫捷，看来似乎学过一点武功。\n"
	);

	set("nickname", "知客僧");
	set("gender", "男性");
	set("attitude", "friendly");
	set("class", "bonze");

	set("age", 20);
	set("shen_type", 1);
	set("str", 20);
	set("int", 20);
	set("con", 35);
	set("dex", 20);
	set("bac", 22);
	set("max_qi", 400);
	set("qi", 400);
	set("max_jingli", 300);
	set("jingli", 300);
	set("neili", 200);
	set("max_neili", 200);
	set("jiali", 10);
	set("combat_exp", 20000);
	
	set_skill("force", 40);
	set_skill("banruo-changong", 40);
	set_skill("dodge", 30);
	set_skill("shaolin-shenfa", 30);
	set_skill("cuff", 40);
	set_skill("luohan-quan", 40);
	set_skill("parry", 30);
	set_skill("buddha", 30);

	map_skill("force", "banruo-changong");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("cuff", "luohan-quan");
	map_skill("parry", "luohan-quan");

	prepare_skill("cuff", "luohan-quan");

	create_family("少林派", 38, "弟子");

	setup();

        carry_object("/d/shaolin/npc/obj/huangjiasha")->wear();
        carry_object("/d/shaolin/npc/obj/sengxie")->wear();
}

void attempt_apprentice(object ob)
{
	object me;
	mapping my_fam, ob_fam;
	me = this_player();

	my_fam = ob->query("family");
	ob_fam = me->query("family");

	if( (string)ob->query("gender") != "男性" )
	{
		command ("say 阿弥陀佛！这位施主呀，贫僧可不敢开这等玩笑啊。");
		return;
	}

	command("say 阿弥陀佛，善哉！善哉！");

	if( (string)ob->query("class")!="bonze" )
	{
		command("say 阿弥陀佛，善哉！善哉！");
		command("say 施主若真心皈依我佛，就请上山拜铜智或是铜慧师兄吧。");
		return;
	}

	if ( ob_fam["generation"] > my_fam["generation"] )
	{
		command("say " + RANK_D->query_respect(ob) + "，贫僧哪里敢当 !");
		return;
	}

	command("say " + RANK_D->query_respect(ob) + "，贫僧只负责看守山门，不能收徒！");
}