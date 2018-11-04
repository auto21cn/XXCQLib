// Room: lijiangbian2.c
// Created by Zeus 1999.6.4
// Modified by Zeus 1999.6.4
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "漓江边");
        set ("long", @LONG
湍急的漓江江水在西北边的悬崖下飞奔，在江水上面的是一座铁索桥，
走过铁索桥可以到达去四川驿道。这里是属于两广地区，向往西南方向走
就可以来到我国古代最伟大的水利工程——灵渠。
LONG);
        set("area","桂林");
        set("outdoors", "guilin");
	set("valid_startroom", 1);

        set("exits", ([
                "northwest" : __DIR__"tiesuo",
                "southwest" : __DIR__"lingqu",
        ]));
        setup();
        replace_program(ROOM);
}

