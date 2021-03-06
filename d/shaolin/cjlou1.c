// Room: /d/shaolin/cjlou1.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
	set("short", "藏经阁二楼");
	set("long", @LONG
千余年来少林寺执中原武林之牛耳，自达摩老祖以下，历代人材辈出
。其中有不少高僧遗著留存，汇集至今，终成名震天下的少林七十二绝艺
。少林精华，尽集于此。二楼四面开窗，确保通风。中间排列着五排大书
架。四周则陈列矮几，以供阅读。几位老僧手执经卷，正在闭目凝思。
LONG );
	set("valid_startroom", 1);

	set("exits", ([
		"down" : __DIR__"cjlou",
	]));

	set("objects",([
		__DIR__"npc/tieting" : 1,
	]));

	setup();
}