//Npc 方歌吟
//Write by godzilla
#include <ansi.h>
inherit NPC;
void create()
{
        set_name("方歌吟", ({ "fang geyin", "fang" }));
        set("long", "他就是一代大侠方歌吟。 \n");
        set("title", HIW"天羽派"HIY"第五代掌门人"NOR);
        set("gender", "男性");
        set("age", 20);
        set("attitude","friendly");
        set("str", 40);
        set("dex", 40);
        set("con", 40);
        set("int", 40);
        set("per", 40);
        set("tianyu_1",1);
        set("max_qi", 10000);
        set("max_jingli", 10000);
        set("max_neili", 10000);
        set("max_douzhi",1000);
        set("qi",10000);
        set("jingli",10000);
        set("jiali",400);
        set("douzhi",1000);
        
        set_skill("dodge",300);
        set_skill("finger",300);
        set_skill("parry",300);
        set_skill("blade",180);
         set_skill("yiqiguan-riyue",150);
         set_skill("jieniu-dao",150);
        set_skill("tao",300);
         set_skill("youran-bu",150);
         set_skill("changkong-zhi",150);
        set_skill("strike",300);
        set_skill("force",300);
        set_skill("sword",300);
        set_skill("tianyu-qijian",300);
        set_skill("tianyu-qigong",300);
        set_skill("tianyu-bufa",300);

        set_skill("literate",350);
        map_skill("sword", "tianyu-qijian");
        map_skill("force", "tianyu-qigong");
        map_skill("dodge", "tianyu-bufa");
        map_skill("parry", "tianyu-qijian");
        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}
void init()
{
        add_action("do_qiecuo","qingjiao");
        add_action("do_skills",({"skills","cha"}));
}
int do_qiecuo(string arg)
{
        object me=this_player(), ob = this_object();
        string special,name;
        int exp,jb;
        if (!arg||sscanf(arg, "%s with %s", arg, name)!=2)
        return notify_fail("命令格式:  qingjiao <skills> with <somebody>。\n");
;
        if (!id(name))
        return notify_fail("你要向谁请教。\n");
        write(CYN"你向"+ob->name()+"抱拳说道：“在下"+me->name()+"，特向方大侠请教一下「" + to_chinese(arg) + "」的疑问。\n"NOR);
        if (!(special=me->query_skill_mapped(arg)))
        {
                if (arg == to_chinese(arg))
                        write( CYN+ob->name()+"说道：“恕在下愚昧，不知「" + arg + "」是什么武功？到向你请较。\n"CYN);
                else
                        write(CYN+ob->name()+"说道：“你必须enable这项特殊武功，才能和我切磋。\n"NOR);
                return 1;
        }
        if (me->is_busy() || me->is_fighting())
        {
                write(CYN+ob->name()+"说道：你正忙着呢。\n"NOR);
                return 1;
        }
                if( (int)me->query("learned_points") >= (int)me->query("potential") )
        {
        write(CYN+ob->name()+"说道：这为" + RANK_D->query_respect(me) + "你的浅能不够了。\n"NOR)
       ;return 1;
          }
        if (!me->query_skill(arg,1))
        {
                write(CYN+ob->name()+"说道：你好象不会这种技能。\n"NOR);
                return 1;
        }
        if( arg == "force")
        {
                write(CYN+ob->name()+"说道：基本内功只能自己掌握，怎么能和我切磋呢？\n"NOR);
                return 1;
        }
        exp=me->query("combat_exp");
        jb=me->query_skill("arg",1);
         if ((int)me->query_skill(arg,1)*(int)me->query_skill(arg,1)*(int)me->query_skill(arg,1)/10 > (int)me->query("combat_exp")) 
        {
                write(CYN+ob->name()+"说道：你实战经练不够，武功造诣上无法进展了。\n"NOR);
                return 1;
        }       
        if((int)me->query("jingli")<100)
        {
                write(CYN+ob->name()+"说道：这为" + RANK_D->query_respect(me) + "先休息一下吧，功夫需要循序渐进，不能急来。\n"NOR);
                return 1;
        }
        write(CYN+ob->name()+"点了点头，说道：“你进招吧！我来从中指点。”\n"NOR);
        write(CYN"你使出毕生所学开始和"+ob->name()+"较量起来。\n"NOR);
        write(CYN"方歌吟使出轻功，来回游动，观察其破绽。\n"NOR);
        write(HIM"几招过后，你对"+to_chinese(arg)+"的体会又深了一层。\n"NOR);
                        me->add("learned_points", 1);
        me->add("jingli",-30);
        me->improve_skill(arg, me->query_int()*3);
        return 1;
}
int do_skills(string arg)
{
        object me;
        me = this_player();
        if( !arg || arg!="fang")
        return 0;
        if(wizardp(me))
        return 0;
        if (me->query("family/family_name") != "天羽派" )
        {
                command("shake "+me->query("id"));
                return 1;
        }
        tell_object(me,"方歌吟目前所学过的技能：\n"+
"  基本轻功 (dodge)                         - 深不可测 300/    0\n"+
"  基本指法 (finger)                        - 深不可测 300/    0\n"+
"  基本内功 (force)                         - 深不可测 300/    0\n"+
"  基本招架 (parry)                         - 深不可测 300/    0\n"+
"  一气贯日月 (yiqiguan-riyue)                    - 深不可测 150/    0\n"+
"  悠然往来 (youran-bu)                     - 深不可测 150/    0\n"+
"  长空神指 (changkong-zhi)                     - 深不可测 200/    0\n"+
"  基本刀法 (blade)                         - 深不可测 180/    0\n"+
"  基本掌法 (strike)                        - 深不可测 300/    0\n"+
"  解牛刀法 (jieniu-dao)                      - 深不可测 150/    0\n"+
"  基本剑法 (sword)                         - 深不可测 300/    0\n"+
"  道家心法 (tao)                         - 深不可测 300/    0\n"+
"□天羽步法 (tianyu-bufa)                   - 深不可测 300/    0\n"+
"□天羽奇功 (tianyu-qigong)                 - 深不可测 300/    0\n"+
"□天羽奇剑 (tianyu-qijian)                 - 深不可测 300/    0\n"
);
        return 1; 
}
int recognize_apprentice(object ob)
{
        if(ob->query("family/family_name")!="天羽派")
        {
                command("say 非我派弟子不能学我功夫。\n");
          return 0;
        }
        if(ob->query("combat_exp")<300000)
        {
                 command("say 你的实战经练不够，我不能传授你功夫。\n");
            return 0;
        }
           return 1;
}               
