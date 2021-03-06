// heiyiranfang.c  by winder

#include <room.h>

inherit ROOM;

void create()
{	
	set("short", "黑衣染坊");
	set("long", @LONG
黑衣染坊是唐朝开元时期建造的，因其创始人冉黑衣而得名。直到现
在这家染坊兴旺更胜从前，你一走进来，就看到几十个人在大院子里忙忙
碌碌，浸布的、洗布的、染布的、晾布的各自忙着。你要是有布要染，尽
管来这里，一定不会失望的。
LONG);	
	set("valid_startroom",1);

	set("exits", ([
		"east" : __DIR__"huangshanjie3",
	]));

	set("objects", ([
		__DIR__"npc/yiran" : 1,
	]));

	set("area", "汴梁");

	setup();

	replace_program(ROOM);
}