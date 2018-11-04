// Room: zongguanfang.c 
// Created by Atlus 1999.7.21
// Modified by Atlus 1999.7.23
// 
// 

inherit ROOM;

void init();
int do_task(string arg);
void delete_served(object);


void create ()
{
        set ("short", "总管房");
        set ("long", @LONG
总管房里陈设不多，桌旁边坐着一个老人。仔细看去，这老者竟是飞
鱼塘三大“死人”之一的总管张雪眠。桌子后面的红木大柜里放着一卷一
卷的纪录，桌子上堆满了卷宗，当然少不了有文房四宝，总管的手不停在
写着东西。
LONG);
        set("area","飞鱼");
        set("valid_startroom", 1);
        set("no_fight", 1);

        set("objects", ([
               "/d/feiyu/npc/zhang" : 1,
        ]));
          set("exits", ([
                "north" : __DIR__"dongyuan",
        ]));
        
        setup();
        replace_program(ROOM);
}
