//sleep。c  by god

#include <room.h>

inherit ROOM;

void create()
{	
        set("short", "卧室");
	set("long", @LONG
这是一间温馨的卧室。 
LONG);	
	set("valid_startroom",1);
	set("no_steal", "1");
	set("no_fight", "1");
	set("sleep_room",1);
        set("exits", ([ "west" : __DIR__"dati",
        ]));
	setup();
	replace_program(ROOM);
}
