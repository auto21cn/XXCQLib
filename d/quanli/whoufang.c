//liangongfang��c          

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "�շ�");
	set("long", @LONG
LONG);
        set("valid_startroom",1);
	set("exits", ([
                        "south" : __DIR__"biandian1",
	]));
        set("area", "Ȩ����");
        set("objects",([
          __DIR__"npc/sha" : 1,
        ]));
	setup();
	replace_program(ROOM);
}
