// sample master.c code
// xiake island master.c

inherit NPC;
inherit F_MASTER;
#include <ansi.h>

void recover_ob();

void create()
{
	set_name("白云", ({"bai yun", "bai", "yun"}));
	set("gender", "男性");
	set("age", 25);
	set("long", 
"他是浣花剑派四代弟子中最干练的一个，也是浣花“十年会”之一，
是受掌门允许收徒的三名四代弟子之一。\n");
	set("attitude", "peaceful");
	set("title", "浣花剑派第四代弟子、"HIC"十年会"NOR);
	set("str", 25);
	set("int", 20);
	set("con", 18);
	set("dex", 22);
	set("bac", 15);

	set("qi", 1900);
	set("max_qi", 1900);
	set("jingli", 1200);
	set("max_jingli", 1200);
	set("neili", 1400);
	set("max_neili", 1400);
	set("jiali", 25);
	
	set("combat_exp", 300000);
	set("shen", 5000);
	
	set_skill("force", 110);
	set_skill("jiuqu-xinfa", 110); 
	set_skill("strike", 120);
	set_skill("feixu-zhang", 120);
	set_skill("dodge", 110); 
	set_skill("huanhua-shenfa", 110); 
	set_skill("sword", 120); 
	set_skill("huanhua-jian", 120); 
	set_skill("parry", 100); 
	set_skill("confu", 90); 
	set_skill("literate", 90); 
	
	map_skill("force", "jiuqu-xinfa");
	map_skill("dodge", "huanhua-shenfa");
	map_skill("strike", "feixu-zhang");
	map_skill("sword", "huanhua-jian");
	map_skill("parry", "huanhua-jian");

	prepare_skill("strike", "feixu-zhang");

	setup();

	create_family("浣花剑派", 4, "弟子");

	carry_object("/d/huanhua/npc/obj/jinpao")->wear();
	carry_object("/clone/weapon/changjian")->wield();

	set("chat_chance_combat", 30);
	set("chat_msg_combat", ({
		(: perform_action, "sword.mantian" :),
		(: perform_action, "sword.luanhong" :),
		(: perform_action, "strike.fenfei" :),
		(: recover_ob :)
	}) );
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
	mapping my_fam;

	if( !ob || environment(ob) != environment() ) return;

	if (!(my_fam = ob->query("family")) || my_fam["family_name"] != "浣花剑派")
		command("welcome "+ob->query("id"));

	return;
}

void recover_ob()
{
	command("yun recover");
	return;
}

void attempt_apprentice(object ob)
{
	object me;
	mapping my_fam, ob_fam;

	me = this_object();

	my_fam = ob->query("family");
	ob_fam = me->query("family");

	if (!(my_fam = ob->query("family")) || my_fam["family_name"] != "浣花剑派")
	{
		command("shake " + ob->query("id"));
		command("say 掌门只许我收浣花低辈弟子，你不是浣花弟子，我不能收你。");
		return;
	}

	if ((int)ob->query("shen") <= (-100))
	{
		command("say 你身为浣花弟子却不主张正义，甘入魔道，我浣花容不下你！");
		command("kaichu "+ob->query("id"));
		return;
	}
        if ( ob_fam["generation"] == my_fam["generation"] )
        {
                command("say 你我同辈弟子，拜我为师？不是和我开玩笑吧？");
                command("xixi");
                return;
        }



	if ( ob->query_skill("huanhua-jian",1) < 60
		||ob->query_skill("huanhua-shenfa",1) < 60
		||ob->query_skill("jiuqu-xinfa",1) < 60)
	{
		command("say 浣花剑法、浣花身法、九曲心法是我们浣花剑派最根本的功夫，你的水平好不够。");
		command("say 再练好一些再来找我吧。");
		return;
	}

	command("say 既然你的功夫已经有了一定的根底，那我就收下你了。");
	command("recruit " + ob->query("id"));

	return;
}
