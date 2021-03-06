// fmquest.c

#include <ansi.h>

int consider_lv(object ob,int a);

int update_condition(object me, int duration)
{
           object ob,where,ob1,*obb;
           int i;

        where=environment(me);
        me->apply_condition("xhquest1", duration - 1);

        if (file_name(where)==me->query_temp("where1"))
        {
                if (present("di zi",where)) {
                        message_vision(HIG"这时一队人马杀过来，$N吓了一跳！\n"NOR,me);
                        message_vision(HIG"$N定睛一看，原来是救援人马把弟子带走了，你不禁长舒一口气。\n"NOR,me);               
                        tell_object(me,HIC"你的任务完成了，快到曹大悲那儿去汇报吧！\n"NOR);
                        me->delete_temp("jobstart");
                        me->delete_temp("followed");            
                        me->set_temp("jobok",1);
                        obb=all_inventory(environment(me));
                        for(i=0; i<sizeof(obb); i++) {
                                if (obb[i]->is_character() )
                                {
                                        if (interactive(obb[i])) continue;
                                        if (obb[i]->query("id")!="di zi") continue;
                                        destruct(obb[i]);
                                        
                                }
                        }
                        return 0;
                }
            else {
                tell_object(me,HIC"你到了地方，可是你保护的弟子跑哪去了？赶快去找找。\n"NOR);
                return 1;
       }
        }
         if ((!(present("sha shou",where))) && (random(12)<=4) && present("di zi",where))
        {
                ob = new("/kungfu/class/xuehepai/dizi1");
                 ob->move(environment(me));
                ob->set_name(me->query_temp("duishou")+"杀手",({"sha shou","shou"}));
                message_vision(HIG"突然一个人影向$N喝道：“血河派弟子杀无赦！”\n"NOR, me);
                ob->set("combat_exp",me->query("combat_exp"));
                ob->set("max_qi",me->query("max_qi")*60/100);
                ob->set("eff_qi",me->query("max_qi")*60/100);
                ob->set("qi",me->query("max_qi")*60/100);
                ob->set("max_jingli",me->query("max_jingli")*60/100);
                ob->set("eff_jingli",me->query("max_jingli")*60/100);
                ob->set("jingli",me->query("max_jingli")*60/100);
                ob->set("mex_neili",me->query("max_neili")*60/100);
                ob->set("neili",me->query("max_neili")*60/100);
                ob->set_skill("cuff",consider_lv(ob, 5));
                ob->set_skill("force",consider_lv(ob, 5));
                ob->set_skill("dodge",consider_lv(ob, 5));
                ob->set_skill("parry",consider_lv(ob, 5));
                ob->set_skill("tianyu-xinfa",consider_lv(ob, 5));
                ob->set_skill("tianyu-shenfa",consider_lv(ob, 5));
                ob->set_skill("finger",consider_lv(ob, 5));
                ob->set_skill("sword",consider_lv(ob, 5));
                ob->set_skill("changkong-zhi",consider_lv(ob, 5));
                ob->set_skill("tianyu-qijian",consider_lv(ob, 5));
                ob->map_skill("force","tianyu-xinfa");
                ob->map_skill("dodge","tianyu-shenfa");
                ob->map_skill("parry","tianyu-qijian");
                ob->map_skill("sword","tianyu-qijian");
                ob->map_skill("finger","changkong-zhi");
                ob->prepare_skill("finger","changkong-zhi");
                  ob->set_leader(me);
                ob->set("followid",me->query("id"));
                ob->kill_ob(me);
                me->kill_ob(ob);
        }

        if ( duration < 1 )
        {
           if (me->query_temp("jobstart"))  {
                if (file_name(where)==me->query_temp("where1"))
                {
                if (present("di zi",where)) {
                                message_vision(HIG"这时一队人马杀过来，$N吓了一跳！\n"NOR,me);
                               message_vision(HIG"$N定睛一看，原来是救援人马把弟子带走了，你不禁长舒一口气。\n"NOR,me);               
                                tell_object(me,HIC"你的任务完成了，快到曹大悲那儿去汇报吧！\n"NOR);
                                me->delete_temp("jobstart");
                                me->delete_temp("followed");            
                                me->set_temp("jobok",1);
                        me->apply_condition("xhquest1",0);
                        obb=all_inventory(environment(me));
                        for(i=0; i<sizeof(obb); i++) {
                                if (obb[i]->is_character() )
                                {
                                        if (interactive(obb[i])) continue;
                                        if (obb[i]->query("id")!="di zi") continue;
                                        destruct(obb[i]);
                                        
                                }
                        }
                                return 0;
                                }
                }
                else if (ob1=present("di zi",where)) 
                {
                       tell_room(where,HIG"突然杀出几个"+me->query_temp("duishou")+"弟子对着"+obb->query("name")+"猛砍一阵。\n然后就四处散开，不见了。\n");
                  ob1->die();
                        tell_object(me,HIC"你没有保护好弟子，任务失败！\n"NOR);                 
                        me->set_temp("jobfailed",1);
                        me->delete_temp("jobstart");
                        me->delete_temp("followed");
                        return 0;
                }
                                tell_object(me,HIC"你保护的弟子跑哪去了？肯定已经凶多吉少！\n"NOR);                    
                me->set_temp("jobfailed",1);
                        me->delete_temp("followed");
                me->delete_temp("jobstart");
                 }
                return 0;
        }

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


