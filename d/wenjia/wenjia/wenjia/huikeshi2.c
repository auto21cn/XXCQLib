// Room: huikeshi2.c
// Created by Zeus 1999.4.16
// Modified by Zeus 1999.6.10
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "会客室");
        set ("long", @LONG
这里是死字号的会客室。牌匾上写着死字号三个大字，太师椅上坐着
的是温辣子。西面的门是到练功房的，而东面的是到死字号首脑温丝卷的
书房。
LONG);
        set("area","岭南");
        set("valid_startroom", 1);

        set("objects", ([
                __DIR__"npc/wenlazi" : 1,
        ]));

        set("exits", ([
                "northdown" : __DIR__"siroad6",
                "east" : __DIR__"shufang",
                "west" : __DIR__"liangongfang",
        ]));

        setup();
        replace_program(ROOM);
}
