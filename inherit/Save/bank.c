#define MAX 100000000
#define CMAX "万两黄金"
//存款的数据要有所变化了，将balance修改为mapping
//balance["part1"]记录有多少存款，这个数字不会超过一万两黄金，即100000000 CMAX所定义的值
//balance["part2"]记录有多少个一万两黄金！

inherit BID_ROOM;

//以下函数都未考虑传入参数错误的情况，所以要求一定要正确估计可能传入的参数
mapping query_max_balance(object me)
{
	mapping tmp;
	//根据me的各个属性控制最大的可存数目！比如上线时间，信誉度！
	//此时临时设置一个替代的值
	tmp=([]);
	tmp["part1"]=MAX;
	tmp["part2"]=0;
	
	if(tmp["part1"]>MAX||tmp["part1"]<0)
		tmp["part1"]=MAX;
	return tmp;
}

string write_balance(mapping tmp)
{
	if(!tmp)
		return "零两黄金";
	if(tmp["part2"]==0&&tmp["part1"]==0)
		return "零两黄金";
	if(tmp["part2"]!=0)
		return " "+chinese_number(tmp["part2"])+" "+CMAX+" 及 "+MONEY_D->money_str(tmp["part1"])+"\n";
	else
		return MONEY_D->money_str(tmp["part1"]);
}

int max_balance(mapping tmp1,mapping tmp2)
{
	if(!tmp1)
		return 0;
	if(!tmp2)
		return 1;
	if(tmp1["part2"]>=tmp2["part2"])//如果大数目相同则进行下面的判断
	{
		if(tmp1["part1"]>tmp2["part1"])
			return 1;//如果1比2大返回1
	}
	return 0;//如果2比1大返回0
}

//如果函数里对tmp的修改能保持，这就没问题！（INT类型是肯定不保持的，但是mapping和array好象例外
mixed add_balance(mapping tmp,int value)
{
	if(!tmp)
		tmp=([]);
	tmp["part1"]+=value;
	if(tmp["part2"]>0)
	{
		if(tmp["part1"]<0)
		{
			tmp["part2"]--;
			tmp["part1"]+=MAX;
		}
	}
	else
	{
		if(tmp["part1"]<0)
		{
			tmp["part1"]-=value;
			return 0;
		}
	}
	return tmp;
}

void init()
{
	::init();
	add_action("do_check", "check");
	add_action("do_check", "chazhang");
	add_action("do_convert", "convert");
	add_action("do_convert", "duihuan");
	add_action("do_deposit", "deposit");
	add_action("do_deposit", "cun");
	add_action("do_withdraw", "withdraw");
	add_action("do_withdraw", "qu");
}
	
int do_deposit(string arg)
{
	int amount;
	string what;
	mapping tmp1,tmp2;
	object ob;
	object me = this_player();
	tmp2=query_max_balance(me);
	write("你的存款极限是："+write_balance(tmp2)+"\n");
	
	if(query_temp("busy"))
	{
		me->receive_damage("qi",10);//避免刷屏幕
		return notify_fail("对不起，现在忙着呢，请稍后！\n");
	}
	remove_call_out("enough_rest");
	call_out("enough_rest",1);
	set_temp("busy",1);
	
	if (!arg || sscanf(arg, "%d %s", amount, what) != 2)
		return notify_fail("命令格式：deposit:cun <数量> <货币单位>\n");
	ob=present(what,me);
	if(!objectp(ob))
		return notify_fail("你要存什么？\n");
	if(!ob->query("money_id"))
		return notify_fail(ob->name(1)+"("+ob->query("id")+")不是钱你也拿来存？\n");
	if (amount < 1)
		return notify_fail("你想存多少" + ob->query("name") + "？\n");
	if ((int)ob->query_amount() < amount)
		return notify_fail("你带的" + ob->query("name") + "不够。\n");
	tmp1=me->query("balance");//这里得到的应该是一个mapping，而不再是整数了
	if(max_balance(tmp1,tmp2))
	{
		tmp1=tmp2;
		me->set("balance",tmp1);
		return notify_fail("你存款的数额已经超过上限值，多出的存款被没收了！\n");
	}
	
	tmp1=add_balance(tmp1,(int)ob->query("base_value")*amount);
		
	if(max_balance(tmp1,tmp2))
	{
		//因为对tmp1的操作直接影响到了玩家数据，所以增加此句恢复玩家数据。
		tmp1=add_balance(tmp1,-(int)ob->query("base_value")*amount);
		return notify_fail(	"你存这么多钱已经超出存款极限了。\n");
	}
	me->set("balance",tmp1);
	message_vision(sprintf("$N拿出%s%s%s，存进了银号。\n", 
		chinese_number(amount), ob->query("base_unit"), 
		ob->query("name")), me);
	ob->add_amount(-amount);
	return 1;
}

int do_check()
{
	mapping tmp;
	object me=this_player();
	tmp=me->query("balance");
	write("你的存款上限是："+write_balance(query_max_balance(me))+"。\n");
	write("你的存款是："+write_balance(tmp)+"。\n");
	return 1;
}

int do_withdraw(string  arg)
{
	int num,v;
	mapping tmp1,tmp2;
	object obj,me;
	if(!arg)
		return notify_fail("你要取什么？\n");
	me=this_player();
	if(query_temp("busy"))
	{
		me->receive_damage("qi",10);//避免刷屏幕
		return notify_fail("对不起，现在忙着呢，请稍后！\n");
	}
	remove_call_out("enough_rest");
	call_out("enough_rest",1);
	set_temp("busy",1);
	if(sscanf(arg,"%d %s",num,arg)!=2)
		num=1;
	tmp2=query_max_balance(me);
	tmp1=me->query("balance");
	if(max_balance(tmp1,tmp2))
	{
		tmp1=tmp2;
		me->set("balance",tmp1);
		return notify_fail("你存款的数额已经超过上限值，多出的存款被没收了！\n");
	}
	arg=lower_case(arg);
	if(arg=="cash")
		arg="thousand-cash";
	if (file_size("/clone/money/" + arg + ".c") < 0)
	{
		return notify_fail("你想取出什么钱？\n");
	}
	arg = "/clone/money/" + arg;
	v=num*arg->query("base_value");
	//应该在这里计算手续费
	if(v<0||v>MAX)
		return notify_fail("你一次不允许取那么多钱！\n");
	if(v>=tmp1["part1"])
	{
		if(tmp1["part2"]!=0)
		{
			tmp1["part1"]+=MAX;
			tmp1["part2"]-=1;
		}
		else
		{
			if(v!=tmp1["part1"])
				return notify_fail("对不起，你好象没存那么多钱呀。\n"+v+" "+tmp1["part1"]);
		}
	}
	
	//开始提取存款
	//不用MONEY_D->pay_player是因为有时候数目过大！
	obj=new(arg);
	obj->set_amount(num);
	if(obj->move(me))//move后已经将原来的跟现在这些合并了，这就是一些怪问题的原因了
	{
		//移动OK
		if(tmp1=add_balance(tmp1,- v))//这里不能用obj->value()了，因为obj->move()合并了money!
		{
			message_vision("$N取了"+chinese_number(num)+obj->query("base_unit")+
				obj->query("name")+"。\n",me);
			me->set("balance",tmp1);
		}
		else
		{
			tmp1=add_balance(tmp1, v);//因为可能影响玩家数据，多写一句恢复。
			destruct(obj);//必须摧毁
			return notify_fail("你没有存那么多钱吧？\n");
		}
	}
	else
	{
		//负载过重。
		obj->move(environment(me));
		if(tmp1=add_balance(tmp1,- obj->value()))
		{
			message_vision("$N取了"+chinese_number(num)+obj->query("base_unit")+
				obj->query("name")+"。可惜太重了，一撒手掉了下来。\n",me);
			me->set("balance",tmp1);
		}
		else
		{
			destruct(obj);//必须摧毁
			return notify_fail("你没有存那么多钱吧？\n");
		}
	}
	return 1;
}

int do_convert(string arg)
{
	string from, to;
	int amount, bv1, bv2;
	object from_ob, to_ob;
	object me;
	
	me = this_player();

	if (!arg || sscanf(arg, "%d %s to %s", amount, from, to) != 3)
	{
		return notify_fail("命令格式：convert|duihuan <数量> <货币单位> to <新货币单位>\n");
	}
	if(query_temp("busy"))
	{
		me->receive_damage("qi",10);//避免刷屏幕
		return notify_fail("对不起，现在忙着呢，请稍后！\n");
	}
	remove_call_out("enough_rest");
	call_out("enough_rest",1);
	set_temp("busy",1);
	from_ob = present(from + "_money", me);
	to_ob = present(to + "_money", me);

	if (!to_ob && file_size("/clone/money/" + to + ".c") < 0)
	{
		return notify_fail("你想兑换成什么？\n");
	}
	if (!from_ob)
	{
		return notify_fail("你身上没有带这种钱。\n");
	}
	if (amount < 1)
	{
		return notify_fail("你想白赚啊？\n");
	}
	if ((int)from_ob->query_amount() < amount)
	{
		return notify_fail("你带的" + from_ob->query("name") + "不够。\n");
	}
	
	bv1 = from_ob->query("base_value");
	if (!bv1)
	{
		return notify_fail("这样东西不值钱。\n");
	}

	bv2 = to_ob ? to_ob->query("base_value") : call_other("/clone/money/" + to, "query", "base_value" );
	
	if (bv1 < bv2)
		amount -= amount % (bv2 / bv1);	

	if (amount == 0)
	{
		return notify_fail("这些" + from_ob->query("name") + "不够换。\n");
	}

	// allowed to convert now
	set_temp("busy", 1);	

	from_ob->add_amount(-amount);

	if (!to_ob) {
		to_ob = new("/clone/money/" + to);
		to_ob->set_amount(amount * bv1 * 10/ (bv2 * 10));
		to_ob->move(me);
	}
	else
		to_ob->add_amount(amount * bv1 * 10 / (bv2 * 10));
	
	message_vision(sprintf("$N从身上取出%s%s%s，换成了%s%s%s。\n",
	chinese_number(amount), from_ob->query("base_unit"), from_ob->query("name"),
	chinese_number(amount * bv1 * 10 / (bv2 * 10)), to_ob->query("base_unit"), 
	to_ob->query("name")), me);

//	from_ob->add_amount(-amount);

	remove_call_out("enough_rest");
	call_out("enough_rest", 5);

	return 1;
}