// Item jiqiu.c
// Created by Zeus 1999.6.5
// Modified by Zeus 1999.6.5
// 
// 
#include <ansi.h>

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(RED"马蹄炒鸡球"NOR, ({"jiqiu"}));
        set_weight(400);
        if (clonep()) set_default_object(__FILE__);
        else {
                set("long", "一盘由秘方制作的桂林名菜。\n");
                set("unit", "碟");
                set("value", 400);
                set("food_remaining", 5);
                set("food_supply", 80);
        }
}
