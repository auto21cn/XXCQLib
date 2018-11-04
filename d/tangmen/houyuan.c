//houyuan.c		四川唐门—后院

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
	set("short", "后院");
	set("long", @LONG
这里是莲云阁后院。这风清景幽的园子里里面有一池荷塘，靖蜒
点水、粉蝶翻称，阳光泛花，坠珊珊，绿芽似旧，拂窗有寒。荷塘寂
寂，荷叶一摇就像在那儿一片一片的分割光影。这里通向唐门的镖房
和毒房。
LONG);
	set("exits", ([
			"east" : __DIR__"houroad4",
			"north" : __DIR__"mishi",
	]));
	set("objects", ([__DIR__"npc/tangkun" : 1,]));
	set("area", "蜀中");
	setup();
	replace_program(ROOM);
}