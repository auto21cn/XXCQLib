//changan city

inherit ROOM;

void create ()
{
        set ("short", "大栅栏西街");
        set ("long", @LONG
这里绝对不是大栅栏一带最热闹的地方，但来来往往的人却绝对不少，因为京
城唯一的一家当铺就坐落在街的北面，虽然京城人家的生活还算不错，但因一时拮
据而光临当铺绝对是不能避免的，而纨绔子弟也经常偷家里的东西来这里变卖。借
当铺的旺气，路南的绸缎庄生意也还不错。再向西似乎比较清静，而往东则是大栅
栏的路口了，在城南无论要去哪里几乎都要经过那里。
LONG);
	set("valid_startroom", 1);

        set("exits", 
        ([
                "north" : __DIR__"dangpu",
		"west" : __DIR__"shalan-w2",
		"east" : __DIR__"shalan",
                "south" : __DIR__"chouduan",
        ]));

        set("objects", 
        ([
        ]));


        set("outdoors", "beijing");
        setup();
	replace_program(ROOM);
}