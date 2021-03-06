// Room: /d/shaolin/shanmen.c
// Date: YZC 96/01/19

#include <room.h>
inherit ROOM;

void create()
{
    set("short", "少林寺");
    set("long", @LONG
一个巨大的牌坊横架在两片山壁之间，牌坊正上方刻着三个斗大的字
『少林寺』。字迹有些剥落，看上去年代久远。一位二十来岁的年轻僧人
守在山门两侧。左侧立着一块石碑。
LONG );
	set("valid_startroom", 1);
    set("exits", ([
        "eastup" : __DIR__"shijie8",
        "west" : __DIR__"shijie7",
    ]));
    set("outdoors", "shaolin");
    set("objects",([
		"/kungfu/class/shaolin/tongren": 1
    ]));
    setup();
}

int valid_leave(object me, string dir)
{
    object *inv;
	mapping myfam;
    int i;

    if (me->query("gender") == "女性" && dir == "eastup" ) {
        if(objectp(present("tong ren", environment(me))))
            return notify_fail("铜人伸手拦住你白眼一翻说道：千年以来，少林向不许"
                "女流擅入。" + RANK_D->query_respect(me) +"\n请下山去吧，免得"
                "自讨没趣。\n");
    }

    myfam = (mapping)me->query("family");

    if ((!myfam || myfam["family_name"] != "少林派" ) && dir == "eastup") {
        inv = all_inventory(me);
        for(i=sizeof(inv)-1; i>=0; i--)
            if(inv[i]->query("weapon_prop") && (inv[i]->query("equipped")))
                if(objectp(present("tong ren", environment(me))))
                    return notify_fail("铜人拦住你说道：这位" +
                        RANK_D->query_respect(me) + "请放下兵刃。少林千年的"
                        "规矩，外客\n不得持兵刃上山。\n");
    }
    return ::valid_leave(me, dir);
}
