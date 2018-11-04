// 山猫ADX by snow 99-12-4

#include <ansi.h>
inherit ROOM;

void create()
{
    set("short", WHT"神雪山"NOR);
    set("long", 
"你走到一间规模极其宏大的庄院大门，门前两旁摆放着两头高大的石狮\n"
"大门上放高高悬挂着一块牌匾"+HBRED WHT"『小雪初晴神雪山』"NOR+
"，你往北走进入\n"
"山中开始学习一些基本的武功。\n"
    );
        set("exits", ([
                "west":__DIR__"dating",
                "east":__DIR__"menqian",
        ]));
        set("no_fight", 1);
        set("valid_startroom", 1);
	setup();
}

int valid_leave(object me, string dir)
{
	if( (dir=="east" )
    &&(me->query("newbei")==1)
	&&!wizardp(me) )
	{
		return notify_fail(HIC"你还不能离开神雪山，你需要继续学习！\n"NOR);
	}
	else {
		me->set("startroom","/d/newbei/menqian");
	}
	return ::valid_leave(me, dir);
}
