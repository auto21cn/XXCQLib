// NPC: baiqingyi.c 白青衣
// Created by Atlus 1999.10.4
// Modified by Atlus 1999.10.4
// 

#include <ansi.h>

inherit NPC;

void recover_ob();

void create()
{
        set_name("白青衣", ({ "bai qingyi","bai"}) );
        set("gender", "男性" );
        set("age", 40);
        set("per", 30);
        set("long",
                "他看上去已是中年，双鬓泛银。\n他的双脚之间,却琐着一条粗如人臂,黑中泛紫,二尺来长的铁链!\n");
        set("attitude", "friendly");

        set("qi", 2300);
        set("max_qi", 2300);
        set("jingli", 2300);
        set("max_jingli", 2300);
        set("neili", 2500);
        set("max_neili", 2500);
        set("jiali", 50);

        set("combat_exp", 750000);

       
        set_skill("force", 130);         //基本内功
        set_skill("dodge", 200);         //基本轻功
        set_skill("parry", 130);         //基本招架
        set_skill("literate", 100);      //读书写字
        set_skill("sword", 130);         //基本剑术
        set_skill("feiyu-jian", 130);    //飞鱼剑法
        set_skill("youyu-quan", 130);    //游鱼拳
        set_skill("fish-steps", 200);    //鱼形步法
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
        carry_object("/d/feiyu/obj/changjian")->wield();
}



void recover_ob()
{
        command("yun recover");
        return;
}
