// Room: bingqifang.c
// Created by Atlus 1999.7.21
// Modified by Atlus 1999.7.21
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "������");
        set ("long", @LONG
��������ʮ�˰�������У�����������ڼ��ϣ�������ר�������İ�
�����������Ӵ���ý��򵶣�����һ����ӿ����������ҵ��ʺ��Լ��ı�
���������߾��Ƕ����䳡��
LONG);
        set("area","����");
        set("valid_startroom", 1);

        set("exits", ([
                  "south" : __DIR__"dongwuchang",
                  "north" : __DIR__"zhangfang",   
        ]));

        set("objects", ([
                "/clone/weapon/changjian" : 2,
                "/clone/weapon/dandao" : 2,
        ]));

        setup();
        replace_program(ROOM);
}