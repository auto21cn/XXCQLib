//为了方便edit命令查看，详细的函数帮助说明放在文件尾
// 可存储，可投标的房间程序 BID ROOM v0.1b0
// JackyBoy@CuteRabbits Studio for CCTX 1999/5/17
/*
A] 数据结构及各种属性：
owner:
	这是一个mapping属性，有关键字id、mid、name、mname、value
	其中id和name为当铺经营者的id及名字，而mid和mname为临时允许的NPC的ID和名字，这样的设计是
	为了方便玩家雇佣NPC来代替自己经营当铺。value为投入的运行资金，可以是投标资金！
bider1,bider2:
	这两个mapping记录了前两位投标者的属性以及价值，包括id,name,value，另外还有投标时间。
bided:
	如果有人已经中标后置则该属性不为空，但是可以用owner属性来取代该属性的。
auto:
	设置自动应答模式，将由auto_model函数处理并返回，由当铺所有者设置，这跟如何处理每笔
	交易有关。
account:
	设置为一个mapping变量，记录盈利情况，本日收入，最有一笔交易的时间，另外也许可以设置
	一个资金余额，但是要看如何处理每笔交易了！
	
B] 提供的命令：
rsave:
	提供给巫师，作用为存储这个ITEM的数据。编写期间使用
rset:
	提供给巫师用来设置一些属性。编写期间使用
bid,sumbit:
	为玩家提供投标的命令，测试中。(未完成)主要是投标后如何选择中标者的问题。
	初步打算使用void reset()函数以及在setup()中调用reset()函数来检查！
show:
	显示当铺的各个属性的状态，测试区使用，在正式使用后分巫师和玩家两个等级！
	
C] TipS:
1、有经营权的玩家应该可以从里面取东西出来或放东西进去卖！这个要考虑好，只有使用投入资金方式
	才可以这样做，否则使用玩家从交易中提成的方式的话就不可以！
2、对那些要对玩家进行写入的操作要检查玩家是否依然存在，同样地，玩家自杀应该要注意对一些数据的
	影响，能避免的应该尽量避免，比如注册玩家数！
	另外在投标中如果某个玩家中标应对该玩家存在否进行检查，在玩家投标时也应该检查原来的玩家是否
	依然存在。
*/

/*
函数集说明：
int do_save()
	用于提供手动给this_object()进行save()调用，需要限制巫师级别，写好程序后，该命令
	可以不存在，目前主要用于配合do_set函数使用
string query_save_file()
	用于确定this_object()的存盘文件
void chat()
	用于提供一个调试的频道和一个宣布的频道，程序完成后应该去除调试的频道，函数可以不
	用重新写过。
void up2owner()
	将bider1这个mapping里的第一投标者升级为经营者，并不删除bider1，因为直接
	set(mapping,mapping)会造成传址的代码，所以写该函数避免，如果数据结构有变化，只需
	要修改这个函数以及下两个函数就可以了。
void down2bider()
	跟上一个函数相反的操作。
void bider12()
	同up2owner()类似，但是是将bider1内容复制到bider2上，bider1也没有删除
void bider21()
	同bider12相反，是将bider2内容复制到bider1上，不清除bider2
int do_set(string arg)
	调试期间为方便写的设置属性的函数，调试完成后应该限制可以设置的属性，仅允许经营者
	设置一些options作用的属性。
string list_bider()
	返回该房间的投标者情况的字符串描述。
void init()
	提供给玩家增加命令的函数，应该随时应情况修改。
int exist_id(string arg)
	检查有没有ID为arg的玩家数据存在，相应返回1或0。
int working()
	如果owner不为空，则返回1表示处于经营状态。
int auto_model()
	如果auto属性非0，表示经营需要玩家干预。该函数应该分级到最高级，而不是bid room级
*/

//这个定义是决定this_object的存储目录的，由于权限问题，涉及到SECURITY_D里的读写控制
#define BIDROOM_DIR DATA_DIR+"SaveRoom/bidroom/"

//这个定义表示距最后一次投标动作多少分钟结束投标，选出经营者
#define BID_TIME 60*30

//这个定义表示多少秒后调用check函数检查一次投标以及经营期结束否
#define CHECK_DELAY 60*30

//这个定义表示多少秒后经营者的经营权结束
#define OWN_TIME 60*120

//文件版权、说明等信息请参看dangpu.h，正式发布后应该移动过来。
//权限设置为对/data/SaveRoom/下的任何读写操作只要是restore_object or save_object都允许
//请参看/adm/daemons/securityd.c

#include <ansi.h>
inherit ROOM;
inherit F_SAVE;

//函数预定义
string query_save_file();
void enough_rest();
void chat(string,string);
int working();
int auto_model();


//书写经营者获取利润的函数，分两个，一个用来计算利润，另一个用作命令来提取利润，还有一个查看在
//show命令里实现！
int make_money(int value)
{
	int i;
	if(!working())
		return 0;
	i=value/20;
	if(i<5)
		i=5;
	if(i>500)
		i=500;
	add("money",i);
	save();
	return query("money");
}

int do_makemoney()
{
	int value;
	object me=this_player();
	value=query("money");
	if(value<=0)
		return notify_fail("你还没有任何利润可以提取的！\n");
	MONEY_D->pay_player(me,value);
	write("你从经营"+query("short")+"获取的利润中提取了："+MONEY_D->money_str(value)+"！\n");
	delete("money");
	save();
	return 1;
}

//定义忙状态删除函数
void enough_rest()
{
        delete_temp("busy");
}

void setup()
{
	restore();
	set("no_clean_up",1);//必须设置不能被摧毁
	chat("sys",query("short")+"的setup()被调用。\n");
	set("no_get",1);
	set("no_get_from",1);//设置这两个属性以防被玩家get走了
	call_out("checking",1,this_object());
}


int do_save()//保存房间数据到存盘文件里
{
	if(wiz_level(this_player(1))<wiz_level("(wizard)"))
		return notify_fail("你的级别不能进行这种操作。\n");
	write("存盘到数据文件："+query_save_file()+"...\n");
	if(!save())
		write(query("short")+"数据存储失败。\n");
	else
		write(query("short")+"数据已经存盘。\n");
	return 1;
}

//存盘文件由继承的文件的全路径转换得到，由于使用了base_name，禁止继承的程序以数字结尾，
//以防造成存盘文件重复！
string query_save_file()
{
	string f_name;
	f_name=base_name(this_object());
	f_name=replace_string(f_name,"/","_");
	return BIDROOM_DIR+f_name;
}

void chat(string type,string arg)
{
	object ob;
	switch(type)
	{
		case "sys":
			foreach( ob in users())
			{
				if(wizardp(ob))
					message("channel:sys", HIR"【系统】"+arg+"\n"NOR, ob);
			}
			break;
		case "chat":
			message("channel:chat",HIC"【闲聊】"+arg+"\n"NOR, users());
			break;
		default:
			break;
	}
}

void up2owner()
{
	mapping tmp;
	//必须确保tmp不会为空
	tmp=query("bider1");
	//set("owner",tmp);//好象这样是传的地址，而不是传值！
	set("owner/id",tmp["id"]);
	set("owner/name",tmp["name"]);
	set("owner/value",tmp["value"]);
	set("owner/time",time());//记录现在的时间，将利用checking()来判断是否已经经过一定期限
}
//将经营者降级为投标者
void down2bider()
{
	mapping tmp;
	//必须确保tmp不会为空
	tmp=query("owner");
	//set("bider1",tmp);//好象这样是传的地址，而不是传值！
	set("bider1/id",tmp["id"]);
	set("bider1/name",tmp["name"]);
	set("bider1/value",tmp["value"]);
	set("bider1/time",time());//记录现在的时间，将利用checking()来判断是否已经经过一定期限
}

//将bider1内容复制到bider2上
void bider12()
{
	mapping tmp;
	//必须确保tmp不会为空
	tmp=query("bider1");
	//set("bider2",tmp);//好象这样是传的地址，而不是传值！
	set("bider2/id",tmp["id"]);
	set("bider2/name",tmp["name"]);
	set("bider2/value",tmp["value"]);
	set("bider2/time",time());//记录现在的时间，将利用checking()来判断是否已经经过一定期限
}

//将bider2的内容复制到bider2上
void bider21()
{
	mapping tmp;
	//必须确保tmp不会为空
	tmp=query("bider2");
	//set("bider1",tmp);//好象这样是传的地址，而不是传值！
	set("bider1/id",tmp["id"]);
	set("bider1/name",tmp["name"]);
	set("bider1/value",tmp["value"]);
	set("bider1/time",time());//记录现在的时间，将利用checking()来判断是否已经经过一定期限
}

int do_set(string arg)//临时提供来设置房间的各种属性，方便调试！
{
	string prop,values;
	int valued;
	if(wiz_level(this_player())<wiz_level("(wizard)"))
		return notify_fail("你的级别不能进行这种操作。\n");
	if(!arg||arg=="")
		return notify_fail("你要设置什么属性？\n");
	if(sscanf(arg,"%s %d",prop,values)==2)
	{
		write("设置"+prop+"的值为"+set(prop,values)+"(数字)。\n");
		return 1;
	}
	if(sscanf(arg,"%s %s",prop,valued)==2)
	{
		write("设置"+prop+"的值为"+set(prop,values)+"(字符串)。\n");
		return 1;
	}
	
	return notify_fail("错误!请检查命令是否输入正确。\n");
}

string list_bider()
{
	mapping tmp;
	string str;
	if(!mapp(tmp=query("bider1")))
	{
		if(query("owner"))
			str=query("short")+"已经有人经营了，现在无候补竞标者！\n";
		else
			str=query("short")+"还没有人投标呢！\n";
	}
	else
	{
		if(query("owner"))
			str=query("short")+"已经有人经营了。\n";
		else 
			str="";
		str=str+query("short")+"第一投标者："+tmp["name"]+"("+tmp["id"]+")\t投标金额："+
			MONEY_D->price_str(tmp["value"])+"\n";
		if(mapp(tmp=query("bider2")))
			str=str+"第二投标者："+tmp["name"]+"("+tmp["id"]+")\t投标金额："+
				MONEY_D->price_str(tmp["value"])+"\n";
	}
	return str;
}
void init()
{

	add_action("do_save","rsave");
	add_action("do_set","rset");
	add_action("do_bid","bid");
	add_action("do_bid","submit");
	add_action("do_show","show");
	add_action("do_makemoney","ticheng");
}

int exist_id(string arg)
{
	object ob=new(USER_OB);
	if(!arg)
		return 0;
	ob->set("id",arg);
	return ob->restore();
}

int working()//这个函数用来给命令调用，控制是否可以执行该命令
{
	if(!query("owner"))
		return 0;
	return 1;
}

int auto_model()//这个函数返回值为一表示处于自动应答模式，即买卖无须玩家干预
{
	return query("auto");
}
//这个函数里不能直接使用set,query，因为它将被call_out调用
void checking(object room)
{
	//在这个函数里检查投标者和经营者的有效ID如果已经自杀了则清除其记录
	//所有的return 语句前都应该再次call_out调用自己！
	mapping tmp;
	room->chat("sys",room->query("short")+"的checking函数被调用。"
		+CHINESE_D->chinese_time(0,(string)localtime(time())));
	room->save();//保存数据，因为检查时间间隔长，应该不影响系统负担。
	if((tmp=room->query("owner"))&&!exist_id(room->query("owner/id")))
	{
		//清除经营者，因为已经无他的用户数据了。
		room->chat("chat",tmp["name"]+"("+tmp["id"]+")已经退出江湖了，"+room->query("short")+
			"重新进行投标。");
		room->delete("owner");
		room->chat("chat",room->list_bider());
		call_out("checking",1,room);
		return;
	}
	if((tmp=room->query("bider1"))&&!exist_id(room->query("bider1/id")))
	{
		//清除第一投标者，因为已经无他的用户数据了。
		room->chat("chat",room->query("short")+"的第一投标者"+tmp["name"]+"("+tmp["id"]+
			")已经退出江湖了。");
		room->delete("bider1");
		if(room->query("bider2"))
		{
			room->bider21();
			room->delete("bider2");
		}
		room->chat("chat",room->list_bider());
		call_out("checking",1,room);
		return;
	}	
	if((tmp=room->query("bider2"))&&!exist_id(room->query("bider2/id")))
	{
		//清除第二投标者，因为已经无他的用户数据了。
		room->chat("chat",room->query("short")+"的第二投标者"+tmp["name"]+"("+tmp["id"]+
			")已经退出江湖了。");
		room->delete("bider2");
		room->chat("chat",room->list_bider());
		call_out("checking",1,room);
		return;
	}
	if(working())
	{
		if(!(tmp=query("owner")))
			room->chat("sys",room->query("short")+"无经营者经营，处于错误状态，请巫师处理！");
		else
		{
			if((time()-tmp["time"])>=OWN_TIME)
			{
				//这里不用检查用户id是否存在了！该函数备用
				//write_money(tmp["id"]);
				room->chat("chat",tmp["name"]+"在"+room->query("short")+
					"的经营权已经到期，现在重新竞标！");
				if(room->query("bider1"))
					room->bider12();
				room->down2bider();
				room->delete("owner");
				//显示投标者信息
				room->chat("chat",room->list_bider());
			}
		}
	}
	else
	{
		if(!(tmp=query("bider1")))
			room->chat("sys",room->query("short")+"还没有投标者！");
		else
		{
			if((time()-tmp["time"])>=BID_TIME)
			{
//但是如果一个玩家用很多钱投标，然后自杀用另一个ID来呢？
//所以应该在中标时检查玩家ID的存款是否足够，否则换第二个投标者中
//解决方法：在投标时就直接扣除，如果退标或者被自动排除则返回起帐目
//room->set("owner",tmp);//这也是传址的！不能这样写！
				room->up2owner();
				room->bider21();
				room->delete("bider2");
				room->set("account",0);
				//用account属性记录利润，最后结束时结帐！
				//account应该是一个mapping属性。
				room->chat("chat",room->query("owner/name")+"获得了"+
					room->query("short")+"的经营权!");
				room->chat("chat",room->query("short")+"的候补竞标者为"+
					room->query("bider1/name"));
				room->save();
				//中标处理
			}
		}
		//检查是否有人投标，以及是否中标
	}
	call_out("checking",CHECK_DELAY,room);
	return;
}

//本函数用来提供给玩家一个投标申请命令
//投标时，以银行帐户为投标资金，并且投标者的投标数必须大于当前投标者才能上投标者榜
//投标者仅保存两位，第二位为后备，当第一位无法投标或撤消时则第二位中标，撤消时不退回投标费用
int do_bid(string arg)
{
	int number,value;
	object me,ob;
	string type;
	mapping tmp;
	me=this_player(1);

	if(query("owner")&&arg&&arg!="cancel")//如果owner属性不为0则表示已经有人在经营。
		return notify_fail("对不起，当铺现在已经有人在经营了。\n");
	if(query_temp("busy"))
	{
		me->receive_damage("qi",10);//避免刷屏幕
		return notify_fail("对不起，现在忙着呢，请稍后！\n");
	}
	remove_call_out("enough_rest");
	call_out("enough_rest",1);
	set_temp("busy",1);
	if(arg&&arg=="cancel")//使用参数"cancel"来退出投标
	{
		//如果已经是中标者，则此命令取消经营权，并且不返回投标资金
		if(query("owner/id")==me->query("id"))
		{
			delete("owner");
			chat("chat",me->query("name")+"无法经营"+query("short")+"，关门倒闭了。");
			//应该返回了，因为投标者跟经营者不是一个人。
			return 1;
		}	
		if(query("bider1/id")==me->query("id"))
		{
			//退出者扣除一半投资，现在仅返回一半！因为投标时已经扣除全部!
			me->add("balance",(to_int(query("bider1/value")/2)));
			chat("chat",me->query("name")+"退出了对"+query("short")+"的竞标！");
			if(!mapp(query("bider2")))
			{
				delete("bider1");
				delete("bider2");
			}
			else
			{
				//提升第二个为第一竞标者
				set("bider1",query("bider2"));
				set("bider1/time",time());//重新设置时间
				chat("chat",query("short")+"的第一竞标者是"+query("bider1/name")+"("+
					query("bider1/id")+")！n");
				delete("bider2");
			}
			return 1;
		}
		if(query("bider2/id")==me->query("id"))
		{
			chat("chat",me->query("name")+"退出对"+query("short")+"竞标了。");
			//如果撤消者是第二个则不进行任何扣除
			me->add("balance",query("bider2/value"));
			delete("bider2");
			return 1;
		}
		write("你并没有列在投标者中，请使用show bider查看投标者情况。\n");
		return 1;
	}
	if(!arg||sscanf(arg,"%d %s",number,type)!=2)
		return notify_fail("请输入你将以多少资金来竞标！\n");
	type=lower_case(type);
	if(member_array(type,({"gold","silver","coin","thousand-cash"}))==-1)
		return notify_fail("没有"+type+"这种货币吧？！\n");
	value=("/clone/money/"+type+".c")->value()*number;
	if(value>me->query("balance"))
		return notify_fail("你的银行帐号没那么多钱！或者你的银行帐号被冻结了。\n");
	//为了避免产生太多bug，先扣除投资资金，如果退标或者被排除，则到时候返回一定资金
	me->set("balance",me->query("balance")-value);
	//应该检查bider1里的玩家是否依然存在。
	if(tmp=query("bider1"))
	{
		if(value<=tmp["value"])
			if(me->query("id")==tmp["id"])
				return notify_fail("只能增加投标金额，不能降低的。\n");
			else
				return notify_fail("你show bider看看，"+tmp["name"]+"的投标金额不比你低哟！\n");
		if(me->query("id")!=tmp["id"])
		{
			//此时应该将bider2的投标资金全部返回
			if(exist_id(query("bider2/id")))
			{
				ob=new(USER_OB);
				ob->set("id",query("bider2/id"));
				ob->restore();
				ob->add("balance",query("bider2/value"));
				if(ob->save())
					chat("sys","第二投标者的资金返回成功。\n");
			}
			bider12();//如果不相同，则将bider1复制到2上，相同则直接覆盖
		}
		else
		{
			//因为是同一个人提高投标资金，应该先返回原来投入的
			me->add("balance",tmp["value"]);
		}
	}
	
	set("bider1/id",me->query("id"));//注意面具的影响
	set("bider1/name",me->query("name"));
	set("bider1/value",value);
	set("bider1/time",time());//记录现在的时间，将利用checking()来判断是否已经经过一定期限
	chat("chat",me->query("name")+"以"+MONEY_D->price_str(value)+"来投标"+query("short")
		+"的经营权。");
	if(save())
		write("投标成功，请用show status命令查看投标情况。\n");
	else
		write("投标出错，请联系巫师解决问题。\n");
	save();
	return 1;	
}

//本函数用来提供一个方便地查看各个属性的值的手段
//差一个查询经营期剩余时间的功能，这个函数在后面被继承后还应该重新写过！
int do_show(string arg)
{
	
	if(!arg||arg=="")
		return notify_fail("你想查看什么？\n");
	if(lower_case(arg)=="bider")
	{
		write(list_bider()+"\n");
		return 1;
	}
	if(lower_case(arg)=="status")
	{
		printf("当铺当前状态：\n"
			"自动应答：%s\n当铺投标状态：%s\n当铺经营者：%s\n"
			"第一投标者：%s\t投标金额：%s\n"
			"第二投标者：%s\t投标金额：%s\n"
			"当铺经营状态：%s\n"
			,
			(auto_model())?"ON":"OFF",
			(query("owner"))?"完成":"未完成",
			(query("owner"))?(query("owner/name")+"("+query("owner/id")+")"):"无",
			(query("bider1"))?(query("bider1/name")+"("+query("bider1/id")+")"):"无",
			MONEY_D->price_str((query("bider1"))?(query("bider1/value")):0),
			(query("bider2"))?(query("bider2/name")+"("+query("bider2/id")+")"):"无",
			MONEY_D->price_str((query("bider2"))?(query("bider2/value")):0),
			(working())?"ON":"OFF",
			
		);
		return 1;
	}
	write("还没有对属性"+arg+"的处理程序。\n");
	return 1;
}
