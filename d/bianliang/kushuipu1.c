// kushuipu1.c

#include <room.h>

inherit ROOM;

void create()
{	
	set("short", "苦水铺");
	set("long", @LONG
这是一条宽阔的青石板街道，向东西两头延伸。

LONG);	
//	set("valid_startroom",1);
//	set("no_steal", "1");
//	set("no_fight", "1");
//	set("sleep_room",1);
	set("exits", ([
		"west" : __DIR__"bh_lukou4",
		"east" : __DIR__"kushuipu2",
	]));
//	set("objects", ([
//		"/clone/weapon/changjian" : 4]));
	set("area", "汴梁");
	setup();
	replace_program(ROOM);
}
