//bcailiao.c		四川唐门—镖房

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
	set("short", "储料房");
	set("long", @LONG
这里是唐门储存制造暗器材料的房间。钢镖，银针，飞蝗石，铁
蒺藜，三叉棱，铁丸，飞刀，没羽箭，龙须钉等等等等，所有可以说
得上名的暗器和制作材料，都可以在这里寻到它的踪影。东北面是一
条青石小路。
LONG);
	set("exits", ([
			"northeast" : __DIR__"houroad3",
	]));
	set("objects", ([__DIR__"npc/bjiading" : 1,]));
	set("area", "蜀中");
	setup();
	replace_program(ROOM);
}