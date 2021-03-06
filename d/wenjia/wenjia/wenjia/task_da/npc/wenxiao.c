// NPC: wenxiao.c 温笑 自创人物 负责领取大字号任务的
// Created by Zeus 1999.5.28
// Modified by Zeus 1999.5.28
// 
// 

inherit NPC;
#include <ansi.h>
void recover_ob();

void create()
{
        set_name("温笑", ({ "wen xiao"}) );
        set("nickname", GRN"哭笑不得" + HIM"之笑大虾"NOR );
        set("gender", "男性" );
        set("age", 30);
        set("long",
                "温笑专门………………………………\n");
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


void recover_ob()
{
        command("yun recover");
        return;
}

int accept_object(object who,object ob)
{
        object room;
        
        if ( who->query_temp("taskda/done") ) {
                command("? "+who->query("id"));
                message_vision("温笑疑惑地对$N说：“你不是已经交了毒药了吗,怎么又跑来了?”\n",who);
                return 1;
        }

        if ( (string)ob->query("name","不知名毒药") && who->query_temp("taskda/given")
             && who->query_temp("taskda/p_given")) {
                command("nod");
                command("thank "+who->query("id"));
                message_vision("温笑对$N说：“收到了，从这里出去，到头儿那里领功吧!\n",who);
                who->set_temp("taskda/done",1);
                destruct(ob);
                return 1;
        } else        	
        {
                command("say 你给我这个干什么?");
                return 0;
        }

}
