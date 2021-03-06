// tune.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string *tuned_ch;
	string target,name;
	object ob;

	tuned_ch = me->query("channels");

	if( !arg ) {
		if( !pointerp(tuned_ch) || !sizeof(tuned_ch) )
			write("你现在并没有收听任何频道。\n");
		else
			write("你现在收听的频道：" + implode(tuned_ch, ", ") + "。\n");
		return 1;
	}

	if (arg[0..5]=="notell")
	{
		if (arg=="notell")
		{
		me->set_temp("notell_all",1);
		write("你开始不接受别人的悄悄话了。\n");
		return 1;
		}
		sscanf(arg,"notell %s",target);
		if(!ob=find_player(target)) 
		return notify_fail("这个人不在线，或是不存在。\n");
		name=ob->query("name");
		me->set_temp("notell/"+target,name);
  		write("你开始不接受"+name+"的悄悄话了。\n");
		return 1;
	}
	if (arg[0..3]=="tell")
	{
		if (arg=="tell")
		{
		me->delete_temp("notell_all");
		write("你开始接受别人的悄悄话了。\n");
		return 1;
		}
		sscanf(arg,"tell %s",target);
		if (!name=me->query_temp("notell/"+target))
		return notify_fail("你并没有关闭和这个人的交谈频道。\n");
		me->delete_temp("notell/"+target);
		write("你决定重新接受"+name+"的悄悄话\n");
		return 1;
	}
	if(me->query("age")<15)
		return notify_fail("你现在还小，无法关闭频道！\n");
		
	if( pointerp(tuned_ch) && member_array(arg, tuned_ch)!=-1 ) {
		write("关闭 " + arg + " 频道。\n");
		tuned_ch -= ({ arg });
		me->set("channels", tuned_ch);
		return 1;
	} else {
		write("要打开某个频道只要用该频道说话即可。\n");
		return 1;
	}
}

int help()
{
	write(@HELP
指令格式：tune [<频道名称>]

这个指令让你选择是否要收听某一频道的讯息，如果没有指定频道名称，就会列出
你目前收听中的频道，如果指定了频道，原来收听中的就会关掉，反之打开。

如果你对一个没有收听中的频道讲话，会自动将它打开。
要对一个频道讲话，只要用：

<频道名称> <讯息> ....

例子：
  chat hello everyone!
  
你可以用 help channels 查询目前有哪些频道可以收听。

此外还可以用来关闭和某人的交谈频道
例如:
tune notell 不接受所有人的tell。
tune notell <某人ID>  不接受某人的tell。
tune tell   开始接受所有人的tell
tune tell <某人id>  开始接受某人的tell
注意：如果你指定关闭了某个人的tell,tune tell将不会打开对于他的tell
必须指定才能打开。

see also : shout
HELP
	);
	return 1;
}

