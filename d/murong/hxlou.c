// hxlou.c

#include <ansi.h>

string look_hole();
inherit ROOM;

void create()
{
         set("short",HIR"红霞楼"NOR);
         set ("long",
HIR"红霞楼"NOR"旁有一个"HIY"小屋"NOR"，"HIY"屋子"NOR"旁的"HIC"石屋"NOR"黑恫恫的。只有一个小窗户(window)
透出几丝阴森。\n"
);
	set("exits",([
	"south" : __DIR__"hhyuan",
	"east" : __DIR__"hffang",
	"north" : __DIR__"yjl",
]));
        set("item_desc",([            
            "window" : (: look_hole :),
        ]));
	setup();
}
string look_hole()
{
    object me, room, ob;
    me = this_player();
    ob = this_object();
    if (!(room = find_object(__DIR__"hole")))
          room = load_object(__DIR__"hole");

    message_vision("$N悄悄转到池边，伸长脖子往窗户里面望去。\n", me);
    "/cmds/std/look.c"->look_room(this_player(), room);
    tell_object(room,"你觉得有人正在向这里窥探。\n");
    return "";
}