// qi.c 戚恋霞


inherit NPC;
inherit F_MASTER;
#include <ansi.h>

void create()
{
    set_name("门卫", ({ "men wei", "wei" }));
    set("gender", "男性");
	set("age", 23);

	set("combat_exp", 60000);
        set_skill("tao",50);
        set_skill("parry",50);
        set_skill("cuff",50 );
        set_skill("force", 50);
        set_skill("dodge", 50);
        set_skill("bairen-shengong",50);
        
        map_skill("force","bairen-shengong");
	
        create_family("发梦二党",4,"弟子");
	setup();
	carry_object("/clone/misc/cloth")->wear();
    carry_object("/clone/weapon/gangdao")->wield();
}

void die()
{
        message_vision("$N惨嚎一声，死了！\n", this_object());
        destruct(this_object());
}

/*
void init()
{
	object ob;

	::init();
	add_action("do_join","join");
  if( interactive(ob = this_player()) && !is_fighting() ) {^M

		remove_call_out("greeting");
		call_out("greeting", 50, ob);
    } 
}

int do_join(string arg)
{
   	object ob;
   	object mee;
   	mapping party;
   	
   	ob = this_player () ;
   	mee=this_object();
   	if( !arg || arg!="fameng" )
		return notify_fail("你要加入什么组织？\n"); 
   	if ((int)ob->query("shen") < 0)
        {
	message_vision(HIC "戚恋霞对$N大怒道：一看你就不是好人!\n" NOR,this_player());
//	set_leader(this_player());
	remove_call_out("kill_ob");
	call_out("kill_ob", 1, this_player()); 
  	return 1;
	}
      	if ((int)ob->query("shen") < 1000)
        {
	message_vision(HIC "戚恋霞摇摇头道：你还不够侠义!\n" NOR,this_player());
  	return 1;
	}
   	if (ob->query("combat_exp")<10000)
        {
	message_vision(HIC "戚恋霞对$N摇头道：你的实战经验太低。\n" NOR,this_player());
  	return 1;
  	}
    	if( !mapp(party = ob->query("party")))
   	{
		party = allocate_mapping(5);
		party["party_name"] = HIG "发梦二党" NOR;
		party["rank"] = "党羽";
		party["level"] = 1;
		party["tasks"] = 0;
		party["enter_time"] = time();
		ob->set("party", party);

		command("smile");
		command("handshake "+this_player()->query("id"));
    		command("tell "+this_player()->query("id")+" 大家从此就是一家人了。\n");
		return 1;
	}
   	if( party["party_name"] != HIG "发梦二党" NOR )
	{
		message_vision("$N对$n摇摇头，说道：$n已经加入其他帮会了。\n",mee,ob);
		return 1;
	}
	if( party["party_name"] = HIG "发梦二党" NOR ) 
	{
		message_vision("$N摇摇头，对$n说道：你已经是我发梦二党的兄弟了。\n",mee,ob);
		return 1;
	}
}
	
*/
