#include <ansi.h>
inherit ITEM;
inherit F_UNIQUE;
void init()
{
        add_action("do_zou","zou");
}

void create()
{
        set_name("破旧乐器", ({ "yue qi", "qi" }) );
        set_weight(4500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
        set("unit", "把");
        set("no_give","这个东西不能给人");
        set("no_pawn","这个东西不能当");
        set("no_get","这个东西不能拣起来");
        set("value", 0);
        set("material", "wood");
        set("long", "这是一把不用的破旧乐器。\n");

        }
        setup();
}

int do_zou(string arg)
{
    object me;
    me = this_player();
    if( !arg || arg !="wen")
	return notify_fail("你不是想乱弹琴吧!\n");
    if( me->query_skill("force",1) < 150 && me->query("max_neili") < 2000)
	return notify_fail("你的内功和内力可能太低了，不能奏出惊人的曲子!\n");
    message_vision(HIY "\n$N依据着纹路的曲谱弹，居然奏得更好，而在这时，那棺盖便轧轧开启……”!\n"NOR, me);
    message_vision(HIW "\n原来棺中有两副骨胳和一本册子(book)!\n"NOR,me);
   message_vision(HIG "\n仔细看看，一定是好东西，能不能拿得出去!\n"NOR,me);
    me->set_temp("open",1);	
    me->start_busy(2);	
     destruct(this_object());
        return 1;
}
	
