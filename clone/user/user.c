// user.c

#include <origin.h>
#include <user.h>
#include <ansi.h>

inherit CHARACTER;
inherit F_AUTOLOAD;
inherit F_SAVE;
inherit F_ENCODING;
static int last_age_set = 0;            // 上一次更新AGE的时间
static int user_say = 0;                // 一定时间以内玩家做的say-action
static int user_command = 0;            // 一定时间以内玩家发送的命令
static int at_time = 0;                 // 在什么时间计算的
static int ban_to = 0;                  // 在什么时间解禁玩家
static int attach_flag = 0;             // 是否正在和系统联络

#define DEFAULT_PRISON          "/d/sroom/jianyu"

// globals variables
string  prison = 0;
int     time_to_leave = 0;

string query_prison()           { return prison; }
int    query_time_to_leave()    { return time_to_leave; }
int    is_in_prison();

#define MAX_COMMAND_ONE_SECTION         40
#define MAX_SAY_ONE_SECTION             5
#define BAN_SAY_PERIOD                  60

int query_current_neili_limit();
int query_neili_limit();
int query_current_jingli_limit();
int query_jingli_limit();
int query_potential_limit();

int is_user() { return 1; }

void create()
{
	::create();
	set_name("使用者物件", ({ "user object", "user", "object" }) );
}

void terminal_type(string term_type)
{
	set_temp("terminal_type", term_type);
	message("system", "终端机型态设定为 " + term_type + "。\n", this_object());
}

void reset()
{
	if( (int)query("potential") - (int)query("learned_points") < 100 )
		add("potential", 1);
	if( (int)query("thief") > 0 )
		add("thief", -1 );
}

// This is used by F_SAVE to determine the filename to save our data.
string query_save_file()
{
	string id;

	id = geteuid();
	if( !id ) id = getuid();
	if( !stringp(id) ) return 0;
	return sprintf(DATA_DIR "user/%c/%s", id[0], id);
}

int save()
{
	int res;

        if (query_temp("user_setup") && environment())
        {
	        save_autoload();
	        res = ::save();
	        clean_up_autoload();		// To save memory
        } else
                res = 0;

	return res;
}

// This function updates player's age, called by heart_beat()
void update_age()
{
	if( !last_age_set )
        {
                last_age_set = time();
                add("mud_age", 0);
        }

        if (! query("env/halt_age") ||
            ! environment(this_object()) ||
            ! environment(this_object())->query("chat_room"))
        {
                // Update age
	        add("mud_age", time() - last_age_set);
                if (time_to_leave)
                        time_to_leave -= time() - last_age_set;
        }

	last_age_set = time();

	set("age", 14 + (int)query("age_modify") + ((int)query("mud_age") / 86400));
}

void setup()
{
	// We want set age first before new player got initialized with
	// random age.
        last_age_set = 0;
	update_age();

	::setup();

        // set the enable flag to enable save
        set_temp("user_setup", 1);

	restore_autoload();

        //delete("no_get");
        //delete("no_get_from");
}

private void user_dump(int type)
{
	switch(type)
	{
		case DUMP_NET_DEAD:
			if (environment())
			{
				tell_room( environment(), query("name") + "断线超过 " +
				NET_DEAD_TIMEOUT/60 + " 分钟，自动退出这个世界。\n");
			}
			catch(command("quit"));
			if (this_object())
			{
				// command quit failed.
				seteuid(getuid());
				destruct(this_object());
			}
			break;
		case DUMP_IDLE:
			if(!wizardp(this_object()))
			{
				tell_object( this_object(), "对不起，您已经发呆超过 " +
					IDLE_TIMEOUT/60 + " 分钟了，请下次再来。\n");
				if (environment())
				{
					tell_room( environment(), "一阵风吹来，将发呆中的" + query("name") +
						"化为一堆飞灰，消失了。\n", ({this_object()}));
				}
				command("quit");
				if (this_object())
				{
					// command quit failed.
					seteuid(getuid());
					destruct(this_object());
				}
			}
			break;
		default:
				return;
	}
}

// net_dead: called by the gamedriver when an interactive player loses
// hir network connection to the mud.
private void net_dead()
{
	object link_ob;

	set_heart_beat(0);
	if( objectp(link_ob = query_temp("link_ob")) )
		destruct(link_ob);

	// Stop fighting, we'll be back soon.
	remove_all_enemy();

	set_temp("netdead", 1);
	if( userp(this_object()) )
	{
		call_out("user_dump", NET_DEAD_TIMEOUT, DUMP_NET_DEAD);
		tell_room(environment(), query("name") + "断线了。\n", this_object());
		CHANNEL_D->do_channel(this_object(), "sys", "断线了。");
	}
	else
	{
		command("quit");
	}
}

// reconnect: called by the LOGIN_D when a netdead player reconnects.
void reconnect()
{
	set_heart_beat(1);
	set_temp("netdead",0);
	remove_call_out("user_dump");
	tell_object(this_object(), "重新连线完毕。\n");
}

int query_neili_limit()
{
	string *skill_names;
	mapping skills;
	int neili_limit;
	int base_lvl, lvl;
	int tmp;
	int i;

	skills = this_object()->query_skills();
	if (! mapp(skills))
                return 0;

        skill_names = keys(skills);

        base_lvl = ((int) skills["force"]) / 2; 
        neili_limit = base_lvl * 10;
        for (i = 0; i < sizeof(skill_names); i++)
        {
                if (file_size(SKILL_D(skill_names[i]) + ".c") == -1)
                {
                        // No such skill
                        continue;
                }

                if (! SKILL_D(skill_names[i])->valid_enable("force"))
                        continue;

                lvl = (int) skills[skill_names[i]];
                tmp = (base_lvl + lvl) * 10;
                tmp += (int) SKILL_D(skill_names[i])->query_neili_improve(this_object());
                if (tmp > neili_limit) neili_limit = tmp;
        }

        return neili_limit;
}

int query_current_neili_limit()
{
        int neili;
        string force;

        force = query_skill_mapped("force");
        neili = (int)query_skill("force", 1) / 2 * 10;
        if (stringp(force) && force != "")
        {
                neili += (int)query_skill(force, 1) * 10;
                neili += SKILL_D(force)->query_neili_improve(this_object());
        }    

        return neili;
}

int query_jingli_limit()
{
        return query_neili_limit() / 4;
}

int query_current_jingli_limit()
{
        return query_current_neili_limit() / 4;
}

int query_potential_limit()
{
        return (int)query("learned_points") +
               query_int() * 10 / 2 + 100;
}

int accept_fight(object ob)
{
	if (query_temp("pending/fight") == ob)
		return 1;

        tell_object(this_object(), YEL "如果你愿意和对方进行比试，请你也对" +
                    ob->name() + "("+ (string)ob->query("id")+")"+
                    "下一次 fight 指令。\n" NOR);

	tell_object(ob, YEL "由于对方是由玩家控制的人物，你必须等对方同意才" +
              "能进行比试。\n" NOR);

        return 0;
}

int accept_hit(object ob)
{
        message_vision("$N大喝道：" + ob->name() + "，你要干什么？\n\n",
                       this_object(), ob);
        return 1;
}

int accept_kill(object ob)
{
        if (is_killing(ob->query("id")))
                return 1;

        tell_object(this_object(), HIR "如果你要和" + ob->name() +
	        "性命相搏，请你也对这个人(" + (string)ob->query("id") +
                ")下一次 kill 指令。\n" NOR);
        return 1;
}

int accept_ansuan(object who)
{
        command(random(2) ? "say 嗯！怎么..." : "say 啊！不好！");
        return 1;
}

int reject_command()
{
        int t;

        if (wizardp(this_object()))
                return 0;

        t = time() & 0xFFFFFFFE;
        if (at_time != t)
        {
                at_time = t;
                user_command = 1;
                user_say = 0;
        } else
                user_command++;

        if (user_command > MAX_COMMAND_ONE_SECTION)
                return 1;

        return 0;
}

int ban_say()
{
        int t;

        if (wizardp(this_object()))
                return 0;

        if (is_in_prison())
        {
                notify_fail("你省省吧，好好做你的牢，少折腾。\n");
                return 1;
        }

        t = time() & 0xFFFFFFFE;
        if (ban_to > t)
        {
                notify_fail("系统禁止你送出信息，请于 " +
                            (ban_to - t) + " 秒钟以后再尝试。\n");
                return 1;
        }
        if (at_time != t)
        {
                at_time = t;
                user_say = 1;
                user_command  = 0;
        } else
                user_say++;

        if (user_say > MAX_SAY_ONE_SECTION)
        {
                ban_to = t + BAN_SAY_PERIOD;
                CHANNEL_D->do_channel(find_object(MASTER_OB), "rumor",
                        "听说" + query("name") + "因为太罗嗦，被人堵住了嘴。");
                notify_fail(HIR "由于你发布的信息太多，因此系统暂时"
                            "禁止你发出信息。\n" NOR);
                return 1;
        }

        return 0;
}

// return true if the user was in prison now
int is_in_prison()
{
        return stringp(prison);
}

// thow the person into prison
void get_into_prison(object ob, string p, int time)
{
        object me;

        me = this_object();
        if (! p) p = prison;
        if (! p) p = DEFAULT_PRISON;

        if (prison && base_name(environment()) == p)
        {
                time_to_leave += time * 60;
                if (ob && time)
                        CHANNEL_D->do_channel(find_object(MASTER_OB), "rumor",
                                "听说" + query("name") + "的刑期被" +
                                ob->query("name") + "加长了" +
                                chinese_number(time) + "分钟。\n");
                return;
        }

        if (prison && prison == p && base_name(environment()) != prison)
        {
                message_vision(HIM "忽然一阵诡秘的烟雾弥漫在四周，两个青面獠牙"
                       "的小鬼跳了出来，一把抓住$N，用\n铁链锁住，恶狠"
                       "狠的叫道：“好家伙！我让你跑...”\n\n" NOR,
                       me);

                message("vision", HIY "忽的一道金光，你登时什么也看不到了...\n\n"
                          HIM "烟雾渐渐的散去... " + me->name() +
                          "不见了？！！\n\n" NOR,
                          environment(me), ({ me }));

                me->set("startroom", prison);
                me->move(prison);
                message_vision("“啪”的一声，$N狠狠的摔倒了地上。\n", me);
                if (living(me)) me->unconcious();

                CHANNEL_D->do_channel(find_object(MASTER_OB), "rumor",
                        "听说" + query("name") + "越狱潜逃，结果被抓"
                        "回去了。\n");

                save();
                return;
        }

        message_vision(HIM "忽然一阵诡秘的烟雾弥漫在四周，两个青面獠牙"
                       "的小鬼跳了出来，一把抓住$N，用\n铁链锁住，恶狠"
                       "狠的叫道：“站住！你犯案了，快跟我们走吧！”\n\n" NOR,
                       me);

        message("vision", HIY "忽的一道金光，你登时什么也看不到了...\n\n"
                          HIM "烟雾渐渐的散去... " + me->name() +
                          "不见了？！！\n\n" NOR,
                          environment(me), ({ me }));

        if (ob)
        {
                CHANNEL_D->do_channel(find_object(MASTER_OB), "rumor",
                        "听说" + query("name") + "被" + ob->query("name") +
                        "送进了" + p->short() + HIM "，禁闭" +
                        chinese_number(time) + "分钟。\n");
        }

        me->set("startroom", prison);
        me->move(p);
        prison = p;
        time_to_leave += time * 60;
        save();

        message_vision("“啪”的一声，$N重重的摔倒了地上。\n", me);
        if (living(me)) me->unconcious();
}

// out of prison
void leave_prison(object ob)
{
        object me;
        string startroom;

        me = this_object();
        time_to_leave = 0;
        prison = 0;
        message_vision("忽然两个小鬼冒了出来，拎住$N，道：好了，你可以"
                       "走了，要是再敢犯案，哼哼...\n\n", me);

        tell_object(me, HIR "你眼前一黑...\n\n" NOR);
        message("vision", "两个小鬼和" + me->name() + "突然在你面前消"
                          "失了... 你不禁叹了一口气。\n",
                          environment(me), ({ me }));
        if (me->is_ghost())
                startroom = "/d/death/gate";
        else
                startroom = "/d/bianliang/guangming";
        me->set("startroom", startroom);

        me->move(startroom);
        message("vision", "一阵诡秘的烟雾过后，只见" + me->name() +
                          "直挺挺的躺在地上。\n", environment(me), ({ me }));
        if (living(me))
                me->enable_player();
        else
                me->revive();
        save();

        if (ob)
                CHANNEL_D->do_channel(find_object(MASTER_OB), "rumor",
                        "听说" + query("name") + "被" + ob->name() +
                        "提前释放了。\n");
        else
                CHANNEL_D->do_channel(find_object(MASTER_OB), "rumor",
                        "听说" + query("name") + "已经刑满释放了。\n");
}

// when the user was in prison, the heart beaten function of
// char will call damage heal_up, then the function will call
// it
void update_in_prison()
{
        object me;

        me = this_object();
        me->set("qi", 0);
        me->set("jing", 0);
        me->set("neili", 0);

        if (time_to_leave > 0)
        {
                if (environment() && base_name(environment()) != prison)
                {
                        // escape from prison?
                        get_into_prison(0, 0, 0);
                }
                return;
        }

        leave_prison(0);
}

// return true if the user was attached system, such as
// command sameip will run a much long time, in the period
// the user shouldn't receive message except from the system
int is_attach_system()
{
        return attach_flag;
}

// start attaching
int attach_system()
{
        attach_flag = 1;
}

// stop, deatched
int detach_system()
{
        attach_flag = 0;
}
