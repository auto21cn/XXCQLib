//changan city

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create ()
{
        set ("short", "秭归镇街口");
        set ("long", @LONG
秭归镇不象其他小镇成十字状，而是丁子型的，这个街口就是秭归镇
的中心，从这里出北口至黄河秭归渡口，东面是金银街，金银钱庄就在那
边，南边则是衙门的所在。
LONG);
	set("valid_startroom", 1);

        set("exits", 
        ([
		"north" : __DIR__"chaoyang2",
		"south" : __DIR__"huiyang1",
		"east" : __DIR__"jinyin1",
	]));

        set("outdoors", "zigui");
        setup();
}