// Room: yaotian1.c
// Created by Zeus 1999.4.8
// Modified by Zeus 1999.4.8
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "ҩ��");
        set ("long", @LONG
������Χ����һ������أ�����������ֵĲ�����ʳ����
��һЩ���ӷǳ���ֵ�ֲ�����������ֵ����¼�С�ֺ�����
�춾ҩ��ԭ�ϡ�����Ȼ���������˸ߵ��������·�ˡ�
LONG);
        set("area","����");
	set("valid_startroom", 1);
        set("outdoors", "wenjia");

        set("exits", ([
                "north" : __DIR__"yaotian"+(random(6)+1),
                "south" : __DIR__"yaotian"+(random(6)+1),
                "east" : __DIR__"yaotian"+(random(6)+1),
                "west" : __DIR__"yaotian2",
        ]));
        setup();
        replace_program(ROOM);
}