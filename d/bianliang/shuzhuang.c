// shuzhuang.c

#include <room.h>

inherit ROOM;

void create()
{	
	set("short", "三友书庄");
	set("long", @LONG
一间小小的书庄，里面四壁全都堆满了书，各种各样的书籍几乎都可
以在这里找到，三、四个读书人翻看着书架上的书，书庄老板是一个斯文
的中年人，虽说只是个秀才，但据说水平不低。
LONG);	
	set("valid_startroom",1);

	set("exits", ([
		"west" : __DIR__"hongbujie6",
	]));

	set("objects", ([
		__DIR__"npc/xiucai" : 1
	]));

	set("area", "汴梁");

	setup();

	replace_program(ROOM);
}