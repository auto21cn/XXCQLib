// /d/playertown/road4.c 碎石小道
// Build 1999.12.10 bmw

inherit ROOM;

void create()
{
	set("short","碎石小道");
	set("long",@LONG
这儿是小村的中心大街，南面是人们喜欢聚集在那聊天的地方，
左右看了看，西面隐约可以看见一栋红红的小楼，而东面的不远
处有一座小亭。
LONG );

	set("recordable_room",1);
	set("outdoors","playertown");
	set("exits",([
		"west"	:	__DIR__"road3",
		"east"	:	__DIR__"road6",
	]));
	
	setup();
	
	replace_program(ROOM);
	
}
