//changan city

#include <ansi.h>
#include <room.h>
inherit MATOU;

void create ()
{
        set ("short", "浣花码头");
        set ("long", @LONG
这里就是浣花码头了，延溪小路也到此为止了，七级台阶一直延伸到
水中，一辆乌篷船靠在码头边，看不到船家，估计正在船舱里抓紧时间歇
息，你如果要船就喊几声船家吧(gu chuan)。
LONG);
	set("valid_startroom", 1);

        set("exits", 
        ([
		"north" : __DIR__"hhxroad2",
        ]));
        set("objects", ([
                 "/d/huanhua/npc/yiren.c": 1,
        ]));

        set("outdoors", "xiao");
        setup();
}
