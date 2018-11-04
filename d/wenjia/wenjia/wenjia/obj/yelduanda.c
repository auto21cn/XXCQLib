// Item yelduanda.c 劲装短打
// Created by Zeus 1999.6.5
// Modified by Zeus 1999.6.5
// 
// 

#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(HIY"劲装短打"NOR, ({ "duanda" }));
        set("long", "这是一件黄色的" + HIY"劲装短打"NOR + "，这是温家第四代弟子的统一装束，有一定的防护力。\n");
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("material", "cloth");
                set("unit", "件");
                set("value", 200);
                set("armor_prop/armor", 10);
        }
        setup();
}
