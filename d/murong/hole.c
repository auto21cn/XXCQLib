// hole.c


inherit ROOM;
#include <ansi.h>

string look_out();
void create()
{
         set("short",HIR"石屋"NOR);
         set ("long",@long
这里漆黑一片，什么都看不见。你能看见的只有一个小窗户(window)。
从这里透过来一丝光亮。
long);
        set("item_desc",([            
            "window" : (: look_out :),
        ]));
	setup();
	replace_program(ROOM);
}

	