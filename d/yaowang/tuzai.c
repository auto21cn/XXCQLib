// Room: 药王谷
// By 山猫adx @ 宁波小雪 17:00 99-10-26

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "屠宰场");
	set("long", @LONG
这里是药王谷的屠宰场，是专门用来屠宰药王谷饲养的动物，
取药材用的，你可以把动物捉到这里，进行屠宰(sha)。
LONG );
	set("area", "药王谷");
	set("areb", "屠宰场");
	set("no_fight", 1);
	set("exits", ([
		"west" : __DIR__"xiaolu2",
	]));
	setup();
}

void init()
{
	add_action("do_sha", "sha");
}

int do_sha(string arg)
{
	object me, ob;
	me=this_player();

	if(me->query("party/party_name")!=HIB"药王谷"NOR
         || me->query("party/level")<3 ) {
		return notify_fail("你还不会取药呢！不会杀动物？\n");
	}

	if( !arg || !objectp(ob = present(arg, environment(me))) )
		return notify_fail("指令格式：sha <ID> \n");

        if( !ob->query("yaowang_zhuo") )
                return notify_fail("这个东西不能在这里杀！\n");

        if( me->is_fighting() || me->is_busy() )
                return notify_fail("你正忙着呢！\n");

	me->improve_skill("healing", ((int)me->query_skill("healing",1)/2));
	message_vision(HIR"$N把$n按在屠宰槽上，一刀砍了下去。\n"NOR, me, ob);
	ob->die();
	return 1;
}
