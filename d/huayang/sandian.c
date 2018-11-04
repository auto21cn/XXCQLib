// Room: /city/zahuopu.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "伞店");
	set("long", @LONG
这是除成都城内的刘记伞店外几十里唯一的一家伞店，本来生意应该
是很不错的，但由于权力帮进攻剑庐，使得附近的居民也都民不聊生，这
家伞店的生意也一落千丈。
LONG
	);

	set("valid_startroom", 1);

	set("exits", ([
		"south" : __DIR__"hyroad4",
	]));

	set("objects", ([
	]));

	setup();
	replace_program(ROOM);
}