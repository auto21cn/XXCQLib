// bing.c 官兵

inherit F_BUKUAI;

void create()
{
	set_name("官兵", ({ "guan bing", "bing" }));
	set("title", "江湖争霸 巡逻");
	set("age", 22);
	set("gender", "男性");
	set("long", "虽然官兵的武艺不能和武林人士相比，可是他们讲究的是人多力量大。\n");
	set("attitude", "heroism");
//	set("vendetta_mark", "authority");
//      set("pursuer", 1);

	set("str", 24);
	set("dex", 16);
	set("combat_exp", 10000);
	set("shen_type", 1);

	set_skill("unarmed", 40);
	set_skill("dodge", 40);
	set_skill("parry", 40);
	set_skill("blade", 40);
	set_skill("force", 40);
	set_temp("apply/attack", 40);
	set_temp("apply/defense", 40);
	set_temp("apply/damage", 20);
	set_temp("apply/armor", 40);

        set("chat_chance_combat", 10);
	set("chat_msg_combat", ({
		"官兵喝道：大胆刁民，竟敢造反不成？\n",
		"官兵喝道：跑得了和尚跑不了庙，你还是快快束手就擒！\n",
	}));

        set("chat_chance",2);
        set("chat_msg",({
	"官兵哼了一声道：“我得，把眼睛睁大些，最近乱党闹得很凶。”\n",
        (: random_move :),
        (: random_move :),
        (: random_move :),
        (: random_move :),
        (: random_move :),
        (: random_move :),
        (: random_move :),
        (: random_move :),
        }));

	setup();
	carry_object("/clone/weapon/gangdao")->wield();
	carry_object("/clone/armor/junfu")->wear();
	carry_object("/clone/food/jitui")->wear();
	add_money("silver",2);
}
