// Room:/d/kunming/kedian.c
// JackyBoy@CuteRabbits Studio for CCTX 1999/4/17

inherit ROOM;

void create()
{
	set("short", "昆明客栈");
	set("long", @LONG
这是一家靠十字路口的客栈，店铺很有点规模了，生意也不错，许多过往
的人都喜欢选择这里落脚，因为这里的店主也是一个江湖中人，所以很少有人
会来此闹事，小二忙前忙后的招呼客人，店主也满脸笑容的陪着说好话。让人
有一种归家的感觉。
LONG
	);

	set("no_fight", 1);
	set("valid_startroom", 1);
	set("no_sleep_room",1);

	set("exits", ([
		"east"  : __DIR__"nanjie1",
		"north" : __DIR__"xijie1",
	]));

	setup();
	call_other("/clone/board/kedian_km_b","???");
	replace_program(ROOM);
}
