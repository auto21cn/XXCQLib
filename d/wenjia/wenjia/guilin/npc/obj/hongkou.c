// Item hongkou.c
// Created by Zeus 1999.6.5
// Modified by Zeus 1999.6.5
// 
// 

#include <ansi.h>

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(MAG"红扣果子狸"NOR, ({"guozili"}));
        set_weight(400);
        if (clonep()) set_default_object(__FILE__);
        else {
                set("long", "一盘由果子狸等桂林特产材料做成的桂林名菜。\n");
                set("unit", "碟");
                set("value", 100);
                set("food_remaining", 4);
                set("food_supply", 50);
        }
}
