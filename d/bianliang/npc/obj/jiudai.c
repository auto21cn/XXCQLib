// wineskin.c  酒袋

#include <ansi.h>
inherit ITEM;
inherit F_LIQUID;

void create()
{
	set_name(YEL"牛皮酒袋"NOR, ({"jiudai", "dai"}));
	set_weight(700);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "一个用来装酒的大酒袋，也可以用来装水。\n");
		set("unit", "个");
		set("value", 300);
		set("max_liquid", 15);
         set("container",1);
	}

	set("liquid", ([
		"type": "alcohol",
		"name": "烧刀子",
		"remaining": 15,
		"drunk_apply": 20,
	]));
}
