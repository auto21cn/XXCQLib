
inherit ROOM;
#include "/kungfu/class/xuehepai/job.h"
void create()
{
        set("short", "小镇中心");
        set("long", @LONG
这里就是这个小镇的广场，也是居民们集合的地方。由于这个小镇
正在建设当中，所以经常有告示贴出来，居民常到这来了解小镇的建设
进度，这里放着一个箱子，是用来让有钱的人士为小镇建设募捐的。
LONG );
        set("valid_startroom",1);
        set("outdoors","龙门");
        set("objects",([
                __DIR__"obj/box" : 1,
      ]));
        set("class","血河派");
        set("exits", ([
                "west"  : __DIR__"xijie",
                "south"  : __DIR__"nanjie",
        ]));
//        set("no_clean_up", 0);
        setup();
}

