// liangong-fu.c

inherit ITEM;
#include <ansi.h>

int do_fill(string);
int do_dao(string);

void create()
{
	set_name(YEL"水桶"NOR, ({ "shui tong", "tong" }));
	set("long", "一个用来打水(fill water)的水桶，打来的水倒(dao water)在水缸里。\n");
	set_weight(2000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("material", "wood");
		set("unit", "个");
		set("no_drop", "扔掉它是会挨骂的，还是算了吧。\n");
	}
	setup();
}

void init()
{
	add_action("do_fill", "fill");
	add_action("do_dao", "dao");
}

int do_fill(string arg)
{
	object ob, me;
	me = this_player();
	ob = this_object();

	if (!arg || arg != "water")
		return notify_fail("你要装什么？\n");

	if (!environment(me)->query("sljob"))
	{
		return notify_fail("这个地方没有水，怎么打水？\n");
	}

	else if ( this_player()->is_busy() )
	{
		return notify_fail("你上一个动作还没有完成。\n");
	}

	else if (ob->query("job"))
	{
		return notify_fail("水桶里已经打满了水，。\n");
	}

	else
	{
		message_vision(CYN"$N将水桶放到溪中打满了水。\n"NOR, me);
		if (random(100)>5)
		{
			ob->set("job",1);
			ob->set("long","一个打满了水的水桶。\n");
			if (me->query_temp("job") == 1)
				me->set_temp("job", 2);
			return 1;
		}
		else
		{
			message_vision(CYN"哎呀，$N一个不小心没有站住，摔了一个跟头，桶竟然随水漂走了。\n"NOR, me);
			me->set_temp("job",3);
			destruct(ob);
			return 1;
		}
	}
	return 1;
}

int do_dao(string arg)
{
	object ob, me;
	me = this_player();
	ob = this_object();

	if (!arg || arg != "water")
		return notify_fail("你要倒什么？\n");

	else if (!ob->query("job"))
		return notify_fail("桶里没水你倒什么？\n");

	else if (!environment(me)->query("sljob2"))
		return notify_fail("这个地方没有缸，你要把水倒在那里？\n");

	else if ( this_player()->is_busy() )
		return notify_fail("你上一个动作还没有完成。\n");

	message_vision(HIW"$N将水桶里的水哗的一声倒到了水缸里，然后把桶放在一边。\n"NOR, me);

	if (me->query_temp("job", 2))
	{
		message_vision("你擦了擦汗，这趟工作总算做完了。\n", me);
		me->add("potential", 50+random(50));
		me->add("combat_exp", 80+random(70));
		me->delete_temp("job");
	}

	destruct(ob);
	return 1;
}