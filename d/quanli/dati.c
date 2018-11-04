//dati.c           

#include <ansi.h>
#include <room.h>
inherit ROOM;


void create()
{
        set("short", "天下第一大堂");
	set("long", @LONG
这里是权力帮的天下第一大堂。这里和其他堂连为一体，错落有致，二者同
为古黄玉石的建筑。堂内四壁镂有权力帮主李沉舟的手迹，气势磅礴.
LONG);
	set("valid_startroom",1);
	set("exits", ([
        	"north" : __DIR__"mingge",
        	"northeast" : __DIR__"zoulang3",
        	"west" : __DIR__"liangongfang",
        	"east" : __DIR__"sleep",
        	"south" : __DIR__"zhuang",
	]));
        set("area", "权力帮");
	setup();
        replace_program(ROOM);
}
