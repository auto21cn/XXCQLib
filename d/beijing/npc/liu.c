// liu.c 刘亚父 

#include <ansi.h>

inherit F_DEALER;

int redeem(string arg);

void create()
{
	set_name("刘亚父", ({ "liu yafu", "liu" }));
	set("title", "当铺老板");
	set("shen_type", 0);

	set("gender", "男性");
	set_max_encumbrance(100000000);
	set("age", 35);
	set("long",
		"他是一个很和蔼的中年男子,听说他和江湖五条龙中的金盛煌很熟。\n");
	set("no_get_from", 1);

	set_skill("strike", 60);
	set_skill("dodge", 60);
	set_temp("apply/attack", 30);
	set_temp("apply/attack", 30);
	set_temp("apply/damage", 15);

	set("combat_exp", 50000);
	set("attitude", "friendly");
	
	setup();
	carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
	add_action("do_sell", "sell");
	add_action("do_value", "value");
	add_action("do_redeem", "redeem");
}

void die()
{
	message_vision("\n$N死了。\n", this_object());
	destruct(this_object());
}

int do_redeem(string target)
{
	object dest, *all;
    int i;

	all = users();

	if (!target)
		return notify_fail("你想赎谁？ 1\n");

	for(i=0; i<sizeof(all); i++) 
	{
		if( target == (string)all[i]->id() || target == all[i]->name() )
			dest = all[i];
	}
	if( !dest )
		return notify_fail("刘亚父说到：他现在不在游戏中，过会再来吧。\n");
	else if( !dest->query_temp("selled"))
		return notify_fail("刘亚父急道：你可别诬陷好人，我怎么会非法扣押玩家呢！\n");

        if (query_temp("busy"))
                return notify_fail("哟，抱歉啊，我这儿正忙着呢……您请稍候。\n");

	switch (MONEY_D->player_pay(this_player(), dest->query("per") * 700))
	{
	case 0:
		return notify_fail("穷光蛋，一边呆着去！\n");
	case 2:
		return notify_fail("您的零钱不够了，银票又没人找得开。\n");
	default:
        	set_temp("busy", 1);
		message_vision("$N从$n那里赎回了一" + dest->query("unit") + 
			dest->query("name") + "。\n", this_player(), this_object());
		dest->move("/d/city/kedian");
		dest->set("startroom","/d/city/kedian");
		dest->delete_temp("selled");
		message("vision",
			HIY "只听见嗖的一声，一个遍体鳞伤的家伙从天花板上掉了下来！\n" NOR,
			environment(dest), dest);
		tell_object(dest, "你被" + this_player()->query("name") + "赎了出来。\n");
	}
        remove_call_out("enough_rest");
        call_out("enough_rest", 1);

	return 1;
}

int accept_object(object who, object ob)
{
	object obj, sil;
	obj = this_object();

	if ((string)ob->query("id") == "dan") 
	{
		if ((string)who->query_temp("goods") != obj->query("name"))
		{
			message_vision("$N把单子递给"+obj->query("name")+"查验。\n", who);
			command("? "+who->query("id"));
			command("say 这份"+ob->query("name")+"不是我们这里的呀！");
			command("say 你还是到别的地方去找找吧。");
			command("give dan to "+who->query("id"));
			return 1;
		}
		else if (!(string)who->query_temp("buygoods") || (string)who->query_temp("buygoods") != "begin")
		{
			message_vision("$N把单子递给"+obj->query("name")+"查验。\n", who);
			command("? "+who->query("id"));
			command("say 这虽然是我们这里的，但是……，大概不是您的吧。");
			command("say 这张单子我们先留下了，省得顾客受损失，谢谢您了。");
  			destruct(ob);
			return 1;
		}
		else
		{
			message_vision("$N把单子递给"+obj->query("name")+"查验。\n", who);
			command("say 太好了，太好了，您终于来了！");
			message_vision(obj->query("name")+"拿过一根笔在账单上划了两下，然后收了起来。\n", who);
			message_vision(obj->query("name")+"转了进去，一会带着一个伙计扛出来一个大包裹。\n", who);
			message_vision(obj->query("name")+"笑了笑说：这就是您们剑庐的货，您收好。\n", who);
			sil = new("/d/huanhua/npc/obj/huo");
			sil->set("name", "典当品");
			sil->set("long", "这是从北京当铺赎回的典当品。");
			sil->move(who);
			who->set_temp("buygoods", "over");
  			destruct(ob);
			return 1;
		}
	}
	else
	{
		command("say 你给我这个干什么?");
		return 0;
	}
	
}
