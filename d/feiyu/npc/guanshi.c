// NPC: feiyudizi.c
// Created by Atlus 1999.10.12
// Modified by Zeus 1999.5.12
// 
// 

int ask_hammer();

inherit NPC;

void create()
{
        set_name("材料房管事", ({ "guan shi"}) );
        set("gender", "男性" );
        set("age", 20+random(10));
        set("long",
                "这是一位飞鱼塘总所材料房的管事。\n");
        set("attitude", "friendly");

        set("qi", 500);
        set("max_qi", 500);
        set("jingli", 400);
        set("max_jingli", 400);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 10);

        set("combat_exp", 30000);

        set("inquiry", ([
            "铁锤": (: ask_hammer :),
		]) );

		set_skill("unarmed", 50);     //搏击格斗
        set_skill("force", 50);       //基本内功
        set_skill("dodge", 50);       //基本轻功
        set_skill("parry", 50);       //基本招架
        set_skill("literate", 30);    //读书写字
 	    set_skill("youyu-quan",90);  //游鱼拳
        create_family("飞鱼塘", 6, "弟子");

        setup();
}

int ask_hammer()
{
        object me, obj, hammer;
        mapping fam;
    
        me=this_player();
        obj=this_object();

        if (!(fam = this_player()->query("family")) || fam["family_name"] !="飞鱼塘") {
                command("say "+RANK_D->query_respect(me) +"，你不是飞鱼塘的弟子，请不要问!");
                return 1;
		}

		if ( me->query_temp("fy_task_datie/given_hammer") )
		{
                command("say "+RANK_D->query_respect(me) +"，你不是已经拿了铁锤吗？");
                return 1;
		}

		if ( !me->query_temp("fy_task_datie/given_task",1) )
		{
                command("say "+RANK_D->query_respect(me) +"，你要铁锤干什么？");
                return 1;
		}

		me->set_temp("fy_task_datie/given_hammer",1);

		hammer=new("/d/feiyu/obj/hammer");
		hammer->move(me);
        command("say "+RANK_D->query_respect(me) +"，拿好,别弄丢了？");
        return 1;
}

int accept_object(object who, object ob) 
{
	   if (who->query_temp("fy_task_datie/done") && ob->query("id")=="hammer" && !who->query_temp("fy_task_datie/huan_hammer"))  {
                command("say 不错,辛苦了。下去休息去吧!");
				destruct(ob);
				who->set_temp("fy_task_datie/huan_hammer",1);
				return 1;
	   } 
       return 0;
}
