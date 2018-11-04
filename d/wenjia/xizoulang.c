// Room: xizoulang.c
// Created by Zeus 1999.3.26
// Modified by Zeus 1999.4.3
// Modified Long
// 

inherit ROOM;
void create ()
{
        set ("short", "西走廊");
        set ("long", @LONG
这是西走廊，走廊左边有一个池塘，几条鱼儿摆动着尾巴在
水里畅游。向西边望去，那里传来吆喝声，那是西练武场。东边
是那个充满肃杀气氛的前厅。
LONG);
        set("area","岭南");
        set("outdoors", "wenjia");

        set("exits", ([
                "east" : __DIR__"qianting",
                "west" : __DIR__"xilianwuchang",
        ]));
        setup();
        replace_program(ROOM);
}
