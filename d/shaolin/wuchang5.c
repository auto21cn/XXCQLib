// Room: /d/shaolin/wuchang3.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
	set("short", "练武场");
	set("long", @LONG
这里是少林寺的练武场。由无数块巨大的花岗岩石板铺就。上千年的
踩踏已使得这些石板如同镜子般平整光滑。练武场中间竖立着不少木人和
草靶。西边角上还有两个大沙坑，十来个僧人正在练习武艺。北面就是闻
名天下的少林戒律院。
LONG
	);
	set("valid_startroom", 1);
	set("exits", ([
		"south" : __DIR__"wuchang",
		"north" : __DIR__"fzlou",
	]));

	set("outdoors", "shaolin");

	set("objects",([
		"/kungfu/class/shaolin/tiewen" : 1,
	]));

	setup();
}

int valid_leave(object me, string dir)
{
	if( !me->query("luohan_winner") && !wizardp(me))
	{
		if (dir == "northup")
		{
			return notify_fail("你级别不够，不能进入达摩院。\n");
		}
	}
	return ::valid_leave(me, dir);
}

