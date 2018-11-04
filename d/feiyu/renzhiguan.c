// Room: renzhiguan.c
// Created by Atlus 1999.7.21
// Modified by Atlus 1999.7.21
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "人止关");
        set ("long", @LONG
这里就是"飞鱼山庄"的天险之一“人止关”，山顶的天然平台和巧
妙的布置使这里形成一个雄伟的关口。从这里向北可以看见整个“飞鱼
山庄”的布局。人止关上守卫森严，加上地势天险，易受难攻。所以一
百七十年来，几乎没有失守过。南面的山峰应该就是“落神岭”了吧！
LONG);
        set("area","飞鱼");
        set("outdoors", "feiyu");
        set("valid_startroom", 1);

        set("objects", ([
                "/d/feiyu/npc/feiyudizi" : 2,
                "/kungfu/class/feiyu/songwandeng" : 1,
         ]));

        set("exits", ([
                "southdown" : __DIR__"shanlu3",
                "north" : __DIR__"liaowangtai",
                "westdown" :__DIR__"shanlu2",
        ]));

        setup();

        
}

int valid_leave(object me, string dir)
{
        if ((!(string)me->query("family") || (string)me->query("family/family_name") != "飞鱼塘") 
               && ( dir == "north" || dir == "westdown")
              && (objectp(present("dizi", environment(me)))
               || objectp(present("dizi", environment(me))) ))
               {  if (objectp(present("dizi", environment(me)))) 
               
                       return notify_fail("飞鱼弟子说道：你不是飞鱼塘弟子，请回吧。\n");
        }

        return ::valid_leave(me, dir);
}
