//jian tian dong
//by mulan

#include <ansi.h>
inherit ROOM;
int do_ba(string arg);
int do_find(string arg);
int do_get(string arg);
int do_open(string arg);

void create ()
{
        set ("short", "见天洞");
        set ("long", @LONG
见天洞也就是萧家祠堂，内部打扫得一尘不染，烛火常明，壁内各处
有凹了进去的地方，供奉着一栩栩如生的神像。神像前是七星灯火，供奉
拜祭的三牲礼酒，坛前架着一把剑。桌上香火烟雾缭绕，壁内神像，看不
是很清楚。这也是历代浣花高手尸身停柩之处，祭祠的石洞内，停放着许
多副棺木(coffin)。那棺棒旁又摆着一些陈旧的乐器(yueqi)。
LONG);

        set("exits", 
        ([
                "east" : __DIR__"jiashan",
        ]));
	set("count",1);

        set("item_desc",([
                "coffin" : "却见其中副棺材特别大，棺上所镂雕的花纹(wen)也特别				    精细, 而且纹路奇特。\n",
		"wen" : "原来棺材上所刻的，都是乐谱上特别的音符，其中有几个古				 怪的音律。\n",
		"yueqi" : "那是不用废久的乐器，可能有些还可以奏(zou)吧。找找\n"
        ]));

        setup();
}

void init()
{
        add_action("do_ba", "qu");
	add_action("do_find","find");
	add_action("do_open","open");
	add_action("do_get","na");
}

int do_get(string arg)
{
	object obj,me = this_player();
	
	if(!arg || arg!="book")
	return notify_fail("你要拿什么?\n");
	
	if(me->query_temp("open") < 1)
	return notify_fail("你知道在哪儿吗?\n");
 if (present("wangqing tianshu",this_player()))
    return notify_fail("你已经有了，还来!\n");

    obj = new("/d/huanhua/npc/obj/tianshu");
  me->set_temp("open",0);
	obj->move(me);
	message("channel:rumor", MAG"【谣言】某人：恭喜"+this_player()->query("name")+"的到《忘情天书》!\n"NOR, users());
	return 1;
}
	
int do_find(string arg)
{
	object obj;
	object me = this_player();
	
	if(!arg || (arg!="yueqi"))
		return notify_fail("你要找什么啊。\n");
        if(me->is_busy())
        return notify_fail("你还忙着呢?\n");
    if(random(me->query("kar")) != 10||this_object()->query("count") < 1)
		{
        me->start_busy(1);
		return notify_fail("你在地上乱找，却什么也没有找到!\n");
		}
	obj = new("/d/huanhua/npc/obj/yueqi");
	obj->move(me);
	this_object()->set("count",0);
        return notify_fail("你找到一把可以用的乐器了!\n");
}

int do_open(string arg)
{
	message_vision("棺盖突然打开，黑暗中飞来一支箭一样的东西；不好....\n",this_player());
	message("channel:rumor", HIW"【谣言】某人："+this_player()->query("name")+"妄图盗去《忘情天书》，被机关所害!\n"NOR, users());
	this_player()->die();
}
	
int do_ba(string arg)
{
        object obj;
        object me = this_player();

        if (!arg || (arg!="jian" && arg!="sword"))
        return notify_fail("你要拿什么？\n");
        if ( !me->query_temp("qu_jian"))
                return notify_fail("你没有得到掌门的允许!\n");
      message("channel:rumor", MAG"【谣言】："+this_player()->query("name")+"在"+environment(me)->query("short")+"得到神剑"+HIW"长歌\n"NOR, users());
    obj = new("/d/huanhua/npc/obj/changge");
	me->delete_temp("qu_jian");
        obj->move(me);
        return 1;
}


