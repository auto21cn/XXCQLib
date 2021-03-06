//changan city

#include <ansi.h>
#include <room.h>
#include <command.h>
inherit ROOM;
int consider_lv(object ob,int a);

void create ()
{
        set ("short", "林间小路");
        set ("long", @LONG
这是一片白杨林，林子很密，只有这一条小路穿林而过，一些阳光透
过密林射在地上，到了晚上这里基本是伸手不见五指的。据过往的路人说
这里时有强人出没，抢取财物。出林子的西面就可以到百花潭了。
LONG);
	set("valid_startroom", 1);

        set("exits", 
        ([
		"west" : __DIR__"tulu2",
		"south" : __DIR__"treeroad4",
       ]));

        set("outdoors", "huayang");
        setup();
}

void init()
{
	object me, ob;
	mapping myfam;

	me = this_player();
	myfam = me->query("family");

	if ( myfam = me->query("family") && (myfam["family_name"] == "浣花剑派") && random(100) < 15 )
	{
		message_vision(HIY"突然树上传来一阵狞笑，伴一阵风势，一个大汉从树上跃了下来。\n"NOR, me);
		message_vision(HIY"大汉大喝一声：你这个浣花余孽，今天落到我手里算你倒霉，纳命来吧！！！\n"NOR, me);
		ob = new("/d/chengdu/npc/jiefei");
		ob->set("combat_exp",me->query("combat_exp") * 9 / 10);
		ob->set("max_qi",me->query("max_qi"));
		ob->set("eff_qi",me->query("max_qi"));
		ob->set("qi",me->query("max_qi"));
		ob->set("max_jingli",me->query("max_jingli"));
		ob->set("eff_jingli",me->query("max_jingli"));
		ob->set("jingli",me->query("max_jingli"));
		ob->set("max_neili",me->query("max_neili"));
		ob->set("neili",me->query("max_neili"));
		ob->set_skill("force", consider_lv(ob, 8));
		ob->set_skill("strike", consider_lv(ob, 8));
		ob->set_skill("cuff",consider_lv(ob, 8));
		ob->set_skill("dodge", consider_lv(ob, 8)); 
		ob->set_skill("whip", consider_lv(ob, 8)); 
		ob->set_skill("spear", consider_lv(ob, 8)); 
		ob->set_skill("axe", consider_lv(ob, 8)); 
		ob->set_skill("club", consider_lv(ob, 8)); 
		ob->set_skill("stick", consider_lv(ob, 8)); 
		ob->set_skill("sword", consider_lv(ob, 8)); 
		ob->set_skill("staff", consider_lv(ob, 8)); 
		ob->set_skill("blade", consider_lv(ob, 8)); 
		ob->set_skill("parry", consider_lv(ob, 8)); 
		ob->set_skill("literate", consider_lv(ob, 8)); 
		ob->move(environment(me));
		ob->kill_ob(me);
		me->kill_ob(ob);
		me->set_temp("jiefei",1);
	}
	return;
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

int valid_leave(object me, string dir)
{

	if (  ((dir == "south")||(dir == "west"))
	   && me->query_temp("jiefei") == 1
	   && objectp(present("bang zhong", environment(me))) )
	{
		message_vision("大汉一闪身将$N拦了下来：想走？没那么容易！！！", me);
		return notify_fail("\n");
	}
	me->delete_temp("jiefei");
	return ::valid_leave(me, dir);
}