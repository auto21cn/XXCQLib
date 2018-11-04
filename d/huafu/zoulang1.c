// zoulang1.c 走廊1
// mlf 设计,lks编程

#include <ansi.h>

inherit ROOM;

void create()
{
	set("short","走廊");
	set("long",@LONG
	 你好不容易走出花阵，前面豁然开朗，北面一坐大房巍然而立，那就
是发梦二党两大巨头之一的，发党首领花枯发日常办公之处。只有花首领
的得意弟子才能自由出入此地。
LONG
	);
	set("outdoors","huafu");
	set("valid_startroom",1);
	set("exits",([
		"west" : __DIR__"huazhen4",
		"north" : __DIR__"neitang",
	]));
	setup();
	replace_program(ROOM);
}
