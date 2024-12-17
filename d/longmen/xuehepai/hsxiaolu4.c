#include <room.h>
inherit ROOM;

void create()
{
        set("short", "碎石小路");
        set("long", @LONG
这里是后山小路。道路越来越窄，山石林立，状若犬齿，碎石扎的脚
刺痛刺痛的，不时从远处传来声声怪啸，让人头皮发麻，小路弯弯曲曲的
向前伸去，通向更加阴暗的后山。
LONG);
        set("valid_startroom",1);
        set("exits", ([
		"northup" : __DIR__"houshan",
		"east" : __DIR__"hsxiaolu2",
		"north" : __DIR__"hsxj1",
        ]));
        set("outdoors", "龙门");
        setup();
        replace_program(ROOM);
}

