// heibujie1.c  by winder

#include <room.h>

inherit ROOM;

void create()
{	
	set("short", "�ڲ���");
	set("long", @LONG

LONG);	
//	set("valid_startroom",1);
//	set("no_steal", "1");
//	set("no_fight", "1");
//	set("outdoors", "bianliang");
	set("exits", ([
		"north" : __DIR__"tsh_lukou",
		"south" : __DIR__"heibujie2",
		"west" : __DIR__"tsh_yuanshenfu",
		"east" : __DIR__"tsh_xiangmengyuan",
	]));
//	set("objects", ([
//		"/clone/weapon/changjian" : 4]));
	set("area", "����");
	setup();
	replace_program(ROOM);
}