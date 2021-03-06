//didao4.c		四川唐门—地道

inherit ROOM;

void create()
{
	set("short", "地道");
	set("long", @LONG
这是一条地道。但是它却并不是一条普通的地道，这里极宽敞
足可以有几十人在这里舞龙戏狮。这里亮如白昼，但是你却无法找
到这光亮的来源，地道向前延伸不知通向何处。你的心中升起一股
莫名的恐惧，还是离开的好。
LONG);
	set("exits", ([
			"northup" : __DIR__"didao3",
			"south" : __DIR__"andao1",
	]));
	set("area", "蜀中");
	setup();
}

void init()
{
	object me, killer;
	me = this_player();

	if ( wizardp(me) )
		return;

	if ( ( (string)me->query("family/family_name") == "四川唐门" )  && me->query_temp("tanglyz"))
		return;
	else
	{
		if ( userp(me) )
		{
			message_vision("突然从石壁中传来一声大喝:“擅闯禁地者，死！！！\n", me);
			message_vision("光滑的石壁上出现了一个石门，一名唐门死士跃了出来，向$N发动进攻！！！\n", me);
			killer = new(__DIR__"npc/killer");
			killer->move(environment(me));
			killer->kill_ob(me);
			me->fight_ob(killer);
		}
	}
	return;
}

int valid_leave(object me, string dir)
{
	me = this_player();

	if ( ((dir == "southdown")||(dir == "northup")) && objectp(present("killer", environment(me))) )
	{
		message_vision("死士一闪身将你拦了下来：想走？没那么容易！！！", me);
		return notify_fail("\n");
	}
	return ::valid_leave(me, dir);
}