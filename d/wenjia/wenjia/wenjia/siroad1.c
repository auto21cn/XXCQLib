// Room: siroad1.c
// Created by Zeus 1999.4.16
// Modified by Zeus 1999.6.10
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "山路");
        set ("long", @LONG
这里是到“死字号”的山路，路旁种的都是一些奇异花草。说不定这
些花草是有毒的？还是快些离开这里吧。向北上去就是山路，向西南方走
就是总部的东广场。
LONG);
        set("area","岭南");
        set("outdoors", "wenjia");
        set("valid_startroom", 1);

        set("exits", ([
                "southwest" : __DIR__"eastsquare",
                "northup" : __DIR__"siroad2",
        ]));

        setup();
        replace_program(ROOM);
}
