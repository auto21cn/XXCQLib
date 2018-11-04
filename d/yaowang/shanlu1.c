// Room: 药王谷
// By 山猫adx @ 宁波小雪 17:00 99-10-26

inherit ROOM;

void create()
{
	set("short", "山路");
	set("long", @LONG
你走在一条狭小的山路上，两边是一片灌木丛，山路往北通向一个烟雾缭绕的
山谷，往南通向汴梁城。山风吹过，你不禁泛起阵阵寒意，还是尽快离开为好。
LONG );
	set("area", "药王谷");
	set("areb", "山路1");
	set("exits", ([
        "south" : "/d/bianliang/jiebei4",
		"north" : __DIR__"shanlu2",
	]));

        set("outdoors", "yaowang");
	setup();
	replace_program(ROOM);
}
