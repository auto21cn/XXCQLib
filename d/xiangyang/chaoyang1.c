//changan city

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create ()
{
        set ("short", "潮阳街");
        set ("long", @LONG
虽然秭归镇最著名的是那家金银钱庄，但若论最古老的应该算是路东
的这家嫡仙楼了，这是小镇最华丽的所在，这里作的佛跳墙也是远近闻名
，甚至特地来此品尝。
LONG);
	set("valid_startroom", 1);

        set("exits", 
        ([
		"north" : __DIR__"zgnorth",
		"south" : __DIR__"chaoyang2",
	]));

        set("outdoors", "zigui");
        setup();
}