
inherit ROOM;
void create()
{
        set("short","西方大厅");
        set("long",@LONG
 你已经来到了洞府的中心地带。
LONG );
        set("valid_startroom",1);
        set("class","权力帮");
        set("exits",([
                "east" : __DIR__"zoulang1",
                 "enter" : __DIR__"biandian1",
        ]));
        set("objects",([
        ]));
//        set("no_clean_up"， 0);
        set("objects",([
          __DIR__"npc/dujue" : 1,
    ]));
        setup();
        replace_program(ROOM);
}

