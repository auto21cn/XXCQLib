// sample master.c code
// xiake island master.c
inherit NPC;
inherit F_MASTER;
#include <ansi.h>

void heal_ob();
void recover_ob();
int ask_fight();

void create()
{
	set_name("萧西楼", ({"xiao xilou", "xiao", "xilou"}));
	set("gender", "男性");
	set("title", "浣花剑派第二代弟子、"HIG"现任掌门"NOR);
	set("age", 54);
set("count",1);
	set("long", 
"他就是萧西楼——“浣花剑派”的一代宗师，天下“八大名剑”之一。\n"
"他一脸正气，三缕短须，无风自动，双目炯炯，令人不敢正视。\n");
	set("attitude", "peaceful");
	set("str", 15);
	set("int", 20);
	set("con", 20);
	set("dex", 20);
	set("bac", 25);

         set("qi", 7000);
         set("max_qi", 7000);
         set("jingli", 4800);
         set("max_jingli", 4800);
         set("neili", 5600);
         set("max_neili", 5600);
         set("jiali", 150);
         
         set("combat_exp", 2800000);
         set("shen", 60000);
         
         set_skill("force", 380);
         set_skill("jiuqu-xinfa", 380); 
         set_skill("strike", 360);
         set_skill("feixu-zhang", 360);
         set_skill("dodge", 380); 
         set_skill("huanhua-shenfa", 360); 
         set_skill("sword", 420); 
         set_skill("cuff", 240);
         set_skill("tiexian-quan", 240);
         set_skill("parry", 360); 
         set_skill("literate", 360); 
         set_skill("huanhua-jian", 420); 
         set_skill("confu", 300); 

         map_skill("force", "jiuqu-xinfa");
         map_skill("cuff", "tiexian-quan");
         map_skill("dodge", "huanhua-shenfa");
         map_skill("strike", "feixu-zhang");
         map_skill("parry", "huanhua-jian");
         map_skill("sword", "huanhua-jian");

         prepare_skill("strike", "feixu-zhang");
         prepare_skill("cuff", "tiexian-quan");
   

	
	create_family("浣花剑派", 2, "弟子");
     set("inquiry", ([
                "fight" : (: ask_fight :),
               "长歌" : "你能打的过我就行",
          ]) );

	setup();

	carry_object("/d/huanhua/npc/obj/changshan")->wear();
	carry_object("/clone/weapon/changjian")->wield();

	set("chat_chance", 3);
	set("chat_msg", ({
		(: heal_ob :),
		"萧西楼双眉紧缩，不停的踱着脚步。\n",
		"萧西楼摇了摇头，叹到：“权力帮贻害江湖，可是……”\n",
	}));

	set("chat_chance_combat", 30);
	set("chat_msg_combat", ({
		(: perform_action, "sword.mantian" :),
		(: perform_action, "sword.luanhong" :),
		(: perform_action, "strike.fenfei" :),
		(: perform_action, "cuff.chong" :),
		(: recover_ob :)
	}) );
}

void heal_ob()
{
	command("yun heal");
	command("yun heal");
	command("yun heal");
	command("yun recover");
	return;
}

void recover_ob()
{
	command("yun recover");
	return;
}

void attempt_apprentice(object ob)
{
	object me;
	mapping my_fam, ob_fam;
	string title;

	me = this_object();

	my_fam = ob->query("family");
	ob_fam = me->query("family");

	title = ob->query("title");

	if (!(my_fam = ob->query("family")) || my_fam["family_name"] != "浣花剑派")
	{
		command("say 我只收浣花弟子中有天分且刻苦者，你根本不是浣花弟子，我怎能收你？");
		return;
	}

	if ((int)ob->query("shen") <= (-100))
	{
		command("say 你身为浣花弟子却不主张正义，甘入魔道，我浣花容不下你！");
		command("kaichu "+ob->query("id"));
		return;
	}

	if (ob->query("shen")<100000)
	{
		command("say 你维护武林正义的义举做得不够，我还不能收你。");
		command("addoil " + ob->query("id"));
		return;
	}

	if (ob->query_skill("huanhua-jian",1)< 120 || ob->query_skill("sword",1)<120)
	{
		command("say 我们浣花剑派以剑法为本，你是否应该在剑法方面多下些功夫呢？");
		command("addoil " + ob->query("id"));
		return;
	}

	command("say 好吧，我收下你无妨，但能否成才还要看你自己的努力。");
	command("recruit " + ob->query("id"));

	return;
}
int accept_fight(object ob)
{
	object me  = this_object();
	
	if ( !ob->query_temp("fight_ok") ) return 0;

	remove_call_out("checking");
	call_out("checking", 1, me, ob);

	ob->delete_temp("fight_ok");
	
	return 1;
}


int checking(object me, object ob)
{

	int my_max_qi, his_max_qi;

	my_max_qi  = me->query("max_qi");
	his_max_qi = ob->query("max_qi");

	if (me->is_fighting()) 
	{
		call_out("checking",2, me, ob);
                return 1;
	}

	if ( !present(ob, environment()) ) return 1; 

	if (( (int)me->query("qi")*100 / my_max_qi) <= 50 ) 
	{
		ob->set_temp("qu_jian",1);		
        this_object()->set("count",0);
		command("say 果然长江后浪推前浪,你现在就是掌门弟子了 !\n");
		command("say 你可以去见天洞取长歌剑,以后好全力对付权利帮!\n");
		return 1;
	}

	if (( (int)ob->query("qi")*100 / his_max_qi) < 50 ) 
	{
		command("say 看来" + RANK_D->query_respect(ob) + 
			"平时叫你多练习不听,哼 !\n");
		command("disapp");
		return 1;
	}

	return 1;  
}

int ask_fight()
{
        mapping myfam;
        object ob;

        ob = this_player();
        myfam = ob->query("family");

        if (myfam["master_name"] != "萧西楼" ) 
	{  command("shake");
       command("say 你不是我的徒弟,我可不想和你切磋!\n");
              return 1;}
        if (this_object()->query("count")<1)
          {
          command("sorry "+ob->query("id"));
          return 1;
          }
           else  
	{  command("say 好吧!我们师徒来切磋一下吧!\n");
       ob->set_temp("fight_ok",1);
      return 1;}
}

