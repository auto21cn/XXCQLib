
inherit ROOM;
#include "/kungfu/class/xuehepai/job.h"
void create()
{
        set("short", "小镇西街");
        set("long", @LONG
路上很干净，赶路的行人来来往往。一阵阵酒香从南面的一个铺子
里面传了出来，一些江湖豪客都进去买酒解馋。北面挂着一个锦旗，上
面写着“龙门客栈”四个大字，再往东走就到了镇中心了。
LONG );
        set("valid_startroom",1);
        set("outdoors","龙门");
        set("class","血河派");
        set("exits", ([
                "west"  : __DIR__"dexit",
                "east"  : __DIR__"sqare",
                "north"  : __DIR__"kezhan",
                "south"  : __DIR__"jiulou",
        ]));
//        set("no_clean_up", 0);
        setup();
}

