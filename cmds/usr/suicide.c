// suicide.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	if( me->is_busy() )
		return notify_fail("你上一个动作还没完成。\n");

	if( !arg ) {
		write("You commit suicide.\n");
		return 1;
	}

	if( arg!="-f" ) 
		return notify_fail("自杀有两种，您是要永远死掉还是重新投胎？\n");

	write(
		"如果您选择永远死掉的自杀方式，这个人物的资料就永远删除了，请务必\n"
		"考虑清楚，确定的话请输入您的密码：");
	input_to("check_password", 1, me, 1);
	return 1;
}

void check_password(string passwd, object me, int forever)
{
	object link_ob;
	string old_pass;

	link_ob = me->query_temp("link_ob");
	old_pass = (me->query("registered")== 1)?link_ob->query("password"):link_ob->query("temp_password");
	if( crypt(passwd, old_pass)!=old_pass ) {
		write("密码错误！\n");
		return;
	}

	if (forever) {
		tell_object( me,
			HIR "\n\n你决定要自杀了，如果二十秒内不后悔，就真的永别了。\n\n\n" NOR);
		me->set_temp("suicide_countdown", 20);
		me->start_busy( (: call_other,this_object(), "slow_suicide" :) );
	}
}

int slow_suicide(object me)
{
	object link_ob;
	int stage,id_temp;
	string id_num;

	stage = me->query_temp("suicide_countdown");
	me->add_temp("suicide_countdown", -1);
	if( stage > 1 ) {
		if( stage%5 == 0 )
			tell_object(me, HIR "你还有 " + stage + " 秒的时间可以后悔。\n" NOR);
		return 1;
	}

	link_ob = me->query_temp("link_ob");
	if( !link_ob ) return 0;

	log_file("static/SUICIDE",
		sprintf("%s commits a suicide on %s\n", geteuid(me), ctime(time())) );

	seteuid(getuid());
//统计注册人数
	id_num=read_file("/adm/daemons/iduser",1);
	id_temp=atoi(id_num); id_temp=id_temp-1;
	id_num=sprintf("%d",id_temp);
	write_file("/adm/daemons/iduser",id_num,1);

	rm( link_ob->query_save_file() + __SAVE_EXTENSION__);
	rm( me->query_save_file() + __SAVE_EXTENSION__ );
		write("好吧，永别了:)。\n");
	tell_room(environment(me), me->name() +
		"自杀了，以后你再也看不到这个人了。\n", ({me}));
	
	destruct(me);
	return 0;
}

int help ()
{
        write(@HELP
指令格式: suicide [-f]
 
如果因为某种原因你不想活了, 你可以选择自杀.
自杀分两种:
 
suicide    : 重新投胎
suicide -f : 永远的除去玩家资料, 系统会要求你
             输入密码以确认身份.
 
请慎重选择 :)
 
HELP
);
        return 1;
}
