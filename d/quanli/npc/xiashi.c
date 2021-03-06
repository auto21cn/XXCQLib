// sample master.c code
// xiake island master.c

inherit NPC;
inherit F_MASTER;
void away();

void create()
{
	set_name("少年侠士", ({ "xia shi","xia","shi" }));
	set("gender", "男性");
	set("age", 26);
	set("long", 
		"他是一个英俊的少年人，背负长剑，剑鞘上似乎有一个小小的萧字。\n");
	set("attitude", "peaceful");
	set("str", 25);
	set("int", 15);
	set("con", 20);
	set("dex", 25);
	set("bac", 15);

	set("qi", 300);
	set("max_qi", 300);
	set("jingli", 200);
	set("max_jingli", 200);
	set("neili", 100);
	set("max_neili", 100);
	
	set("combat_exp", 1000);
	
	set_skill("force", 10);
	set_skill("jiuqu-xinfa", 10); 
	set_skill("strike", 10);
	set_skill("feixu-zhang", 10);
	set_skill("dodge", 10); 
	set_skill("huanhua-shenfa", 10); 
	set_skill("sword", 10); 
	set_skill("huanhua-jian", 10); 
	set_skill("parry", 10); 
	set_skill("confu", 10); 
	set_skill("literate", 10); 

	map_skill("force", "jiuqu-xinfa");
	map_skill("dodge", "huanhua-shenfa");
	map_skill("strike", "feixu-zhang");
	map_skill("sword", "huanhua-jian");
	map_skill("parry", "huanhua-jian");

	prepare_skill("strike", "feixu-zhang");
	
	setup();

	carry_object("/clone/misc/cloth")->wear();
	carry_object("/clone/weapon/changjian")->wield();

	set("chat_chance", 20);
	set("chat_msg", ({
		(: away :),
	}));
        add_money("silver", 20+random(10));
}

void away()
{
	if( living(this_object()) )
	{
		message_vision(this_object()->query("name") + "一纵身，已经从你的视线里消失了。\n", this_object());
		destruct(this_object());
	}
	return;
}