// baikudajie5.c  by winder

#include <room.h>

inherit ROOM;

void create()
{	
	set("short", "界碑");
	set("long", @LONG
这里空空旷矿，眼前只是一片荒芜，几个人在紧张的施工中，地上立
有一块大大的汉白玉界碑，上面写有：“前方施工，访客回头。”八个大
字，下面的落款是汴梁城工程总监笨小孩，看来你只能回头了。
LONG);	
	set("valid_startroom",1);

	set("exits", ([
		"west" : __DIR__"huangkudajie6",
	]));

	set("outdoors", "bianliang");

	set("area", "汴梁");

	setup();

	replace_program(ROOM);
}