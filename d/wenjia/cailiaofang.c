// Room: cailiaofang.c
// Created by Zeus 1999.4.8
// Modified by Zeus 1999.4.10
// 修改长描述。
// 

inherit ROOM;
void create ()
{
        set ("short", "材料房");
        set ("long", @LONG
这里是小字号存放材料的房间。光线十分昏暗，只点了一只
蜡烛。这里有很多的瓶瓶罐罐，一些瓶罐里面放着已经磨成粉末
的药材。还有一些透明的瓶子里放这一些虫子，看起来十分恶心。
看了，你几乎要吐出来。这里只有向上的一个出口，到制毒室。
LONG);
        set("area","岭南");
	set("valid_startroom", 1);
        set("exits", ([
                "up" : __DIR__"zhidushi",
        ]));
        setup();
        replace_program(ROOM);
}
