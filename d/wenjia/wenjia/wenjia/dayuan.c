// Room: dayuan.c
// Created by Zeus 1999.4.8
// Modified by Zeus 1999.6.10
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "大院");
        set ("long", @LONG
这里是一个大院，打扫得非常干净，四周放着一些矮凳，墙边有一个
大水缸。水缸里的水呈现出一种绿色，十分怪异。有两个温家弟子守卫在
这里。向北走就是后院，西边是制毒室，东边是实验室，向南走是就是会
客室。
LONG);
        set("area","岭南");
        set("outdoors", "wenjia");
        set("valid_startroom", 1);

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
