inherit NPC;
inherit F_MASTER;
#include <ansi.h>
void recover_ob();

void create()
{
	set_name("树林", ({"shu lin", "shu", "lin"}));
	set("gender", "男性");
	set("age", 24);
	set("long", 
		"他是浣花剑派四代弟子中以坚持原则，决不妥协著称的一个。\n");
	set("attitude", "peaceful");
	set("title", "浣花剑派第四代弟子、"HIC"十年会"NOR);
	set("str", 16);
	set("int", 15);
	set("con", 20);
	set("dex", 24);
	set("bac", 25);

	set("qi", 1700);
	set("max_qi", 1700);
	set("jingli", 1100);
	set("max_jingli", 1100);
	set("neili", 1300);
	set("max_neili", 1300);
	set("jiali", 10);
	
	set("combat_exp", 200000);
	set("shen", 1000);
	
	set_skill("force", 100);
	set_skill("jiuqu-xinfa", 100); 
	set_skill("strike", 110);
	set_skill("feixu-zhang", 110);
	set_skill("dodge", 120); 
	set_skill("huanhua-shenfa", 120); 
	set_skill("sword", 110); 
	set_skill("huanhua-jian", 110); 
	set_skill("parry", 100); 
	set_skill("confu", 100); 
	set_skill("literate", 110); 
	
	map_skill("force", "jiuqu-xinfa");
	map_skill("dodge", "huanhua-shenfa");
	map_skill("strike", "feixu-zhang");
	map_skill("sword", "huanhua-jian");
	map_skill("parry", "huanhua-jian");

	prepare_skill("strike", "feixu-zhang");
	
	create_family("浣花剑派", 4, "弟子");

	setup();

	carry_object(__DIR__"obj/jinpao")->wear();
	carry_object("/clone/weapon/changjian")->wield();

	set("chat_chance_combat", 30);
	set("chat_msg_combat", ({
		(: perform_action, "sword.mantian" :),
		(: perform_action, "sword.luanhong" :),
		(: perform_action, "strike.fenfei" :),
		(: recover_ob :)
	}) );
}

void recover_ob()
{
	command("yun recover");
	return;
}

void attempt_apprentice(object ob)
{
	command("say 这位"+ RANK_D->query_respect(ob) +
		"，庄主不准我收徒，如果你真的想拜师，还是找别人吧。");
	return;
}