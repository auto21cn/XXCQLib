// huazhen3.c 花阵
// mlf设计,lks编程

#include <ansi.h>

inherit ROOM;

void create()
{
	set("short",HIR"花阵"NOR);
        set("long",
"这庭院只深一丈六尺三，四周都是花，隐约可见有几条小路通向四周
，阵阵花香飘来，你不觉有些昏昏欲睡。路象蜘蛛丝一样复杂，看来你是
迷路了。\n"
	);
	set("outdoors","huafu");
	set("exits", ([
            "northeast" : __FILE__,
            "southeast" : __FILE__,
            "southwest" : __FILE__,
            "northwest" : __FILE__,
            "north" : __FILE__,
            "east" :  __DIR__"huazhen4",
            "south" : __DIR__"huazhen2",
            "west" : __FILE__,
        ]));
        setup();
        replace_program(ROOM);
}


int valid_leave(object me, string dir)
{
        int jingli_cost;

        me=this_player();

        jingli_cost=(-1) * ( me->query("max_jingli") ) / 20 ;

        return ::valid_leave(me, dir);
}

