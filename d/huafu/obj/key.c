//key.c
inherit ITEM;
void create()
{
     set_name( "钥匙", ({ "bedroomkey" }));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long","这是一把神秘的钥匙。\n");
                set("value", 0);
                set("material", "iron");
                set("no_drop","这东西不能离开你。\n");
              }
}
