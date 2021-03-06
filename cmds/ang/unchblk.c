// write by jackyboy@cctx 1999/2/8

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	string who, ch_name;
	string* channels=({"all","cctx","rumor","chat","es","party","new","wiz","arch","gwiz","gbwiz"});

	if (!arg)
		return notify_fail("语法: unchblk <玩家id> <频道名>\n");
	if (sscanf(arg, "%s %s", who, ch_name) != 2)
		return  notify_fail("语法: chblk <玩家id> <频道名>\n");
	ob = LOGIN_D->find_body(who);
	if (!ob) return notify_fail("这个人不在！\n");
	if (wizardp(ob)) return notify_fail("不能对巫师进行频道操作。\n");
	if(member_array(ch_name,channels)!=-1)
	{
		if(ch_name!="all")
		{
			ob->set("chblk_channel/"+ch_name,time());
			tell_object(me,ob->query("name")+"的"+ch_name+"频道被打开了。\n");
		}
		else
		{
			ob->delete("chblk_channel");
			tell_object(me,ob->query("name")+"的所有频道都被打开了。\n");
		}
	}
	else
		return notify_fail("没有这个频道！\n");
	return 1;
}

int help(object me)
{
write(@HELP
指令格式 : unchblk <某人> <频道名>

此命令将打开某人的频道。如果没有频道名就打开所有合法频道。
<某人>　也可以是频道名。
<频道名> 可以是rumor、chat、es等，或 all 打开全部。

HELP
    );
    return 1;
}
