// /u/beyond/mr/npc/wang.c 王夫人
// this is made by beyond
// update 1997.6.29
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
int do_ask();
void create()
{
	set_name("王夫人",({"wang furen","wang","furen"}));
	set("gender", "女性");
        set("unique", 1);
	set("rank_info/respect", "夫人");
        set("title","曼佗罗山庄主");
  	set("long", 
              "她就是曼佗罗山庄的主人，她看上去虽以四十有加，但风韵尤存。\n");
        set("age", 40);
	set("attitude", "friendly");
	set("shen_type", 0);
	set("str", 20);
	set("int", 22);
	set("con", 28);
	set("dex", 23);
	set("per", 30);
	
	set("max_qi", 1500);
	set("max_jing", 1500);
	set("neili", 1000);
	set("max_neili", 1500);
	set("jiali", 0);
	set("combat_exp", 80000);
	set("score", 15000);
        set("inquiry", ([
            "name" : "我就是曼佗罗山庄的主人，见到我难道没有什么表示吗？\n",
            "here" : "这里是曼佗罗山庄的庄院之所在，此处名为云锦楼？\n",
            "rumors" : "最近我那表亲慕容博不幸仙逝了。\n",
            "王语嫣" : "语嫣是我的宝贝女儿，你可别想打她的主意。\n",
            "慕容复" : "慕容复是我那不成器的侄儿，练就了以彼之道还施彼身的绝技，名震江湖。\n",
            "娘缳玉洞" : "娘缳玉洞是我曼佗罗山庄的藏书之处，一般人是别想进去了。\n",
            "曼佗罗山庄" : "这里就是曼佗罗山庄，我就是这里的主人。\n",
            "还施水阁" : "那是燕子坞的秘密之所在，不过还施水阁的藏书比那里可是多的多呀。\n",       
            "job" : (: do_ask :),
]));
        set_skill("murong-xinfa", 70);
        set_skill("dodge",70);
        set_skill("force", 70);
	set_skill("shenyuan-gong", 70);
	set_skill("yanling-shenfa", 70);
        set_skill("parry", 70);
	set_skill("literate", 70);
        set_skill("strike", 65);
	map_skill("force", "shenyuan-gong");
	map_skill("dodge", "yanling-shenfa");
        
	setup();
        carry_object(__DIR__"obj/shoe")->wear();
        carry_object(__DIR__"obj/red_silk")->wear();
        carry_object(__DIR__"obj/skirt")->wear();
       
}

int do_ask()
{
        mapping myfam;
        object me, ob, target;
        object* living;
        int i,j,size,tcomp,ucomp,tasktype;//tasktype=0 索命 1 招魂
        size=sizeof(living);       
        i=random(size);
        j=i;        
        living=livings(); 
        me=this_player();                                         
       	ob=this_object();                                         
        target=living[j];
       	seteuid(geteuid(me));       	
        myfam = (mapping)me->query("family");


        ucomp=(int)me->query("combat_exp");
        tcomp=(int)target->query("combat_exp");        

	
	if(!myfam || myfam["family_name"] != "姑苏慕容")
            return notify_fail("你要干什么？\n");
        while(1)
        {  

            if((target->query("race")=="人类") && !userp(target) && !wizardp(target) )
            {
            	    if((tasktype==0) && (tcomp>=1.2*ucomp) && (tcomp<=2.2*ucomp))
                    {
                        command("say "+target->name()+"常与本教做对，你去把他杀了！\n");
                   	tell_object(me,"洪安通拿出一块索命牌，在上面刻下了"+target->name()+"几个字，交给了你。\n");
                    	tell_room(environment(me),"洪安通拿出一块索命牌，在上面刻下了"+
                        target->name()+"几个字，交给了"+me->name()+"。\n");
                    	return 1;
                }
                    else if(tasktype==1)
                    {
        	        command("say "+"现在令你速去设法让"+target->name()+"归顺本教！\n");
	                tell_object(me,"洪安通拿出一块招魂牌，在上面刻下了"+target->name()+"几个字，交给了你。\n");
                    	tell_room(environment(me),"洪安通拿出一块招魂牌，在上面刻下了"+
                        target->name()+"几个字，交给了"+me->name()+"。\n");
                    	if(me->query_temp("quest/huilu",1)!=0)
                        me->delete_temp("quest/huilu");
	                return 1;
                    }
            }
            j++;
            if(j>=size)
                j=0;
            if(j==i)
                break;
        } 
        command("say 现在没有任务，你等下再来吧。");
        return 1;                                
}