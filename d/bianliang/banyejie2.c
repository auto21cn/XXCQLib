// banyejie2.c

#include <room.h>

inherit ROOM;

void create()
{	
	set("short", "半夜街");
	set("long", @LONG
这条大街是新近衙门程知府用收来的地税钱派人新铺的，用大理石铺设的路面，
十分华丽。

LONG);	
//	set("valid_startroom",1);
//	set("no_steal", "1");
//	set("no_fight", "1");
//	set("sleep_room",1);
	set("exits", ([
		"west" : __DIR__"banyejie1",
		"east" : __DIR__"bh_lukou4",
	]));
//	set("objects", ([
//		"/clone/weapon/changjian" : 4]));
	set("area", "汴梁");
	setup();
	replace_program(ROOM);
}
