// liuqianbian.c 柳千变

#include <ansi.h>

inherit NPC;

void create()
{
	set_name("柳千变",({"liu qianbian","liu"}));
	set("long",
	"他是武林黑白道闻风丧胆的柳千变，身怀绝世轻功“青云步”，更有\n"
	"一柄专打人体三十六大穴，七十二小穴的千变万幻的折扇。\n"
	"他温文尔雅，不是将手中折扇挥动两下。\n");
	set("party/rank",HIC"无影神魔"NOR);
	set("party/party_name","权力帮");
	set("nickname",HIB"天马行空"NOR);
	set("age",39);
	set("gender","男性");
	set("autitude","friendly");
	set("str",24);
	set("con",28);
	set("dex",33);
	set("int",27);
	
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
			
    set_skill("dodge",200);
    set_skill("force",150);
    set_skill("sword",150);
//    set_skill("qingyun-step",200);
	
	setup();
	
	carry_object("/clone/misc/cloth")->wear();

	
}
#include "quanli.h"


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
        if( !arg || arg!="liu" )
                return 0;
        if(wizardp(ob))  return 0;
        if (ob->query("party/party_name") != "权力帮")
        {
                message_vision("$N摇了摇头。\n",this_object());
                command("tell "+ob->query("id")+" 不是权利帮的人不能察看。\n"); 
                return 1;
        }
    command("tell "+ob->query("id")+" 我所有的武功如下：\n"+
"※ 柳千变目前所学过的技能：    \n\n"+
"  基本轻功 (dodge)                         - 深不可测 200/    0        \n"+
"  基本内功 (force)                         - 出神入化 150/    0     \n"+
"  基本剑法 (sword)                         - 出神入化 150/    0 \n");
   return 1;
}
