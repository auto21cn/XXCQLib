// Room: /city/chouduanhang.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "南厢回廊");
	set("long", @LONG
整个的剑庐是连绵不断的回廊连接的，现在所在的南厢回廊的左、右
分别是花坛和南厢院，而沿着回廊向西则通向落花潭、观鱼阁等地方，不
时有丫鬟、家丁走过这里。
LONG
	);

	set("valid_startroom", 1);

	set("exits", ([
		"north" : __DIR__"qianroad2",
		"west" : __DIR__"southlang_2",
		"south" : __DIR__"southyuan",
	]));

        set("objects", ([
	]));

	setup();
	replace_program(ROOM);
}