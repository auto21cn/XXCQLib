

// NPC: zhangxuemian.c

// Created by Atlus 1999.7.23

// Modified by M.A.D. 1999.7.21

// 

// 



inherit NPC;

#include <ansi.h>



void init();

void greeting(object);

int give_task(string);

int do_join(string arg);

int do_uplevel(string arg);

void delete_served(object);

int consider_lv(object ob,int a);



void create()

{

        set_name("张雪眠", ({ "zhang xuemian" , "zhang"}) );

        set("nickname", HIC"飞鱼总管"NOR );

        set("gender", "男性" );

        set("age", 45);

        set("long",

                "张雪眠是飞鱼塘的总管，也是飞鱼塘中仅存的三个“死人”之一。他负责处理飞鱼塘的一切日常事物。\n"+

                "他内外兼修，一副非常精明的样子。\n");

        set("attitude", "friendly");



        set("qi", 250);

        set("max_qi", 250);

        set("jingli", 250);

        set("max_jingli", 250);

        set("neili", 400);

        set("max_neili", 400);

        set("jiali", 50);



        set("combat_exp", 1000000);



        create_family("飞鱼塘", 2, "弟子");



        set("inquiry", ([

            "加入" : (: do_join :),

            "job": (: give_task :),

        ]) );



        setup();

        

        carry_object("/d/feiyu/obj/chouduan")->wear();

}

        

void init()

{

        object ob;



        add_action("give_task", "task");

        add_action("give_uplevel", "uplevel");



        ::init();



        if( interactive(ob = this_player()) && !is_fighting() ) {

                 remove_call_out("greeting");

                 call_out("greeting", 1, ob);

        }

}



void greeting(object ob)

{

        if( !ob || environment(ob) != environment() ) return;



        if (ob->query("feiyutask/reg")) {

                 say("张雪眠说道：“这位" + RANK_D->query_respect(ob)

                 + "你想为飞鱼塘出力吗，向我要任务吧(task)。”\n");

        }

        else {

                 say("塘中弟子不多，还有不少体力活要干呢。”\n");

        }

}



int do_join(string arg)

{

        object me;



        me=this_player();



        if (!(string)me->query("family") || (string)me->query("family/family_name") != "飞鱼塘") {

                message_vision("张雪眠恭敬地对$N说：“你不是飞鱼弟子，如何敢劳您的大架?\n”",me);

                return 1;

        }



        if (me->query("feiyutask/reg")) {

                command("angry "+me->query("id"));

                message_vision("张总管对$N说：“你已经登记过了，还在糊弄什么?”\n",me);

                return 1;

        }



        me->set("feiyutask/reg",1);

        me->set("feiyutask/done",1);

        me->set("feiyutask/first",1);

        me->set("title",RED"飞鱼人"NOR);

        command("smile " + me->query("id"));

        message_vision("张总管微笑地对$N说道：“好好干吧，飞鱼塘的壮大就靠你们这些人了!”\n",me);



        return 1;

}



int give_task(string arg)

{

        object me,givesilver;

        int givepot,giveexp,i,tasktime;



        me=this_player();



        message_vision("$N向张总管询问了做任务的具体情况!\n",me);



        if ( arg || arg == "ok" ) { //如果玩家输入task ok，那么表示玩家完成任务。

                if( me->query_temp("feiyutask/given") && me->query_temp("di1mark") && me->query_temp("di2mark") && me->query_temp("di3mark")  && me->query_temp("di4mark")  ) {

                        command("pat " + me->query("id"));

                        message_vision("张总管对$N说：“好，你已经完成任务，这是你的报酬!”\n",me);

                        if ( me->query("feiyutask/first")) {

                                message_vision(HIY"张总管微笑地对$N说：“第一次做任务就有这样的成绩，要给你特别奖赏!”\n"NOR,me);

                                me->add("potential", 100+random(300));

                                me->add("combat_exp", 300+random(400));

                                givesilver=new("/clone/money/gold");

                                givesilver->move(me);

                                me->set("feiyutask/first",0);

                        }
                        
                        givepot=30+random(20);

                        giveexp=200+random(50);

						me->add("feiyutask/done",1);

                        tasktime=me->query("feiyutask/done");

                        me->add("potential", givepot);

                        me->add("combat_exp", giveexp);

                        message_vision(HIY"$N被奖励了"+chinese_number(givepot)+"点潜能和"+chinese_number(giveexp)+"点经验。\n"NOR,me);

                        for (i=1;i<2+random(4);i++) {

                        givesilver=new("/clone/money/silver");

                        givesilver->move(me);}

                        message_vision(HIC"$N已经为飞鱼塘完成了"+chinese_number(tasktime)+"次任务。\n"NOR,me);

                        message_vision(HIC"张总管拿出几两银子，奖给了$N。\n"NOR,me);

                        me->delete_temp("feiyutask/done");

                        me->delete_temp("feiyutask/given");

                        me->delete_temp("di1mark");

                        me->delete_temp("di2mark");

                        me->delete_temp("di3mark");

                        me->delete_temp("di4mark");

                        me->set_temp("busying", 1);

                        call_out("delete_served", 120, me);

            

                

                return 1;

                }

                else if ( !(me->query_temp("feiyutask/given")) ) {

                        command("angry " + me->query("id"));

                        message_vision("张总管对$N说：“你还没有领任务做!”\n",me);

                        return 1;

                }

                else if ( me->query_temp("feiyutask/given") ) {

                        command("angry " + me->query("id"));

                        message_vision("张总管对$N说：“你领了任务不赶快去做，超时完成是无效的!”\n",me);

                        return 1;

                }

        }        



        if ( !(me->query("feiyutask/reg"))) {

                if (!(string)me->query("family") || (string)me->query("family/family_name") != "飞鱼塘") {

                        message_vision("张雪眠恭敬地对$N说：“你不是飞鱼弟子，如何敢劳您的大架?”\n",me);

                return 1;

                } {

                message_vision("张总管对$N说：“请你登记一下，再来领任务!”\n",me);

                return 1;}                

        }

        

        if( (int)me->query("combat_exp") < 50000) {

                        message_vision("张雪眠对$N说： “你在这里干这个太危险了，去找些别的工作吧？” \n",me);

                 return 1;}

 

        if ( me->query_temp("feiyutask/given") ) {

                command("angry " + me->query("id"));

                message_vision("张总管对$N说：“你领了任务不赶快去做，超时完成是无效的！”\n",me);

                return 1;

        }

        

        if ( me->query_temp("busying") ) {

                message_vision("张总管对$N说：“你刚刚才劳动回来，先去休息一会儿吧。” \n",me);

                return 1;

        }

                

        me->set_temp("feiyutask/given",1);

        message_vision("张总管对$N说：“你去四处巡查一下,有什么情况回来报告!”\n",me);



        remove_call_out("clone_killer");

        call_out("clone_killer", 30+random(15), me, 0);



        return 1;

}



int give_uplevel(string arg)

{

        object me;

        int donenum;

        int exp;

        

        me=this_player();

        donenum=(int)me->query("feiyutask/done");

        exp=(int)me->query("combat_exp");

        

        if ( donenum>300 && exp<50000 ){

                me->set("title",RED"飞鱼人"NOR);

                message_vision("张总管对$N说：“你就是飞鱼塘的人了。”\n",me);

                return 1;

        } else if ( donenum<600 && exp>50000 ) {

                me->set("title",GRN"新秀"NOR);

                message_vision("张总管对$N说：“恭喜你!从今天开始你就是飞鱼塘的新秀了。”\n",me);

                return 1;



        } else if ( donenum<900 && exp>100000 ) {

                me->set("title",GRN"中秀"NOR);

                message_vision("张总管对$N说：“恭喜你!经过“老头子”的推荐，从今天开始你就是飞鱼塘的中秀了。”\n",me);

                return 1;

        } else if ( donenum<1500 && exp>200000 ) {

                me->set("title",YEL"老秀"NOR);

                message_vision("张总管对$N说：“不错!经过“老头子”的推荐，从今天开始你就是飞鱼塘的老秀了。”\n",me);

                return 1;

        } else if ( donenum<2000 && exp>400000 ) {

                me->set("title",BLU"老头子"NOR);

                message_vision("张总管高兴对$N说：“庄主决定从今天开始提升你为我们飞鱼塘的“老头子”。”\n",me);

                return 1;

        } else if ( donenum<2500 && exp >800000) {

                me->set("title",MAG"死人"NOR);

                message_vision("张总管恭敬地对$N说：“兄弟，从今天开始你就是飞鱼塘的“死人”了，你我已经平起平坐，不须多礼了。”\n",me);

                return 1;

        } else if (donenum>3000 && exp >1200000) {

                me->set("title",CYN"婴孩"NOR);

                message_vision("张总管恭敬地对$N说：“经过大家的讨论，一致决定从今天开始你就是辈分最高的“婴孩”了，日后请多多包涵！”\n",me);

                return 1;

        }

        message_vision("张总管对$N说：“你对飞鱼塘的贡献还不够，不能让你升级。”\n",me);

        return 1;

}



void delete_served(object me)

{

      if ( objectp(me) ) me->delete_temp("busying");

}



int clone_killer(object me,int stage)

{

        object killer;



        killer=new(__DIR__"killer");

        killer->move(environment(me));



        killer->set("combat_exp",me->query("combat_exp")-random(10000));

        killer->set("max_qi",me->query("max_qi"));

        killer->set("eff_qi",me->query("max_qi"));

        killer->set("qi",me->query("max_qi"));

        killer->set("max_jingli",me->query("max_jingli"));

        killer->set("eff_jingli",me->query("max_jingli"));

        killer->set("jingli",me->query("max_jingli"));

        killer->set("max_neili",me->query("max_neili"));

        killer->set("neili",me->query("max_neili"));

        killer->set_skill("parry", consider_lv(killer, 10));

        killer->set_skill("dodge", consider_lv(killer, 10)); 

        killer->set_skill("sword", consider_lv(killer, 10)); 

        killer->set_skill("cuff", consider_lv(killer, 10)); 
		
		killer->set_skill("force", consider_lv(killer, 10)); 
		
		killer->set("jiali", 50);



        me->kill_ob(killer);

        killer->kill_ob(me);



        return 1;

}

int consider_lv(object ob,int a)

{

        int level; 

        float exper;



        exper = to_float(ob->query("combat_exp"));

        level = ceil( pow( exper*10.0, 0.333333) );



        level = level * a / 10;



        return level;

}
