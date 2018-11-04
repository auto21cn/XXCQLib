//changan city

inherit ROOM;

void create ()
{
        set ("short", "落花别院");
        set ("long", @LONG
落花别院不但因为其建在落花湖畔，更因为院内的每逢金秋的满院落
花。振眉阁就建在院中，本来那是掌门及夫人的起居所，但最近住进了两
个神秘的人，不但从来不出门，掌门夫人更是每日亲自再此把守。
LONG);
	set("valid_startroom", 1);

        set("exits", 
        ([
		"south" : __DIR__"qqlang_2",
		"north" : __DIR__"zhenmei",
	]));

        set("objects", ([
		"/kungfu/class/huanhua/huishan" : 1,
	]));

        set("outdoors", "xiao");
        setup();
	replace_program(ROOM);
}