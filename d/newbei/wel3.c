// 山猫ADX by snow 99-12-4

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short",WHT"欢迎光临小雪初晴"NOR);
	set("long",
"如果你想加入某个门派，可以先拜"+HIC"(bai)"NOR+"个师傅，你可以跟他学习"+HIC"(xue)\n"NOR
"也可以通过其他方式，如读书"+HIC"(du)"NOR+"或"+HIC"(study)"NOR+",也可以向同门的师兄弟讨教。\n"
    );
        

        set("exits", ([
                "south":__DIR__"welx",
                "west" :__DIR__"wel1",
        ]));
        set("objects",([
                __DIR__"npc/jieyinshi3":1,
                ]));
        set("no_fight", 1);
        
	setup();
        replace_program(ROOM);
}
