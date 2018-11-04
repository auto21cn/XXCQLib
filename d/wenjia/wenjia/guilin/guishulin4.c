// Room: guishulin.c
// Created by Zeus 1999.6.4
// Modified by Zeus 1999.6.4
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "桂树林");
        set ("long", @LONG
茂密的桂树林，这里种植着一片茂密的桂树林，而这里被称为桂林的
原因就是因为桂林周围有非常多的桂树林。西北边的路就是到著名的芦笛
岩。
LONG);
        set("area","桂林");
        set("outdoors", "guilin");
	set("valid_startroom", 1);

        set("exits", ([
                "northwest" : __DIR__"ludi",
                "south" : __DIR__"jiedao",
        ]));
        setup();
        replace_program(ROOM);
}

