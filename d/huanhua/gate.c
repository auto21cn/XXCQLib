//changan city

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create ()
{
        set ("short", "剑庐大门");
        set ("long", @LONG
这里是浣花剑庐的大门口，你的面前是一扇大敞的朱红大门，透过门
可以看到一面题字的影壁，大门上方横挂一块木匾，上书〔浣花剑庐〕四
个朱红大字。大门两侧立有两尊威风凛凛的石狮子，一名浣花弟子持剑而
立，把守着剑庐的安全。
LONG);
	set("valid_startroom", 1);

        set("exits", 
        ([
		"enter" : __DIR__"qianroad1",
		"eastdown" : "/d/huayang/hhroad",
       ]));

        set("objects", ([
                 __DIR__"npc/zuyuan_q": 1,
	]));

        set("outdoors", "xiao");
        setup();
}

int valid_leave(object me, string dir)
{
	mapping myfam;

	if ((!(myfam = (mapping)me->query("family"))
		|| myfam["family_name"] != "浣花剑派" )
		&& dir == "enter")
	{
        	if(objectp(present("jia ding", environment(me))))
        		return notify_fail("家丁伸手拦住你谦声说道：浣花剑庐，不容外人擅自入内，\n若非拜师的话"
				+ RANK_D->query_respect(me) +"还是请回去吧，免得自讨没趣。\n");
	}

	return ::valid_leave(me, dir);
}