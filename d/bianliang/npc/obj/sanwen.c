// laozi16.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name( WHT"古散文集"NOR, ({ "gusanwen", "book", "shu" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long","Sorry,我也没读过。

	笨小孩\n");
		set("value", 6000);
		set("material", "paper");
		set("skill", ([
			"name":	"literate",
			"exp_required":	0,
			"jingli_cost":  50,
			"difficulty":	10,
			"max_skill":	120,
			"min_skill":	110,
		]) );
	}
}