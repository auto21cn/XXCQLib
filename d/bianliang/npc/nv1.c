// 迎宾少女。
//星君千圣 1999-12-14。

#include <ansi.h>
inherit NPC;

int do_hunli();

void create()
{
      
        set_name( HIR"迎宾少女"NOR, ({ "girl" }));
        set("gender", "女性");
        set("age", 20);
        set("long", "她就是红娘庄专门带宾客参加婚礼的迎宾少女。\n");
        set("combat_exp", 7000);
        set("shen_type", 1);
        set("attitude", "peaceful");
        
        set_skill("unarmed", 40);
        set_skill("dodge", 40);
        set_temp("apply/attack", 20);
        set_temp("apply/defense", 20);
        set("inquiry", ([
                "婚礼"     : (: do_hunli :),
                "参加婚礼" : (: do_hunli :),
        ])); 
        setup();
        carry_object("/clone/misc/cloth")->wear();
//      add_money("silver", 2);

}
int do_hunli()
{
  object me, ob ;
  
  me= this_player();

  ob= this_object();

 if (!( present("qing tie", me)) )
        {
say ("迎宾少女福了一福：“请贴有吗?”\n");
             return 1;
        }

  say("迎宾少女对"+(string)me->query("name")+"说：“你请跟我来。”\n");

  say((string)me->query("name")+"被带到了红娘庄。\n");

 me->move( "/d/bianliang/hongniang-zhuang" );

  return 1;
}  

