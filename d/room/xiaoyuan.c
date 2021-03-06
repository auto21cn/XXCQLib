// xiaoyuan.c 小院
// Written by Doing Lu 1998/11/17

inherit ROOM;

#include <ansi.h>

void create()
{
	set("short", "小院");
	set("long", @LONG
	这里是一个小院，正中坐着一个人，看不出年纪有多大，四周围着四个垂
髫童子，正在聆听先生教导。院中有一些尚未成型的石具，木模，制作的非常精细，
实在是难以用语言来形容。
LONG
	);

	set("no_fight", 1);
	set("valid_startroom", 1);
        set("no_sleep_room",1);

	set("objects", ([
		"/adm/npc/luban.c"   : 1,
		__DIR__"npc/tongzi1" : 1,
		__DIR__"npc/tongzi2" : 1,
		__DIR__"npc/tongzi3" : 1,
		__DIR__"npc/tongzi4" : 1,
	]));

	set("exits", ([
         "east"    : __DIR__"playtown/chunzhangjia",
		"dule"    : __DIR__"dule/xiaoyuan",
		"caihong" : __DIR__"caihong/xiaoyuan",
	]));

	setup();
}
