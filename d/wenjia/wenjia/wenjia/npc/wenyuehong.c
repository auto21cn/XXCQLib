// NPC: wenyuehong.c
// Created by Zeus 1999.4.7
// Modified by Zeus 1999.4.7
// 
// 

inherit NPC;
void recover_ob();

void create()
{
        set_name("温约红", ({ "wen yuehong", "yuehong"}) );
        set("gender", "男性" );
        set("age", 36);
        set("per", 25);
        set("long",
                "这个人看上去醉熏熏的，一看就知他是个酒鬼，人称“三缸公子”\n"+
                "他就是老字号中的活字号的老二，他也经常被派出去执行任务。\n");
        set("attitude", "friendly");

        set("qi", 2000);
        set("max_qi", 2000);
        set("jingli", 2000);
        set("max_jingli", 2000);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 100);

        set("combat_exp", 2500000);

        set_skill("lphand", 150);    //施毒手法
        set_skill("force", 150);     //基本内功
        set_skill("dodge", 150);     //基本轻功
        set_skill("parry", 150);     //基本招架
        set_skill("duzun", 150);     //惟毒独尊
        set_skill("zhixin", 150);    //温故知新
        set_skill("qianli", 150);    //毒行千里
        set_skill("poisonk", 150);   //毒药知识
        set_skill("bupangguan", 150);//袖手不旁观
        set_skill("literate", 130);  //读书写字

        map_skill("force", "zhixin");
        map_skill("dodge", "qianli");
        map_skill("lphand", "bupangguan");
        map_skill("parry", "bupangguan");

	prepare_skill("lphand", "bupangguan");

	create_family("老字号温家", 3, "弟子");

        set("chat_chance_combat", 40);
        set("chat_msg_combat", ({
		(: recover_ob :)
        }) );

        setup();

        add_money("gold", 5);

	carry_object("/d/huanhua/npc/obj/liangongfu")->wear();
}
void recover_ob()
{
        command("yun recover");
        return;
}
