// tiefu.c

#include <weapon.h>
#include <ansi.h>
inherit AXE;

void create()
{
	set_name(CYN"铁斧"NOR, ({ "tie fu", "axe", "fu", "tiefu"}) );
	set_weight(10000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "把");
		set("long", "这是一把劈柴用的铁斧，砍起东西来非常顺手。\n");
		set("value", 1000);
		set("distance", 2);
                set("material","iron");
		set("wield_msg", "$N拿出一把砍柴的$n，握在手中当作武器。\n");
		set("unwield_msg", "$N将$n反插在背后。\n");
	}
	init_axe(20);
	setup();
}
