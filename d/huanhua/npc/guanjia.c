// shang.c 韦伯

inherit NPC;
//inherit F_DEALER
#include <ansi.h>

int ask_job();
int ask_join();

void create()
{
	set_name("贾先生", ({ "jia xiansheng", "jia" }));
	set("title", "浣花萧家杂役管家");
	set("gender", "男性");
	set("long", "他是浣花萧家的杂役管家，萧家的家丁丫鬟都归他管。\n");
	set("age", 35);

	set("int", 30);
	
	set("qi", 500);
	set("max_qi", 500);
	set("jing", 300);
	set("max_jing", 300);
	set("shen_type", 1);

	set("combat_exp", 5000);
	set("attitude", "heroism");

	set_skill("dodge", 20);
	set_skill("parry", 20);
	set_skill("literate", 100);
	set_temp("apply/attack", 20);
	set_temp("apply/defense", 20);
	set_temp("apply/damage", 20);

        set("inquiry", ([
                "job" : (: ask_job :),
        ]) );

	setup();
	add_money("gold", 1);
	carry_object("/clone/misc/cloth")->wear();
}

int ask_job()
{
	object me, ob;
	mapping myfam;
	me = this_player();

	myfam = me->query("family");

	if ( !myfam || myfam["family_name"] != "浣花剑派" )
	{
		command("say "+RANK_D->query_respect(me)+"不是我浣花的弟子，我们又怎敢劳烦您呢？");
		return 1;
	}
        else if (me->query("combat_exp")<30000)
        {
                command("shake");
                command("say 你是新来的,还是帮西面的厨师,做一些事情吧。");
                return 1;
        }

	else if ((int)me->query("combat_exp")>60000)
	{
		command("shake " + me->query("id"));
		command("say "+RANK_D->query_respect(me)+"现在武功高强，再做这些应该我们下人作的活不太好吧？");
		return 1;
	}

	else if ((me->query_temp("jobcloth")=="1") || (me->query_temp("jobcloth")=="2"))
	{
		command("hmm");
		command("say 有工作还来要，真是一个不安分的家伙。");
		return 1;
	}

	else if (me->query_temp("jobcloth")=="3")
	{
		command("sigh");
		command("say 衣服丢了就算了吧,这里还有一件,你去洗洗吧。");
		me->set_temp("jobcloth", "1");
		ob = new("/d/huanhua/npc/obj/jobcloth1");
		ob->move(me);
		return 1;
	}

	me->set_temp("jobcloth", "1");
	ob = new("/d/huanhua/npc/obj/jobcloth1");
	ob->move(me);
	command("say 你愿意帮我们下人干活真是太好了。");
	command("say 这里有一些脏衣服，你拿去溪边洗洗吧，谢谢了。");
	return 1;
}

int accept_object(object who, object ob)
{
    object me;
	mapping myfam;
// int i;
	me = this_player();
	myfam = me->query("family");

	if ((string)ob->query("name") == "干净衣服") 
	{
		if ( !myfam || myfam["family_name"] != "浣花剑派" )
		{
			command("say 真是的，不知道又是谁丢的。");
			command("thank "+who->query("id"));
			return 1;
		}
		else if ((string)who->query_temp("jobcloth") != "2")
		{
			command("hmm");
			command("say 你不愿意干就不要干，拿别人洗好的衣服来交差，这又何必呢？。");
			return 1;
		}
		else
		{
			command("say 多谢，多谢，辛苦了，你去休息休息吧。");
			message_vision("管家叫人将洗好的衣服晾在了院子里。\n", who);
			who->add("potential", 30+random(30));
			who->add("combat_exp", 50+random(30));
			who->add("succeed", 1);
			who->delete_temp("jobcloth");
			return 1;
		}
	}
	else if ((string)ob->query("name") == "破衣服") 
	{
		if ( !myfam || myfam["family_name"] != "浣花剑派" )
		{
			command("say 真是的，不知道又是谁丢的。");
			command("thank "+who->query("id"));
			return 1;
		}
		else if ((string)who->query_temp("jobcloth") != "3")
		{
			command("say 真是的，不知道又是谁丢的。");
			command("thank "+who->query("id"));
			return 1;
		}
		else
		{
			command("say 你这个笨蛋，连洗衣服都洗不好！");
			who->delete_temp("jobcloth");
			return 1;
		}
	}
	else
	{
		command("say 你给我这个干什么?");
		return 0;
	}
	
}
