//chanting.c
inherit ROOM;
void create()
{
        set("short","厨房");
        set("long",@LONG
这是一间雅致的大厅，厅上摆着几张紫檀木大桌。桌上银制餐具一应
俱全，桌边一溜犁花木椅。厨师们在展示各自的烹饪绝活。整个房间弥漫
着令人垂涎欲滴的菜香。
LONG );
        set("exits",([
            "west" : __DIR__"caodi",
        ]));
        set("objects",([
             __DIR__"npc/nanpu" : 1,
        ]));
	set("valid_startroom",1);
        setup();
        replace_program(ROOM);
}
