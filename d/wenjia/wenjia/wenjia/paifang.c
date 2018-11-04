// Room: paifang.c
// Created by Zeus 1999.3.26
// Modified by Zeus 1999.6.10
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "牌坊");
        set ("long", @LONG
这是立在山路上的一个大牌坊，牌坊上写着红色大字“岭南老字号温
家”从这里上去就是温家的总堂了。你想起温家在江湖中的“事迹”，不
禁打个冷颤。“还是不要去吧”的念头在你心里升起。
LONG);
        set("area","岭南");
        set("outdoors", "wenjia");
        set("valid_startroom", 1);

        set("exits", ([
                "northup" : __DIR__"square",
                "south" : __DIR__"shanlu4",
        ]));

        setup();
        replace_program(ROOM);
}
