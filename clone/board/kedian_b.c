// /clone/board/kedian_b.c

inherit BULLETIN_BOARD;

void create()
{
	set_name("大光明栈留言板", ({ "board" }) );
	set("location", "/d/beijing/kedian");
	set("board_id", "kedian_b");
	set("long", "这块留言板主要是用来让玩家互相留言用的，严禁灌水。\n" );
	setup();
	set("capacity", 50);
	replace_program(BULLETIN_BOARD);
}

