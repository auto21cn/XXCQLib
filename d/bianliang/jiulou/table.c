// xiongzhang.c 熊掌

inherit ITEM;

void create()
{
        set_name("酒席", ({"table"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "冰火熊掌(xiongzhang)    鲍    鱼(baoyu)      燕    窝(yanwo)\n"+
                            "鱼    翅(yuchi)         海    参(haishen)    龙 凤 汤(tang)\n"+
                            "女儿红酒(nverhong)      陈年花雕(huadiao)    东坡肘子(zhouzi)\n"+
                            "珍 珠 糕(gao)           烤 乳 猪(ruzhu)      猴    脑(hounao)\n");
                set("unit", "桌");
                set("value", 500);
                set("no_get", "你在赴宴，还是文明点吧。\n");    
                set("fd_count", 300);
                set("wt_count", 150);
        }
}

void init()
{
        add_action("do_jia", "jia");
        add_action("do_drink", "drink");
        add_action("do_sit", "sit");
}

int do_sit(string arg)
{       object me;
        me = this_player();
         if( !arg || arg=="" ) {
                return notify_fail("你要坐在哪里？指令格式：sid chair\n");
                }
        if (me->query_temp("marks/坐"))return notify_fail("你已经坐下了。\n");
         if( arg=="chair"
		&&( (me->query_temp("marks/赴宴"))
		|| (me->query_temp("marks/主人")) )){
                message_vision("$N找了个比较舒服的坐位坐了下来。\n", this_player());
                me->set_temp("marks/坐",1);
                return 1;}
                 else{
                 message_vision("$N想找个坐位坐下来吃东西，却发现自己没有被邀请赴这次宴会，顿时羞得满脸通红。\n", this_player());return 1;
                }
}

int do_jia(string arg)
{       object me;
        me = this_player();
        
        if (me->query_temp("marks/坐")){
         if( !arg || arg=="" ) 
                message_vision("$N拿起筷子左看右看，想着该挟什么吃才好。\n", this_player());
         if( (int)this_player()->query("food") >= (int)this_player()->max_food_capacity() )
                return notify_fail("你已经喝得太饱了。\n");
         if(query("fd_count") < 1){
         message_vision("$N将筷子抻到盘子里挟东西吃，却发现盘子里的菜已经被吃光了。\n", this_player());return 1;}
         if( arg=="xiongzhang")
                message_vision("$N挟起冰火熊掌有滋有味地嚼了几口，大声赞倒：好香！好香！\n", this_player());
         if( arg=="baoyu")
                message_vision("$N挟起一块鲍鱼有滋有味地嚼了几口。\n", this_player());
         if( arg=="yanwo")
                message_vision("$N挟起一块燕窝有滋有味地嚼了几口。\n", this_player());
         if( arg=="yuchi")
                message_vision("$N挟起一块鱼翅有滋有味地嚼了几口，砸巴了几下嘴，说道：嗯！不错！不错！\n", this_player());
         if( arg=="haishen")
                message_vision("$N挟起一片海参有滋有味地嚼了几口。\n", this_player());
         if( arg=="zhouzi")
                message_vision("$N抓起东坡肘子有滋有味地啃了几口，赞道：肥美而不腻，不错！不错！\n", this_player());
         if( arg=="gao")
                message_vision("$N挟起一块珍珠糕有滋有味地吃了几口。\n", this_player());
         if( arg=="ruzhu")
                message_vision("$N撕下一大块烤乳猪大嚼了几口，弄得满嘴都是油。\n", this_player()); 
         if( arg=="hounao")
                message_vision("$N拿起汤匙小心翼翼舀了一匙猴脑尝了尝，大声说道：好味道！\n", this_player());
         me->add("food", 5);
         add("fd_count", -1);
         return 1;}
                 else return notify_fail("你还没坐下来。\n");
}

int do_drink(string arg)
{       object me;
        me = this_player();
        
        if (me->query_temp("marks/坐")){
         if( !arg || arg=="" ) 
                message_vision("$N左看右看，想着该喝点什么才好。\n", this_player());
         if( (int)this_player()->query("water") >= (int)this_player()->max_water_capacity() )
                return notify_fail("你已经喝得太饱了。\n");
         if(query("wt_count") < 1){
         message_vision("$N拿起酒壶准备替自己斟杯酒，发现壶里的酒已经被吃光了。\n", this_player());
                return 1;}
         if( arg=="tang")
                message_vision("$N拿起汤匙舀了一匙龙凤汤喝了几口。\n", this_player());
         if( arg=="yuchi")
                message_vision("$N拿起汤匙舀了一匙鱼翅汤有滋有味地喝了几口，砸巴了几下嘴，说道：嗯！不错！不错！\n", this_player());
         if( arg=="nverhong")
                message_vision("$N端起酒杯大声说道：来来来！今儿大家喝个高兴，我先饮为敬！说完一仰脖子把杯中的女儿红酒咕嘟吞了下去。\n", this_player());
         if( arg=="huadiao")
                message_vision("$N端起酒杯大声说道：来来来！今儿大家喝个高兴，我先饮为敬！说完一仰脖子把杯中的陈年花雕酒咕嘟就吞了下去。\n", this_player());
         this_player()->add("water",10);
         add("wt_count", -1);
         return 1;}
                else return notify_fail("你还没坐下来。\n");

}
