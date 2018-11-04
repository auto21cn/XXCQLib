// hhyuan.c

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short",MAG"后花园"NOR);
	set ("long",
"后花园和庄中其它地方一样种满了"MAG"山茶花"NOR", 参杂在假山"BLU"巨石"NOR", "GRN"绿竹小溪"NOR"\n"
"中, 此所谓"HIY"「千呼万唤始出来, 犹报琵琶半遮面」"NOR"更增姿媚。 抬头望去, 只\n"
"见"HIC"藏书阁"NOR"的窗户半开着,一根"HIY"古藤"NOR"蜒伸在墙上。一股"HIW"清泉"NOR"从假山上涌出，尝一\n"
"口沁人心脾。\n"
);
         set("resource/water", 1);
         set("outdoors", "姑苏慕容");            

         set("exits",([
             "north" : __DIR__"hxlou",            
]));
         set("item_desc",([
             "teng" : "一条顺着墙壁攀延而上的"HIG"绿树藤"NOR"。\n"
]));
	setup();
}

void init()
{
	add_action("do_pa", "pa");
}

int do_pa(string arg)
{
	object me;
	me = this_player();
	
	if(!living(me))
		return 0;
	if( arg == "" || !arg || arg != "up")
		return notify_fail("你要往哪里爬？\n");   
		
	if(arg = "up")
	{
	         write("你沿着大树藤爬了上去。\n");
        	 message("vision", me->name()+"沿着大树藤爬了上去。\n", environment(me), ({me}));
	         me->move(__DIR__"shuteng");
	return 1;
        }
}
		