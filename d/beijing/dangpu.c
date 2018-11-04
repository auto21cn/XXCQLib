// Room: /city/dangpu.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "当铺");
	set("long", @LONG
	这是京城唯一的一家当铺，因为在京城开当铺，不但要招揽好客户，而且
还要打点好上上下下的关系，这家当铺的刘老板能在京城开这家当铺长达几十年，
必然有后台支撑，至于是谁，就不得而知了。走进当铺，一个五尺高的柜台挡在你
的面前，柜台后坐着刘老板，一双精明的眼睛上上下下打量着你。
LONG
	);
	set("no_fight", 1);
	set("no_beg",1);

	set("valid_startroom", 1);
	set("objects", ([
		__DIR__"npc/liu" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"shalan-w1",
	]));

	setup();
	replace_program(ROOM);
}

