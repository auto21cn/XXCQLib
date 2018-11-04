
#include <ansi.h>

inherit F_AUTOLOAD;
inherit F_UNIQUE;
#include <armor.h>

inherit CLOTH;

void create()
{
        set_name(HIR"血翼"NOR, ({ "xueyi","yi" }) );
        set("long",@LONG
这就是萧萧天赖以成名的宝物。
LONG );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("material", "cloth");
                  set("armor_prop/armor", 20);
                  set("value",100000);
                  set("armor_prop/dodge", 20);
        }
        setup();
}


/*
void init()
{
        add_action( "do_fly", "fly" );
}

int query_autoload(object me)
{
        if (wizardp(me=this_player())) return 1;
        else return 0;
}

int do_fly(string arg)
{
        string home;
        object mme;
        object obj;
        string msg;
        mme=this_player();
        if (mme->is_fighting())
          return notify_fail("你还是专心战斗吧！\n");
        if( !arg ) return notify_fail("你要去哪里？\n");
        obj = find_player(arg);
        if(!obj) return notify_fail("没有这个玩家呀。\n");
         if (mme->query("max_qi")<=200)
         mme->add("qi",-1*(mme->query("max_qi")-1));
         else  mme->add("qi",-200);
         this_player()->add("qi",-200);
         this_player()->add("jingli",-50);
        tell_object(mme,HIM"你穿上血翼,将内劲运满全身。\n"NOR);
        tell_object(mme,HIM"只见血翼涨得满满的，活象一把滑翔伞!你运起轻功，向"+obj->query("name")+"飞去！\n"NOR);
        mme->move(environment(obj));
        tell_object(mme,HIM"你缓缓下降,脚一点地。然后收起血翼。\n"NOR);
        return 1;
}
*/
