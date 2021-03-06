// dealer.c 商人
// This is a inheritable object.
// Each dealer should support buy, sell, list, value 4 commands

#include <dbase.h>
#include <ansi.h>
inherit NPC;

void setup()
{
	set("no_get",1);
	set("no_get_from",1);
	::setup();
}

int is_dealer()//在CHAR_D里复制dealer的尸体时，利用该函数判断是否要保留身上的东西到尸体上
{
	return 1;
}

string is_vendor_good(string arg)
{
	string *goods;
	int i;

	if (arrayp(goods = query("vendor_goods"))) 
		for (i = 0; i < sizeof(goods); i++) 
			if (goods[i]->id(arg))
				return goods[i];
	return "";
}

int do_value(string arg)
{
	object ob;
	int value;

	if (!arg || !(ob = present(arg, this_player())))
		return notify_fail("你要估什么的价？\n");
	
	if (ob->query("money_id"))
		return notify_fail("你没用过钱啊？\n");

	if (userp(ob))
		ob->set("value", ob->query("per") * 500);

	value = ob->query("value");
	if (value < 1)
		write(ob->query("name") + "一文不值！\n");
	else 
		write(ob->query("name") + "值" + 
		MONEY_D->price_str(value * 70 / 100) + "。\n");
	return 1;
}

int do_sell(string arg)
{
	object ob;
	int value;
	
	if (!arg || !(ob = present(arg, this_player())))
		return notify_fail("你要卖什么？\n");

	if (ob->query("money_id"))
		return notify_fail("你想卖「钱」？？\n");

	if (stringp(ob->query("no_drop"))||ob->query("no_pawn")||ob->query("nopawn"))
		return notify_fail("这样东西不能卖。\n");

	if (ob->query("item_origin"))
		return notify_fail("粗坯是不能卖的。\n");

	if (is_vendor_good(arg) != "") 
		return notify_fail("卖给你好不好？\n");

	if (ob->query("food_supply"))
		return notify_fail("剩菜剩饭留给您自己用吧。\n");
	
	if (ob->query("shaolin"))
		return notify_fail("小的只有一个脑袋，可不敢买少林庙产。\n");
	
	if(sizeof(all_inventory(this_object()))>60)
		return notify_fail("小的已经有60件货物了，没办法收购你的东西了！\n要不，你先买几样？\n");

	if (userp(ob))
	{
		ob->set("value", ob->query("per") * 500);
		CHANNEL_D->do_channel(ob, "rumor",
			sprintf("%s被某人拐卖了。", ob->name(1)));
	}
	else
	if((ob->query("enpawn")==0)//如果这个属性不为0，说明它是可以卖的！
		&&(
			ob->query("hunmi")!=0||living(ob)
			||ob->query_temp("block_msg/all")==1
		)
	)
		return notify_fail("这个东西是活的呀？！怎么卖嘛，真够笨的了！\n");
	value = ob->query("value");
	if (value < 30)
		write(ob->query("name") + "一文不值！\n");
	else {
		message_vision("$N卖掉了一" + ob->query("unit") + 
		ob->query("name") + "给$n。\n", this_player(), this_object());
		MONEY_D->pay_player(this_player(), value * 70 / 100);
		if ( userp(ob))
		{
			ob->move("/d/sroom/storage");
			ob->set("startroom","/d/sroom/storage");
			ob->set("jackyboy/selled",1);
		}
		else if (value < 50)
			destruct(ob);
		else
			ob->move(this_object());
	}
	return 1;
}

int do_list()
{
	string *goods,str;
	object *inv,ob;
	mapping tmp;
	int i,j;
	inv = all_inventory(this_object());

	if (!sizeof(inv) && !arrayp(goods = query("vendor_goods")))
		return notify_fail("目前没有可以卖的东西。\n");
	tmp=([]);
	printf("你可以向%s购买下列物品：\n", query("name"));
	for(i=0;i<sizeof(inv);i++)
	{
		str=replace_string(base_name(inv[i]),"/","\\");
		if(undefinedp(tmp[str]))
			tmp[str]=1;
		else
			tmp[str]++;
	}
	goods=keys(tmp);
	for(i=0;i<sizeof(keys(tmp));i++)
	{
		j=tmp[goods];
		str=replace_string(goods[i],"\\","/");
		ob=new(str);
		if(!objectp(ob))
			continue;
		if (!ob->query("equipped") && !ob->query("money_id"))
		printf("%d%s%30-s：%s\n", j, ob->query("unit"),ob->short(),
		MONEY_D->price_str(ob->query("value") * 6 / 5));
	}
	if (arrayp(goods = query("vendor_goods")))
		for (i = 0; i < sizeof(goods); i++)
			printf("%30-s：%s\n", goods[i]->short(),
			MONEY_D->price_str(goods[i]->query("value")));
	return 1;
}	

int do_buy(string arg)
{
	int val_factor;
	string ob_file;
	object ob;
	if (!arg)
		return notify_fail("你想买什么？ \n");
	else if (!(ob = present(arg, this_object())))
		if ((ob_file = is_vendor_good(arg)) == "")
			return notify_fail("你想买什么？ \n");

	if (!ob) {
		ob = new(ob_file);
		val_factor = 10;
	}
	else {
		if (ob->query("equipped"))
			return notify_fail("你想买什么？ \n");
		val_factor = 12;
	}

        if (query_temp("busy"))
                return notify_fail("哟，抱歉啊，我这儿正忙着呢……您请稍候。\n");

	
	switch (MONEY_D->player_pay(this_player(), ob->query("value") *  val_factor / 10)) {
	case 0:
		return notify_fail("穷光蛋，一边呆着去！\n");
	case 2:
		return notify_fail("您的零钱不够了，银票又没人找得开。\n");
	default:
        	set_temp("busy", 1);
		message_vision("$N从$n那里买下了一" + ob->query("unit") + 
		ob->query("name") + "。\n", this_player(), this_object());
		ob->move(this_player());
	}
        remove_call_out("enough_rest");
        call_out("enough_rest", 1);

	return 1;
}

void enough_rest()
{
        delete_temp("busy");
}
