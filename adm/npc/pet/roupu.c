// 肉铺 ROOM
// By 山猫Adx @ snow 99-12-12

inherit ROOM;

void create()
{
	set("short", "肉铺");
	set("long", @LONG
这是一间不大的肉铺，老板大胡子屠夫坐在案板后面的躺椅上，有个
伙计正在忙碌着，案板上放在两扇猪肉。案板上面的挂钩上挂满了切
好的猪肉，看来没什么生意。
LONG );

	set("exits", ([
         "south"  :  "/d/room/playtown/guandao6",
	]));

	set("objects", ([
		__DIR__"tufu":1,
        __DIR__"petowner":1,
	]) );
	setup();
	replace_program(ROOM);
}
