// Item yaolou.c  
// Created by Zeus 1999.7.30
// Modified by Zeus 1999.7.30
// 
// 

inherit ITEM;

void create()
{
        set_name( "药篓",({ "yao lou"}));
        set_weight(500);
        set_max_encumbrance(80000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "个");
                set("long","这是一个药篓。\n");
                set("value", 100);
                set("material", "bamboo");
        }
}
