//Npc 萧河
//by godzilla 11.18.99

#include <ansi.h>

inherit F_MASTER;

inherit NPC;

void create()
{
        set_name("萧河",({"xiao he","xiao","he"}));
        set("long","他就是天羽门下，号称为「追风一剑」萧河，\n");
        set("title",HIW"天羽派"NOR);
        set("nickname",HIR"追风一剑"NOR);
        set("age", 35);
	set("attitude", "friendly");
	set("shen_type", 0);
	set("str", 30);
	set("int", 35);
	set("con", 30);
	set("dex", 30);
	
	set("max_qi", 3500);
	set("max_jing", 3000);
	set("neili", 3500);
	set("max_neili", 3500);
	set("jiali", 100);
	set("combat_exp", 500000);
       
        set_skill("strike",140);
        set_skill("dodge",140);
        set_skill("tao",150);
        set_skill("force", 140);
	set_skill("parry", 140);
	set_skill("sword", 140);
	set_skill("literate", 140);
        set_skill("tianyu-qigong",140);
        set_skill("tianyu-qijian",105);
        set_skill("tianyu-bufa",140);
        set_skill("tianyu-zhenfa",80);
        
        map_skill("sword", "tianyu-qijian");
        map_skill("force", "tianyu-qigong");
        map_skill("dodge", "tianyu-bufa");
        map_skill("parry", "tianyu-qijian");
        
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
}

void greeting(object me)
{
	if( !me || environment(me) != environment() )
	return 0;
        command("smile "+me->query("id"));
}
void attempt_apprentice(object ob)
{
	
	if(ob->query("family/master_name")=="祝幽")
	{
		command("say 既然你是已经是祝幽的弟子，何必又到我这儿呢?\n");
		return;
	}
	if(ob->query("int")<25)
	{
		command("say 你悟性太差，不会在天羽派有多大作为的。\n");
		return;
	}
	command("nod "+ob->query("id"));
	command("say 天羽派需要你们来发扬光大。");	
	command("recruit " + ob->query("id"));
   ob->set("class","tianyumen");
}	
 



