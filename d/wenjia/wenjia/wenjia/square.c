// Room: square.c
// Created by Zeus 1999.3.26
// Modified by Zeus 1999.7.10
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "总部广场");
        set ("long", @LONG
这里是"岭南老字号"温家总部“大字号”前面的广场。向前看去是一
座宏伟的建筑，它的宏伟也代表了温家的庞大和温家在武林中的地位广场
四周插满了旗帜，每个旗帜周围都有一个人守卫着。向北走可以进入前厅，
而东西方向上也是一个小广场。
LONG);
        set("area","岭南");
        set("outdoors", "wenjia");
        set("valid_startroom", 1);

        set("objects", ([
                __DIR__"npc/wendating" : 1,
                __DIR__"npc/wenxiaoting" : 1,
                "/kungfu/class/wenjia/wenxiaobian" : 1,
        ]));

        set("exits", ([
                "southdown" : __DIR__"paifang",
                "north" : __DIR__"qianting",
                "west" : __DIR__"westsquare",
                "east" : __DIR__"eastsquare",
                "feiyu":"/d/feiyu/lysquare",
        ]));

        setup();

        "/clone/board/wenjia_b"->foo();
}

int valid_leave(object me, string dir)
{
        if ((!(string)me->query("family") || (string)me->query("family/family_name") != "老字号温家") 
               && ( dir == "north" || dir == "east" || dir == "west" )
               && !present("wenjiacard", this_player()) &&
               (objectp(present("wen dating", environment(me)))
               || objectp(present("wen xiaoting", environment(me))) ))
               {  if (objectp(present("wen dating", environment(me)))) 
               
                       return notify_fail("温大听喝道：你不是温家弟子，不得入内。\n");
               else
                       return notify_fail("温小听喝道：你不是温家弟子，不得入内。\n");
               
        }

        if ((string)me->query("family/family_name") == "老字号温家" && dir == "southdown" && (int)me->query("combat_exp") <= 100000 )
                       return notify_fail("你突然想起：师父说过，武功不够高不能出温家，在江湖上丢温家的脸。\n");

        return ::valid_leave(me, dir);
}
