// /clone/board/news_b.c

inherit BULLETIN_BOARD;

void create()
{
	set_name("客栈留言簿",({"board"}) );
	set("location","/d/kunming/kedian");
	set("long","这是一个让来昆明客栈的客人留言的簿子。\n");
        setup();
        set("capacity",200);
        replace_program(BULLETIN_BOARD);
}
