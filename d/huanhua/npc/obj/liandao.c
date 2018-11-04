//Obj 镰刀


#include <weapon.h>
#include <ansi.h>

inherit BLADE;

void create()
{
        set_name(HIW"镰刀"NOR, ({ "liandao", "dao" }));
        set_weight(7000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "这是一把除草用的镰刀。\n");
                set("value", 1000);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一声抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n插回腰间。\n");
        }
        init_blade(5);
        setup();
}

