// Room: /city/chouduanhang.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "九曲廊");
	set("long", @LONG
一进入湖南岸的九曲廊，就听到了南边远处有阵阵的练武的喊声，向
南望，一条石板路向南延伸，隐约看到一个大大的广场，看来应该是剑庐
的练武场。长廊向西曲曲折折沿湖而行。
LONG
	);

	set("valid_startroom", 1);

	set("exits", ([
		"west" : __DIR__"jqlang_2",
		"northeast" : __DIR__"hupan_s",
		"south" : __DIR__"wuroad2",
	]));

        set("objects", ([
	]));

	setup();
	replace_program(ROOM);
}