// Room: bingqifang.c
// Created by Atlus 1999.7.21
// Modified by Atlus 1999.7.21
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "兵器房");
        set ("long", @LONG
兵器房里十八般兵器都有，整齐地排列在架上，可能有专人整理的吧
。飞鱼塘弟子大多用剑或刀，所以一般弟子可以在这里找到适合自己的兵
器。向南走就是东练武场。
LONG);
        set("area","飞鱼");
        set("valid_startroom", 1);

        set("exits", ([
                  "south" : __DIR__"dongwuchang",
                  "north" : __DIR__"zhangfang",   
        ]));

        set("objects", ([
                "/clone/weapon/changjian" : 2,
                "/clone/weapon/dandao" : 2,
        ]));

        setup();
        replace_program(ROOM);
}
