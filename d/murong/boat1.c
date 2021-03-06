// boat1.c
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", HIY"小木船"NOR);
	set("long",
"一只仅容得下两三人的小木舟，你刚跳上来时差点没摔下去。船上有根\n"
HIG"竹篙"NOR"(bole)，你要不要试一试(use)。\n"
);
	set("exits", ([
	"out": __DIR__"muqiao",
]));
        set("no_clean_up", 0);
	set("item_desc", ([
	"bole":  HIG"一根丈来长的竹篙，你用手掂了掂，其实并不重。\n"NOR,         
	"hetian" : HIG"一片绿油油的荷叶(heye)，上面长满了莲蓬(lianpeng)。\n"NOR,
	"heye" : HIG"碧绿青翠的荷叶，几颗晶莹透亮的水珠在荷叶上滚来滚去。\n"NOR,
	"lianpeng" : HIY"鼓鼓的莲蓬。新鲜极了。\n"NOR,
]));
        setup();
}


void init()
{
	add_action("do_use","use");                  
	add_action("do_save","save");
	add_action("do_quit","quit");	                        
	add_action("do_zhai", "zhai");
	add_action("do_zhai", "cai");
	add_action("do_bo", "bo");
}                                    

int do_save()
{
	write("这里不准存盘！\n");
	return 1;
}

int do_quit()
{
	write("这里不准退出！\n");
	return 1;
}


int do_use(string arg)
{
	object me, ob;
	me = this_player();
	ob = this_object();
	if(!arg||arg!="bole")
		return notify_fail("你要用什么?\n");
	message_vision(HIG"$N拿起竹篙就是一阵乱撑。\n......\n......\n"NOR,me);
	message("vision", HIG"$N一用劲，一下把小船儿划得好远。\n"NOR, environment(me), ({me}));
	write(HIR"累的你满头大汗。\n"NOR);
	me->receive_damage("jingli", 10);
	delete("exits/out");
	if(!ob->query("busy"))
	ob->set("busy", 1);
	switch(random(20))
	{
		case 0:
		case 1:
		case 2:
		case 3:                                                     
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		message_vision(HIR"~ ~ ~ 船儿在湖中央荡呀荡~ ~ ~\n"NOR, me);
		me->add_temp("hua", 1);
		break;
		case 11:
		case 12:
		case 13:
		message_vision("不远处就是一大片绿油油的"HIG"荷田"NOR"(hetian)。\n", me);
		break;
		case 14:
		message_vision("你划着划着，好象又回到了原地。\n", me);
		me->delete_temp("hua");
		set("exits/out", __DIR__"muqiao");
		break;		
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
		message_vision(HIG"你划了好久竟不知道自己在哪了。\n"NOR,me);
		break;
	}
	return 1;
}

int valid_leave(object me, string dir)
{
	 object qiao;
	 qiao = find_object(__DIR__"muqiao");
 	 if( dir == "out" )
	 {
        	this_object()->delete("busy");            
        	me->delete_temp("hua");
	 	if(!(qiao = find_object(__DIR__"muqiao")))
                     qiao = load_object(__DIR__"muqiao");
                {
         	qiao->set("long",
"这是通往湖中小亭的木桥，从这望去湖面碧波荡漾，景色宜人。木桥的\n"
"扶手上雕刻着一尊尊小木头狮子，让人爱不释手。木桥往南走能够看到一座\n"
"湖中小亭。在木桥下栓着一艘小木船，显然船的主人不在。\n");       
		}              
		return 1; 
	}
        return ::valid_leave(me,dir);
}

int do_zhai(string arg)
{
	object me, ob;
	me = this_player();

	if( !living(me)) return 0;
	if( me->is_busy()) return notify_fail("你正忙着呢。\n");
	if( me->is_fighting()) return notify_fail("你正忙着呢。\n");
	if( !arg || arg != "lianpeng" || arg == "") return notify_fail("你要摘什么？\n");
	if( arg == "lianpeng")
	{       
		switch(random(5))
		{       
			case 0:
			case 1:
			tell_object(me, "荷叶挡住了你的脸，让你觉得晕头转向的。\n");
			break;
			case 2:
			tell_object(me, "你伸手够向莲蓬，但是距离太长了，你够不着。\n");
			message("vision", "$N伸手够向莲蓬，但是距离太长了，$N够不着。\n", environment(me), ({me}));
			break;
			case 3:
			tell_object(me, "你伸手够向莲蓬，一把抓住了一个大莲蓬。\n");
			message("vision", "$N伸手够向莲蓬，一把抓住了一个大莲蓬。\n", environment(me), ({me}));
			break;
			case 4:
			tell_object(me, "突然脚下一晃，瞎了你一跳，连忙用手扶住船边。\n");
			message("vision", "突然脚下一晃，瞎了$N一跳，连忙用手扶住船边。\n", environment(me), ({me}));
			break;
		}
		return 1;
	}
}

int do_bo(string arg)
{
	object me, ob;
	me = this_player();
	ob = this_object();
	if( !living(me)) return 0;
	if( me->is_busy()) return notify_fail("你正忙着呢。\n");
	if( me->is_fighting()) return notify_fail("你正忙着呢。\n");
	if( !arg || arg != "heye" || arg == "") return notify_fail("你要干什么？\n");
	if( (int)me->query_temp("hua", 1) < 10 ) return 0;
	if( arg == "heye")
	{       
        	message_vision("$N用手拨开了挡在面前的荷叶。\n", me);
        	tell_object(me, "突然有一个小岛出现在你的面前，你不禁想上岛探个究竟。\n");
        	me->move(__DIR__"ab");
        	ob->delete("busy");
        	return 1;
        }
}