// Room: /city/chouduanhang.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "南厢回廊");
	set("long", @LONG
南厢回廊和北厢回廊都是从建造之初到现在从没修缮过的，廊顶绘的
楚汉之争的故事也已经斑驳了，回廊两侧更是留下了孩子顽皮的图鸦。从
这里望向西面，已经可以看到落花湖的湖面了。
LONG
	);

	set("valid_startroom", 1);

	set("exits", ([
		"east" : __DIR__"southlang",
		"west" : __DIR__"hupan_s",
	]));

        set("objects", ([
	]));

	setup();
	replace_program(ROOM);
}