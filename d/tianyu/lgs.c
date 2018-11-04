// Room: 练功房
// Date: by godzilla 1999.11.18

int do_xiulian();
inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", "练功房");
	set("long", @LONG
天羽派的剑法最重要是个悟字，一般师父都无法言传，需要弟子
门在这里闭观靠自己探索剑法当中的奥秘，因此天羽长辈门特意修建
练功房，为弟子门闭观所用，东边是个休息室提供饮食和休息的地方
。
LONG );
	set("exits", ([
	        "out" : __DIR__"lgsw",
	        "east" :__DIR__"xiuxis"
		]));
	set("no_fight",1);	
	setup();

}
void init()
{
	add_action("do_xiulian","lianxi");
	add_action("do_quit","quit");
}
int do_quit()
{
       object me=this_player();
       tell_object(me,"闭关时不能退出！\n");
       return 1;
}
int do_xiulian()
{
	 object me,weapon;
	 me=this_player(); 
	 if (!me->query_skill_mapped("sword","tianyu-qijian"))
	 return notify_fail("你还没有enable tianyu-qianjian，无法练习\n");
	 if (me->query("jingli")<50)
	 return notify_fail("你现在太累了休息一下在来吧！\n");
	 if (me->query("neili")<100)
	 return notify_fail("你现在内力不够了！\n");
	 if ((int)me->query_skill("tianyu-qijian",1)*(int)me->query_skill("tianyu-qijian",1)*(int)me->query_skill("tianyu-qijian",1)/10 > (int)me->query("combat_exp")) 
	 return notify_fail("也许是缺乏实战经验，你的练习总没法进步。\n");
	 if (!objectp(weapon = me->query_temp("weapon"))
         || (string)weapon->query("skill_type") != "sword")
                return notify_fail("没有剑怎么练习天羽奇剑。\n");
     if (me->query_skill("tianyu-qijian",1)<=100)
      return notify_fail("你的天羽奇剑火候不够，无法练习。\n");
     tell_object(me,HIR"你按照师父所传练剑口诀，练习了一遍天羽剑法，对其剑意的体会又深了一层。\n"NOR);
         me->add("jingli",-30);
         me->add("neili",-5);
         me->improve_skill("tianyu-qijian", me->query("int")*8);
         return 1;
}         

int valid_leave(object me, string dir)
{
	object room;
	room=find_object(__DIR__"lgsw");
	if(me->query_temp("xiulian_sword") && dir=="out")
	{
		room->add("mask/闭关",-1);
		me->set_temp("xiulian_sword",0);
		return 1;
	}
	return ::valid_leave(me, dir);
}
	
		
	
