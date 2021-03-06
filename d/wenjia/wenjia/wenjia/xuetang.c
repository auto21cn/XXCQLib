// Room: xuetang.c
// Created by Zeus 1999.3.26
// Modified by Zeus 1999.7.22
// 
// 

inherit ROOM;

void create ()
{
        set ("short", "学堂");
        set ("long", @LONG
未走入学堂就听到了隐隐约约的读书声，走进来之后读书声变的很大。
这种清脆的童声是非常好听的。这里坐着的大部分都是小孩，有一些是大
人，他们就象鹤立鸡群一样，真是“少小不努力，老大图伤悲”。墙壁上
贴的是学规(xuegui)。
LONG);
        set("area","岭南");
        set("valid_startroom", 1);

        set("exits", ([
                "west" : __DIR__"donglianwuchang",
                "south" : __DIR__"cangshufang",
        ]));

        set("item_desc", ([
             "xuegui" : "日讲经书三起，日看纲目数页。"  
                        "\n通晓时务物理，参读古文诗赋。" 
                        "\n读书必须过笔，会课按时蚤完。"
                        "\n夜读仍戒晏起，疑误定要力争。\n"
        ]));

        set("objects", ([
               __DIR__"npc/wenkongzi": 1,
        ]));

        setup();
}

int valid_leave(object me, string dir)
{
        object obj;
        
        me=this_player();

        if (dir == "south" && ((int)me->query("wentask/done") <= 150 || (int)me->query_skill("literate")<=30 )) {
                if (objectp(present("dizi", environment(me)))){
                        message_vision("一名温家弟子对$N说道：你还没有进藏书房读书的资格，请回去吧!\n", me);
                        return notify_fail("");
                } else {
                obj=new("/d/wenjia/npc/wenjiadizi");
                obj->move("/d/wenjia/xuetang");
                message_vision("一名温家弟子从藏书房走出来对$N说道：你还没有进藏书房读书的资格，请回去吧!\n", me);
                return notify_fail("");
                }
        }

        return ::valid_leave(me, dir);
}
