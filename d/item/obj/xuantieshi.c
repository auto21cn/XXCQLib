// xuantieshi.c  玄铁石  武器原料
// Written by Doing Lu 1998/11/9

inherit ITEM;

#include <ansi.h>

// 打造武器粗坯时需要的一种原料
// 根据 material_ attrib = x 为判断标志，其有效点数为:power_point
// 有效点数是 100

void create()
{
	set_name(WHT "玄铁石" NOR, ({"xuantie shi", "shi"}));
	set_weight(3000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "这是一块黑黝黝的石头，看起来毫不起眼，但是入手非常沉重。\n" NOR);
		set("unit", "块");
		set("material_attrib", "x");
		set("power_point", 100);
		set("value", 40000);
	}
}
