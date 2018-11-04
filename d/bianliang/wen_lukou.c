// wen_lukou.c  by winder

#include <room.h>

inherit ROOM;

void create()
{	
	set("short", "路口");
	set("long", @LONG
这是个丁字路口，东，西两边都是黄裤大街。

LONG);	
//	set("valid_startroom",1);
//	set("no_steal", "1");
//	set("no_fight", "1");
//	set("sleep_room",1);
	set("exits", ([
		"north" : __DIR__"wazixiang5",
		"east" : __DIR__"huangkudajie2",
		"west" : __DIR__"huangkudajie1",
	]));
//	set("objects", ([
//		"/clone/weapon/changjian" : 4]));
	set("area", "汴梁");
	setup();
	replace_program(ROOM);
}
