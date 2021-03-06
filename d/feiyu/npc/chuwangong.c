// NPC: chuwangong.c 飞鱼四小之一、初级师父  楚晚弓
// Created by M.A.D. 1999.7.21
// Modified by M.A.D. 1999.7.21
// 
// 原著人物!  特殊武功--游鱼拳法，飞鱼剑法

#include <ansi.h>

inherit NPC;

void recover_ob();

void create()
{
        set_name("楚晚弓", ({ "chu wangong","chu"}) );
        set("nickname", MAG"飞鱼四小"NOR );
        set("gender", "男性" );
        set("age", 20);
        set("per", 10);
        set("long",
                "楚晚弓是“飞鱼塘”飞鱼山庄庄主沈星南的徒弟之一，飞鱼四小之一,他主要练飞鱼剑法。\n他看上去大约二十岁，十分精明的样子。\n");
        set("attitude", "friendly");

        set("qi", 1000);
        set("max_qi", 1000);
        set("jingli", 800);
        set("max_jingli", 800);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 50);

        set("combat_exp", 100000);

        set_skill("cuff", 60);          //基本拳法
        set_skill("force", 60);         //基本内功
        set_skill("dodge", 60);         //基本轻功
        set_skill("parry", 60);         //基本招架
        set_skill("literate", 40);      //读书写字
        set_skill("feiyu-jian", 60);   //飞鱼剑法
        set_skill("youyu-quan", 60);    //游鱼拳
        set_skill("fish-steps", 60);    //鱼形步法
        set_skill("tianlongforce", 60); //天龙功
        
        create_family("飞鱼塘", 5, "弟子");

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
