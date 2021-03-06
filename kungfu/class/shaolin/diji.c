// Npc: /kungfu/class/shaolin/xuan-ci.c
// Date: YZC 96/01/19

inherit NPC;
inherit F_MASTER;

void recover_ob();

void create()
{
	set_name("地极大师", ({"diji dashi", "diji", "dashi",}));
	set("long",
		"他是一位白须白眉的老僧，身穿一袭金丝绣红袈裟。\n"
		"他身材略显佝偻，但却满面红光，目蕴慈笑，显得神完气足。\n"
	);


	set("title", "少林寺般若堂首座");
	set("gender", "男性");
	set("attitude", "friendly");
	set("class", "bonze");

	set("age", 70);
	set("shen_type", 1);
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	set("max_qi", 2500);
	set("max_jingli", 1500);
	set("neili", 3000);
	set("max_neili", 3000);
	set("jiali", 50);
	set("combat_exp", 1200000);
	set("score", 500000);
	set_skill("force", 190);
	set_skill("banruo-changong", 190);
	set_skill("dodge", 170);
	set_skill("shaolin-shenfa", 170);
	set_skill("strike", 190);
	set_skill("parry", 170);
	set_skill("banruo-zhang", 190);
	set_skill("buddha", 180);
	set_skill("literate", 180);

	map_skill("force", "banruo-changong");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("strike", "banruo-zhang");
	map_skill("parry", "banruo-zhang");

	prepare_skill("strike", "banruo-zhang");

	create_family("少林派", 35, "弟子");

	setup();

	set("chat_chance_combat", 30);
	set("chat_msg_combat", ({
		(: perform_action, "strike.banruo" :),
		(: recover_ob :)
	}) );

        carry_object("/d/shaolin/npc/obj/jinjiasha")->wear();
        carry_object("/d/shaolin/npc/obj/sengxie")->wear();
}

void recover_ob()
{
	command("yun recover");
	return;
}