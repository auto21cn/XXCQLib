// Item xiaoshuzhi.c
// Created by Zeus 1999.5.27
// Modified by Zeus 1999.5.27
// 
// 

inherit ITEM;

void create()
{
        set_name( "小树枝",({ "xiao shuzhi"}));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long","这是一枝小树枝。\n");
                set("value", 100);
                set("material", "wood");
        }
}
