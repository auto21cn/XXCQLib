// Room: /city/sanhelou2.c
// YZC 1995/12/04 

#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", "宴宾厅");
	set("long", @LONG
这里是叁合楼的宴宾厅，地上铺着大红色的地毯，一块屏风上画着
一个烫金色的大红喜字。经常有人在这里举办宴席。如果你也想宴请宾
客不妨打听一下胡老板。
LONG);
	set("no_fight",1);
	set("objects", ([
		__DIR__"hu" : 1,
	]));
	set("exits", ([
		"out" : __DIR__"sanhelou2",
	]));

	setup();
}

void init()
{
	add_action("do_work", "quit");
	add_action("do_work", "du");
	add_action("do_work", "dazuo");
	add_action("do_work", "tuna");
	add_action("do_work", "zhoutian");
        add_action("do_stand", "stand");
}

int do_work()
{
	if( present("table", environment(this_player())) )
	{
                write(WHT"你这是在宴会厅啊！礼貌点！\n"NOR);
		return 1;
	}
}

int do_stand(string arg)
{       object me;
        me = this_player();

        if( !arg || arg=="" ) return 0;

        if( arg=="up"&&(me->query_temp("marks/坐"))){
		me->delete_temp("marks/坐");
		me->delete_temp("marks/赴宴");
	message_vision("$N拍了拍肚皮，打了个饱嗝，站起来准备不吃了。\n", this_player());
        return 1;
	}
	else return notify_fail("你本来就站着的。\n");
}

int valid_leave(object me, string dir)
{
	if( dir=="out"
	&& this_player()->query_temp("marks/坐") )
	return notify_fail(WHT"你要先离开椅子。(指令格式：stand up)\n"NOR);

	if( dir=="out"
     && this_player()->query_temp("marks/开始") )
	return notify_fail(WHT"你要先结束宴会才能离开。(指令格式：jieshu)\n"NOR);

        return ::valid_leave(me, dir);
}
