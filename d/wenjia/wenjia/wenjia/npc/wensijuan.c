// NPC: wensijuan.c
// Created by Zeus 1999.4.7
// Modified by Zeus 1999.4.7
// 
// 

inherit NPC;

void recover_ob();

void create()
{
        set_name("温丝卷", ({ "wen sijuan"}) );
        set("gender", "男性" );
        set("age", 45);
        set("per", 15);
        set("long",
                "这位老哥经常游历在外，懂得很多江湖规矩。他是老字号中死字号的老大。\n");
        set("attitude", "friendly");

        set("qi", 2000);
        set("max_qi", 2000);
        set("jingli", 2000);
        set("max_jingli", 2000);
        set("neili", 5000);
        set("max_neili", 5000);
        set("jiali", 250);

        set("combat_exp", 2000000);

        set_skill("lphand", 180);    //施毒手法
        set_skill("force", 180);     //基本内功
        set_skill("dodge", 180);     //基本轻功
        set_skill("parry", 180);     //基本招架
        set_skill("duzun", 180);     //惟毒独尊
        set_skill("poisonk", 180);   //毒药知识
        set_skill("zhixin", 180);    //温故知新
        set_skill("qianli", 180);    //毒行千里
        set_skill("literate", 160);  //读书写字

        map_skill("force", "zhixin");
        map_skill("dodge", "qianli");
        map_skill("lphand", "duzun");
        map_skill("parry", "duzun");

	prepare_skill("lphand", "duzun");

	create_family("老字号温家", 3, "弟子");

        setup();

        set("chat_chance_combat", 40);
        set("chat_msg_combat", ({
                (: perform_action, "lphand.weiwo" :),
		(: recover_ob :)
        }) );

        add_money("gold", 10);

	carry_object("/d/wenjia/obj/chouduan")->wear();
}

void recover_ob()
{
        command("yun recover");
        return;
}
