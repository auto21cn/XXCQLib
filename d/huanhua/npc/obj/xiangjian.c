// blade.c

#include <weapon.h>
#include <ansi.h>
inherit F_UNIQUE;
inherit BLADE;

void create()
{
	set_name(HIC"相见宝刀"NOR, ({"xiangjian baodao","baodao", "dao", "blade" }) );
	set_weight(4000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "柄");
		set("value", 500);
		set("material", "steel");
		set("rendu", 250);
		set("long", "一柄天青色的单刀，吹毛断发，是著名刀客孔别离的配刀。\n");
		set("wield_msg", CYN"$N抽出$n"CYN"在手，刀锋映起一道眩光，一看便知是柄宝刀。\n"NOR);
		set("unwield_msg", "$N将手中的$n插入腰间的刀鞘。\n");
	}
	init_blade(45);
	setup();
}
