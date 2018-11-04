// Room: /city/chouduanhang.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "七曲廊");
	set("long", @LONG
这段长廊之所以称为七曲廊就是因为它沿湖而行，曲曲折折，站在这
里可以欣赏落花湖优美的景色，阵阵湖风吹过，非常惬意。从北面出长廊
就是一座小楼，那是庄主的书房，轻易不要去打扰的好。
LONG
	);

	set("valid_startroom", 1);

	set("exits", ([
		"southeast" : __DIR__"hupan_n",
		"west" : __DIR__"qqlang_2",
        "north" : __DIR__"menqian",
	]));

        set("objects", ([
	]));

	setup();
	replace_program(ROOM);
}
