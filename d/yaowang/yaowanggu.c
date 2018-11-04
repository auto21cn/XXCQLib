// Room: 药王谷
// By 山猫adx @ 宁波小雪 17:00 99-10-26

inherit ROOM;

void create()
{
	set("short", "药王谷");
	set("long", @LONG
这里就是药王谷了，周围是高高的山峰，山谷中一大片的空地，中央起了一座
庄园。两边是一片农田，种着许多象草不知道是怎么东西。
LONG );
	set("area", "药王谷");
	set("areb", "药王谷");
	set("no_fight", 1);
	set("exits", ([
		"north" : __DIR__"dating",
		"south" : __DIR__"zhuangqian",
		"west" : __DIR__"tiandi1",
		"east" : __DIR__"tiandi2",
	]));
         set("objects", ([
                 __DIR__"npc/lufeng" : 1,
         ]));

	setup();
	replace_program(ROOM);
}
