// uptime.c
//Write By JackyBoy@CuteRabbit for CCTX

#include <mudlib.h>

inherit F_CLEAN_UP;

// This command is also called by LOGIN_D, so we don't want it use 
// arguments.
int main()
{
	int t, d, h, m, s;
	string time;

	t = uptime();
	s = t % 60;		t /= 60;
	m = t % 60;		t /= 60;
	h = t % 24;		t /= 24;
	d = t;

	if(d) time = chinese_number(d) + "天";
	else time = "";

	if(h) time += chinese_number(h) + "小时";
	if(m) time += chinese_number(m) + "分";
	time += chinese_number(s) + "秒\n";

	write(CHINESE_MUD_NAME+"已经执行了" + time + "\n");
	return 1;
}

int help(object nouse)
{
	write(@HELP
指令格式 : uptime
 
这个指令告诉您这个游戏已经连续执行了多久。
 
HELP
    );
    return 1;
}
