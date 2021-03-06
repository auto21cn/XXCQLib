// Npc: 仆人
// Date: by godzilla 1999.11.18

inherit NPC;
int ask_zhao();
void create()
{
	set_name("仆人", ({ "pu ren", "ren" }));
        set("gender", "男性");
        set("age", 30+random(30));       
        set("str", 17);
        set("int", 20);
        set("con", 20);
        set("dex", 20);
        set("combat_exp", 2000);
        set("attitude", "peaceful");
        set("max_qi",800);
        set("max_jingli",800);
        set("neili",600);
        set("max_neili",600);
        
        set_skill("dodge", 20);
        set_skill("unarmed",20);
        set_skill("parry",20);
        
        set_temp("apply/attack", 20);
        set_temp("apply/defense", 20);
        set("inquiry", ([
        "找什么"       : (: ask_zhao :),
        "花名册": "花名册上面记载了历代天羽派弟子的名字，如果上面没有名字的弟子还不能算天羽派弟子",
         ]));
        set("chat_chance",2);
        set("chat_msg",({
                "仆人自言自语道：“嗨！我已经找了半天都找不到急死人了。”\n",
                "仆人自言自语道：“天羽派如果丢了这个东西，可牵涉重大啊！”\n",
                "仆人在草丛中忙碌的搜索着。\n",
        }) );        
        setup();
        carry_object(__DIR__"obj/cloth2")->wear();
}
int ask_zhao()
{
	object me;
	me=this_player();
	if(me->query("family/family_name")!="天羽派")
	{
		command("say 没...没什么，不用你操心了，这是我们派的家务事。\n");
		return 1;
	}
	me->set_temp("do_find_ce",1);
	command("say 嗨！天羽派的花名册丢了，掌门正叫我找呢，这为"+RANK_D->query_respect(me)+"帮我找找吧(search)。\n");
	command("say 如果找到，看看上面有没有你的名字，没有就在册上写上大名(write) 。\n");
	return 1;
}	