// jieyinshi.c 接客童子
// CLEANSWORD 1996/2/2

inherit NPC;
#include <ansi.h>

void create()
{
        set_name("接客童子", ({ "tong zi" }));
        set("long", "这是一为专门接待新玩家的童子\n");
        set("gender", "男性");
        set("age", 18);

        set("shen_type", 1);
        setup();

        carry_object("/clone/misc/cloth")->wear();
}

void init()
{       
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
		say("童子说道：这位"+ RANK_D->query_respect(ob)
                 + ",欢迎光临小雪初晴，老玩家请往南走，新玩家请往东走。\n");
}
