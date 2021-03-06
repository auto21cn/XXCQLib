// hp.c
// write by JackyBoy for Snow 99/11/12
 
#include <ansi.h>
 
inherit F_CLEAN_UP;
 
string status_color(int current, int max);
 
int main(object me, string arg)
{
	object ob;string str,tmp;
	mapping my;
	seteuid(getuid(me));
	if(!arg)
		ob = me;
	else if (wizardp(me))
	{
		ob = present(arg, environment(me));
		if (!ob) ob = find_player(arg);
		if (!ob) ob = find_living(arg);
		if (!ob) return notify_fail("你要察看谁的状态？\n");
	}
	else
		return notify_fail("只有巫师能察看别人的状态。\n");
	my = ob->query_entire_dbase();
	write(sprintf(HIG"个人状态简表："HIY"%s [%s]\n"NOR,ob->name(),capitalize(ob->query("id"))));
	write(sprintf(HIY"──────────────────────────────\n"NOR));
	write(sprintf("〖气息〗 %s%4d/ %4d %s(%3d%%)" NOR "   〖斗志〗 %s%4d / %4d (+%d)\n" NOR,
		status_color(my["qi"], my["eff_qi"]), my["qi"], my["eff_qi"],
		status_color(my["eff_qi"], my["max_qi"]), my["eff_qi"] * 100 / my["max_qi"],
		status_color(my["douzhi"], my["eff_douzhi"]), my["douzhi"], my["eff_douzhi"], my["jia_douzhi"],));
	write(sprintf("〖精力〗 %s%4d/ %4d %s(%3d%%)" NOR "   〖内力〗 %s%4d / %4d (+%d)\n" NOR,
		status_color(my["jingli"], my["eff_jingli"]), my["jingli"], my["eff_jingli"],
		status_color(my["eff_jingli"], my["max_jingli"]), my["eff_jingli"] * 100 / my["max_jingli"],
		status_color(my["neili"], my["max_neili"]), my["neili"], my["max_neili"], my["jiali"] ));
	write(sprintf("〖神智〗 %s%4d/ %4d " NOR "         〖杀气〗 %s%d\n" NOR,
		status_color(my["shenzhi"], my["max_shenzhi"]), my["shenzhi"], my["max_shenzhi"],
		HIW,my["kill"]));
	if(my["food"]*100/ob->max_food_capacity()>90) str=HIG+"充足";
	else if(my["food"]*100/ob->max_food_capacity()>80) str=HIC+"正常";
	else if(my["food"]*100/ob->max_food_capacity()>60) str=HIY+"不饿";
	else if(my["food"]*100/ob->max_food_capacity()>40) str=HIM+"饿了";
	else if(my["food"]*100/ob->max_food_capacity()>20) str=HIR+"饥饿";
	else str=HIR+"饥饿";
	tmp=status_color(my["food"], ob->max_food_capacity());
	write(sprintf("〖食物〗 %s%4d/ %4d [%4s"NOR"%s]" NOR "   〖潜能〗 %s%d\n" NOR,
		tmp,my["food"], ob->max_food_capacity(),str,tmp,
		HIY,(int)ob->query("potential") - (int)ob->query("learned_points")));
	if(my["water"]*100/ob->max_water_capacity()>90) str=HIG+"充足";
	else if(my["water"]*100/ob->max_water_capacity()>80) str=HIC+"正常";
	else if(my["water"]*100/ob->max_water_capacity()>60) str=HIY+"不渴";
	else if(my["water"]*100/ob->max_water_capacity()>40) str=HIM+"渴了";
	else if(my["water"]*100/ob->max_water_capacity()>20) str=HIR+"缺水";
	else str=HIR+"饥渴";
	tmp=status_color(my["water"], ob->max_water_capacity());
	write(sprintf("〖饮水〗 %s%4d/ %4d [%4s"NOR"%s]"NOR "   〖经验〗 %s%d\n" NOR,
		tmp,my["water"], ob->max_water_capacity(),str,tmp,HIM,my["combat_exp"]));
	write(HIY"──────────────────────────────\n"NOR);
	return 1;
}
 
string status_color(int current, int max)
{
	int percent;
	if( max>0 ) percent = current * 100 / max;
	else percent = 100;
	if( percent > 100 ) return HIC;
	if( percent >= 90 ) return HIG;
	if( percent >= 60 ) return HIY;
	if( percent >= 30 ) return YEL;
	if( percent >= 10 ) return HIR;
	return RED;
}
 
int help(object me)
{
	write(@HELP
指令格式 : hp
           hp <对象名称>                   (巫师专用)
这个指令可以显示你(你)或指定对象的精, 气, 神数值。
see also : score
HELP
	);
	return 1;
}
