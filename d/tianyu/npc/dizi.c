//Npc 弟子
//by godzilla 11.18.99

#include <ansi.h>

int ask_ruguan();

inherit NPC;

void create()
{
        set_name("守关弟子", ({"dizi"}));
        set("long",
                "这是以为专门为师兄门守关的弟子。\n"
        );
        set("gender", "男性");
        set("attitude", "peaceful");
        set("age", 44);
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);
        set("max_qi", 700);
        set("max_jingli", 700);
        set("neili", 1000);
        set("jingli",1000);
        set("max_neili", 1000);
        set("jiali", 60);
        set("combat_exp", 80000);
        
        set_skill("force", 80);
        set_skill("dodge", 80);
        set_skill("strike",80);
        set_skill("parry", 80);
        set_skill("sword",90);
        set_skill("tianyu-qigong",80);
        set_skill("tianyu-qijian",85);
        set_skill("tianyu-bufa",80);
        
        map_skill("sword", "tianyu-qijian");
        map_skill("force", "tianyu-qigong");
        map_skill("dodge", "tianyu-bufa");
        map_skill("parry", "tianyu-qijian");
 
        set("inquiry", ([
        "闭关"       : (: ask_ruguan :),
        ]));
        create_family("天羽派", 7, "弟子");
        setup();
        carry_object(__DIR__"obj/cloth2")->wear();
        carry_object("/clone/weapon/changjian")->wield();
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
int ask_ruguan()
{       
        object ob,me;
        ob=this_object();
        me=this_player();
          if(me->query("family/family_name")!="天羽派")  
{
         command("say 你与本派素无来往，不知此话从何谈起？\n");
          return 1;
}
        if (me->query_skill("tianyu-qijian",1)<=100)
{
            command("say 你现在天羽剑法修为不够，还不能闭关！\n");
           return 1;
}
        if (environment(ob)->query("mask/闭关")>=3)
        {
        	tell_object(me,"现在已经有三个弟子在闭关修炼，人多嘈杂，你还是等会再来吧！\n");
        	return 1;
        }	 
        tell_object(me,"好吧！你可以进去练功了。\n");
        command("party "+me->name()+"开始闭关修炼天羽剑法！其他弟子不得骚扰！！\n");
        me->set_temp("xiulian_sword",1);
        environment(ob)->add("mask/闭关",1);
        me->move("/d/tianyu/lgs");
        tell_object(environment(ob),me->name()+"在守关弟子的带领下进入了里面的练功房。\n");
        return 1;
        
}
