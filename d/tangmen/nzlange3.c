//nzlange3.c		四川唐门—碎石小路

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
	set("short", "碎石小路");
	set("long", @LONG
这是一条碎石铺就的小路。一些唐门的弟子往来穿梭，这里还真是很热
闹。这里向
LONG);
	set("exits", ([
			"west" : __DIR__"nzlange2",
			"east" : __DIR__"lianparry",
			"north" : __DIR__"lianthrow",
			"south" : __DIR__"liandodge",
	]));
	set("area", "蜀中");
	setup();
//	replace_program(ROOM);
}