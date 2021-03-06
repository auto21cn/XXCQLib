// NPC: chuwangong.c 沈星南，高级师父  
// Created by Atlus 1999.9.24
// Modified by Atlus 1999.9.24
// 
// 原著人物!  特殊武功--飞鱼剑法

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void recover_ob();

void create()
{
        set_name("沈星南", ({ "shen xingnan","shen"}) );
        set("nickname", MAG"飞鱼塘飞鱼山庄庄主"NOR );
		set("gender", "男性" );
        set("age", 50);
        set("per", 30);
        set("long",
                "沈星南是飞鱼塘飞鱼山庄的主人,白道总盟盟主。\n他眉目如画,仙风道骨,古冠古衣,腰上还搭着一弓三箭.\n");
        set("attitude", "friendly");

        set("qi", 3000);
        set("max_qi", 3000);
        set("jingli", 3000);
        set("max_jingli", 3000);
        set("neili", 3500);
        set("max_neili", 3500);
        set("jiali", 75);

        set("combat_exp", 1750000);

        set_skill("cuff", 300);          //基本拳法
        set_skill("force", 300);         //基本内功
        set_skill("dodge", 300);         //基本轻功
        set_skill("parry", 300);         //基本招架
        set_skill("literate", 250);      //读书写字
        set_skill("sword", 331);         //基本剑术
        set_skill("feiyu-jian", 330);    //飞鱼剑法
        set_skill("youyu-quan", 300);     //游鱼拳
        set_skill("fish-steps", 300);    //鱼形步法
        set_skill("tianlongforce", 300); //天龙功
        set_skill("tao",350);            //道学心法

        map_skill("cuff", "youyu-quan");
		map_skill("force", "tianlongforce");
		map_skill("sword", "feiyu-jian");
		map_skill("dodge", "fish-steps");

		prepare_skill("sword", "feiyu-jian");

		create_family("飞鱼塘", 2, "弟子");

        setup();

        set("chat_chance_combat", 40);
        set("chat_msg_combat", ({
		(: recover_ob :)
        }) );

        add_money("silver", 10);

        carry_object("/d/feiyu/obj/chouduan")->wear();
        carry_object("/d/feiyu/obj/changjian")->wield();
}

void attempt_apprentice(object me)
{
        if ((string)me->query("family/family_name") != "飞鱼塘") {
                command("say " + RANK_D->query_respect(me)+"既然已有名师指导，又何需拜我为师呢？");
                return;
         }

        if ( (int)me->query("combat_exp")<400000 ) {
                command("say " + RANK_D->query_respect(me)+"似乎火候未够，先去江湖上磨练磨练再来吧！");
                return;
        }
        if ((int)me->query_skill("feiyu-jian", 1) < 120) {
                command("say 你在飞鱼剑法上的修为未够。"); 
                command("say " + RANK_D->query_respect(me) + 
                        "是否还应该在剑法上多下点功夫？");
                return;
         }
        if ( (int)me->query_skill("literate",1) < 100 ) {
                command("say 我看" + RANK_D->query_respect(me) + "的读书识字还没学到家吧。");
                return;
        }
        if (((int)me->query_skill("force",1) < 80) || ((int)me->query_skill("tianlongforce",1) < 80)) {
                command("say 我看" + RANK_D->query_respect(me) + "的金刚天龙神功还没学到家吧。");
                return;
        }
        if ((int)me->query("shen") < 100000) {
                command("say 我飞鱼塘乃是堂堂名门正派，对弟子德行要求严格。");
                command("say 在德行方面，" + RANK_D->query_respect(me) +"是否还做得不够？");
                return;
        } 
 

        command("say 好吧，我就收下你做徒弟吧。");
        command("say 飞鱼塘的武功博大精深，你要好好的学呀!");
        command("recruit " + me->query("id"));
}

void recover_ob()
{
        command("yun recover");
        return;
}
