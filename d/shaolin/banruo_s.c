// Room: /d/shaolin/banruo1.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
	set("short", "般若堂偏殿");
	set("long", @LONG
这是般若堂南偏殿，是一间极为简陋的禅房。环视四周，除了几幅佛
竭外，室内空荡荡地别无他物。西面是少林功夫房之一的穷武房，地上摆
放着一个破烂且发黑的黄布蒲团，一位须发花白的老僧正在坐在上面闭目
入定，他就是负责看管穷武房的天音。
LONG );
	set("valid_startroom", 1);
	set("exits", ([
		"north" : __DIR__"banruo",
		"west" : __DIR__"kfroom_5",
	]));

	set("objects",([
		"/kungfu/class/shaolin/tianyin" : 1,
	]));

	setup();

}

int valid_leave(object me, string dir)
{
	if( !me->query_temp("kfroom_5"))
	{
		if (dir == "west")
		{
			return notify_fail("穷武房机关重重，没有天音的允许谁也进不去。\n");
		}
	}
	return ::valid_leave(me, dir);
}