
#include <ansi.h>
inherit F_BUKUAI;

void create()
{
        set_name("捕快", ({ "bu kuai", "bu" }));
	set("title", "江湖争霸");
        set("gender", "男性");
        set("age", 30);
        set("str", 30);
        set("dex", 16);
        set("long", "他是衙门负责缉拿要犯的捕快\n");
        set("combat_exp", 20000);
        set("shen_type", 1);
        set("attitude", "heroism");

        set_skill("unarmed", 60);
        set_skill("force", 60);
        set_skill("sword", 60);
        set_skill("dodge", 60);
        set_skill("parry", 60);
        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/armor", 50);
        set_temp("apply/damage", 50);

        set("neili", 1000); 
        set("max_neili", 1000);
        set("jiali", 50);
        
        set("chat_chance",2);
        set("chat_msg",({
     "捕快哼了一声，说道：“有我在就谁也别想杀人...谁要是杀了人给我找麻烦，就让他妈的去坐牢！”\n",
     BLU"捕快低声嘟囔着：遇上杀人我才不理会呢！却来个欲擒故纵，只等他杀人得手逃去我才缉拿，如此就有赏银花了...哼哼...\n"NOR,
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
        carry_object("/clone/weapon/gangjian")->wield();
        carry_object("/clone/armor/tiejia")->wear();
}

void die()
{
	object ob;
	message_vision("$N倒在地上,挣扎了几下,死了。\n", this_object());
	ob = new("/clone/npc/bukuai");
	bu_move(ob);
	destruct(this_object());
}
