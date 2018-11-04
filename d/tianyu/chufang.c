// Room: 厨房
// Date: by godzilla 1999.11.18

#include <room.h>
#include <ansi.h>

inherit ROOM;
void create()
{
         set("short","厨房");
         set("long",@long
这是一间小厨房, 虽然不大, 但是锅碗瓢盆, 油盐酱醋，
到很奇全。灶台上堆满了新鲜瓜果蔬菜, 活鱼活虾, 不仅不
脏不乱, 还十分干净整齐。
long);
         set("exits",([
         "west" : __DIR__"qianyuan",
         ]));
           set("no_fight",1);
         set("resource/water", 1);
           set("objects", ([
           __DIR__"npc/chushi" :1,
           __DIR__"obj/hulu" : 2,
           __DIR__"obj/feicui-yuyuan" : 1,
           __DIR__"obj/meihua-zaoya" : 2,
         ]));
         create_door("west","木门","east",DOOR_CLOSED);
         setup();
}
void init()
{
	 add_action("do_add","add");
}	
int do_add(string arg)
{
	 object me;
	 me=this_player();
	 if(!arg||arg=="")
	 return 0;
	 if(!me->query_temp("do_over_job1"))
	 return 0;
	 if(arg=="chai")
	 message_vision(CYN"$N赶忙把劈好的柴火，添加到灶里。\n"NOR,me);
	 message_vision(HIR"不一会，原本已经奄奄一息的火苗又窜得老高，火越燃越旺，灶里正煮着的食物已经可以闻到香味了。\n"NOR,me);
	 message_vision(CYN"厨师满意的对$N点了点头,说道“干得不错，去睡房休息一会吧！”\n"NOR,me);
	 me->add("combat_exp",90+random(30));
	 me->add("potential",60+random(30));
	 me->delete_temp("do_over_job1");
	 return 1;
}	 
int valid_leave(object me, string dir)
{
        if (present("qingshui hulu",me)||present("kao ya",me)&&dir == "west" )
        {
                   return notify_fail("你全拿走了，别人怎么办。\n");
        }
        return ::valid_leave(me, dir);
}
