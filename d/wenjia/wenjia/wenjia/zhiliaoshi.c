// Room: zhiliaoshi.c
// Created by Zeus 1999.4.16
// Modified by Zeus 1999.6.10
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "治疗室");
        set ("long", @LONG
这里活字号里的治疗室，温家弟子中了毒后可以在这里解毒并且在北
面的病房里休息。东南方向上是会客室。
LONG);
        set("area","岭南");
        set("valid_startroom", 1);

        set("exits", ([
                "southeast" : __DIR__"huikeshi1",
                "north" : __DIR__"bingfang",
        ]));

        setup();
        replace_program(ROOM);
}
