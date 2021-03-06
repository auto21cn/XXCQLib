// Room: /d/shaolin/shijie10.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
	set("short", "石阶");
	set("long", @LONG
松树与松树似乎都挤在一块生长，阳光到这里变得格外黯淡只在地上
留下斑驳的碎影。静听不远处格的一声，象是松枝断落的声音。
LONG );
	set("valid_startroom", 1);
	set("exits", ([
		"southdown" : __DIR__"shijie9",
		"northup" : __DIR__"shijie11",
	]));
	set("no_clean_up", 0);
	set("outdoors", "shaolin");
	setup();
}

int valid_leave(object me, string dir)
{
	me = this_player();

	if (( present("shui tong", this_player())) && dir == "northup")
	{
		if (me->query("jingli")<15)
			return notify_fail("提着大水桶，你已经累的走不动道了。\n");
		me->add("jingli",-10);
		me->improve_skill("dodge",10+random(5));
		me->start_busy(1);
	}

	return ::valid_leave(me, dir);
}
