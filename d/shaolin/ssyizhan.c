// Room: /city/chouduanhang.c
// YZC 1995/12/04 

#include YIZHAN
inherit ROOM;

void create()
{
	set("short", "嵩山驿站");
	set("long", @LONG
这是一间黄土砌就的小房，后面则是依山而建的一间大木棚，里面传
来阵阵马嘶声，柜台就在你面前，但却没有人在后面。如果你想坐车，就
雇一辆(gu che)吧。
LONG
	);

	set("valid_startroom", 1);

	set("exits", ([
		"east" : __DIR__"shijie1",
	]));

	setup();
}
