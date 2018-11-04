//changan city

#include <ansi.h>
inherit ROOM;
#include "/kungfu/class/xuehepai/job.h"

void create ()
{
        set ("short", "华阳镇西口");
        set ("long", @LONG
你站在华阳镇的西口，再往西已经没有房屋了，只有一条路通往一片
树林而东面的那二十余间古老的房子便组成了这个古老的华阳小镇。在路
的南面有一家驿站，里面不时传来马嘶鸣的声音，一辆辆乌蓬马车也不时
的出发和到达。
LONG);
	set("valid_startroom", 1);

        set("exits", 
        ([
		"west" : __DIR__"hyroad1",
		"north" : __DIR__"hyyizhan",
		"east" : __DIR__"hyroad3"
       ]));

        set("outdoors", "huayang");
        setup();
}
