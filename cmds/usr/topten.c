// toptenadd.c
#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string str;
	seteuid(geteuid(me));
	if (!arg||arg=="")
		return notify_fail("指令格式 : topten <类型>\n");
	str=TOPTEN_D->topten_query(arg);
	write(str+"\n");
	return 1;
}

int help(object)
{
write(HIW"指令格式 : topten <类型>\n"NOR+TOPTEN_D->query_type());
    return 1;
}
