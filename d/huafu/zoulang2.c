// zoulang2.c 走廊2
// mlf设计,lks编程

#include <ansi.h>

inherit ROOM;

void create()
{
	set("short","走廊");
        set("long",
"这是通往花府内堂的道路，北面是一个圆形的拱门，那里好象种满了
花，使得你在这里都可以闻到花香。但是又好象隐隐透着一股杀气。你不
禁打了个寒噤。。。\n"
	);
	set("valid_startroom",1);
	set("outdoors","huafu");
	set("exits",([
		"north" : __DIR__"huazhen1",
		"southwest" : __DIR__"dating",
	]));
	setup();
	replace_program(ROOM);
}
