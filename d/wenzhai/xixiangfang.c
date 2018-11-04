// xixiangfang.c 西厢房
// mlf设计,lks编程

#include <ansi.h>

inherit ROOM;
#include <room.h>

void create()
{
	set("short","西厢房");
	set("long",
	"这里不知道是谁住的，房间内极尽简朴，一张粉红色的大床，床的右
侧是一张女孩子常用的梳妆台，再就是一张檀木做的椅子，桌子上积了一
层厚厚的灰，象是许久没人住了，不知道是不是画上的那位姑娘。\n"NOR
     	);
     	set("valid_startroom",1);
	set("exits",([
     		"east" : __DIR__"xiting",
     	]));
           set("objects",([
                    "/d/huafu/npc/luo" : 1,
           ]));
     	create_door("east", "木门", "west", DOOR_CLOSED);
     	setup();
     	replace_program(ROOM);
}
