// NPC: cangjian.c 谷藏剑
// Created by Atlus 1999.10.4
// Modified by Atlus 1999.10.4
// 

#include <ansi.h>

inherit NPC;

void recover_ob();

void create()
{
        set_name("谷藏剑", ({ "gu cangjian","gu"}) );
        set("nickname", MAG"藏剑老人"NOR );
		set("gender", "男性" );
        set("age", 60);
        set("per", 20);
        set("long",
                "他身着黑袍，白发苍苍，双肩瘦削，直耸双颧，双手一直藏在袖子里。\n");
        set("attitude", "friendly");

        set("qi", 2300);
        set("max_qi", 2300);
        set("jingli", 2300);
        set("max_jingli", 2300);
        set("neili", 2500);
        set("max_neili", 2500);
        set("jiali", 50);

        set("combat_exp", 800000);

       
        set_skill("force", 130);         //基本内功
        set_skill("dodge", 130);         //基本轻功
        set_skill("parry", 130);         //基本招架
        set_skill("literate", 100);      //读书写字
        set_skill("sword", 180);         //基本剑术
        set_skill("feiyu-jian", 180);    //飞鱼剑法
        set_skill("youyu-quan", 130);    //游鱼拳
        set_skill("fish-steps", 130);    //鱼形步法
        set_skill("tianlongforce", 130); //天龙功
        set_skill("cuff", 130);          //基本拳法

        map_skill("cuff", "youyu-quan");
		map_skill("force", "tianlongforce");
		map_skill("sword", "feiyu-jian");
		map_skill("dodge", "fish-steps");
		
		create_family("飞鱼塘", 3, "弟子");

        setup();

        set("chat_chance_combat", 40);
        set("chat_msg_combat", ({
		(: recover_ob :)
        }) );

        add_money("silver", 10);

        carry_object("/d/feiyu/obj/jinshenfu")->wear();
        carry_object("/d/feiyu/obj/changjian")->wield();   //双手是剑不会写：），先从权了
}



void recover_ob()
{
        command("yun recover");
        return;
}
