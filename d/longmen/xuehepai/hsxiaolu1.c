//hsxiaolu。c             龙门后山--碎石小路

#include <room.h>
inherit ROOM;

void create()
{
	set("short", "碎石小路");
	set("long", @LONG
这里是后山小路。只容一人通过，两边杂草丛生，不时传出悉悉索索
的拨草声，偶尔还有一两只小动物自面前掠过，小路弯弯曲曲的向前伸去
，通向更加阴暗的后山。
LONG);
	set("exits", ([
			"northeast" : __DIR__"hsxiaolu3",
			"northwest" : __FILE__,
//			"southwest" : __FILE__,
//			"west" : __FILE__,
//			"east" : __FILE__,
//			"south" : __FILE__,
			"north" : __FILE__,
			"southeast" : __DIR__"shandao3",
	]));
	set("outdoors","龙门");
	setup();
	replace_program(ROOM);
}
