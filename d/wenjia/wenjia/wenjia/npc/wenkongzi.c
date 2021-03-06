// NPC: wenkongzi.c
// Created by Zeus 1999.3.28
// Modified by Zeus 1999.7.12
// 
// 

#include <ansi.h>

inherit NPC;
int ask_teach();
void greeting(object);
void init();

void create()
{
        set_name("温孔子", ({ "wen kongzi", "wen"}) );
        set("gender", "男性" );
        set("nickname",MAG"赛孔子"NOR);
        set("age", 25+random(10));
        set("long",
                "温孔子是温家肚子里墨水最多的人。\n");

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
        ]) );

	create_family("老字号温家", 4, "弟子");

        setup();
}

void init()
{	
        object ob;

        ::init();
        add_action("do_xue", "wen");

        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;

        say("温孔子看见有人进来，放下手中的书，说道：“这位" + RANK_D->query_respect(ob)
             + "是到我这里来学习的吗?”\n");
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

	message_vision("温孔子温和的笑了笑道："+RANK_D->query_respect(me)+"你是来求学的？\n", me);
	command("look "+me->query("id"));

	if ((int)me->query_skill("literate", 1) > 31)
	{
		message_vision("\n温孔子谦逊的笑了笑道：这位"+RANK_D->query_respect(me)+"颇有学识，在下愧不敢教。\n\n", me);
		return 1;
	}

	else if ((int)me->query("age") > 18)
	{
		message_vision("\n温孔子笑着摇了摇头道：乡野小堂，也就是教教孩子，可不敢教您。\n\n", me);
		return 1;
	}

	else
	{
		message_vision("\n温孔子高兴的说：好好，快做好。\n\n", me);
		message_vision("$N走到一个空座前坐了下来。\n\n", me);
		me->apply_condition("xuetang", 10);
		me->set_temp("xuet", 1);
		return 1;
	}
}