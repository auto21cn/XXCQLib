// Room: dayuan.c
// Created by Zeus 1999.4.8
// Modified by Zeus 1999.4.10
// 修改长描述。
// 

inherit ROOM;
void create ()
{
        set ("short", "大院");
        set ("long", @LONG
这里是一个大院，打扫得非常干净，四周放着一些矮凳，墙
边有一个大水缸。水缸里的水呈现出一种绿色，十分怪异。有两
个温家弟子守卫在这里。向北走就是后院，西边是制毒室，东边
是实验室，向南走是就是会客室。
LONG);
        set("area","岭南");
        set("outdoors", "wenjia");

        set("objects", ([
                __DIR__"npc/wenjiadizi" : 2,
        ]));

        set("exits", ([
                "south" : __DIR__"huikeshi",
                "north" : __DIR__"houyuan",
                "east" : __DIR__"shiyanshi",
                "west" : __DIR__"zhidushi",
        ]));
        setup();
        replace_program(ROOM);
}
