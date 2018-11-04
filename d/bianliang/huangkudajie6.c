// huangkudajie6.c

#include <room.h>

inherit ROOM;

void create()
{       
        set("short", "黄裤大街");
        set("long", @LONG
本来五匹马宽的大街从这里往东渐渐更开阔起来，路边已经没有各种
店铺、民房了，往西边望去，看到不远就是京城最大的广场了。东边则通
向京城四大帮派之一的迷天七圣盟的总坛。
LONG);  
        set("valid_startroom",1);

        set("exits", ([
                "west" : __DIR__"guangchang",
                "east" : __DIR__"huangkudajie7",
        "north":__DIR__"hongniang-zhuang",
        ]));

        set("outdoors", "bianliang");
        set("area", "汴梁");

        setup();

        replace_program(ROOM);
}

