// qing.c 清谋石
// mlf设计,lks 编程

#include <ansi.h>
#include "/d/huafu/npc/cam.h"
#include "/d/wenzhai/npc/qing.h"
inherit NPC;
#include "/kungfu/class/fameng/erdai.h"
inherit F_MASTER;

int ask_me();
int ask_job();
void create()
{
	set_name("清谋石",({"qing moushi","qing"}));
	set("nickname",HIY"温家十石"NOR);
	set("gender","男性");
	set("attitude","peaceful");
	set("age",33);
	set("combat_exp",500000);
	set_skill("tao",100);
	set("max_qi",1000);
	set("max_neili",1500);
	set("max_jingli",500);
	set_skill("force",180);
	set_skill("bairen-shengong",180);
	set_skill("dodge",150);
	set_skill("parry",180);
	set_skill("fengye-xiangsi",150);
        set_skill("blade",180);	
	
        map_skill("force","bairen-shengong");
	map_skill("dodge","fengye-xiangsi");
        create_family("发梦二党",2,"弟子");
	setup();
	
        set("inquiry",([
                "book" : (: ask_me :),
                "书" : (: ask_me :),
                "job" : (: ask_job :),
        ]));
	carry_object("/clone/misc/cloth")->wear();
	set("chat_chance", 20);
	set("chat_msg", ({
		(: exert_function, "recover" :),
		(: exert_function, "heal" :),
	}));
	set("chat_chance_combat", 30);
	set("chat_msg_combat", ({
		(: exert_function, "recover" :),
	}) );
}
