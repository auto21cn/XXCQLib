// arrow.c 箭
#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
	set_name(HIC"青羽箭"NOR, ({ "arrow" }));
        set_weight(2000);		                      	
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "袋");
		set("long", HIY"这是一袋用精铁做的箭，箭的尾部插着几只青色羽毛。\n"NOR);
		set("value", 10000);
                set("material", "iron");            
		set("base_value", 200);
                set("base_unit", "支");
                set("base_weight", 50);	                
	}                                                       
	set_amount(40);
        setup();
}