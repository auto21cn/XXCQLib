// NPC: wendabao.c
// Created by Zeus 1999.3.27
// Modified by Zeus 1999.3.27
// 
// 

inherit NPC;

void create()
{
        set_name("温家弟子", ({ "dizi"}) );
        set("gender", "男性" );
        set("age", 20+random(10));
        set("long",
                "这是一位温家弟子。在温家总堂里到处可以看见这种服色的人。\n");
        set("combat_exp", 30000);
        set("attitude", "friendly");

        set("qi", 400);
        set("max_qi", 400);
        set("jingli", 500);
        set("max_jingli", 500);
        set("neili", 800);
        set("max_neili", 800);
        set("jiali", 10);

        set_skill("hand", 80);
        set_skill("force", 40);
        set_skill("dodge", 80);
        set_skill("parry", 40);
        set_skill("literate", 60);

        add_money("silver", 5);

        setup();
}
