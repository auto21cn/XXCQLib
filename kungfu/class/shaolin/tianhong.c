// Npc: /kungfu/class/shaolin/xuan-ci.c
// Date: YZC 96/01/19

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
int ask_enter();

void create()
{
        set_name("天鸿", ({
                "tian hong",
                "tian",
                "hong",
        }));
        set("long",
                "他是一位须发花白的老僧，身穿一袭金边黑布袈裟。他身材瘦高，\n"
                "太阳穴高高鼓起，似乎身怀绝世武功。\n"
        );

	set("nickname", HIR"伏虎罗汉"NOR);
        set("gender", "男性");
        set("attitude", "friendly");
        set("class", "bonze");

        set("age", 50);
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 1500);
        set("max_jing", 1000);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 150);
        set("combat_exp", 1000000);
        set("score", 500000);
/*
        set_skill("force", 110);
        set_skill("hunyuan-yiqi", 110);
        set_skill("dodge", 110);
        set_skill("shaolin-shenfa", 110);
        set_skill("finger", 110);
        set_skill("strike", 110);
        set_skill("hand", 110);
        set_skill("claw", 110);
        set_skill("parry", 110);
        set_skill("nianhua-zhi", 110);
        set_skill("sanhua-zhang", 110);
        set_skill("fengyun-shou", 110);
        set_skill("longzhua-gong", 110);
        set_skill("buddhism", 110);
        set_skill("literate", 110);

        map_skill("force", "hunyuan-yiqi");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("finger", "nianhua-zhi");
        map_skill("strike", "sanhua-zhang");
        map_skill("hand", "fengyun-shou");
        map_skill("claw", "longzhua-gong");
        map_skill("parry", "nianhua-zhi");

        prepare_skill("finger", "nianhua-zhi");
        prepare_skill("strike", "sanhua-zhang");
*/
        create_family("少林派", 36, "弟子");
        setup();
        set("inquiry", ([
                "enter" : (: ask_enter :),
                "进入" : (: ask_enter :),
        ]) );

        carry_object("/d/shaolin/npc/obj/heijiasha")->wear();
        carry_object("/d/shaolin/npc/obj/sengxie")->wear();
}

int ask_enter()
{
        object me,ob;
        me = this_player();
        ob = this_object();

        if ( me->query_temp("kfroom_6"))
        {
                command("?");
                command("say 已经允许你进去了还问什么？");
                return 1;
          }
        else if ( !me->query("family") || me->query("family/family_name") != "少林派")
        {
                command("shake");
                command("say 你不是少林弟子，不能进入进武房。");
                return 1;
        }
        else if ( me->query_condition("kf_job") )
        {
                command("say 你刚从功夫房出来，暂时不能进去练功。");
                return 1;
        }
        else if ( environment(ob)->query_temp("kfroom_6") )
        {
                command("say 现在有弟子在里面，你等一会吧。");
                return 1;
        }

        else if ( me->query("combat_exp") < 800000 )
        {
                command("say 你的功力不足,还是先去穷武房打好基础吧。");
                return 1;
        }
	else if (me->query("combat_exp") > 1000000)
        {
                command("say 你的功夫已经相当不错了，不需要在武房练功啦。");
                return 1;
        }
        else
        {
                command("say 好吧，你进去吧，千万小心，撑不住了就出来。");
                message_vision(HIW"\n$N伸手在座垫下摸了摸，座垫下发出了喀嗒一声轻响。\n"NOR,ob);
                message_vision(HIW"\n突然$N的身后闪出两个木人，将$N架进了进武房。\n"NOR,me);
                me->set_temp("kfroom_6",1);
                environment(me)->set_temp("kfroom_6",1);
                me->move("/d/shaolin/kfroom_6");
                call_out("check",100,me,ob);
                return 1;
        }
}

void check(object me,object ob)
{
        if (environment(ob)->query_temp("kfroom_6"))
        {
                command("?");
                command("say 怎么还不出来呢？");
                command("say 算了，不管他了。");
                environment(ob)->delete_temp("kfroom_6");
        }
}
