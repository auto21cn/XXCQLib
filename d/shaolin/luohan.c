// Room: /d/shaolin/banruo1.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
	set("short", "罗汉堂");
	set("long", @LONG
般若堂、罗汉堂肩负为少林培养武僧的责任，其中你所在的罗汉堂掌
管少林功夫房中的进武、精武、厌武三房，罗汉堂主持木蝉大师的功夫也
是出神入化，是少林七大高僧之一，般若堂的西面就是精武房，坐在木蝉
大师下手的就是负责看管精武房的天罗。
LONG );
	set("valid_startroom", 1);
	set("exits", ([
		"north" : __DIR__"luohan_n",
		"east" : __DIR__"kfroom_4",
		"south" : __DIR__"luohan_s",
		"west" :__DIR__"wuchang7",
	]));

	set("objects",([
		"/kungfu/class/shaolin/tianluo" : 1,
		"/kungfu/class/shaolin/muchan" : 1,
	]));

	setup();

}

int valid_leave(object me, string dir)
{
	if( !me->query_temp("kfroom_4"))
	{
		if (dir == "east")
		{
			return notify_fail("精武房机关重重，没有天罗的允许谁也进不去。\n");
		}
	}
	return ::valid_leave(me, dir);
}