//changan city

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create ()
{
        set ("short", "长江江畔");
        set ("long", @LONG
走在长江江畔，俯瞰着滚滚长江，甚是壮观。由于过了巨石横滩，江
水变得湍急，江面上也没有什么船只了。你的西面就是有名的巨石横滩，
东面则是望不到头的长江江畔，南面一条土路通向几户人家。
LONG);
	set("valid_startroom", 1);

        set("exits", 
        ([
		"west" : __DIR__"hengtan",
		"east" : __DIR__"jiangpan3",
		"south" : __DIR__"tulu1",
       ]));

        set("outdoors", "zigui");
        setup();
}