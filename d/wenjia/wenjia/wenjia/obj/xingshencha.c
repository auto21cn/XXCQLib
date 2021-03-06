// Item xingshencha.c
// Created by Zeus 1999.3.27
// Modified by Zeus 1999.3.27
// 
// 

inherit ITEM;

void init();
void do_eat();

void create()
{
        set_name("醒神茶",({"tea", "cha", "xingshen cha"}));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一杯醒神茶，悠悠地冒着香气，据说这里面放了温家的特效药，可以有益于身体。\n");
                set("unit", "杯");
                set("value", 1000);
                set("remaining", 5);
                set("drink_supply", 20);
        }
	
        setup();
}

void init()
{
        add_action("do_drink", "drink");
}

int do_drink(string arg)
{

        int heal, recover, qi, e_qi, m_qi;
	
        recover = 20;
	
        if( !this_object()->id(arg) ) return 0;
        if( this_player()->is_busy() )
                return notify_fail("你上一个动作还没有完成。\n");
        if( (int)this_player()->query("water")
                >= (int)this_player()->max_water_capacity() )
                return notify_fail("你已经喝太多了，再也灌不下一滴水了。\n");

	set("value", 0);
        this_player()->add("water", (int)query("drink_supply"));
        qi = (int)this_player()->query("qi");
        e_qi = (int)this_player()->query("eff_qi");
        m_qi = (int)this_player()->query("max_qi");

// No heal effect for 醒神茶
/***

       if ( e_qi < m_qi )
       { 	
                if ( (e_qi + heal) >= m_qi )
                {
                        this_player()->set("eff_qi", m_qi);
                } else {	
                        this_player()->set("eff_qi", e_qi+heal);
                }	
       } 
***/

        if (qi < e_qi )
        {
        if ( (qi + recover) >= e_qi )
        {
                this_player()->set("qi", e_qi);
        } else
        {   
               this_player()->set("qi", qi+recover);
        }   
	}

        if( this_player()->is_fighting() ) this_player()->start_busy(2);

        add("remaining", -1);
        if ( query("remaining") )
        {
                message_vision("$N端起杯醒神茶，有滋有味地品了几口。\n"+
      		"一股香气直入心脾，$N觉得精神好多了。\n", this_player());
        } else 
        { 
                message_vision("$N端起雕花小杯，把剩下的醒神茶一饮而尽。\n"+
                "一股香气直入心脾，$N觉得精神好多了。\n", this_player());
		
                destruct(this_object());
        }

        return 1;
}
