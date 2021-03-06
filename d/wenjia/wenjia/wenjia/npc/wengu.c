// NPC: wengu.c
// Created by Zeus 1999.5.28
// Modified by Zeus 1999.7.11
// 
// 

inherit NPC;
#include <ansi.h>

void init();
void greeting(object);
int do_join(string arg);
int uplevel();
int ask_cloth();

void create()
{
        set_name("温古", ({ "wen gu" , "wen"}) );
        set("nickname", HIC"古董管家"NOR );
        set("gender", "男性" );
        set("age", 60);
        set("long",
                "温古是温家的管家，他负责处理温家的一切日常事物。\n"+
                "他的头发黑白相间，一副非常精明的样子。\n");
        set("attitude", "friendly");

        set("qi", 500);
        set("max_qi", 500);
        set("jingli", 500);
        set("max_jingli", 500);
        set("neili", 100);
        set("max_neili", 100);
        set("jiali", 5);

        set("combat_exp", 10000);

        set_skill("dodge", 20);
        set_skill("parry", 20);
        set_skill("literate", 200);
        set_temp("apply/attack", 20);
        set_temp("apply/defense", 20);
        set_temp("apply/damage", 20);

        create_family("老字号温家", 6, "弟子");

        set("inquiry", ([
                "加入" : (: do_join :),
                "升级" : (: uplevel :),
                "服饰" : (: ask_cloth :),
        ]) );

        setup();

        add_money("silver", 50);
}

void init()
{	
        object ob;

        ::init();

        if( interactive(ob = this_player()) && !is_fighting() ) {
                 remove_call_out("greeting");
                 call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;

        if (!ob->query("wentask/reg")) {
                 say("温古停下手中的活，说道：“这位" + RANK_D->query_respect(ob)
                 + "你想干我们温家的任务吧，加入我们吧(ask wen about 加入)。”\n");
        }
        switch (random(2))
        {
                 case 0:
                 say("温古说道：“温家弟子可以在我这里领公用服装(ask wen about 服饰)。”\n");
                 break;
                 case 1:
                 say("温古说道：“干了一定数量的任务还可以升级(ask wen about 升级)呢!”\n");
                 break;
        }        
}

int do_join(string arg)
{
        object me;

        me=this_player();

        if (!(string)me->query("family") || (string)me->query("family/family_name") != "老字号温家") {
                message_vision("温古很客气地对$N说：“你不是我们温家的人，如何敢劳您的大架?\n”",me);
                return 1;
        }

        if (me->query("wentask/reg")) {
                command("angry "+me->query("id"));
                message_vision("温古对$N说：“你不是已经参加了温家工作吗，怎么又来了?”\n",me);
                return 1;
        }

        me->set("wentask/reg",1);
        me->set("wentask/done",1);
        me->set("wentask/dafirst",1);
        me->set("title",RED"温家低级家丁"NOR);
        command("smile " + me->query("id"));
        message_vision("温古对$N说道：“好好干吧，我们这些老头子已经老了，温家就靠你们这些人了!”\n",me);

        return 1;
}

int uplevel()
{
        object me;
        int donenum;

        me=this_player();
        donenum=(int)me->query("wentask/done");

        if ( donenum<150 ){
                me->set("title",RED"温家高级家丁"NOR);
                message_vision("温古对$N说：“不错!从今天开始你就是高级家丁了。”\n",me);
                return 1;
        } else if ( donenum<300 ) {
                me->set("title",GRN"温家家丁小头目"NOR);
                message_vision("温古对$N说：“不错!从今天开始你就是家丁小头目了。”\n",me);
                return 1;
        } else if ( donenum<500 ) {
                me->set("title",YEL"温家家丁大头目"NOR);
                message_vision("温古对$N说：“不错!从今天开始你就是家丁大头目了。”\n",me);
                return 1;
        } else if ( donenum<1000 ) {
                me->set("title",BLU"温家副管家"NOR);
                message_vision("温古对$N说：“不错!从今天开始你就是我们温家的副管家了。”\n",me);
                return 1;
        } else if ( donenum<1500 ) {
                me->set("title",MAG"温家副长老"NOR);
                message_vision("温古对$N说：“不错!从今天开始你就是我们温家的副长老了。”\n",me);
                return 1;
        } else {
                me->set("title",CYN"温家长老"NOR);
                message_vision("温古对$N说：“不错!从今天开始你就是我们温家长老了。”\n",me);
                return 1;
        }
        message_vision("温古对$N瞄了瞄，说：“别想这么多了，还是脚踏实地的做任务吧。”\n",me);
        return 1;
}

int ask_cloth()
{
        int mygener;
        object me,ob;

        me=this_player();
        
        mygener=me->query("family/generation");

        if ( !(string)me->query("family") || (string)me->query("family/family_name") != "老字号温家" ) {
                message_vision("温古很客气地对$N说：“你不是我们温家的人，怎么来问我要东西了。”\n",me);
                return 1;
        }

        switch (mygener)
        {
                case 7:{
                ob=new("/d/wenjia/obj/yelduanda");
                ob->move(me);
                message_vision("温古在身后的柜子里翻出了一件衣服。”\n",me);
                message_vision("温古对$N说：“拿着，这件衣服就是你的服饰。”\n",me);
                return 1;
                }
                case 6:{
                ob=new("/d/wenjia/obj/redduanda");
                ob->move(me);
                message_vision("温古在身后的柜子里翻出了一件衣服。”\n",me);
                message_vision("温古对$N说：“拿着，这件衣服就是你的服饰。”\n",me);
                return 1;
                }
                case 5:{
                ob=new("/d/wenjia/obj/grnduanda");
                ob->move(me);
                message_vision("温古在身后的柜子里翻出了一件衣服。”\n",me);
                message_vision("温古对$N说：“拿着，这件衣服就是你的服饰。”\n",me);
                return 1;
                }
                case 4:{
                ob=new("/d/wenjia/obj/yelduanda");
                ob->move(me);
                message_vision("温古在身后的柜子里翻出了一件衣服。”\n",me);
                message_vision("温古对$N说：“拿着，这件衣服就是你的服饰。”\n",me);
                return 1;
                }
                case 3:{
                ob=new("/d/wenjia/obj/chouduan");
                ob->move(me);
                message_vision("温古在身后的柜子里翻出了一件衣服。”\n",me);
                message_vision("温古对$N说：“拿着，这件衣服就是你的服饰。”\n",me);
                return 1;
                }
       }
       return 1;
}                