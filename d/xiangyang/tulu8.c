//changan city

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create ()
{
        set ("short", "土路");
        set ("long", @LONG
这是很短的一段路，向西已经没有路了，只是一片乱草堆，路北有一
间茅屋，东边则连着村里的主路。
LONG);
	set("valid_startroom", 1);

        set("exits", 
        ([
		"east" : __DIR__"tulu4",
		"north" : __DIR__"minju4",
	]));

        set("outdoors", "zigui");
        setup();
}