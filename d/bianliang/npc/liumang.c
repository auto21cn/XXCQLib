// waiter.c

inherit NPC;

void create()
{
               int value;
                    value = random(10);
          set("combat_exp", 2000 + 5 * value);
          set_name("流氓", ({ "liu mang" }));
    set("age", 24);
        set("gender", "男性");
        set("long", "一个看上去流里流气年轻人，不务正业到处流窜。");
        set("attitude", "peaceful");
          set("str", 24);
        set("dex", 16);
        set("shen", -800);
        set_skill("cuff", 20);
        set_skill("dodge", 20);
        set_skill("parry", 20);
        set_skill("force", 20);

        set("chat_msg", ({
                "流氓左顾右盼，不知在找什么。”\n",
        }));

         setup();
            carry_object("/clone/misc/cloth")->wear();
      add_money("silve", 15 + value);
}
