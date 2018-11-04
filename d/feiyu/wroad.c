// Room: wroad.c
// Created by Atlus 1999.7.21
// Modified by Atlus 1999.7.21
// 

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create ()
{
        set ("short", "小路");
        set ("long", @LONG
这是一条青石铺成的小路，两旁还种着一大片不知名的花草。布置和
东边的小路是一模一样的从这里向西走就到飞鱼塘的东院了。东边也是一
大块空地，那里就是西练武场了。
LONG);
	set("valid_startroom", 1);

        set("exits", 
        ([
		"west" : __DIR__"xiyuan",
		"east" : __DIR__"xiwuchang",
        "north" : __DIR__"jzroad1",
	   ]));

        set("outdoors", "feiyu");
        setup();
        replace_program(ROOM); 
}

