// Room: 大门
// Date: by godzilla 1999.11.18

inherit ROOM;

void create()
{
	set("short", "大门");
	set("long", @LONG
这里四周杂草丛生，门上锈记斑斑，看来很就都没有人来过了，
门上悬着一块大匾，上书【天羽门】。
LONG );
        set("outdoors", "tianyu");
	set("exits", ([
            "south" : "/d/xiangyang/tulu5",
		"north"  : __DIR__"qingshilu",
	]));
	setup();
	replace_program(ROOM);
}
