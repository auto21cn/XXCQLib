// qianyuan.c

#include <ansi.h>
inherit ROOM;

void create()
{
         set("short",HIR"前院"NOR);
         set("long",@long
这里是曼陀罗山庄的前院, 只见一个个丫环, 卑女人来人往穿梭不息, 而
且个个不法轻灵, 显然武功不弱！院子的东面是一个小石桥，南面是一条长廊。
往北走就到了庄门。
long);
         set("outdoors","姑苏慕容");
         set("exits",([
             "north" : __DIR__"zhuangmen",
             "east" : __DIR__"sq1",
             "south" : __DIR__"cl",
]));
	set("objects",([
		__DIR__"npc/binu" : 2,
]));
         setup();
         replace_program(ROOM);
}
