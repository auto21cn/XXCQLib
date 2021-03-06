// wei.c 韦老板 

inherit F_DEALER;
#include "/d/bianliang/npc/hhjob.h"

void create()
{
	set_name("刘铁匠", ({ "liu tiejiang", "liu", "tiejiang" }));
	set("title", "打铁铺主人");
	set("shen_type", 1);
	set("gender", "男性");
	set("age", 35);
	set("long",
		"他就是华阳镇唯一一家打铁铺的主人，坚实的臂膀淌满了汗水。\n");
	set_skill("strike", 50);
	set_skill("dodge", 50);
	set_temp("apply/damage", 15);

	set("combat_exp", 10000);
	set("attitude", "friendly");
	set("vendor_goods", ({
		__DIR__"obj/bishou",
		__DIR__"obj/caidao",
		__DIR__"obj/chutou",
		__DIR__"obj/gangpa",
		__DIR__"obj/liandao",
		__DIR__"obj/litou",
		__DIR__"obj/tiefu",
		"/clone/weapon/changjian",
	}));
	
	setup();
	carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}
