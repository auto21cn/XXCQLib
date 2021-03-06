// NPC: wenku.c 温哭 自创人物 负责领取大字号任务的
// Created by Zeus 1999.5.28
// Modified by Zeus 1999.6.4
// 
// 

inherit NPC;
#include <ansi.h>
void recover_ob();
void init();
int get_duyao(string arg);

void create()
{
        set_name("温哭", ({ "wen ku"}) );
        set("nickname", GRN"哭笑不得" + HIM"之哭大虾"NOR );
        set("gender", "男性" );
        set("age", 30);
        set("long",
                "温哭专门………………………………\n");
        set("attitude", "friendly");

        set("qi", 500);
        set("max_qi", 500);
        set("jingli", 500);
        set("max_jingli", 500);
        set("neili", 100);
        set("max_neili", 100);
        set("jiali", 5);

        set("combat_exp", 10000);

        set_skill("lphand", 40);    //施毒手法
        set_skill("force", 40);     //基本内功
        set_skill("dodge", 40);     //基本轻功
        set_skill("parry", 40);     //基本招架
        set_skill("zhixin", 50);    //温故知新
        set_skill("qianli", 50);    //毒行千里
        set_skill("bupangguan", 50);//袖手不旁观
        set_skill("literate", 60);  //读书写字

        map_skill("force", "zhixin");
        map_skill("dodge", "qianli");
        map_skill("lphand", "bupangguan");
        map_skill("parry", "bupangguan");

        prepare_skill("lphand", "bupangguan");

        create_family("老字号温家", 6, "弟子");

        set("chat_chance_combat", 40);
        set("chat_msg_combat", ({
		(: recover_ob :)
        }) );

        setup();
  
        add_money("silver", 5);

        carry_object("/d/wenjia/obj/redduanda")->wear();
}
void init()
{
        add_action("get_duyao","拿");
        add_action("get_duyao","take");
}

void recover_ob()
{
        command("yun recover");
        return;
}

int get_duyao(string arg)
{
        object me,ob;

        me=this_player();

        if (!arg || arg!="毒药" ) return notify_fail("你要拿什么?\n");

        if ( me->query_temp("taskda/p_given") ) {
                command("? "+me->query("id"));
                message_vision("温哭对$N说道：“不是已经给了你毒药了吗?你怎么又来向我要药!”\n",me);
                return 1;
        }
                
        if ( !(me->query("wentask/reg"))) {
                if (!(string)me->query("family") || (string)me->query("family/family_name") != "老字号温家") {
                        message_vision("温哭惊讶地对$N说：“你不是我们温家的人，怎么向我来要毒药?”\n",me);
                return 1;
                } {
                message_vision("温哭对$N说：“你要做任务吗?请先到温古那里登记，在到头儿那里领任务!”\n",me);
                return 1;}                
        }

        if ( !(me->query_temp("taskda/given")) ) {
                command("? "+me->query("id"));
                message_vision("温哭对$N说道：“你没有向头儿领任务怎么到我这里来要毒药?”\n",me);
                return 1;
        }

        if ( me->query_temp("taskda/given") ) {
                command("nod");
                message_vision("温哭对$N说道：“既然你已经向头儿领了任务，这个毒药就给你了!”\n",me);
                ob=new(__DIR__"obj/unknownp");
                ob->move(me);
                me->set_temp("taskda/p_given",1);
                if ( me->query("wentask/dafirst") ) {
                        message_vision("温哭想了一下，说：“$N，你是第一次送吧?"+RED"那个树林是一个迷宫，用这些东西走这个迷宫吧!走出来后可要记住路线呀!”\n"NOR,me);
                        message_vision("温哭给了$N一些东西。\n"NOR,me);
                        ob=new(__DIR__"obj/dashuzhi");
                        ob->move(me);
                        ob=new(__DIR__"obj/xiaoshuzhi");
                        ob->move(me);
                        ob=new(__DIR__"obj/dashucha");
                        ob->move(me);
                        ob=new(__DIR__"obj/xiaoshucha");
                        ob->move(me);
                        ob=new(__DIR__"obj/dashitou");
                        ob->move(me);
                        ob=new(__DIR__"obj/xiaoshitou");
                        ob->move(me);
                        ob=new(__DIR__"obj/dashuye");
                        ob->move(me);
                        ob=new(__DIR__"obj/xiaoshuye");
                        ob->move(me);
                }
                return 1;
        }
        return 1;
}

int accept_object(object who, object ob)
{
        if (ob->query("money_id") && ob->value() >= 10000) 
	{
          command("whisper "+who->query("id")+" 既然怎么会做，告诉你，走迷宫的顺序是se s e ne sw n w nw。可别告诉头儿。");
          return 1;
	}

        if (ob->query("money_id") && ob->value() >= 500) 
	{
          command("nod "+who->query("id"));
          command("whisper "+who->query("id")+" 告诉你，走对方向你会受一点伤。");
          return 1;
	}

        if (ob->query("money_id") && ob->value() >= 300) 
	{
          command("nod "+who->query("id"));
          command("whisper "+who->query("id")+" 告诉你，走迷宫的顺序实际上是8个方向各有一个位置。");
          return 1;
	}
	return 0;
}
