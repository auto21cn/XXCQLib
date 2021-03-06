// shang.c 上太师

inherit F_DEALER;

void create()
{
	set_name("上太师", ({ "shang taishi", "shang", "taishi" }));
	set("title", "回春堂老板");
	set("gender", "男性");
	set("long", "他就是京城最有名的名医上太师，据说曾经在宫里做过御医。\n");
	set("age", 65);

	set("int", 30);
	
	set("qi", 200);
	set("max_qi", 200);
	set("jing", 200);
	set("max_jing", 200);
	set("shen_type", 1);

	set("combat_exp", 2000);
	set("attitude", "heroism");

	set_skill("dodge", 20);
	set_skill("parry", 20);
	set_temp("apply/attack", 20);
	set_temp("apply/defense", 20);
	set_temp("apply/damage", 20);

	set("vendor_goods", ({
	}));

	setup();
	add_money("gold", 1);
	carry_object("/clone/misc/cloth")->wear();
}

int accept_object(object who, object ob)
{
	object obj, sil;
	obj = this_object();

	if ((string)ob->query("id") == "dan") 
	{
		if ((string)who->query_temp("goods") != obj->query("name"))
		{
			message_vision("$N把单子递给"+obj->query("name")+"查验。\n", who);
			command("? "+who->query("id"));
			command("say 这份"+ob->query("name")+"不是我们这里的呀！");
			command("say 你还是到别的地方去找找吧。");
			command("give dan to "+who->query("id"));
			return 1;
		}
		else if (!(string)who->query_temp("buygoods") || (string)who->query_temp("buygoods") != "begin")
		{
			message_vision("$N把单子递给"+obj->query("name")+"查验。\n", who);
			command("? "+who->query("id"));
			command("say 这虽然是我们这里的，但是……，大概不是您的吧。");
			command("say 这张单子我们先留下了，省得顾客受损失，谢谢您了。");
  			destruct(ob);
			return 1;
		}
		else
		{
			message_vision("$N把单子递给"+obj->query("name")+"查验。\n", who);
			command("say 太好了，太好了，您终于来了！");
			message_vision(obj->query("name")+"拿过一根笔在账单上划了两下，然后收了起来。\n", who);
			message_vision(obj->query("name")+"转了进去，一会带着一个伙计扛出来一个大包裹。\n", who);
			message_vision(obj->query("name")+"笑了笑说：这就是您们剑庐的货，您收好。\n", who);
			sil = new("/d/huanhua/npc/obj/huo");
			sil->set("name", "药材");
			sil->set("long", "这是从北京回春堂取来的药材。");
			sil->move(who);
			who->set_temp("buygoods", "over");
  			destruct(ob);
			return 1;
		}
	}
	else
	{
		command("say 你给我这个干什么?");
		return 0;
	}
	
}
