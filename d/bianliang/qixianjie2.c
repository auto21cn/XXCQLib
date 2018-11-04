// qixianjie2.c  by winder

#include <room.h>

inherit ROOM;

void create()
{	
	set("short", "七贤街");
	set("long", @LONG
这里的大街街面要比别处的干净、整洁。大概因为靠近国师府的缘故，
往西是圣贤庙，往东是富丽堂皇的庞将军府。

LONG);	
//	set("valid_startroom",1);
//	set("no_steal", "1");
//	set("no_fight", "1");
//	set("sleep_room",1);
	set("exits", ([
		"north" : __DIR__"qixianjie1",
		"south" : __DIR__"qixianqiao",
		"west" : __DIR__"by_shengxianmiao",
		"east" : __DIR__"by_pangfu",
	]));
//	set("objects", ([
//		"/clone/weapon/changjian" : 4]));
	set("area", "汴梁");
	setup();
	replace_program(ROOM);
}
