// longsword.c 长剑
#include <ansi.h>
#include <weapon.h>
inherit SWORD;
void create()
{
          set_name(HIC"天羽剑"NOR, ({ "tianyu sword", "sword", "jian" }));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "这是一柄普通的精钢剑，一般的剑客都配带此剑。\n");
                set("value", 100);
                set("sword",1);
                set("nopawn",1);
                set("material", "steel");
                set("wield_msg", HIC"$N「唰」的一声抽出一柄$n"+HIC+"握在手中。\n"NOR);
                set("unwield_msg",HIC "$N将手中的$n"+HIC+"插回剑鞘。\n"NOR);
        }
        init_sword(50);
        setup();

}
