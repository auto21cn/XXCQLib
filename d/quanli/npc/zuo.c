// zuochangsheng.c ����	

#include <ansi.h>

inherit NPC;

void create()
{
	set_name("����",({"zuo changsheng","zuo"}));
	set("long",
	"�������껼һ�漲���������ã���ƾ������ǿ���������Լ�ҽ���߳���ҽ\n"
	"����ǿ�����������������;�����\n"
	"����ò��㣬������㣬��ֹ������㡣\n");
	set("party/rank",HIC"һ����ħ"NOR);
    set("accept",2000);
	set("party/party_name","Ȩ����");
	set("age",48);
	set("gender","����");
	set("autitude","friendly");
	set("str",25);
	set("con",22);
	set("dex",31);
	set("int",27);
	
	set("max_qi",3000);
	set("max_jing",2000);
	set("neili",3000);
	set("max_neili",3000);
	set("jiali",50);
	
	set("combat_exp",1500000);
	set("score",2000);
	
	set("inquiry",([
		"Ȩ����":"��ԸΪȨ���︰�����𣬾��Ҿ�����",
		]));
			
	set_skill("dodge",180);
	set_skill("force",180);
	set_skill("sword",200);
	set_skill("unarmed",120);
	
	setup();
	
	carry_object("/clone/misc/cloth")->wear();

	
}
#include "quanli.h"

void init()
{
::init();
add_action("do_skills","skills");
add_action("do_skills","cha");
add_action("do_join","join");
}
int do_skills(string arg)
{
        object ob ;
        ob = this_player () ;
        if( !arg || arg!="qu" )
                return 0;
        if(wizardp(ob))  return 0;
        if (ob->query("party/party_name") != "Ȩ����")
        {
                message_vision("$Nҡ��ҡͷ��\n",this_object());
                command("tell "+ob->query("id")+" ����Ȩ������˲��ܲ쿴��\n"); 
                return 1;
        }
    command("tell "+ob->query("id")+" �����е��书���£�\n"+
"������ɽĿǰ��ѧ���ļ���       \n"+
"  �����Ṧ (dodge)                         - ��ɲ� 200/    0        \n"+
"  �����ڹ� (force)                         - ��ɲ� 200/    0        \n"+
"  �����м� (parry)                         - ��ɲ� 200/    0        \n"+
"  �������� (sword)                         - ��ɲ� 220/    0        \n"+
"  ����д�� (literate)                      - �����ž� 180/    0       0/    0  \n"+
"������֮�� (wuxing-jian)                   - �������� 220/    0       0/    0  \n");
   return 1;
}