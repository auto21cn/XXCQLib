//By adx by snow 99-12-5

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short",WHT"女休息室"NOR);
	set("long",
"这是武馆的女休息室，武馆的女弟子一般都在这里睡觉，\n"+
"睡一觉"+HIC"(sleep)"NOR+"可以恢复精、气，但连续的睡觉则不能全部恢复。\n"
);
	set("exits", ([
	"north"  : __DIR__"houyuan",
	]));

	set("sleep_room","1") ;
    
	setup();
	replace_program(ROOM);
}
