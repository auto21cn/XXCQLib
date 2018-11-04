//wzlang1.c		四川唐门—走廊

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
	set("short", "走廊");
	set("long", @LONG
这里是莲云阁西侧的走廊。北边通向唐门的兵器房，南边则是练
功场，还不时的传出声声大喝。
LONG);
	set("exits", ([
//			"south" : __DIR__"liangong",
			"north" : __DIR__"wselfroom1",
			"west" : __DIR__"wzlang2",
			"east" : __DIR__"nzlang1",
	]));
	set("area", "蜀中");
	setup();
	replace_program(ROOM);
}