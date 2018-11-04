// Room: paifang.c
// Created by Zeus 1999.3.26
// Modified by Zeus 1999.3.26
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "牌坊");
        set ("long", @LONG
这是立在山路上的一个大牌坊，牌坊上写着红色大字“岭南
老字号温家”从这里上去就是温家的总堂了。你想起温家在江湖
中的“事迹”，不禁打个冷颤。“还是不要去吧”的念头在你心
里升起。
LONG);
        set("area","岭南");
        set("outdoors", "wenjia");

        set("exits", ([
                "up" : __DIR__"square",
        ]));
        setup();
        replace_program(ROOM);
}
