//changan city

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create ()
{
        set ("short", "江中巨石");
        set ("long", @LONG
走上江心巨石，立时感到心情澎湃，滚滚长江从脚下流过，阵阵水浪
扑面，长江在巨石面前分为两半，流速陡然加急，奔腾而去。一位身着铁
衣消瘦老人坐在这里旁若无闻的垂钓。
LONG);
	set("valid_startroom", 1);

        set("exits", 
        ([
		"south" : __DIR__"hengtan",
        ]));

	set("objects", ([
		"/kungfu/class/quanli/futianyi": 1,
	]));

        set("outdoors", "zigui");
        setup();
}