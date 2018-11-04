// Room: shulin1.c
// Created by Zeus 1999.4.8
// Modified by Zeus 1999.4.10
// 修改长描述。
// 

inherit ROOM;
void create ()
{
        set ("short", "树林");
        set ("long", @LONG
这里是茂密的树林，由于树枝的茂密遮住了阳光，觉得有些阴森
恐怖。不时有两只野兔跑过你身边。向西走还是一片树林，向南走是
条非常陡峭的山径。
LONG);
        set("area","岭南");
        set("outdoors", "wenjia");

        set("objects", ([
                __DIR__"npc/yetu" : 1,
        ]));

        set("exits", ([
                "southup" : __DIR__"shanjing2",
                "west" : __DIR__"shulin2",
        ]));
        setup();
        replace_program(ROOM);
}
