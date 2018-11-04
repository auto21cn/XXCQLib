// Room: qixingyan.c
// Created by Zeus 1999.6.4
// Modified by Zeus 1999.6.4
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "七星岩");
        set ("long", @LONG
七星岩自从隋唐起就是旅游胜地。是桂林山水中“二洞”之一。七星
岩是桂林较大的岩洞，分为上、中、下三层，下层为河，终年有水。洞内
钟乳凝结，石笋、石柱、石花瑰丽多彩、蔚为壮观。
LONG);
        set("area","桂林");
        set("outdoors", "guilin");
	set("valid_startroom", 1);

        set("exits", ([
                "west" : __DIR__"guishulin2",
        ]));
        setup();
        replace_program(ROOM);
}

