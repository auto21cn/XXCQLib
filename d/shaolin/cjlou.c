// Room: /d/shaolin/cjlou.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
	set("short", "藏经阁一楼");
	set("long", @LONG
不愧为中原佛法的总源，少林寺此处藏经之富，天下罕有其匹。这里
都是密密麻麻，高及顶棚的书架，书架间仅有容身一人通行的空隙。几排
大书架中间，间隔地放着数丈长的书桌。目光及处，你看到桌上放了几本
佛经。
LONG );
	set("valid_startroom", 1);

	set("exits", ([
		"east" : __DIR__"zhulin5",
		"up" : __DIR__"cjlou1",
	]));

	set("objects",([
		__DIR__"obj/jing1" : 2,
	]));

	setup();
}