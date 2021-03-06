// NPC: tiejiang.c
// Created by Atlus 1999.9.27
// Modified by Atlus 1999.10.12
// 
// 
#include <ansi.h>

int ask_job();
int ask_cancal();

inherit NPC;

void create()
{
        set_name("铁匠", ({ "tie jiang"}) );
        set("gender", "男性" );
        set("age", 20+random(10));
        set("long",
                "这是一位飞鱼塘铁匠房的带工。\n");
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
            "job": (: ask_job :),
		    "cancal": (: ask_cancal :),
		
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

int ask_job()
{
        object me, obj;
        mapping fam;
    
        me=this_player();
        obj=this_object();

        if (!(fam = this_player()->query("family")) || fam["family_name"] !="飞鱼塘") {
                command("say "+RANK_D->query_respect(me) +"，你不是飞鱼堂的弟子，问这个干什么？");
                return 1;
		}

		if( (int)me->query("combat_exp") > 50000) {

                        message_vision("铁匠对$N说： “你在这里干这个太浪费了，去找些别的工作吧？” \n",me);

                 return 1;}
		
		
		if ( me->query_temp("fy_task_datie/given_task",1) )
		{
                command("say "+RANK_D->query_respect(me) +"，你已经要了任务");
                return 1;
		}

		me->set_temp("fy_task_datie/given_task",1);
		me->set_temp("fy_task_datie/da_time",5);

        command("say "+RANK_D->query_respect(me) +"，好,先去材料房借个铁锤,再回来打铁!");
        return 1;
}

int accept_object(object who, object ob) 
{
       int pot,exp;

		if ( !who->query_temp("fy_task_datie/huan_hammer"))
		{
                command("say 请先去把铁锤还了,再来找我!");
				return 1;
		}
	   if (!who->query_temp("fy_task_datie/done"))  {
	            command("angry"+who->query("id"));
                command("say 你怎么能够拿别人的东西来向我交差!");
				return 1;
	   }

	   if (who->query_temp("fy_task_datie/done") && ob->query("id")=="wuqi" )  {
                command("nod "+who->query("id"));
                destruct(ob);
				exp=100+random(50);
                pot=25+random(15);
				who->add("potential",pot);
                who->add("combat_exp",exp);
                who->add("feiyu_job",1);
                who->delete_temp("fy_task_datie");
                message_vision(HIY"$N被奖赏了"+chinese_number(pot)+"点潜能和"+chinese_number(exp)+"点经验。\n"NOR,who);
                message_vision(HIC"$N已经为飞鱼塘做了"+chinese_number(who->query("feiyu_job"))+"次任务。\n"NOR,who);
                command("say 不错,辛苦了。下去休息去吧!");
				return 1;
	   } 
       return 0;
}
int ask_cancal()
{
        object me, obj;
        mapping fam;
    
        me=this_player();
        obj=this_object();

        if (!(fam = this_player()->query("family")) || fam["family_name"] !="飞鱼塘") {
                command("say "+RANK_D->query_respect(me) +"，你不是飞鱼堂的弟子，问这个干什么？");
                return 1;
		}

		
		if ( !me->query_temp("fy_task_datie/given_task",1) )
		{
                command("say "+RANK_D->query_respect(me) +"，你还没要任务呢!");
                return 1;
		}

		me->delete_temp("fy_task_datie/given_task");
		me->delete_temp("fy_task_datie/da_time");
        me->delete_temp("fy_task_datie/given_hammer");             
		me->delete_temp("fy_task_datie");
		me->delete_temp("fy_task_datie/hot");
		me->delete_temp("fy_task_datie/done");
	    me->delete_temp("fy_task_datie/has_put");
        me->delete_temp("fy_task_datie/tiere_time");
        me->delete_temp("fy_task_datie/ran");
        me->delete_temp("fy_task_datie/huan_hammer");
        me->add("potential",-20);

        command("say "+RANK_D->query_respect(me) +"，你不做了,那就算了吧!");
        return 1;
}
