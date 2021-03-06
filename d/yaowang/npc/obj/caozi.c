// Obj 可以种的 草药
// By 山猫adx @ 宁波小雪 17:00 99-10-26

#include <ansi.h>
inherit ITEM;

void create()
{
	set_name("草籽", ({"cao zi"}));
	set_weight(10);
	set("no_clean_up", 1);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "粒");
		set("long", "一粒淡褐色的草籽，种在田地里(zhong)会长成草药。\n");
		set("value", 10);
	}
	setup();
}

void init()
{
	add_action("do_zhong", "zhong");
}

int do_zhong(string arg)
{
	object ob, me, where;

	me = this_player();
	ob = this_object();
	where=environment(me);

	if(me->query("party/party_name")!=HIB"药王谷"NOR
		|| me->query("party/level")<3 )
		return notify_fail("你不会种植草药！\n");

	if(me->is_fighting() || me->is_busy())
		return notify_fail("你很忙，没时间。\n");

	if( !arg || !present(arg, me))
		return notify_fail("指令格式：zhong cao zi\n");

	if( !where->query("yaotian"))
		return notify_fail("只能种在药田里。\n");

	if( where->query("zhongyao")>=10)
		return notify_fail("这里已经没地方种药材了。\n");

	if( me->query("jingli") <= 20)
		return notify_fail("你太累了，还是先休息一下吧！\n");

	if( ob->query("value")!=10)
		return notify_fail("已经种在地里了！\n");

	message_vision("$N轻轻将$n种在地里！\n", me, ob);

	ob->move(where);
/*
		remove_call_out("grow_a");
		remove_call_out("grow_b");
		remove_call_out("grow_c");
		remove_call_out("grow_d");
		remove_call_out("grow_e");
*/
	message_vision(WHT"草籽慢慢长出了芽。\n"NOR, ob);
        set_name( "小青草" , ({"xiao qingcao"}));
	set("long", "一株淡绿色的小青草，还没有长成。\n");
	set("value", 0);
	set("no_get", 1);

	where->add("zhongyao", 1);
	me->improve_skill("healing", ((int)me->query_skill("healing",1)/4));
	me->add("jingli", -20);
	call_out("grow_a", 1, ob);
	return 1;
}

int grow_a(object ob)
{
	int i=100+random(50);
	set("no_get", 1);
	call_out("grow_b", i, ob);
	return 1;
}

int grow_b(object ob)
{
        int i=100+random(100);
	message_vision(WHT"小青草慢慢地长出了一片叶子。\n"NOR, ob);
        set_name( "青草" , ({"qingcao"}));
	set("long", "一株淡绿色的青草，还没有长成。\n");
        call_out("grow_c", i, ob);
        return 1;
}

int grow_c(object ob)
{
        int i=100+random(200);
	message_vision(WHT"青草慢慢地长大了一点。\n"NOR, ob);
        call_out("grow_d", i, ob);  
        return 1;
}

int grow_d(object ob)
{
        int i=100+random(400);
	message_vision(WHT"青草慢慢地又长大了一些。\n"NOR, ob);
        set_name( CYN"大青草"NOR , ({"da qingcao"}));
	set("long", "一株绿色的大青草，还没有长成。\n");
        call_out("grow_e", i, ob);  
        return 1;
}
/*
int grow_e(object ob)
{
	object obj;
	int i=random(4);

	if(i=0) { obj=new(__DIR__"renshen"); }
	if(i=1) { obj=new(__DIR__"shouwu"); }
	if(i=2) { obj=new(__DIR__"wugencao"); }
	if(i=3) { obj=new(__DIR__"duanchang"); }

	message_vision(WHT"大青草长成了，可以挖起来了(dig)。\n"NOR, ob);
	obj->move(environment(ob));
	destruct(ob);
        return 1;
}
*/
int grow_e(object ob)
{
	object obj;

	message_vision(WHT"大青草长成了，可以挖起来了(dig)。\n"NOR, ob);
	switch( random(4) ) {
		case 0:
			obj=new(__DIR__"renshen");
			obj->move(environment(ob));
			(environment(ob))->add("zhongyao",-1);
			destruct(ob);
		case 1:
			obj=new(__DIR__"shouwu");
			obj->move(environment(ob));
			(environment(ob))->add("zhongyao",-1);
			destruct(ob);
			break;
		case 2:
			obj=new(__DIR__"wugencao");
			obj->move(environment(ob));
			(environment(ob))->add("zhongyao",-1);
			destruct(ob);
			break;
		case 3:
			obj=new(__DIR__"duanchang");
			obj->move(environment(ob));
			(environment(ob))->add("zhongyao",-1);
			destruct(ob);
			break;
		case 4:
			obj=new(__DIR__"cao");
			obj->move(environment(ob));
			(environment(ob))->add("zhongyao",-1);
			destruct(ob);
			break;
		}
}
