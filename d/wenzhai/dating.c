// dating.c 大厅
// mlf设计,lks编程

#include <ansi.h>

inherit ROOM;

void create()
{
	set("short","大厅");
	set("long",
	"这里是温府的大厅，左右各一排英雄席，正中一张黑色大桌，两边端
放着两把太师椅。墙上挂着一幅笔里苍劲的大字“通文 精武”显然出自
名家之手，让人肃然起敬。左右各有小门通往偏厅和厢房。\n"NOR
     	);
     	set("valid_startroom",1);
	set("exits",([
     		"west"  : __DIR__"xiting",
     		"east"  : __DIR__"dongting",
     		"north"   : __DIR__"caodi",
     		"south" : __DIR__"huayuan",
     	]));
     	setup();
     	replace_program(ROOM);
}
