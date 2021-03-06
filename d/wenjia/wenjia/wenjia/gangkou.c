// Room: dukou.c
// Created by Zeus 1999.6.4
// Modified by Zeus 1999.6.4
// 
// 
#include <ansi.h>

inherit ROOM;
void init();
int do_shang(string arg);
int arrived(object me,int stage);

string *around_msg = ({
        HIC "船沿着岸边向下游航行，旁边连绵的山脉也渐渐的消失了。\n\n" NOR,
        HIG "江水的流动变得非常缓慢，渐渐的前面出现了另一条大江，那是西江。\n\n" NOR,
        CYN "船在两江的汇流处停了下来，慢慢的调转方向，船头竟然转向了西江的上游。\n\n" NOR,
        WHT "前面的江水出现了分流，航船慢慢的航行方向向右转。开入漓江。\n\n" NOR,
        HIY "一座象鼻一样的山出现在你的视野里，越来越大，那就是著名的象鼻山。\n\n" NOR,
        GRN "欣赏着优美的山水的同时，右手边出现了一个城镇，桂林镇。\n\n" NOR,
        BLU "桂林镇慢慢变大，渡口出现在眼前。\n\n" NOR,
});

void create ()
{
        set ("short", "港口");
        set ("long", @LONG
北江岸上唯一的港口，从这里坐船，经过北江，来到漓江，逆行可以
去到桂林。漓江上游是桂林，那里是外浣花的所在地，也是到四川的必经
之路。岸边立着一块木牌(mupai)。
LONG);
        set("area","岭南");
        set("outdoors", "wenjia");
        set("valid_startroom", 1);

        set("item_desc", ([
                "mupai" : "有客船到桂林镇，可以上(shang)船。\n",
        ]));

        set("exits", ([
                "east" : __DIR__"shandi",
        ]));
        setup();
}

void init()
{
        add_action("do_shang", "shang");
}

int do_shang(string arg)
{
        object room,me;
        me=this_player();

        if(!arg || arg!="chuan")
               return notify_fail("你要上什么?\n");
         
        message_vision("$N朝江上的船夫叫道：“喂，雇船呀!”\n", me);

        if( !(room = find_object("/d/guilin/fengfan")) )
                room = load_object("/d/guilin/fengfan");

        message_vision("船夫慢慢的将船靠岸，将一个木板架到岸上。$N走了上船。\n", me);
        me->move("/d/guilin/fengfan");

        call_out("arrived", 5, me);

        return 1;
}

int arrived(object me,int stage)
{
        object room;

        tell_object(me, around_msg[stage]);
        if( ++stage < sizeof(around_msg) ) {
                call_out( "arrived", 5, me, stage );
                return 1;
        } else
                me->reincarnate();

        if( room = find_object("/d/guilin/fengfan") )
        {
                me->move("/d/guilin/gangkou");
                message_vision("大船慢慢的驶进岸边，船夫架了一块木板到岸上，$N走了下来。\n", me);
                return 1;
        }
}

