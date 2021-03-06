// gangdao.c

#include <weapon.h>
#include <ansi.h>
inherit F_UNIQUE;
inherit SWORD;

void create()
{
	set_name(HIB"阴"HIW"阳"NOR+CYN"剑"NOR, ({ "yinyang jian","yinyang", "jian","sword" }));
	set_weight(2000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "柄");
		set("long", @LONG
此剑出剑时，剑芒通白，静立时，剑身全黑，江湖中只有一把这种剑，
名叫“阴阳剑”。“阴阳剑”轻若鸿毛；所以出手尽可发挥，而使这把
剑的人是一名隐侠，叫做张临意。
LONG);
		set("value", 20000);
		set("no_break", 1);
		set("endure", 150);
		set("material", "steel");
		set("wield_msg", CYN"$N抽出鞘中剑，本来"HIB"漆黑"NOR+CYN"的剑身在内力所逼之下竟然变得通体"HIW"煞白。\n"NOR);
		set("unwield_msg", "$N反手收剑，剑一离手，"HIW"煞白"NOR"的剑身重又归于"HIB"漆黑。\n"NOR);
	}
	init_sword(60);
	setup();
}