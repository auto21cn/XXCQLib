//zoulang1��c              

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
	set("short", "Ȩ��¥����");
	set("long", @LONG
LONG);
	set("valid_startroom",1);
	set("area","����");
	set("exits", ([
                        "down" : __DIR__"quanlilou2",
	]));
        replace_program(ROOM);
	setup();
}
