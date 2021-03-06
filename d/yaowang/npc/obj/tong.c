// 扫把 回春堂做任务的道具。
// By 山猫Adx 16:53 99-10-25

#include <ansi.h>
inherit ITEM;

void create()
{
	set_name("水桶", ({ "tong" }));
        set_weight(50000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "个");
		set("long", "这是一个木制的水桶，用来打水(dashui)浇地(jiaodi)。\n");
		set("yaowang", 1);
		set("value", 1);
		set("weight", 1000);
	}
}

void init()
{
           add_action("do_dashui","dashui");
           add_action("do_jiaodi","jiaodi");
}

int do_dashui(string arg)
{
	object me=this_player();
	object obj=this_object();

	if (me->query_temp("renwu_wancheng") >= 100)
	{
		me->set_temp("renwu_wancheng",100);   //表示完成任务
		return notify_fail ("你完成了任务，回去复命吧！\n");
	}

	if (obj->query("renwu_dashui") )
		return notify_fail ("已经打满水了！\n");

	if(!environment(me)->query("resource/water") )
		return notify_fail ("这里没有水打！\n");

	obj->set("renwu_dashui",1);
	message_vision ("$N拿起水桶打满了一桶清水！\n", me);
        return 1;

}

int do_jiaodi(string arg)
{
        object *inv;
        object me;
        int jing;

	me = this_player();
	jing = ( random(me->query("str"))/3 );
	inv = all_inventory(me);
	if (jing <= 0)
		jing = 5;

	if(environment(me)->query("short")!="田地" )
		return notify_fail ("你的任务不是在这里浇地吧！\n");

	if (me->query("jingli")<=jing) {
		message_vision ("$N太累了，得先休息一下，才能继续完成任务！\n", me );
        	return 1;
	}

	if (!me->query_temp("renwu_name1")) {
		message_vision ("$N拿起水桶，浇了自己一身！真傻！\n", me);
        	return 1;
	}

	if (me->query_temp("renwu_wancheng") >= 100) {
		me->set_temp("renwu_wancheng",100);   //表示完成任务
		return notify_fail ("你完成了任务，回去复命吧！\n");
	}

	if (!this_object()->query("renwu_dashui") )
		return notify_fail ("水桶是空的，怎么浇地？\n");

	this_object()->delete("renwu_dashui");
	me->add_temp("renwu_wancheng",jing);
	me->add("jingli", -jing);
	me->improve_skill("healing", (jing/2));
	message_vision ("$N拿起水桶把桶中的水浇在田地中！\n", me);
        return 1;
}
