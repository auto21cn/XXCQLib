// by mulan

inherit NPC;
int ask_me();

void create()
{
        set_name("萧易人", ({"xiao yiren", "xiao"}));
        set("gender", "男性");
        set("age", 62);
        set("long", "这人便是浣花剑派的大弟子!\n");

        set("attitude", "peaceful");
        set("str", 15);
        set("int", 20);
        set("con", 20);
        set("dex", 20);
        set("bac", 25);

        set("qi", 3000);
        set("max_qi", 3000);
        set("jingli", 2000);
        set("max_jingli", 2000);
        set("neili", 2500);
        set("max_neili", 2500);
        set("jiali", 60);
        
        set("combat_exp", 1000000);
        set("shen", 10000);
        
        set_skill("force", 150);
        set_skill("jiuqu-xinfa", 150);
        set_skill("strike", 150);
        set_skill("feixu-zhang", 150);
        set_skill("dodge", 150);
        set_skill("huanhua-shenfa", 180); 
        set_skill("sword", 150);
        set_skill("cuff", 100);
        set_skill("parry", 150); 
        set_skill("literate", 150); 
        set_skill("huanhua-jian", 150);
        set_skill("confu", 120); 
        
        map_skill("force", "jiuqu-xinfa");
        map_skill("cuff", "tiexian-quan");
        map_skill("dodge", "huanhua-shenfa");
        map_skill("strike", "feixu-zhang");
        map_skill("parry", "huanhua-jian");
        map_skill("sword", "huanhua-jian");

        prepare_skill("strike", "feixu-zhang");
        prepare_skill("cuff", "tiexian-quan");
        
        create_family("浣花剑派", 3, "弟子");
        set("inquiry", ([
          "金甲铁衣" : "不是吧,这你都想要!",
        ]) );

        setup();

        carry_object("/d/huanhua/npc/obj/jinjia")->wear();

        set("chat_chance", 3);
        set("chat_msg", ({
                "萧易人着急的望着前面，想火速赶到剑庐。\n",
                "萧易人叫手下的人先往前冲，权力帮的人一定到了剑庐了!\n",
        }));
}

int accept_object(object who, object ob)
{

        string name,temp_name;
        object me;
        me = this_player();
         name = ob->query("name");
         temp_name = me->query_temp("obj");
	
       if(!temp_name)
       return 0;
        if (name[1..2] == temp_name[1..2]) 
        {
	command("ok");
       command("say 你作为浣花弟子杀死权力帮众,得到一些经验和潜能!\n");
       command("say 其他地方还有很多权力帮的帮众,要小心应付!\n");
       me->add("combat_exp",me->query_skill("confu",1));
       me->add("potential",me->query_skill("confu",1)/2);
       me->add("shen",this_object()->query("combat_exp")/1000);	
	return 1;
         }
	else
	{
	   command("say "+name+"我可不要!\n");
	   return 0;
	}
}
