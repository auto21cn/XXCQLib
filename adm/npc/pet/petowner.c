// 出售宠物的小贩 NPC
// By 山猫Adx @ snow 99-12-12

#include <ansi.h>
inherit NPC;

int do_answer(string arg);
int pet_type(object me, string arg);
int pet_gender(object me, string arg);

void create()
{
        set_name("小贩", ({ "xiaofan" }) );
        set("gender", "男性" );
        set("age", 32);
        set("long","一个专门卖宠物的小贩\n");
        set("combat_exp", 5);
        set("chat_chance", 2);
        set("chat_msg", ({
                (: random_move :)
        }) );
        set("attitude", "friendly");
        setup();
        carry_object("/clone/misc/cloth")->wear();

}

void init()
{	
        object ob;
        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
	add_action("do_answer","answer");
}

void greeting(object ob)
{
	object obj;
        if( !ob || environment(ob) != environment() ) return;

	if(!ob->query("pet") && !present("pet book",ob)) {
		obj=new(__DIR__"petbook");
		obj->move(ob);
		message_vision("$N给了$n一本《饲养宠物》。\n",this_object(),ob);
	}
        switch( random(3) ) {
                case 0:
			command("say 这位"+RANK_D->query_respect(ob)
                                + "，要买只宠物么？每只一百两黄金！");
                        break;
                case 1:
			command("say 出售宠物啦！有小猫、小狗、"
				+"小猪、小猴、还有小鹰！每只一百两黄金！");
                        break;
                case 2:
			command("say 这位"+RANK_D->query_respect(ob)
                                + "，养只宠物吧！每只一百两黄金！");
                        break;
        }
}

int accept_object(object me, object ob)
{
	command("xixi");
	command("say 呵呵，多谢这位" + RANK_D->query_respect(me) + " ！");
    if(me->query("combat_exp")<100000||me->query("wizsong")==1)
		return notify_fail("你的实战经验不够，专心练功以后再养宠物吧！\n");
	if( ob->query("money_id"))
	{
		if(me->query("pet"))
		{
			command("say "+me->query("name")+ 
				"你不是已经有宠物了吗？怎么不喜欢？");
			return 0;
		}
		if(ob->value() < 1000000)
		{
			command("say 这位给的未免少了点！每只宠物要一百两黄金！");
			return 0;
		}
		else
		{
			me->set("pet/money",1);
			command("say 好我收下了！");
			command("say "+me->query("name")
				+"现在我这里有：小猫、小狗、小猪、小猴、小鹰这几种宠物！");
			command("say 请选择你要的动物 answer <type>");
			return 1;
		}
	}
	return 1;
}

int do_answer(string arg)
{
	object me=this_player();
	int i=me->query("pet/money");

	if (! arg || arg == "")
	{
		command("say 这位"+RANK_D->query_respect(me)+"，每只宠物一百两黄金！");
		return 0;
	}

	switch(i) {
	case 1 : pet_type(me, arg); break;
	case 2 : pet_gender(me, arg); break;
	default: command("say 这位"+RANK_D->query_respect(me)+"，每只宠物一百两黄金！");
	}
	return 1;
}

int pet_type(object me, string arg)
{
	string msg, msgid;
	msg=me->query("name")+"的宠物";
	msgid=me->query("id")+"'s ";

        switch( arg ) {
                case "小猫":
			me->set("pet/type", "cat");
			me->set("pet/name",(msg+"猫"));
			me->set("pet/id",(msgid+"cat"));
			break;
                case "小狗":
			me->set("pet/type", "dog");
			me->set("pet/name",(msg+"狗"));
			me->set("pet/id",(msgid+"dog"));
			break;
                case "小猪":
			me->set("pet/type", "pig");
			me->set("pet/name",(msg+"猪"));
			me->set("pet/id",(msgid+"pig"));
			break;
                case "小猴":
			me->set("pet/type", "monkey");
			me->set("pet/name",(msg+"猴"));
			me->set("pet/id",(msgid+"monkey"));
			break;
                case "小鹰":
			me->set("pet/type", "hwak");
			me->set("pet/name",(msg+"鹰"));
			me->set("pet/id",(msgid+"hawk"));
			break;
		default:
			command("say "+me->query("name")
				+"现在我只有：小猫、小狗、小猪、小猴、小鹰这几种宠物！");
			break;
	}
	me->set("pet/money", 2);
	command("say 哦！"+me->query("name")+"你想要只"+arg+"！");
	command("say 请给选择你的宠物性别！answer <雄性> or <雌性>");
	return 1;
}

int pet_gender(object me, string arg)
{
        switch( arg ) {
                case "雄性":
			me->set("pet/gender", arg);
			command("say 哦！"+me->query("name")+"你想要雄性的宠物！");
			break;
                case "雌性":
			me->set("pet/gender", arg);
			command("say 哦！"+me->query("name")+"你想要雌性的宠物！");
			break;
		default:
			command("say 请给选择你的宠物性别！answer <雄性> or <雌性>");
			break;
	}
        me->start_busy(2);
	me->set("pet/path",("/data/pet/"+me->query("id")+".o"));
	me->set("pet/money", 3);
	call_out("grow", 1, me);
	return 1;
}

int grow(object me)
{
	object newpet;
	if (me->query("pet/money")!=3) return 1;
	me->set("pet/money","ok");
	seteuid(ROOT_UID);
	newpet = new("/adm/npc/pet/pet");
	newpet->set("owner",me->query("id"));
	newpet->set("possessed",me);
	newpet->set("name",me->query("pet/name"));
	newpet->set("id",me->query("pet/id"));
	newpet->set("gender",me->query("pet/genter"));

        switch( me->query("pet/type") ) {
                case "cat":
			newpet->set("str",random(20)+10);
			newpet->set("int",random(20)+10);
			newpet->set("con",random(20)+10);
			newpet->set("dex",random(20)+10);
			newpet->set("kar",random(40)+10);
			break;
                case "dog":
			newpet->set("int",random(20)+10);
			newpet->set("con",random(20)+10);
			newpet->set("dex",random(20)+10);
			newpet->set("kar",random(20)+10);
			newpet->set("str",random(40)+10);
			break;
                case "pig":
			newpet->set("str",random(20)+10);
			newpet->set("int",random(20)+10);
			newpet->set("dex",random(20)+10);
			newpet->set("kar",random(20)+10);
			newpet->set("con",random(40)+10);
			break;
                case "monkey":
			newpet->set("str",random(20)+10);
			newpet->set("con",random(20)+10);
			newpet->set("dex",random(20)+10);
			newpet->set("kar",random(20)+10);
			newpet->set("int",random(40)+10);
			break;
                case "hwak":
			newpet->set("str",random(20)+10);
			newpet->set("int",random(20)+10);
			newpet->set("con",random(20)+10);
			newpet->set("kar",random(20)+10);
			newpet->set("dex",random(40)+10);
			break;
	}
        switch( me->query("pet/gender") ) {
                case "雌性":
			newpet->set("max_jingli",(random(100)+100));
			newpet->set("max_qi",(random(100)+100));
			newpet->set("xing",(random(500)+100));
			newpet->set("kill",random(500));
			break;
                case "雄性":
			newpet->set("max_jingli",(random(200)+100));
			newpet->set("max_qi",(random(200)+100));
			newpet->set("xing",(random(500)+300));
			newpet->set("kill",random(1000));
			break;
	}
	newpet->save();
	destruct(newpet);
	command("say 你可以吹声口哨召唤你的宠物！<whistle>\n");
        seteuid(getuid());
	return 1;
}
