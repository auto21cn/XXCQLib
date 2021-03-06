// Room: /d/shaolin/zhulin6.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
	set("short", "初祖庵");
	set("long", @LONG
竹林走到这里，突然出现了一片空地，只见几间小庵，几株小树，
古意清凉，寒气顿消；庵前立有一块石碑，由于年代久远，小字已经看
不太清楚了，只是初祖庵三个篆刻大字挺拔如昔。这里是通往面壁石的
必经之路。
LONG );
	set("valid_startroom", 1);

	set("exits", ([
		"south" : __DIR__"zhulin5",
		"east" : __DIR__"zhulin11",
		"west" : __DIR__"zhulin12",
	]));

	set("no_clean_up", 0);

	set("outdoors", "shaolin");

	setup();

	replace_program(ROOM);
}

