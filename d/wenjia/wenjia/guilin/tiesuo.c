// Room: tiesuo.c
// Created by Zeus 1999.6.4
// Modified by Zeus 1999.6.4
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "铁索桥");
        set ("long", @LONG
一条横跨漓江的铁索桥。桥连接着漓江的东西岸，往西北边就是四川
了，而过了这座桥就是两广境内了。认真看看铁索桥，桥挂在两个悬崖峭
壁上，由于这里还是漓江的上游，桥下的水流非常的湍急，掉下去肯定没
命的了，你可要抓紧铁索呀!
LONG);
        set("area","桂林");
        set("outdoors", "guilin");
	set("valid_startroom", 1);

        set("exits", ([
                "southeast" : __DIR__"lijiangbian2",
                "northwest" : __DIR__"lijiangbian1",
        ]));
        setup();
        replace_program(ROOM);
}

