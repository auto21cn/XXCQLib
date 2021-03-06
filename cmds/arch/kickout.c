
#include <command.h>

inherit F_CLEAN_UP;

void create() 
{
	seteuid(getuid());
}

int main(object me, string arg)
{
	int i;
	object ob;
	object *inv;
	int force=0;
                        
    if (!arg) return 0; 
    if(sscanf(arg,"-f %s",arg)==1)
    	force=1;//不存盘强制退出
	ob=find_player(arg);
	if (!ob) return notify_fail("没有这个人："+arg+"\n");
	if(  wiz_level(me) <= wiz_level(ob) &&
		!( force&&wiz_level(me)==wiz_level("(admin)") ) ) 
                 return notify_fail("你没有这个权力。\n");
	if( !wizardp(ob) ) {
		inv = all_inventory(ob);
		for(i=0; i<sizeof(inv); i++)
			if( !inv[i]->query_autoload() )
				DROP_CMD->do_drop(ob, inv[i]);
	}
	CHANNEL_D->do_channel(this_object(), "sys",
		me->name()+"把"+ob->name() + "(" + ob->query("id") + ")踢出了游戏。");
          CHANNEL_D->do_channel(this_object(), "rumor",
                ob->name() + "被系统踢出了游戏。");
	if(!force)
		ob->save();
	destruct(ob);
	return 1;
}
