// huangkudajie4.c

#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{	
	set("short", "黄裤大街");
	set("long", @LONG
到了这里,已经很少见到朝廷的士兵了，三教九流都在这里汇集。这
里俨然成为了江湖人士的天堂，最近又由于发梦二党的花当家大寿，这里
更显得分外的热闹。
LONG);	
        set("valid_startroom",1);
        set("no_steal", "1");
        set("outdoors", "bianliang");
	set("exits", ([
//                "north" : __DIR__"luobuzhuang",
                "south" : "/d/huafu/menfang",
		"west" : __DIR__"hua_lukou",
		"east" : __DIR__"huangkudajie5",
	]));
//	set("objects", ([
//		"/clone/weapon/changjian" : 4]));
	set("area", "汴梁");
	setup();
}

/*
int valid_leave(object me, string dir)
{
        object ob;
        mapping myfam,party;
        myfam=(mapping)me->query("family");
        party=(mapping)me->query("party");

        if( (party && party["party_name"]== HIG "发梦二党" NOR) || (myfam && myfam["family_name"]== "发梦二党")
                && (dir == "south") )
        return ::valid_leave(me, dir);
           if (!myfam && !party)
        return ::valid_leave(me, dir);
         if (dir=="south")
         {
                if(!objectp(present("men wei", environment(me))))              
                {
                	if (query("shibai"))
            {
                  me->set_temp("killwei",1);
                		return ::valid_leave(me,dir);
      }
                ob=new("/d/huafu/npc/menwei1");
                ob->move(environment(me));      
                message_vision("一个身影挡在$N的面前。\n",me);
                	set("shibai",1);
                }
                if(!objectp(present("bai tie",me)))
                      return notify_fail("门卫伸手拦住你谦声说道：发梦二党花府不容外人擅自入内，\n若非拜师的话"
                                + RANK_D->query_respect(me) +"还是请回去吧，免得自讨没趣。\n");
		return notify_fail("门卫笑眯眯的对你说道：把拜帖给我吧。\n");
         }
       return ::valid_leave(me, dir);
}


*/
