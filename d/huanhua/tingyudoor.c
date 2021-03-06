//changan city

inherit ROOM;

void create ()
{
        set ("short", "听雨楼门前");
        set ("long", @LONG
听雨楼是浣花剑庐接待外客的地方，现在你就站在听雨楼的楼下，仰
望阁楼，飞檐雕花，颇为精美，阳光曜处，檐角闪出刺眼的光芒。四代弟
子、十年会之一的秋月在这里接待着来访的客人。
LONG);
	set("valid_startroom", 1);

        set("exits", 
        ([
		"enter" : __DIR__"tingyulou",
		"east" : __DIR__"qianroad2",
	]));

        set("objects", ([
                 __DIR__"npc/qiuyue": 1,
	]));

        set("outdoors", "xiao");

        setup();
}

int valid_leave(object me, string dir)
{
	mapping myfam;

	myfam = (mapping)me->query("family");

	if ((!myfam || myfam["family_name"] != "浣花剑派" ) && dir == "enter" )
	{
        	if(objectp(present("qiu yue", environment(me))))
        		return notify_fail("秋月伸手拦住你谦声说道：听雨楼乃少庄主待客之处，外人不得入内，\n"
			+ RANK_D->query_respect(me) +"若是为拜师而来，就去南、北偏院吧。\n");
	}

	return ::valid_leave(me, dir);
}