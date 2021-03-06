// shaogong.c

inherit NPC;

int ask_location();

void create()
{
	set_name("艄公", ({ "gong", "shaogong" }) );
	set("gender", "男性" );
	set("age", 50);
	set("combat_exp", 100);
	set("attitude", "friendly");
	set("rank_info/respect", "老船家");
	set("inquiry", ([
		"位置": (: ask_location :),
		"location": (: ask_location :),
		"走": "您得告诉我往哪边开呀(turn n|w|s|e)！",
		"出海": "您得告诉我往哪边开呀(turn n|w|s|e)！",
		"开船": "您得告诉我往哪边开呀(turn n|w|s|e)！",
		"起航": "您得告诉我往哪边开呀(turn n|w|s|e)！",
		"启航": "您得告诉我往哪边开呀(turn n|w|s|e)！",
	]) );
	setup();
}

int ask_location()
{
	object ob=this_player();

	say("艄公看了看荷花塘，说道：我们现在的位置是(" + ob->query_temp("mr_locx") + ","
	+ ob->query_temp("mr_locy") + ")。\n");
	return 1;
}
