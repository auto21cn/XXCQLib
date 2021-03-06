// Room: cailiaofang.c
//Created by Atlus 1999.7.21
// Modified by Atlus 1999.7.21
// 

inherit ROOM;

void init();
int do_zhao(string);
int do_open(string arg);
void delete_served(object);

void create ()
{
        set ("short", "材料房");
        set ("long", @LONG
这里是飞鱼塘的杂务房间。光线十分昏暗，只点了一根蜡烛。这里有
很多的瓶瓶罐罐和大柜子，一些瓶罐里面放着已经磨成粉末的药材。还有
一些乱七八糟的东西胡乱堆在墙角在这里应该可以找到一些有用的东西(zhao)。
LONG);
        set("area","飞鱼");
        set("valid_startroom", 1);

        set("exits", ([
                "south" : __DIR__"xiwuchang",
        ]));

        set("objects", ([
                       __DIR__"npc/guanshi" : 1,
        ]));

		setup();
}

void init()
{
        add_action("do_zhao", "zhao");
	add_action("do_open", "open");
}

int do_zhao(string arg)
{

        object yaocai;
        object me;

        me = this_player();

        if ( !arg || arg != "yaocai")
        {
                return notify_fail("这里可以找到的都是些药材！\n");	
        }
		
        if( me->query_temp("mark") )
        {
                message_vision("$N找遍了整个房间，好象没有什么发现。\n", me);
                return notify_fail("");
        }

        write("你找到一包药材。\n");
        me->set_temp("mark", 1);
        call_out("delete_served", 30, me);

         yaocai=new(__DIR__"obj/yaocai");
        yaocai->move(this_player());

        return 1;
}

int do_open(string arg)
{
        object me;
        if(!arg || arg=="")
        {
                write("你要打开什么？\n");
                return 1;
        }
        if( arg == "guizi" || arg == "柜子" || arg == "gui")
        {
        me = this_player();
        message_vision("$N打开了柜子，一阵发霉的臭味扑鼻而来，$N屏息细看，发现了一条通向密室的路。\n", me);
        if( !query("exits/northup") ) {
        set("exits/northup", __DIR__"mishi");
        call_out("close_path", 3);
        }
        return 1;
        }
        else
        {
                write("无法打开"+arg+"\n");
                return 1;
        }
}
void close_path()
{
        if( !query("exits/northup") ) return;
        message("vision",
"嘎的一声，暗门又关上了。\n",
                this_object() );
                delete("exits/northup");
}

void delete_served(object me)
{
      if ( objectp(me) ) me->delete_temp("mark");
}
