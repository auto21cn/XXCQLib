//Npc 宋自雪
//by godzilla 11.18.99

#include <ansi.h>

int ask_sword();

inherit F_MASTER;

inherit NPC;

void create()
{
        set_name("宋自雪",({"song zixue","song","zixue"}));
        set("long","他就是天羽门掌门，是百年来难得的奇材，天羽奇剑原创只有七剑，
宋自雪17岁就自创15剑，24岁就创出24套全部剑法，27岁就自立为掌门。是武林三
正四奇之一。\n");
        set("title",HIW"天羽派"HIY"掌门"NOR);
        set("nickname",HIR"天羽奇剑"NOR);
        set("age", 35);
	set("attitude", "friendly");
	set("shen_type", 0);
	set("str", 50);
	set("int", 55);
	set("con", 50);
	set("dex", 50);
	
	set("max_qi", 6500);
	set("max_jing", 6000);
	set("neili", 10000);
	set("max_neili", 6000);
	set("jiali", 200);
	set("combat_exp", 2000000);
	set("tianyu_1",1);
       
        set_skill("strike",200);
         set_skill("tianyu-zhenfa",200);
        set_skill("dodge",200);
        set_skill("force", 200);
	set_skill("parry", 200);
	set_skill("sword", 200);
	set_skill("literate", 200);
        set_skill("tianyu-qigong",200);
        set_skill("tianyu-qijian",250);
        set_skill("tianyu-bufa",200);
        set_skill("tao",250);
        
        map_skill("sword", "tianyu-qijian");
        map_skill("force", "tianyu-qigong");
        map_skill("dodge", "tianyu-bufa");
        map_skill("parry", "tianyu-qijian");
;

        set("inquiry", ([
        "金虹剑"       : (: ask_sword :),
        ]));
        create_family("天羽派", 7, "弟子");
        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object(__DIR__"obj/cloth2")->wear();
}
void init()
{
	object me;
	::init();
	if(interactive(me=this_player()) && !is_fighting() )
	{
		remove_call_out("greeting");
		call_out("greeting",1,me);
	}
	add_action("do_accept","accept");
}
int ask_sword()
{       
        object me,ob,obj;
        obj=this_object();
        me=this_player();
        if(me->query("family/family_name")=="天羽派")
        {
        	if(this_object()->query("mark/取剑"))
        	{
        		command("say 金虹剑已经让你师兄拿去了。\n");
        		return 1;
        	}	
        	message_vision(CYN"宋自雪对$N说道：金虹剑乃天羽派掌门信物，见剑如见掌门，你如果能接
        	我几招，就可以借剑与你。如果同意请用(accept test)\n"NOR,me);
        	me->set_temp("try_1",1);
        	return 1;
        }
        else
        {      
        	if(this_object()->query("mark/取剑"))
        	{
        		command("say 尽敢打我派掌门信物的主意，"+me->name()+"拿命来吧！");
        		this_object()->kill_ob(me);
        		return 1;
        	}	
        	message_vision(CYN"宋自雪喝道：$N尽敢打我派掌门信物的主意，好吧让你见识一下金虹剑的威力！\n"NOR,me);
        	command("unwield jian");
        	ob=new(__DIR__"obj/jinhong-jian");
        	ob->move(this_object());
        	command("wield jinhong jian");
        	this_object()->kill_ob(me);
        	return 1;
        }	
        	
               
}
void greeting(object me)
{
	if( !me || environment(me) != environment() )
	return 0;
	if(me->query("family/family_name")=="天羽派")
	{
		command("smile "+me->query("id"));
		command("pat "+me->query("id"));
	}
	else
	{
		message_vision(CYN"宋自雪对$N说道：赶快离开，天羽派可是你们这些人乱闯的。\n"NOR,me);
		command("consider "+me->query("id"));
	}	
	
}
void attempt_apprentice(object ob)
{
	if(!ob->query("congra_baishi"))
	{
		command("say 今天我心情不好不想收徒!\n");
		return;
	}
        if((int)ob->query_skill("tianyu-qijian",1)<150)
	{
		command("say 你天羽奇剑不够纯熟，先修炼一阵再来吧！\n");
		return;
	}		
	command("nod "+ob->query("id"));
	command("say 天羽派需要你们来发扬光大。");	
	command("recruit " + ob->query("id"));
	ob->delete("congra_baishi");
	ob->set("title",HIR"天羽派掌门亲传弟子"NOR);
}	
int do_accept(string arg)
{
	object ob,me;
	me=this_player();
	if(!arg||arg=="")
	return 0;
	if(!me->query_temp("try_1"))
	return 0;
	if(arg=="test")
	{
		command("say 好吧!请接招!\n");
		COMBAT_D->do_attack(this_object(), me, query_temp("weapon"));
		COMBAT_D->do_attack(this_object(), me, query_temp("weapon"));
		COMBAT_D->do_attack(this_object(), me, query_temp("weapon"));
		if(me->query("qi")<150)
		{
			command("sigh");
			command("say 看来你得多加练习!");
			me->set_temp("try_1",0);
			return 1;
		}
		else
		{
			command("say 不错！天下能接我三招之人已经不多，看来你是个可塑之材！\n");
			command("say 金虹剑乃本门掌门信物，见剑如见掌门，你要好好保管！\n");
			ob=new(__DIR__"obj/jinhong-jian");
			ob->move(me);
			message_vision(CYN"说完,宋自雪解下自己的"+YEL+"金虹剑"+CYN+"递给了$N。\n"NOR,me);
			set("mark/取剑",1);
			me->set_temp("try_1",0);
			return 1;
		}	
	
	}	
		
}
int accept_object(object me, object obj)
{
	object ob  = this_object();
	if(obj->query("id") == "huaming ce")
	{
		 if(me->query("family/family_name")!="天羽派")
		 {
		 	command("say 哦？ 没想到我派的花名册被这为"+RANK_D->query_respect(ob)+"找到了，不错不错！\n");
		 	return 1;
		 }
		 if(obj->query("write_name")!=me->query("id")||!obj->query("write_name"))
		 {
		 	message_vision(CYN"宋自雪看了看花名册上的名字，又看看了$N，眼中失望神色一闪而过。\n"NOR,me);
		 	command("say 哦？没想到我派的花名册被这为"+RANK_D->query_respect(ob)+"找到了，不错不错！\n");
		 	return 1;
		  }
		  command("say 不错不错，你为我派立了大功，今天我心情不错，怎么样想拜我为师吗?\n");
		  me->set("congra_baishi",1);
		  remove_call_out("destroying");
		  call_out("destroying",1,ob,obj);
		  return 1;
	}	  
}
void destroying(object ob,object obj)
{
	destruct(obj);
        return;
}        
