// Room: caodi.c
// Created by Zeus 1999.4.8
// Modified by Zeus 1999.4.10
// �޸ĳ�������
// 

inherit ROOM;
void create ()
{
        set ("short", "�ݵ�");
        set ("long", @LONG
������С�ֺŽ���Ⱥǰ���һƬ�ݵء��ݳ���ʮ�ֵð�����
���͵�ʮ�ֺÿ�����������С�ֺŵĻ���ң����߾ͻص�����
Ƭ���֡�
LONG);
        set("area","����");
        set("outdoors", "wenjia");

        set("exits", ([
                "south" : __DIR__"shulin2",
                "north" : __DIR__"huikeshi",
        ]));
        setup();
        replace_program(ROOM);
}