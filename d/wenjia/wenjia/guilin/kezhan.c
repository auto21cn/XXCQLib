// Room: kezhan.c
// Created by Zeus 1999.6.4
// Modified by Zeus 1999.6.4
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "客栈");
        set ("long", @LONG
这是一间由壮族老伯开的客栈，为经过此处的旅人提供舒适的休息地
方。老伯本着为旅人服务的原则，收费特便，方便旅人。这里有一个牌子
(paizi)。
LONG);
        set("area","桂林");
        set("no_sleep_room",1);
        set("valid_startroom", 1);

        set("item_desc", ([
                "paizi" : "舒适的客房，每夜一两白银。\n",
        ]));

        set("objects", ([
                __DIR__"npc/zzoldman" : 1,
        ]));

        set("exits", ([
                "east" : __DIR__"jiedao",
                "enter" : __DIR__"kefang",
        ]));
        setup();
}

int valid_leave(object me, string dir)
{

       if ( !me->query_temp("rent_paid") && dir == "enter" )
       return notify_fail("壮族老伯笑咪咪的对你说：“可怜我这个老头子吧，开间客栈不容易呀，特别是这个时候，给点钱吧。”\n");

       return ::valid_leave(me, dir);
}

