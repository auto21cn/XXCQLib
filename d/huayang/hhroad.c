//changan city

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create ()
{
        set ("short", "青石阶");
        set ("long", @LONG
这是一条青石铺成的山路，从浣花溪的飞花桥上来就是这里了。从这
里再向上走几步就到了浣花剑派的剑庐门前了。这条路上不事的有家丁、
丫鬟打扮的人来来往往，他们有说有笑好不热闹。
LONG);
	set("valid_startroom", 1);

        set("exits", 
        ([
		"westup" : "/d/huanhua/gate",
		"eastdown" : __DIR__"hhxroad1",
       ]));
        set("objects", ([
                 "/d/huanhua/npc/bzong": 2,
        ]));

        set("outdoors", "xiao");
        setup();
}
