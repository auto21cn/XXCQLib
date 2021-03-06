// feng.c 风波恶

inherit NPC;
inherit F_MASTER;
#include "app.h"
int ask_here();
void create()
{
	set_name("风波恶",({"feng boe","feng","boe"}));
        set("title","玄霜庄庄主");
        set("nickname","一阵风");
  	set("long", "他就是姑苏慕容玄霜庄的庄主。\n");
        set("age", 25);
	set("attitude", "friendly");
        set("unique", 1);
	set("shen_type", 1);
	set("str", 26);
	set("int", 26);
	set("con", 26);
	set("dex", 26);
	
	set("max_qi", 2000);
	set("max_jing", 2000);
	set("neili", 2500);
	set("max_neili", 2500);
	set("jiali", 100);
	set("combat_exp", 850000);
	set("score", 85000);

        set_skill("strike",130);
        set_skill("dodge",130);
        set_skill("force", 130);
	set_skill("shenyuan-gong", 130);
	set_skill("yanling-shenfa", 130);
        set_skill("parry", 130);
	set_skill("xingyi-zhang", 130);
        set_skill("literate", 130);

	map_skill("force", "shenyuan-gong");
	map_skill("dodge", "yanling-shenfa");
        map_skill("parry", "xingyi-zhang");
        map_skill("strike", "xingyi-zhang");	
        prepare_skill("strike", "xingyi-zhang");
        setup(); 
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/blade")->wear();
       
        create_family("姑苏慕容",3,"弟子");
        set("inquiry", ([
            "name" : "我就是姑苏慕容玄霜庄庄庄主风波恶。\n",
            "here" : (: ask_here :),
            "rumors" : "最近少林寺一位大师被少林名技韦驮杵所害，天下人竟以为是慕容的以彼之道，还施彼身所为。\n",            
            "阿珠" : "阿珠住在听香水榭，是慕容公子的贴身丫鬟，跟阿碧两个人一同侍奉公子。\n",
            "阿碧" : "阿碧姑娘住在琴韵小筑，所有要拜见慕容公子的人都要由她那里经过。\n",
            "王语嫣" : "王姑娘是慕容公子的表妹，不知道什么时候他们成亲。\n",
            "邓百川" : "邓百川是我大哥，是燕子坞青云庄的庄主。\n",
            "公孙乾" : "公孙乾是我二哥，是燕子坞赤霞庄的庄主。\n",
            "包不同" : "包不同是我三哥，是燕子坞金凤庄的庄主，他老是喜欢说“非也，非也”。\n",
            "听香水榭" : "听香水榭是阿珠姑娘住的地方，离这里不远。\n",
            "琴韵小筑" : "琴韵小筑是阿碧姑娘住的地方，坐小舟有三九水路就到了。\n",
            "曼佗罗山庄" : "曼佗罗山庄是公子的姑妈住的地方，平时连我都不敢去。\n",
            "还施水阁" : "这是燕子坞的秘密之所在，我可不便对你说。\n",       
            "灵位" : "灵位不是摆在这里么？\n",            
]));
        
}

int ask_here()
{
	mapping fam; 
	int i;
	object me, ob, *obj;
	me = this_player();
	ob = this_object();
	obj = all_inventory(environment(ob));

        
        if( sizeof(obj) > 2)
        {
		for(i=0; i<sizeof(obj); i++)
		{
			if( obj[i]->is_character() && obj[i]->query("family/family_name") != "姑苏慕容")
			{
				command("say 有外人在这里还是不说也罢。");
				return 1;
			}

			else                                                                                 
			{
				command("say 这里供奉着诸位老爷子的灵位，公子每天都到这里来请安。");
		                return 1;
			}
		}
	}

        if (!(fam = this_player()->query("family")) || fam["family_name"] != "姑苏慕容")
        {
                command("say "+ RANK_D->query_respect(this_player()) + "与本派素无来往，不知此话从何谈起？");
                return 1;
	}

	command("say 这里供奉着诸位老爷子的灵位，公子每天都到这里来请安。");
	return 1;
}              