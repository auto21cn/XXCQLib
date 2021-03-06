
inherit NPC;

#include <ansi.h>
int serve_me(object who);
void create()
{
        set_name("仆人", ({ "pu ren", "pu" }));
        set("gender", "男性");
        set("age", 25);

        set("combat_exp", 4000);
        set_skill("dodge", 20);
         set("serve",100);
        setup();

        set("inquiry", ([
                "原料" : (: serve_me :),
	]) );
        add_money("silver",3);
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        object ob;

	
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

	say("仆人笑眯眯的说道：“这位" + RANK_D->query_respect(ob)
	     + "想要酿酒的原料，就知会我一声。”\n");
}


int serve_me(object who)
{
        object ob;
        object room;

       who=this_player();
        if( !who || environment(who) != environment() ) return 0;

        if( !objectp(room = environment(who)) ) return 0;
        if ((ob=present("gaoliang",who)) || (ob=present("mianfen",who)) || (ob=present("gaoliangfan",who)))
        {
               command("hmm");
               command("say 你已经拿了原料了，还没用完呢。");
               return 1;
        }

          if (query("serve")>0) {
        ob = new("/d/huafu/obj/gaoliang");
        ob->move(who);
        message_vision("仆人递给$N一根高粱。\n",who);

        ob = new("/d/huafu/obj/mianfen");
        ob->move(who);
        message_vision("仆人递给$N一包面粉。\n",who);
      add("serve",-1);
       }
       else
        message_vision("仆人四处看了看，对$N说道：原料已经用光了，等会再来。\n",who);
		
        return 1;
}
