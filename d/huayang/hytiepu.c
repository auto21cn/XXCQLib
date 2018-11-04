// Room: /city/zahuopu.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "华阳打铁铺");
	set("long", @LONG
还没走进打铁铺，阵阵热浪已经传了过来，由于是乡村的打铁铺，所
以屋内挂着的也都是农民用的铁器，看到你进来，铁匠停下手中的活站起
来迎了上来。
LONG
	);

	set("valid_startroom", 1);

	set("exits", ([
		"south" : __DIR__"hyroad3",
	]));

	set("objects", ([
		__DIR__"npc/tiejiang": 1,
	]));

	setup();
	replace_program(ROOM);
}