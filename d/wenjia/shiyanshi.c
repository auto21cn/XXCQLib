// Room: shiyanshi.c
// Created by Zeus 1999.4.8
// Modified by Zeus 1999.4.16
// 修改长描述。
// 

inherit ROOM;
void create ()
{
        set ("short", "实验室");
        set ("long", @LONG
这里是小字号制造药品药方的实验室，房子里放着几张长桌
子，长桌上摆着很多瓶子和药品，桌旁有许多人在那里摆弄着瓶
子药品。墙边有一张书桌，上面有文房四宝，有人在那里记录实
验过程。不时有人到北面的资料室去取资料，也有人到东面的炼
丹房制作实验品。
LONG);
        set("area","岭南");
        set("exits", ([
                "east" : __DIR__"liandanfang",
                "west" : __DIR__"dayuan",
                "north" : __DIR__"ziliaoshi",
        ]));
        setup();
        replace_program(ROOM);
}
