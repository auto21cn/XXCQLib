// void.c (re-created after Elon screwed it up on 07-24-95)

inherit ROOM;

void create()
{
	set("short","虚无世界");
	set("long",@LONG	
这就是穿越时空的虚无世界，据说穿过这里可以到达遥远的未来，但是
没有人能够真的穿越这里，神也不能，所以没人知道这个传说是真是假。你
的周围一片漆黑，你就在这空无一物的空间飘浮着，根本无处可去，你要大
声的叫喊，却听不到任何声音，片刻间，你突然有些绝望了，突然有一扇闪
光的门出现在面前，这可能是稍纵即逝的机会，不要犹豫了，出去吧！
LONG
	);

	set("exits", ([
		"down" : "/d/bianliang/guangming",
	]));

	setup();
	replace_program(ROOM);
}