//changan city

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create ()
{
        set ("short", "青石路");
        set ("long", @LONG
这是一条青石铺就小路，也是由华阳县城去往百花潭、飞花桥、浣花
溪、落花湖的必经之路，路上行人很是不少。青石路往西延伸不远便消失
了，取而代之的是一条土路蜿蜒入林，往东望，华阳镇就在不远的前方。
LONG);
	set("valid_startroom", 1);

        set("exits", 
        ([
		"west" : __DIR__"treeroad4",
		"east" : __DIR__"hyroad2",
       ]));

        set("outdoors", "huayang");
        setup();
}