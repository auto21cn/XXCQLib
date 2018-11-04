// NPC: wennuansan.c
// Created by Zeus 1999.4.7
// Modified by Zeus 1999.4.7
// 
// 

inherit NPC;

void create()
{
        set_name("温暖三", ({ "wen nuansan", "nuansan"}) );
        set("gender", "男性" );
        set("age", 38);
        set("per", 25);
        set("long",
                "这个人看上去好像很随和，他就是老字号中的活字号的负责人。\n"+
                "不过，千万不要在他面前提到他儿子，否则......\n");
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
