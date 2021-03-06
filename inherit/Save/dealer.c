//当铺的包含文件
/*函数说明：
void init()
	增加sell,list,buy,value几个命令
	注意：这些命令都实现了同时操作数个物品的支持！
int do_value(string arg)
	提供一个命令给玩家估计身上物品的价值
int do_list()
	列出当铺里有多少东西正在出售
int do_sell(string arg)
	将玩家身上的物品卖到当铺里！
void pay_money(object ob,int value,int num,string op)
	付钱以及信息显示，默认付钱对象为this_player()，op的值只允许是"卖"或者"典当"
void get_money()跟pay_money相反
*/

//定义最多可以卖多少物品进来，应该按种类计算，这里只是一个原则上的最大值，实际最大值
//将由query("max_sell")得到
#define MAX_SELL 100

/* 属性说明:
sell_number : 是别人卖进来的物品种类计数，初始为0
sell_object : 用来记录别人卖进来的物品
拐卖属性    : 移动到/d/sroom/storage，并设置为开始房间设置tag/selled属性为1表示被卖了

*/

inherit BID_ROOM;

string get_dwei(object);

void pay_money(object ob,int value,int num,string op)
{
	string dwei;
	dwei=get_dwei(ob);
	if(!op)
		op="卖";
	message_vision("$N"+op+"了"+chinese_number(num)+
		dwei + ob->query("name") + "。\n",this_player(1));
	MONEY_D->pay_player(this_player(), value * 70 / 100);
	tell_object(this_player(),"你获得了"+MONEY_D->price_str( value * 70 / 100)+"。\n");
}


string get_dwei(object ob)
{
	string dwei;
	//判定数量单位
	if(!stringp(dwei=ob->query("base_unit")))
		dwei=ob->query("unit");
	if(!stringp(dwei))
		dwei="些(数量单位不祥!)";
	return dwei;
}

void init()
{
	::init();
	add_action("do_sell","sell");
	add_action("do_list","list");
	add_action("do_buy","buy");
	add_action("do_value","value");
}


int do_value(string arg)
{
	//还有个问题，不能对base_value高，但是value底的估计价值！
	object ob;
	string dwei;
	int value,num;
	if (!arg)
		return notify_fail("你要估什么的价？\n");
	if (sscanf(arg,"%d %s",num,arg)!=2)
		num = 1;
	if (!arg || !(ob = present(arg, this_player())))
		return notify_fail("你要估什么的价？\n");
	if (ob->query("money_id"))
		return notify_fail("你没用过钱啊？\n");
	if (userp(ob))
		ob->set("value", ob->query("per") * 500);
	dwei=get_dwei(ob);		
	value = ob->query("value");
	value*=num;
	if(value==0)
		value=ob->query("base_value")*num;
	if (value < 1)
		write(chinese_number(num)+dwei+ob->query("name") + "一文不值！\n");
	else 
		write(chinese_number(num)+dwei+ob->query("name") + "值" + 
		MONEY_D->price_str(value * 70 / 100) + "。\n");
	return 1;
}

//op的值只允许是"买"或者"赎回"
void get_money(object ob,int num,string dfn,string op)
{
	string dwei;
	object nob,me;
	int vl;
	me=this_player();
	if(!vl=ob->query("base_value"))
		vl=ob->query("value");
	if(!op)
		op="买";
	if(op!="买"&&op!="赎回")
		return notify_fail("get_money()错误!->op="+op+"\n");
	if(vl<1)
	{
		write("这个物品的价格有点问题，暂时不能给你！\n");
		return;
	}
	dwei=get_dwei(ob);
	switch (MONEY_D->player_pay(me, vl*num))
	{
		case 0:
			write("你身上的钱不够"+op+chinese_number(num)+dwei+ob->name(1)+"！\n");
			return;
		case 2:
			write("你的零钱不够了，银票又没人找得开。\n");
			return;
		default:
			message_vision("$N花了"+MONEY_D->price_str(vl*num)+
				op+"了"+chinese_number(num)+dwei+ob->name(1)+"\n",me);
			//移动OB，注意！没有计算负荷情况！
			if(ob->query_amount()!=0)
			{
				ob->set_amount(num);
				if(ob->move(me)==0)
				{
					ob->move(environment(me));
					message_vision("$N身上的东西太多了，"+chinese_number(num)+dwei+ob->name(1)
						+"拿不稳掉了下来！\n",me);
				}
			}
			else
			{
				for(vl=num;vl>0;vl--)
				{
					nob=new(base_name(ob));
					if(nob->move(me)==0)
					{
						nob->move(environment(me));
						message_vision("$N身上的东西太多了，"+nob->name(1)+"拿不稳掉了下来！\n",me);
					}
				}
			}
			//减少当铺里的货物数量！根据不同的调用进行不同的处理
			if(op=="买")
			{
				if((query("sell_object/"+dfn+"/number")-num)==0)
					delete("sell_object/"+dfn);
				else
					add("sell_object/"+dfn+"/number",-num);
			}
			else
			{
				if((query("pawn_object/"+me->query("id")+"/"+dfn+"/number")-num)==0)
					delete("pawn_object/"+me->query("id")+"/"+dfn);
				else
					add("pawn_object/"+me->query("id")+"/"+dfn+"/number",-num);
			}
	}
	return ;
}	
int do_buy(string arg)
{
	int num,sno;
	mapping sob,fob;
	string fn,dfn;
	object ob;
	if(!sob=query("sell_object"))
		return notify_fail("现在这里没有任何东西可以买卖！\n");
	if(!arg)
		return notify_fail("你要买什么？\n");
	if(query_temp("busy"))
	{
		this_player()->receive_damage("qi",10);//避免刷屏幕
		return notify_fail("对不起，现在忙着呢，请稍后！\n");
	}
	remove_call_out("enough_rest");
	call_out("enough_rest",1);
	set_temp("busy",1);
	if(sscanf(arg,"%d %s",num,arg)!=2)
		num=1;
	if(sscanf(arg,"%s %d",arg,sno)!=2)
		sno=1;
	dfn="无此物";
	foreach(fn in keys(sob))
	{
		fob=sob[fn];
		if(member_array(arg,fob["id"])!=-1)
			sno--;
		if(sno==0)
		{
			dfn=fn;
			break;
		}
	}
	if(dfn=="无此物"||sno!=0)
		return notify_fail("你要买的东西好象这里没有卖啊！\n");
	ob=new(replace_string(dfn,"\\","/"));
	fob=sob[fn];
	if(num>fob["number"])
		num=fob["number"];
	get_money(ob,num,dfn,"买");//使用默认的this_player()进行操作！
	return 1;
}

int do_list()
{
	object ob;
	mapping sob;
	int number;
	string file,str,tmp,prop;
	str="";
	if(!sob=query("sell_object"))
		return notify_fail("现在这里没有任何东西可以买卖！\n");
	foreach(file in keys(sob))
	{
		ob=new(replace_string(file,"\\","/"));
		if(!objectp(ob))
			continue;//应该删除该属性！
		prop="sell_object/"+file;
		number=query(prop+"/number");
		if(ob->query_amount()!=0)
			ob->set_amount(number);
		ob->set_name(query(prop+"/name"),query(prop+"/id"));
		if(!(tmp=ob->query("base_unit")))
			tmp=ob->query("unit");
		str+=chinese_number(number)+tmp+ob->name(1)+"("+
			implode(ob->parse_command_id_list(),",")+") 单价：";
		if(ob->query("base_value"))
			str+=MONEY_D->price_str(ob->query("base_value"));
		else
			str+=MONEY_D->price_str(ob->query("value"));
		str+=" 最后进货："+CHINESE_D->chinese_time(5,(string)ctime(query(prop+"/time")))+"\n";
	}
	this_player()->start_more(str);
	return 1;
}

int do_sell(string arg)
{
	//对于no_give的物品
	object ob,me,nob,tmpob;
	object *obs,*tobs;
	int number,num,tmp;
	string str,prop;
	int value,i;
	if (!arg)
		return notify_fail("你要卖什么？\n");
	me=this_player(1);
	if(query_temp("busy"))
	{
		me->receive_damage("qi",10);//避免刷屏幕
		return notify_fail("对不起，现在忙着呢，请稍后！\n");
	}
	remove_call_out("enough_rest");
	call_out("enough_rest",1);
	set_temp("busy",1);
	if (sscanf(arg,"%d %s",num,arg)!=2)
		num=1;
	if (!(ob = present(arg, me)))
		return notify_fail("你要卖什么？\n");
	if (ob->query("money_id"))
		return notify_fail("你想卖「钱」？？\n");
	if (stringp(ob->query("no_drop"))||ob->query("no_pawn")||ob->query("nopawn")||
		ob->query("nopawn")||ob->query("no_pawn")||ob->query("item_origin"))
		return notify_fail("这样东西不能卖。\n");
	if (ob->query("food_supply"))
		return notify_fail("剩菜剩饭留给您自己用吧。\n");
	if (ob->query("shaolin"))
		return notify_fail("小的只有一个脑袋，可不敢买少林庙产。\n");
	if (userp(ob))
	{
		/*临时禁止在这里卖玩家，要修改为只可以向人贩子卖玩家！*/
		return notify_fail("这里是做正当生意的，不能拐卖人口！快滚出去，不然我叫官兵了！\n");
		num=1;//因为人只可能有一个，所以加个语句避免恶意输入！
		CHANNEL_D->do_channel(ob, "rumor",
			sprintf("%s被某人拐卖了。", ob->name(1)));
	}
	else
	if((ob->query("enpawn")==0)//如果这个属性不为0，说明它是可以卖的！或者用is_character()判断呢？
		&&(
			ob->query("hunmi")!=0||living(ob)
			||ob->query_temp("block_msg/all")==1
		)
	)
		return notify_fail("这个东西是活的呀？！怎么卖嘛，真够笨的了！\n");
	//此处检查num数是否合法！
	if((tmp=ob->query_amount())!=0)//如果是set_amount类物品则直接查询amount
	{
		if(tmp<num)
			num=tmp;
	}
	else//否则按ID和名字进行统计！先获取所有物品然后排除其他只剩同类再统计！
	{
		obs=all_inventory(me);
		tmp=sizeof(obs);//拐卖人口时这里有错！
		tobs=({});
		for(i=0;i<tmp;i++)
		{
			if( !( obs[i]->name(1)!=ob->name(1) || !obs[i]->id(ob->query("id")) ) )
				tobs=tobs+({ obs[i] });//将同类物复制到tobs里
		}
		obs=tobs;//将obs设为tobs
		tmp=sizeof(obs);
		if(tmp<num)
			num=tmp;
	}
	//如果是amount物品应该分离出来！
	if(ob->query_amount()!=0)
	{
		if(!objectp(nob=new(base_name(ob))))
			write("复制新物品错误！"+(string)(ob->query_amount()-num)+"\n");
		nob->set_amount(ob->query_amount()-num);//设置玩家身上的物品（减少！）
		//nob->move(this_player());可能是这里如果move到ob的话就有两个同类OBJECT了！
		ob->set_amount(num);
	}
	else
		nob=ob;//避免value<30时判断出错。
	value = ob->query("value");
	if(!value)
		value=ob->query("base_value");
	if(value<1)
		value=1;
	value*=num;
	number=num;	
	if (value < 30)
	{
		ob->set_amount(nob->query_amount()+num);
		write(ob->query("name") + "一文不值！\n");
	}
	else 
	{
		if ( userp(ob))
		{
			//卖进来的不花经营者的钱，但是卖出的时候也只允许经营者提成
			pay_money(me,value,1,"卖");
			ob->move("/d/sroom/storage");
			ob->set("startroom","/d/sroom/storage");
			ob->set("tag/selled",1);
		}
		else
		if (value < 50)
		{
			pay_money(ob,value,num,"卖");
			if(pointerp(obs))//如果为真说明是非amount物品，应该按num清除！
			{
				for(i=num;i>0;i--)
				{
					tmpob=obs[0];
					obs=obs - ({ tmpob });
					if(objectp(tmpob))
						destruct(tmpob);
				}
			}
			else//如果不存在说明前面已经摧毁了，否则就应该是amount物品
			{
				destruct(ob);
				nob->move(me);
			}
		}
		else
		{
			//这里是处理真正的存放收购进来的物品的代码
			//如何记录购买进来的物品呢？
			//物品文件名，时间，数量，name，id
			//str保存基本文件名
			str=base_name(ob);
			str=replace_string(str,"/","\\");		//注意："\\"即"\"!
			//因为如果是可以amount计数的，那么query_amount肯定不等于0
			//而不可以amount的query_amount肯定等于0
			//所以直接query_amount就可以判断是否可以用amount计数
			//所以如果number==0那么说明不是amount物品，它的数量一定是1
			prop="sell_object/"+str;//设置存储该物品的属性名
			
			//可以买卖的最大货物种类可以靠投资或其他方法来增加
			//最基本的应该支持可以买卖一种货物，但是同时最多不应该比MAX_SELL多
			i=query("max_sell");
			if(i>MAX_SELL)
				i=MAX_SELL;
			if(i<1)
				i=1;
			if(!query(prop))//如果查询到了，说明原来就已经存在该物品了，没有则表示将增加新物品！
				if(sizeof(query("sell_object"))>i)
					return notify_fail("对不起，仓库已经堆满了货物，无法购买你的东西了。\n");
			set(prop+"/time",time());
			set(prop+"/name",ob->name(1));//可以当的应该都存在这个函数
			set(prop+"/id",ob->parse_command_id_list());//这是一个string *类型！
			set(prop+"/number",number+query(prop+"/number"));//是否应该对这个物品
			pay_money(ob,value,num,"卖");
			//这里是要增加种类的处理，这里负责增加，buy命令里负责清除
			if(pointerp(obs))//如果为真说明是非amount物品，应该按num清除！
			{
				for(i=num;i>0;i--)
				{
					tmpob=obs[0];
					obs=obs - ({ tmpob });
					if(objectp(tmpob))
						destruct(tmpob);
				}
			}
			else//如果不存在说明前面已经摧毁了，否则就应该是amount物品
			{
				destruct(ob);
				nob->move(me);
			}
		}
	}
	return 1;
}
