// Room: /d/wizard/wizard_room.c

#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
	set("short", HIW "巫师公会" NOR);
	set("long", @LONG
这里是小雪初晴的巫师公会办公大厅，十分宽敞，大理石的地面整洁
如新，洁白的墙面，一盏豪华的大吊灯将这里照的十分明亮，巫师们在这
里交流，讨论。
    北面是会议室。
    东边是巫师工作进度报告室。
    西边是一间通向各地的通道。
    南边是小雪初晴的新闻发布中心。
从高大的落地窗看出去，只见外面是一片绿色的草地，远处是碧波荡漾的
湖水。
LONG );

	set("exits", ([
  	"north" : __DIR__"huiyishi",
	"east"  : __DIR__"lpcroom",
	"south" : __DIR__"newsroom",
	"west"  : __DIR__"exitroom",	
 ]));

	set("valid_startroom", 1);
	set("no_clean_up", 0); 
	set("objects",([
                "/clone/food/jitui":1,
	]));
        set("sleep_room", 1);
        set("no_fight", 1);
	setup();
	call_other("/clone/board/wiz_b", "???");
}

