// Room: /d/shaolin/shijie9.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
	set("short", "石阶");
	set("long", @LONG
眼前遽然出现一大片松林。松林长得极密，石阶上铺满了厚厚的朽黄
的松针。踩在脚下，发出察察的响声。一只小松鼠吱地在眼前闪过，消失
在林海里。
LONG );
	set("valid_startroom", 1);
	set("exits", ([
		"southdown" : __DIR__"shijie8",
		"northup" : __DIR__"shijie10",
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
