// Room: yaofang.c
// Created by Zeus 1999.3.26
// Modified by Zeus 1999.6.10
// 
// 

inherit ROOM;

void init();
int do_zhao(string);
void delete_served(object);

void create ()
{
        set ("short", "药房");
        set ("long", @LONG
一股浓浓的药味弥漫着整个房间。这里排列着几个药柜，一些基本的
接毒药和金创药是可以在这里找到的。
LONG);
        set("area","岭南");
        set("valid_startroom", 1);

        set("exits", ([
                "west" : __DIR__"bingqifang",
        ]));

        set("objects", ([
                __DIR__"npc/wenjiadizi" : 1,
        ]));

        setup();
}
void init()
{
        add_action("do_zhao", "zhao");
}

int do_zhao(string arg)
{

        object yao;
        object me;

        me = this_player();	

        if (!arg || (arg != "yao"))
        {
                return notify_fail("你要找什么？\n");	
        }
		
        if( me->query_temp("marks/served") )
        {
                message_vision("温家弟子用很厌恶的表情对$N说：“刚刚才拿了一包药，这么快又要，真怀疑你拿药干什么！”$N不好意思的缩了缩手。\n", me);
                return notify_fail("");
        }

        write("你找到一包金创药。\n");
        me->set_temp("marks/served", 1);
        call_out("delete_served", 60, me);

        yao=new("/d/wenjia/obj/jinchuang");
        yao->move(this_player());

        return 1;
}

void delete_served(object me)
{
      if ( objectp(me) ) me->delete_temp("marks/served");
}

