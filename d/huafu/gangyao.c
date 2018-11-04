// gangyao.c  缸窑
// made by lks

#include <ansi.h>

inherit ROOM;

void create()
{
	set("short","缸窑");
        set("long",
"来到这里，除了一阵浓浓的酒香外，由于空气不流通还感到一丝丝头
晕。透过墙壁上的烛光，依稀可以看到一个个突起的小土包。上面都插着
牌子。原来这里就是埋酒的地方。\n"
	);
	set("exits",([
		"up" : __DIR__"zaofang",
	]));
	set("valid_startroom",1);
	setup();
}

void init()
{
	add_action("do_mai","mai");
}

int do_mai(string arg)
{
	object me;
	object ob;
	me=this_player();
	
        if ( (arg!="九酝酒") && (arg!="jiuyunjiu") )
		return 0;
	if (!ob=present("jiuyunjiu",me))
		return 0;
	message_vision("$N用锹挖了一个坑，把酒埋了进去。还立了个牌子，注明埋酒的日期。\n",me);
       me->set_temp("fmjob_ok",1);
	me->start_busy(random(5));
	destruct(ob);
	return 1;
}

