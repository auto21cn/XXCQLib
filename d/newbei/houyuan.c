// Room: /welcome/houyuan.c
//By adx @ CuteRabbit 15:57 99-5-18

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short",WHT"神雪后院"NOR);
	set("long",
"这是神雪山的后院。院里种植许多珍奇花卉，西面是武馆女弟子的休息室\n"+
"东面是武馆男弟子的休息室。院子里有一口水井如果你有容器你可以在\n"+
"这里装水喝"+HIC"（zhuang xxxx容器名）\n"NOR
	);
	set("exits", ([
	"west" :__DIR__"bingqiku",
	"east" :__DIR__"houting",
	"north" :__DIR__"nan-xiuxi",
	"south" :__DIR__"nv-xiuxi",
	"northwest" :__DIR__"liangong3",
	"southwest" :__DIR__"liangong4",
	]));
	set("resource/water", 1);
	set("outdoors", "welcome");
	setup();
}

int valid_leave(object me, string dir)
{       
	if ( ((dir=="south")||(me->query("gender")!="男性")) &&
		((dir=="north")||(me->query("gender")!="女性")) )
	{
	return notify_fail ("你看清楚别走错房间！\n");
	}
        return ::valid_leave(me, dir);
}
