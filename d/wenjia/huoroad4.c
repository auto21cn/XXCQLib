// Room: huoroad4.c
// Created by Zeus 1999.4.16
// Modified by Zeus 1999.4.16
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "ɽ·");
        set ("long", @LONG
�����ǵ������ֺš���ɽ·��·���ֵĶ���һЩ���컨�ݡ�
˵������Щ�������ж��ģ����ǿ�Щ�뿪����ɡ�������ɽ
·�������߻���ɽ·��
LONG);
        set("area","����");
        set("outdoors", "wenjia");

        set("exits", ([
                "east" : __DIR__"huoroad5",
                "south" : __DIR__"huoroad3",
        ]));
        setup();
        replace_program(ROOM);
}