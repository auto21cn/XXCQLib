// zhuangmen.c
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",GRN"庄门"NOR);
        set("long",
"你转过一丛茂密的花丛, 猛然间, 只见一座红檐绿瓦, 小巧玲珑的庄院矗\n"
"利在灿澜的花丛中。庄门大匾上赫然写着「"BLINK HIY"曼陀山庄"NOR"」四个金光闪闪的大字。\n"
);
       set("outdoors","姑苏慕容");
       set("exits",([
        "west" : __DIR__"ab",
	"south" : __DIR__"qianyuan",
	"north" : __DIR__"hc",
]));
        setup();                                                   
        replace_program(ROOM);
}
