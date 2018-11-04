// Room: shanlu2.c
//Created by Atlus 1999.7.21
// Modified by Atlus 1999.7.21
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "山路");
        set ("long", @LONG
脚下虽然是塌实的青石路，可是由于常年的雾水弥漫，青石路反而觉
得有点滑，这里已经是半山腰了，你感到越来越冷。从这里再向东攀上去
就是著名的“人止关”了。这里可以看见一些飞鱼弟子从上面下来，你无
意之间向下望了望，只觉得有些头昏,不过还是看到了几座小房。
LONG);
        set("area","飞鱼");
        set("outdoors", "feiyu");

        set("objects", ([
                __DIR__"npc/feiyudizi" : 2,
        ]));

        set("exits", ([
                "westdown" : __DIR__"shanjianxiaowu",
                "eastup" : __DIR__"renzhiguan",
        ]));
        setup();
        replace_program(ROOM);
}
