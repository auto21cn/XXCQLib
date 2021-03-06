// Room: /d/shaolin/smdian.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
	set("short", "山门殿");
	set("long", @LONG
这里是少林寺的前殿山门殿。殿内青砖铺地，两侧分列哼、哈二将。
身躯雄伟，面相忿怒，头带宝冠，上半身裸露，手执金刚杵，一鼓鼻，一
张口，露牙睁目，凶猛可畏。两边各放一红木供桌，陈列香烛，以供僧俗
叩拜。自此左右各有一间偏殿，供比丘们打坐诵经之用。南面是一道三丈
来高的朱红杉木包铜大门。
LONG );
	set("valid_startroom", 1);
	set("exits", ([
		"east" : __DIR__"smdian1",
		"west" : __DIR__"smdian2",
		"north" : __DIR__"taijie",
		"south" : __DIR__"guangchang1",
	]));
	set("objects",([
		__DIR__"npc/seng-bing3" : 2,
		__DIR__"npc/xiang-ke" : 1,
	]));

	setup();
}

int valid_leave(object me, string dir)
{
	if ( me->query("id") == "seng bing" &&  dir == "south" ) return 0;

	return ::valid_leave(me, dir);
}

