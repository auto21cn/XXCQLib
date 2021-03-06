// dujue.c 杜绝	

#include <ansi.h>

inherit NPC;

void create()
{
	set_name("杜绝",({"du jue","du"}));
	set("long",
	"杜绝做事最绝，杜绝自小家人被仇人杀光，寄养在恩人家里，后杀性\n"
	"兴起，把恩人全家杀光，手段之残忍，令人发指。\n"
	"他脸上杀气冲冲，眼中布满血丝，手紧紧握着刀柄。\n");
	set("age",42);
	set("party/rank",HIC"快刀天魔"NOR);
	set("party/party_name","权力帮");
	set("gender","男性");
	set("autitude","friendly");
	set("str",24);
	set("con",28);
	set("dex",30);
	set("int",28);
	
	set("max_qi",3000);
	set("max_jing",2000);
	set("neili",3000);
	set("max_neili",3000);
	set("jiali",50);
	
	set("combat_exp",1500000);
	set("score",2000);
	
	set("inquiry",([
		"权力帮":"我愿为权力帮赴汤蹈火，尽忠尽力！",
		]));
			
    set_skill("dodge",180);
    set_skill("parry",180);
    set_skill("blade",200);
    set_skill("force",180);
	
	setup();
	
	carry_object("/clone/misc/cloth")->wear();
	carry_object("/clone/weapon/gangdao")->wield();

	
}

void init()
{
::init();
add_action("do_skills","skills");
add_action("do_skills","cha");
add_action("do_join","join");
}
int do_skills(string arg)
{
        object ob ;
        ob = this_player () ;
        if( !arg || arg!="du" )
                return 0;
        if(wizardp(ob))  return 0;
        if (ob->query("party/party_name") != "权力帮")
        {
                message_vision("$N摇了摇头。\n",this_object());
                command("tell "+ob->query("id")+" 不是权利帮的人不能察看。\n"); 
                return 1;
        }
    command("tell "+ob->query("id")+" 我所有的武功如下：\n"+
"杜绝目前所学过的技能：    \n\n"+
"  基本刀法 (blade)                         - 深不可测 200/    0   \n"+
"  基本轻功 (dodge)                         - 一代宗师 180/    0   \n"+
"  基本内功 (force)                         - 一代宗师 180/    0    \n"+
"  基本招架 (parry)                         - 一代宗师 180/    0  \n");
   return 1;
}
