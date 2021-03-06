// Room: /d/shaolin/banruo1.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
	set("short", "罗汉堂偏殿");
	set("long", @LONG
这是罗汉堂南偏殿，是一间极为简陋的禅房。环视四周，除了几幅佛
竭外，室内空荡荡地别无他物。西面是少林功夫房之一的厌武房，地上摆
放着一个破烂且发黑的黄布蒲团，一位须发花白的老僧正在坐在上面闭目
入定，他就是负责看管厌武房的天鸿。
LONG );
	set("valid_startroom", 1);
	set("exits", ([
		"north" : __DIR__"luohan",
		"east" : __DIR__"kfroom_6",
	]));

	set("objects",([
		"/kungfu/class/shaolin/tianhong" : 1,
	]));

	setup();

}

int valid_leave(object me, string dir)
{
	if( !me->query_temp("kfroom_6"))
	{
		if (dir == "east")
		{
			return notify_fail("厌武房机关重重，没有天鸿的允许谁也进不去。\n");
		}
	}
	return ::valid_leave(me, dir);
}