// Room: liandanfang.c
// Created by Zeus 1999.4.8
// Modified by Zeus 1999.6.10
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "炼丹房");
        set ("long", @LONG
这里是小字号的炼丹房。在实验室里配好药方的药品就来这里炼丹做
成实验品。这里只有一个出口，向西走就是实验室。
LONG);
        set("area","岭南");
        set("valid_startroom", 1);
 
        set("exits", ([
                "west" : __DIR__"shiyanshi",
        ]));
 
        setup();
        replace_program(ROOM);
}
