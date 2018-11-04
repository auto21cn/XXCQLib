// Room: /city/chouduanhang.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "观鱼阁二层");
	set("long", @LONG
走上观鱼阁二层，马上就被展现在眼前的湖光美景所吸引，那风起的
波澜、风中摇曳的荷花，加上万里碧空，真是美极了。一个女孩子站在楼
栏前望着远方，不知在想着什么。
LONG);

	set("valid_startroom", 1);
	set("exits", ([
		"down" : __DIR__"guanyu",
	]));

        set("objects", ([
		"/kungfu/class/huanhua/xueyu" : 1,
	]));

	setup();
	replace_program(ROOM);
}