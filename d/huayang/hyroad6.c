//changan city

#include <ansi.h>
inherit ROOM;
#include "/kungfu/class/xuehepai/job.h"

void create ()
{
        set ("short", "华阳镇东口");
        set ("long", @LONG
从华阳镇东口向东走出去只是一条长长的小路，如果自己走恐怕十天
半个月也走不到的，这条路只是为了走马车预备的，据称连接着湖北武汉
和河北保定。
LONG);
        set("valid_startroom", 1);

        set("exits", 
        ([
                "west" : __DIR__"hycs",
                "east" : "/d/longmen/lukou",
        ]));

        set("outdoors", "huayang");
        setup();
}

