// murong-fu.c  慕容复
inherit NPC;
inherit F_MASTER;

#include <ansi.h>
#include "skill.h"
int ask_fuming(string arg);
string ask_bo();
string ask_skill();
string ask_wang();
string ask_learn();
string ask_ge();
string ask_sword();
void create()
{
        set_name("慕容复",({"murong fu","murong","fu"}));
        set("title",HIC"以彼之道 还施彼身"NOR);
        set("long",
              "他就是天下号称以彼之道，还彼之身的姑苏慕容复。\n"
              "他脸上带着不可一世的笑容。\n");
        set("age", 27);
        set("attitude", "friendly");
        set("shen_type", 0);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
	set("per", 30);

        set("max_qi", 3500);
        set("max_jing", 3000);
        set("neili", 3500);
        set("max_neili", 3500);
        set("jiali", 0);
        set("combat_exp", 1000000);
        set("score", 50000);
        set("chat_msg_combat", ({
        (: perform_action, "parry.xingyi" :)
}));
        set_skill("strike",170);
        set_skill("finger",170);
        set_skill("dodge",180);
        set_skill("force", 170);
        set_skill("canhe-zhi", 160);
        set_skill("murong-jianfa",160);
        set_skill("shenyuan-gong", 160);
        set_skill("yanling-shenfa", 160);
        set_skill("xingyi-zhang",170);
        set_skill("douzhuan-xingyi", 180);
        set_skill("parry", 180);
        set_skill("sword", 160);
        set_skill("literate", 170);
        set_skill("murong-daofa", 160);
        set_skill("blade",160);

        map_skill("blade", "murong-daofa");
        map_skill("finger", "canhe-zhi");
        map_skill("force", "shenyuan-gong");
        map_skill("dodge", "yanling-shenfa");
        map_skill("strike", "xingyi-zhang");
        map_skill("parry", "douzhuan-xingyi");
        map_skill("sword", "murong-jianfa");

        prepare_skill("finger","canhe-zhi");
        prepare_skill("strike","xingyi-zhang");

        create_family("姑苏慕容",2,"弟子");

        set("inquiry",
                ([
                        "name" : "公子我就是天下文明的“南慕容”姑苏慕容复。\n",
                        "here" : "这里是燕子坞，我们慕容世代居住于此。\n",
                        "rumors" : "家父突染恶疾，我连他老人家最后一面都没见到，此事顶有蹊跷！\n",
                        "姑妈" : "我的姑妈住在曼佗罗山庄，娘缳玉洞的武学藏书竟不亚于我们还施水阁。\n",
                        "还施水阁" : (: ask_ge :),
                        "慕容博" : (: ask_bo :),
                        "老爷子" : (: ask_bo :),
                        "王语嫣" : (: ask_wang :),
                        "宝剑" : (: ask_sword :),
                        "武学" : (: ask_learn :),
                        "复命" : (: ask_fuming :),
                ]));
        setup();
	carry_object("/clone/misc/cloth")->wear();
}
void init()
{
        ::init();
        add_action("do_jiaoliang", "jiaoliang");
}
void attempt_apprentice(object ob)
{
        if (ob->query_skill("parry", 1) < 120)
        {
                command("say 我姑苏慕容以彼之道、还施彼身对招架要求甚高，小兄弟似乎不宜学习。");
		command("say " + RANK_D->query_respect(ob) + "的功力不够，还是请回吧。");
                return;
        }

        if (ob->query_skill("shenyuan-gong", 1) < 100)
        {
                command("say 我姑苏慕容以彼之道、还施彼身对内功心法要求甚高，小兄弟似乎不宜学习。");
		command("say " + RANK_D->query_respect(ob) + "的功力不够，还是请回吧。");
                return;
        }
	if( ob->query("gender") == "无性")
	{
		command("say 我最讨厌的就是不男不女之人。");
		return;
	}

	command("say 嗯，看你还是个学武的料，我就收下你吧！");
        command("say 苍天在上，让我姑苏慕容又得一良材，为复兴我大燕多了一份力量。");
        command("say 朗声说道：公子我又收一良材，大燕兴复指日可待啦！");
        command("say haha");
        command("recruit " + ob->query("id"));
        ob->set("title","姑苏慕容第三代弟子");
}

string ask_wang()
{
	mapping fam;
	object ob;
        if (!fam = this_player()->query("family") || fam["family_name"] !="姑苏慕容")
        return RANK_D->query_respect(this_player()) +
        "与本派素无来往，不知此话从何谈起？";
        return "语嫣是我表妹，她经常到还施水阁来研习各派武学。\n";
}


string ask_ge()
{
	mapping fam;
        object ob;
        if (!(fam = this_player()->query("family"))
           || fam["family_name"] != "姑苏慕容")
                return RANK_D->query_respect(this_player()) +
                "与本派素无来往，不知此话从何谈起？";
                return "还施水阁是我慕容收藏天下秘籍之所在。\n";
}

string ask_sword()
{
	mapping fam;
        object ob;
        if (!(fam = this_player()->query("family"))
           || fam["family_name"] != "姑苏慕容")
                return RANK_D->query_respect(this_player()) +
                "与本派素无来往，不知此话从何谈起？";
                return "碧玉剑是老爷子仙逝后的遗物，我让阿朱姑娘收起来好好保管！\n";
}

string ask_bo()
{
        mapping fam;
        if(!(fam = this_player()->query("family"))
        || fam["family_name"] != "姑苏慕容")
                return RANK_D->query_respect(this_player()) +
                "与本派素无来往，不知此话从何谈起？";
        	return "老爷子已然仙逝了，我每年清明和邓大哥给他老人家扫墓。\n";
}

string ask_learn()
{
	object *ob;
	mapping skills = skills[random(sizeof(skills))];
	mapping fam;
	int i;
	i = 10+random(5);
	ob = all_inventory(environment(this_player()));
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "姑苏慕容") // 必须是慕容派弟子
		return RANK_D->query_respect(this_player()) +
		"与本派素无来往，不知此话从何谈起？";
	if( (int)this_player()->query_skill("parry", 1) < 100 ) // 招架必须大于等于100级
		return RANK_D->query_respect(this_player()) +
		"于本门武学尚不能运用自如，如何谈及天下之武学？";
	if( (int)this_player()->query_skill("douzhuan-xingyi", 1) < 100 )  // 斗转星移必须大于等于100级
		return RANK_D->query_respect(this_player()) +
		"于本门武学尚不能运用自如，如何谈及天下之武学？";
	if( this_player()->query_condition("mr_job") )
		return RANK_D->query_respect(this_player()) +
		"还没完成我交给你的任务呢。";
	if( this_object()->is_fighting())
		return "嚷什么嚷，没看见我这正忙着呢吗？";
	if( (int)this_player()->query_condition("wait_mr_job", 1) > 0)
		return RANK_D->query_respect(this_player()) +
		"先等等吧，我现在没有什么感兴趣的武功想学。";
	if( this_player()->query("gender") == "无性")
		return "公子我最讨厌不男不女之人。";
	if( sizeof(ob) > 3 )
		return "你疏于练功，老想偷学天下之武学，对你毫无好处。";

	this_player()->set_temp("skill_target", skills["skill_name"]);  // 此标记表明此次偷学目标技能的中文名字
	this_player()->set_temp("skill_id", skills["skill_id"]); // 此标记表明此次偷学目标技能的英文名字
	this_player()->set_temp("skill_type", skills["skill_type"]); // 此标记表明此次偷学目标技能的英文类型
	this_player()->set_temp("skill_lvl", i); // 此标记表明此次偷学目标技能所需要的级别
	this_player()->apply_condition("mr_job", 50); // 设置此次任务必须在所需时间内完成
        message_vision(HIG"$N朝旁边招了招手。\n"NOR, this_object());
        message_vision(HIG"$N的弟子走了过来。\n"NOR, this_player());
        message_vision(CYN"$N说道：我姑苏慕容傲视天下所有武功，但也不乏为之羡慕的。\n"NOR, this_object());
        message_vision(CYN"$N对着"+this_player()->name()+"的弟子说道：让你也出去见识见识。\n"NOR, this_object());
        new(__DIR__"job-dizi")->move(environment(this_player()));
	return "好吧，"HIY+"「"+skills["skill_name"]+"」"HIR"「"+skills["skill_id"]+"」"CYN"我垂涎已久，你们把它学回来，我大大的有赏。\n";

}

int ask_fuming(string arg)
{
       	object me, ob, obj;
	me = this_player();
	ob = this_object();
	if( !arg)
	{
        	command("say 你要展示什么？");
        	return 1;
        }

	if( !me->query_condition("mr_job"))
	{
		command("say 你现在没有任务吧？");
		return 1;
	}

	if( !objectp(obj = present("dizi", environment(ob))))
	{
		command("say 你的弟子呢？");
		return 1;
	}

	if( objectp(obj = present("dizi", environment(ob))) && obj->query("family/master_id") != me->query("id"))
	{
		command("say 这个弟子好象不是你的吧？");
		return 1;
	}

	if( me->is_busy())
	{
		command("say 你正忙着呢，有什么事情呆会再说。");
		return 1;
        }

	if( me->is_fighting())
	{
		command("say 你正打架呢，有什么事情呆会再说。");
		return 1;
        }
	if( (int)obj->query_skill(obj->query_temp("skill_id"), 1) < (int)obj->query_temp("skill_lvl") )
        {
                command("say 你学到什么东西了？还有脸敢回来？");
                return 1;
        }
       	if( this_object()->is_fighting())
	{
		command("say 嚷什么嚷，没看见我这正忙着呢吗？");
		return 1;
	}

        if( obj->query("id") == "dizi" && obj->query("family/master_id") == me->query("id"))
        {
        	me->start_busy(21);
         	ob->fight_ob(obj);
		message_vision("\n$N对着$n的弟子说道：既然你们回来了，必有所成，就让公子我看看吧！ "
			+ RANK_D->query_self(ob)
			+ ob->name() + "，跟"
			+ RANK_D->query_respect(obj) + "讨教几招！\n\n", ob, me);
		obj->fight_ob(ob);
		message_vision("\n$N的弟子对着$n说道：弟子不敢，然后摆一起手式，"
			+ RANK_D->query_self(obj)
			+ "，领教公子高招！\n\n", me, ob);

	        call_out("halt", 20, ob);
        	return 1;
        }
}

int halt()
{
	object me, ob;
	me = this_player();
	ob = this_object();
	command("halt");
        message_vision(CYN"\n慕容复哈哈大笑起来。\n\n"NOR, me);
	call_out("confirm", 1, me);
	return 1;
}

int confirm()
{
	object obj, me, ob;
	string name;
	int bouns;
	me = this_player();
	ob = this_object();
	obj = present("dizi", environment(ob));
	name = obj->query_temp("skill_target");
	bouns = (int)me->query_temp("skill_lvl")*5/2;
	bouns = bouns + (int)me->query_skill("douzhuan-xingyi", 1)/2;
	bouns = bouns + (int)me->query_int();
	message_vision(CYN"慕容复“啊”的一声，情不自禁地说道：好一个"+name+"。\n"NOR, me);
	message_vision(CYN"慕容复拍了拍$N的头，对$N说道：辛苦你了，下去休息吧。\n"NOR, me);
	me->add("combat_exp", (int)bouns*3/2);
	me->improve_skill("douzhuan-xingyi", me->query_int()*4);
	if( ((int)me->query("potential", 1)+bouns) >= (int)me->query("max_pot", 1))
	{
		me->set("potential", (int)me->query("max_pot"));
	}
        if( ((int)me->query("potential", 1)+bouns) < (int)me->query("max_pot", 1))
        {
	  	me->add("potential", bouns);
        }
	if( objectp( obj = present("dizi", environment(ob))))
  	{
  		message_vision(CYN"\n慕容复对着$N的弟子说道：你也辛苦了，下去休息吧。\n\n"NOR, me);
  		message_vision(CYN"\n$N的弟子深深一拜，说道：谢过庄主和师傅。\n\n"NOR, me);
	     	destruct(obj);
	}
	log_file("static/TOUXUE",
        sprintf("%s %s(%s) touxue %s(%s) on %s。\n",
	this_player()->query("title"), this_player()->name(1), geteuid(this_player()),
	this_player()->query_temp("skill_target"), this_player()->query_temp("skill_id"), ctime(time()) ));
	me->delete_temp("skill_target");
        me->delete_temp("skill_id");
        me->delete_temp("skill_type");
        me->delete_temp("skill_lvl");
        me->clear_condition("mr_job");
        me->apply_condition("wait_mr_job", 5);
        return 1;
}
/*
void relay_message(string msgclass, string msg)
{
        object room;
        string *ary;
        int i;

        msg = "1\n" + msg;
        ary = explode(msg, "\n");
        room = load_object(environment(this_object())->query("dest_room"));
        for (i=1;i<sizeof(ary);i++)
        if (room) message("vision", HIY"【燕子坞】"NOR+ary[i]+NOR+"\n", room);
}
  */