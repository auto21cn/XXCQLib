// liangjiushi.c

inherit NPC;
#include <ansi.h>

int ask_me(object who);
void create()
{
        set_name("酿酒师", ({ "niangjiu shi", "shi" }));
        set("gender", "男性");
        set("age", 25);

        set("combat_exp", 4000);
        set_skill("dodge", 20);
        set_skill("unarmed", 20);
        set_temp("apply/attack",  10);
        set_temp("apply/defense", 10);
        setup();

        set("inquiry", ([
        	"酿酒" : (: ask_me :),
		"工序" : (: ask_me :),
	]) );
        add_money("silver",3);
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
        if( interactive(ob=this_player()) && ob->query_temp("killwei") ) {
                remove_call_out("kill_ob");
                call_out("kill_ob", 1, ob);
        }

}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;

	say("酿酒师笑眯眯的说道：“这位" + RANK_D->query_respect(ob)
	     + "对酿酒有什么不懂的，就问我。”\n");
}

int ask_me(object who)
{
        object room;

        if( !who || environment(who) != environment() ) return 0;

        if( !objectp(room = environment()) ) return 0;
	command("say 首先准备好酿酒的原料--高粱饭。");
	command("say 然后到这里来，把高粱饭装入(zhuang)窖中。");
	command("say 给窖加热(fire)。");
	command("say 得到醅子后，再装入(zhuang)锡锅中。");
	command("say 再给锡锅加热(fire)。");
	command("say 收集酒露后，把酿好的九酝酒埋在缸窑里面。回管事那复命就可以了(ask tang about job)。");
        return 1;
}

