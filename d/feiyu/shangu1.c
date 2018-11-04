// Room: sahngu1.c
// Created by Atlus 1999.7.21
// Modified by Atlus 1999.7.21
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "山谷");
        set ("long", @LONG
这里的地势忽然变低了，你觉得似乎暖和了一点，向两旁望去，只见
山边上有些植物，有的还着开花。山谷一直向南延伸过去，回头望去，北
边的山峰上围绕着一些薄雾，有些虚无缥缈的感觉。
LONG);
        set("area","飞鱼");
        set("outdoors", "feiyu");

        set("objects", ([
                __DIR__"npc/feiyudizi" : 1,
        ]));

        set("exits", ([
                "northup" : __DIR__"shaozhan",
                "southdown" : __DIR__"shangu2",
        ]));
        setup();
        replace_program(ROOM);
}
