// NPC: wenliangyu.c
// Created by Zeus 1999.4.7
// Modified by Zeus 1999.4.7
// 
// 

inherit NPC;

void create()
{
        set_name("温亮玉", ({ "wen liangyu", "liangyu"}) );
        set("gender", "男性" );
        set("age", 38);
        set("per", 20);
        set("long",
                "这位文质彬彬的中年人一团和气,他就是老字号里专管藏毒的大字号的负责人。\n");
        set("attitude", "friendly");

        set("qi", 1000);
        set("max_qi", 1000);
        set("jingli", 1000);
        set("max_jingli", 1000);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jiali", 50);

        set("combat_exp", 80000);

        set_skill("hand", 100);
        set_skill("force", 100);
        set_skill("dodge", 100);
        set_skill("parry", 100);
        set_skill("literate", 60);

        add_money("silver", 10);

        setup();
}
