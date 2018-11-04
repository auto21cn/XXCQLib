// xiting.c 西偏厅
// mlf设计，lks编程

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
	set("short","西偏厅");
	set("long",
	"这里只是一个偏厅，摆设很简单，一张圆桌，几张圆凳。桌子上方有
一幅画，画中是一个貌若天仙，素雅之极的少女，画得栩栩如生，仿佛将
从画中走出。不知是否真有其人，不禁让人浮想联翩。西边一扇门关着。\n"NOR
     	);
     	set("valid_startroom",1);
	set("exits",([
     		"east" : __DIR__"dating",
     		"west" : __DIR__"xixiangfang",
     	]));
     	create_door("west", "木门", "east", DOOR_CLOSED);
     	setup();
     	replace_program(ROOM);
}