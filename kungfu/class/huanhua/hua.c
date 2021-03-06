// sample master.c code
// xiake island master.c

inherit NPC;
inherit F_MASTER;

#include <ansi.h>
void recover_ob();

void create()
{
	set_name("花灵", ({"hua ling", "hua", "ling"}));
	set("nickname", HIM"凤组组长"NOR);
	set("gender", "女性");
	set("age", 22);
	set("long", 
		"她是一个假小子一样的女孩子，一张坚毅的脸上露出淡淡的面容。\n");
	set("attitude", "peaceful");
	set("str", 12);
	set("int", 24);
	set("con", 20);
	set("dex", 24);
	set("bac", 20);

	set("qi", 1000);
	set("max_qi", 1000);
	set("jingli", 600);
	set("max_jingli", 600);
	set("neili", 700);
	set("max_neili", 700);
	
	set("combat_exp", 70000);
	set("score", 4000);
	
	set_skill("force", 50);
	set_skill("jiuqu-xinfa", 50); 
	set_skill("strike", 50);
	set_skill("feixu-zhang", 50);
	set_skill("dodge", 50); 
	set_skill("huanhua-shenfa", 50); 
	set_skill("sword", 50); 
	set_skill("parry", 50); 
	set_skill("literate", 50); 
	set_skill("confu", 50); 
	set_skill("huanhua-jian", 50); 
	
	map_skill("force", "jiuqu-xinfa");
	map_skill("dodge", "huanhua-shenfa");
	map_skill("strike", "feixu-zhang");
	map_skill("parry", "huanhua-jian");
	map_skill("sword", "huanhua-jian");

	prepare_skill("strike", "feixu-zhang");
	
	create_family("浣花剑派", 5, "弟子");

	setup();

	carry_object("/d/huanhua/npc/obj/liangongfu")->wear();
	carry_object("/clone/weapon/changjian")->wield();

	set("chat_chance_combat", 30);
	set("chat_msg_combat", ({
		(: recover_ob :)
	}) );
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

	me = this_object();

	my_fam = ob->query("family");
	ob_fam = me->query("family");

	if (ob->query("killding"))
	{
		command("say 大胆狂徒，胆敢硬闯萧府，纳命来吧！");
		me->kill_ob(ob);
		ob->kill_ob(me);
		return;
	}

	if ((int)ob->query("shen") <= (-100))
	{
		if (!(my_fam = ob->query("family")) || my_fam["family_name"] != "浣花剑派")
		{
			command("hmm");
			command("say 浣花萧家乃名门正派，岂能容纳邪魔外道，你还不快快滚出剑庐！！！");
			return;
		}
		else
		{
			command("say 你身为浣花弟子却不主张正义，甘入魔道，我浣花容不下你！");
			command("kaichu "+ob->query("id"));
			return;
		}
	}

	if ((!(my_fam = ob->query("family")) || my_fam["family_name"] != "浣花剑派") && (int)ob->query("combat_exp")>20000)
	{
		command("say "+RANK_D->query_respect(ob)+"已是江湖成名之士，萧家哪敢相留。");
		command("say 对不起了，您请回吧。");
		return;
	}

	if ( my_fam )
	{
		if ( my_fam["family_name"] == "浣花剑派" )
		{
			if ( ob_fam["generation"] == my_fam["generation"] )
			{
				command("say 你我乃同辈弟子，切磋切磋倒是可以，拜师却是从何说起？");
				return;
			}
	
			if ( ob_fam["generation"] > my_fam["generation"] )
			{
				message_vision("$N一脸的诚惶诚恐道：究竟弟子犯了什么错，您要和弟子开这样的玩笑。\n", me);
				return;
			}
		}
	}

	if (ob->query("gender")=="男性")
	{
		command("say 凤组只收女弟子，你要拜师就去找其他组吧。");
		return;
	}

	command("say 好吧，" + RANK_D->query_respect(ob) +"入我凤组，就好好为剑庐出力吧。");
	command("recruit " + ob->query("id"));
	ob->set("title", "浣花剑派第六代弟子、"HIM"凤组组员"NOR);
	if (!(my_fam = ob->query("family")) || my_fam["family_name"] != "浣花剑派")
		ob->set("pay_money", ob->query("age"));

	return;
}