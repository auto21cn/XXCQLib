// Item laozi.c
// Created by Zeus 1999.3.28
// Modified by Zeus 1999.3.28
// 
// 

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name( "老子", ({ "laozi"}));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
                        CYN
                        "\n\t道可道，非常道。名可名，非常名。\n"
                        "\t无名天地之始；有名万物之母。\n"
                        "\t故常无，欲以观其妙；常有，欲以观其徼。\n"
                        "\t此两者，同出而异名，同谓之玄。玄之又玄，众妙之门。\n\n"
                        NOR
                );
                set("value", 500);
		set("material", "paper");
                set("skill", ([
                        "name":"literate",      // name of the skill
                        "exp_required":	0,      // minimum combat experience required
                        "jingli_cost": 20,      // jing cost every time study this
                        "difficulty":  30,      // the base int to learn this skill
                        "max_skill":   61,      // the maximum level you can learn
                ]) );
        }
}
