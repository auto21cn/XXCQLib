// poison_dust.c
//Date: godzilla@cctx /1999/06/01
inherit ITEM;
#include <ansi.h>
void create()
{

        set_name(RED"镇心理气丸"NOR, ({ "zhenxin dan", "dan" }) );
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long",
                        "这是“杀人神医”平一指，精心研制的丹药,泡在酒里方显功效\n" );
                set("value", 5000);
                set("unit", "粒");
                set("weight", 30);
        }

}

void init()
{
        add_action("do_pour", "pour");
}

int do_pour(string arg)
{
        string me, what;
        object ob;

        if( !arg
        ||      sscanf(arg, "%s into %s", me, what)!=2
        ||      !id(me) )
                return notify_fail("命令格式: pour <药> into <物品>。\n");

        ob = present(what, this_player());
        if( !ob )
                return notify_fail("你身上没有" + what + "这样东西。\n");
        if( !ob->query("liquid/remaining") )
        return notify_fail(ob->name() + "里什么也没有，先装些酒才能溶化"+RED+"镇心理气丸"+NOR+"。\n");
        if( ob->query("liquid/type")=="water")
        return notify_fail(RED"镇心理气丸"+NOR+"只能放到酒里。\n"); 
        message_vision("$N将一粒" + name() + "倒进" + ob->name() 
                + "摇晃了几下。\n", this_player());
        ob->set("liquid/type","yaojiu");
        destruct(this_object());
        return 1;
}

