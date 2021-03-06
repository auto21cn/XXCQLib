// xueyu 萧雪鱼
// By load

inherit NPC;
inherit F_MASTER;

void heal_ob();
void recover_ob();
#include <ansi.h>

void create()
{
	set_name("萧雪鱼", ({"xiao xueyu", "xiao", "xueyu"}));
	set("gender", "女性");
	set("nickname", HIC"冰雪聪明"NOR);
	set("age", 23);
	set("long", 
"她是一个爱笑的女孩子，虽然看上去象个孩子一样天真，但其实是\n"
"冰雪聪明，文武双全，巾帼不让须眉。\n"
"她是浣花现任掌门萧西楼的小女儿。一直打理着剑庐的内务。\n");
	set("attitude", "peaceful");
	set("str", 17);
	set("int", 23);
	set("con", 16);
	set("dex", 20);
	set("bac", 24);

	set("qi", 2200);
	set("max_qi", 2200);
	set("jingli", 1400);
	set("max_jingli", 1400);
	set("neili", 1600);
	set("max_neili", 1600);
	set("jiali", 50);
	
	set("combat_exp", 600000);
	set("shen", 20000);
	
	set_skill("force", 140);
	set_skill("jiuqu-xinfa", 140); 
	set_skill("strike", 140);
	set_skill("feixu-zhang", 140);
	set_skill("dodge", 160); 
	set_skill("huanhua-shenfa", 160); 
	set_skill("sword", 140); 
	set_skill("parry", 140); 
	set_skill("literate", 140); 
	set_skill("confu", 140);
	set_skill("huanhua-jian", 140); 
	
	map_skill("force", "jiuqu-xinfa");
	map_skill("dodge", "huanhua-shenfa");
	map_skill("strike", "feixu-zhang");
	map_skill("parry", "huanhua-jian");
	map_skill("sword", "huanhua-jian");

	prepare_skill("strike", "feixu-zhang");
	
	create_family("浣花剑派", 3, "弟子");

	setup();

	carry_object("/d/huanhua/npc/obj/shaqun")->wear();
	carry_object("/d/huanhua/npc/obj/ruanxiang")->wear();
	carry_object("/clone/weapon/changjian")->wield();

	set("chat_chance", 3);
	set("chat_msg", ({
		(: heal_ob :),
		"萧雪鱼突然扑哧一声笑出了声，不知道想到的什么好事。\n",
		"萧雪鱼转头看了你一眼，却似乎没有看到一般又再次回过头继续发呆。\n",
	}));

	set("chat_chance_combat", 30);
	set("chat_msg_combat", ({
		(: perform_action, "sword.mantian" :),
		(: perform_action, "sword.luanhong" :),
		(: perform_action, "strike.fenfei" :),
		(: recover_ob :)
	}) );
}

void heal_ob()
{
	command("yun heal");
	command("yun heal");
	command("yun heal");
	command("yun recover");
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
		command("look " + ob->query("id"));
		command("say 我从来没见过你，拜我为师？不是开玩笑吧。");
		command("giggle");
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

	if (ob->query("shen")<40000)
	{
		command("say 你维护武林正义的义举做得不够，我还不能收你。");
		command("addoil " + ob->query("id"));
		return;
	}

	if (ob->query_int()<26)
	{
		command("shake " + ob->query("id"));
		command("say 你看起来一点也不聪明，我可不愿意教你，还是算了吧。");
		return;
	}

	if (ob->query_skill("sword",1)< 80 || ob->query_skill("huanhua-jian",1) < 80)
	{
		command("say 我们浣花剑派以剑法为本，你是否应该在剑法方面多下些功夫呢？");
		return;
	}

	if (ob->query("gender")=="男性")
	{
		command("say 我只收女弟子，你要拜师就去找我二哥开雁吧。");
		return;
	}

	command("say 好吧，就收下你吧，不过我的功夫可不如我的哥哥们好呦。");
	command("recruit " + ob->query("id"));

	return;
}