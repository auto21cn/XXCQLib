// waiter.c

inherit NPC;

void create()
{
         int value;

         value = random(10);
       set_name("小男孩", ({ "kid" }));
           set("age", 8);
        set("gender", "男性");
          set("long", "这是一个年幼无知的小男孩，正在和小伙伴一起玩。");
        set("attitude", "peaceful");
        set("max_qi",50);
          set("str", 24);
        set("dex", 16);
          set("combat_exp", 200 + 5 * value);
                 set("shen", 0);

        set("chat_msg", ({
        }));

         setup();
           add_money("coin", 120 + value);
          carry_object("/clone/misc/cloth")->wear();
}
