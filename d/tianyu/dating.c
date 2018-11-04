// Room: 大厅
// Date: by godzilla 1999.11.18


inherit ROOM;

void create()
{
	set("short", "大厅");
	set("long", @LONG
大厅布局简单，只有几张简陋的桌椅，墙上却挂满了字画，看来
主人是个喜欢书画之人。正中的紫檀木的茶几上摆放着茶壶，茶壶里
正冒着热气。
LONG );
	set("exits", ([
	        "south" : __DIR__"qianyuan", 
		"west" : __DIR__"qixuant",
		"east" :__DIR__"xiuxishi",
        "north" :__DIR__"zhangfang",
	]));
	set("objects",([
                 __DIR__"npc/zhuyou" : 1,
	        ]));
	setup();
	replace_program(ROOM);
}
