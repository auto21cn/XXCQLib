// heibujie7.c  by winder

#include <room.h>

inherit ROOM;

void create()
{       
        set("short", "黑布街");
        set("long", @LONG
这里是黑布街，向南便可到菜市口，西边是一家钱庄，可以听到叮
叮当当的金银声音。

LONG);  
//      set("valid_startroom",1);
//      set("no_steal", "1");
//      set("no_fight", "1");
//      set("outdoors", "bianliang");
        set("exits", ([
                "north" : __DIR__"heibujie6",
                "south" : __DIR__"caishikou",
//              "west" : __DIR__"mingliquan",
                "west" : __DIR__"qianzhuang",
        ]));
//      set("objects", ([
//              "/clone/weapon/changjian" : 4]));
        set("area", "汴梁");
        setup();
        replace_program(ROOM);
}

