// ding.c 家丁

inherit NPC;

int ask_teach();
int ask_book();

void create()
{
        set_name("杜先生", ({ "du xiansheng", "du", "xiansheng" }));
        set("age", 25);
        set("title", "草堂主人");
        set("gender", "男性");
        set("long", "他是文儒的中年人，在这里开堂授课已经好几年了，据说他是杜甫的\n玄孙，可是问起时他总是笑着摇头。\n");
        set("attitude", "friendly");

        set("str", 24);
        set("dex", 16);
        set("combat_exp", 10000);
        set("shen_type", 1);

        set_skill("strike", 20);
        set_skill("dodge", 30);
        set_skill("parry", 20);
        set_skill("force", 20);
        set_temp("apply/attack", 30);
        set_temp("apply/defense", 20);
        set_temp("apply/damage", 20);
        set_temp("apply/armor", 20);

        set("inquiry", ([
                "study" : (: ask_teach :),
                "听课" : (: ask_teach :),
                "学习" : (: ask_teach :),
                "literate" : (: ask_teach :),
                "book" : (: ask_book :),
                "confu" : (: ask_book :),
        ]) );

        setup();

        carry_object("/clone/misc/cloth")->wear();
}

int ask_teach()
{
        object me,ob;
        me = this_player();
        ob = this_object();

        if ( me->query_temp("xuet"))
        {
                tell_object(me,"你不是正在学习吗?\n ");
                return 1;
        }

        message_vision("杜先生温和的笑了笑道："+RANK_D->query_respect(me)+"可是来求学的？\n\n", me);
        command("look "+me->query("id"));

        if ((int)me->query_skill("literate", 1) > 31)
        {
                message_vision("\n杜先生谦逊的笑了笑道：这位"+RANK_D->query_respect(me)+"颇有学识，在下愧不敢教。\n\n", me);
                return 1;
        }

        else if ((int)me->query("age") > 18)
        {
                message_vision("\n杜先生笑着摇了摇头道：乡野小堂，也就是教教孩子，可不敢教您。\n\n", me);
                return 1;
        }

        else
        {
                message_vision("\n杜先生高兴的说：好好，快做好。\n\n", me);
                message_vision("$N走到一个空座前坐了下来。\n\n", me);
                me->apply_condition("xuetang", 10);
                me->set_temp("xuet", 1);
                return 1;
        }
}

int ask_book()
{
        object me, ob;
        me = this_player();

        if (this_object()->query("no_book"))
        {
                command("say 难得" +RANK_D->query_respect(me)+
                "有心学习我们儒家的思想，但我的那本《中庸》已经送人了，真是抱歉。");
                return 1;
        }

        if (me->query_skill("confu",1)>50)
        {
                command("say "+RANK_D->query_respect(me)+
                "似是饱学之士，《中庸》早已熟读，我实在帮不上什么帮。");
                return 1;
        }

        ob = new(__DIR__"obj/zhongyong");
        ob->move(this_object());

        command("say " +RANK_D->query_respect(me)+
                "有心学习我们儒家的思想真是太好了，这里一本《中庸》你拿去读读吧，或有好处。");
        command("give " + me->query("id") + " book");
        this_object()->set("no_book",1);
        return 1;
}
