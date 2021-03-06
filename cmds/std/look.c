// look.c
// Modify By JackyBoy 1999/6/8

#include <room.h>
#include <ansi.h>

inherit F_CLEAN_UP;

int look_room(object,object);
int look_item(object,object);
int look_living(object,object);
int look_room_item(object,string);
string do_query(object);
string inventory_look(object,int);
string room_desc(object);
	
void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object obj;
	int result;

	if( !arg ) result = look_room(me, environment(me));
	else if( (obj = present(arg, me)) || (obj = present(arg, environment(me)))) {
		if( obj->is_character() ) result = look_living(me, obj);
		else result = look_item(me, obj);
	} else result = look_room_item(me, arg);

	return result;
}

int look_room(object me, object env)
{
	int i,n;
	object *inv;
	mapping exits;
	string str, *dirs;

	if( !env ) {
		write("你的四周灰蒙蒙地一片，什么也没有。\n");
		return 1;
	}
	if ( n=NATURE_D->night() && (int) env->query("outdoors")
		&&!(wizardp(me)&&me->query("env/debug")) )
		//并且如果是设置了debug的巫师的话就都能看清
	{	
		str = sprintf(  HIR"【"NOR + "%s" + HIR"】"NOR +"- %s\n"+"%s%s",
		env->query("short"),
		wizardp(me)? file_name(env): "",
		"这里由于光线不足，什么都看不清。\n",
		env->query("outdoors")? NATURE_D->outdoor_room_description() : "" );
		
		}
	else{
	str = sprintf(  HIR"【"NOR + "%s" + HIR"】"NOR + " - %s\n%s%s",
		env->query("short"),
		wizardp(me)? file_name(env): "",
		room_desc(env),//修饰房间描述
		env->query("outdoors")? NATURE_D->outdoor_room_description() : "" );
	}
	str+=BBLK;
	if( mapp(exits = env->query("exits")) ) 
	{
		dirs = keys(exits);
		for(i=0; i<sizeof(dirs); i++)
			if( (int)env->query_door(dirs[i], "status") & DOOR_CLOSED )
				dirs[i] = 0;
		dirs -= ({ 0 });

       if(sizeof(dirs)==0)
			if ( n&&!(wizardp(me)&&me->query("env/debug")) ) 
				str += "    四周一片漆黑，看不清出路。\n";
			else
				str += "    这里没有任何明显的出路。\n";
		else 
			if( sizeof(dirs)==1 )
				if ( n&&!(wizardp(me)&&me->query("env/debug")) )
					if ( ! random(5) ) 
						str += "    四周一片漆黑，看不清出路。\n";
					else 
						str += "   这里的出口好象是"  HIY + dirs[0] + NOR "。\n";
				else
					str += "    这里唯一的出口是 " HIY  + dirs[0]  + NOR  "。\n";
			else   
				if ( n&&!(wizardp(me)&&me->query("env/debug")) ) 
					if ( ! random(5) ) 
						str += "    四周一片漆黑，看不清出路。\n";
			      	else 
			      		str += sprintf ("   这里的出口好象是" HIY +  "%s"   + NOR " 和 "   HIY  + "%s"  + NOR "。\n",
							implode(dirs[0..sizeof(dirs)-2], "、"), dirs[sizeof(dirs)-1]);
				else
					str += sprintf("    这里明显的出口是 " HIY + "%s"   + NOR  " 和 " HIY + "%s"  + NOR "。\n",
						implode(dirs[0..sizeof(dirs)-2], "、"), dirs[sizeof(dirs)-1]);
	}

	inv = all_inventory(env);
     if ( n && (int)env->query("outdoors") &&!wizardp(me)&&!me->query("env/debug"))
	{
		for(i=0; i<sizeof(inv); i++) 
		{
			if( inv[i]==me ) continue;
			if( !me->visible(inv[i]) ) continue;
			if (inv[i]->is_character() )
				str += "一个朦胧的身影，看不清楚是谁。\n";
			else 
				str += "一团模模糊糊的东西。\n";
		}
	}
	else
	{
		for(i=0; i<sizeof(inv); i++) 
		{
			if( inv[i]==me ) continue;
			if( !me->visible(inv[i]) ) continue;
			str += "  " + inv[i]->short() + "\n";
		}
	}
	write(BBLK+str+BBLK);
	return 1;
}

int look_item(object me, object obj)
{
	mixed *inv;
	int i;
	string str;
	str="\n";
	me->start_more(obj->long());
	inv = all_inventory(obj);
	if( sizeof(inv) ) {
		//inv = map_array(inv, "inventory_look", this_object() );
		//这句似乎有错，故注释！用下面的程序取代Jackyboy
		for(i=0;i<sizeof(inv);i++)
			str+=(string)inv[i]->name(1)+"\n";
		message("vision", sprintf(BBLK+"里面有：\n  %s\n"+BBLK,str), me);
	}
	return 1;
}

int look_living(object me, object obj)
{
    string str, pro,pp,banghui;
	mixed *inv;
	mapping my_fam, fam;
    int me_shen, obj_shen,phlye,bhrank;
	phlye= (int)obj->query("phlye");	
	me_shen = (int)me->query("shen");
	obj_shen = (int)obj->query("shen");
        banghui = obj->query("banghui");
        bhrank = obj->query("bhrank");

	if( me!=obj )
		message("vision", me->name() + "正盯著你看，不知道打些什么主意。\n", obj);

	str = BBLK+obj->long();

	pro = (obj==me) ? gender_self(obj->query("gender")) : gender_pronoun(obj->query("gender"));

	if( (string)obj->query("race")=="人类"
	&&	intp(obj->query("age"))  )
	{	if (phlye)
		{
			switch (phlye){
			case 1 :  pp=sprintf("江南人氏"); break;
			case 2 :  pp=sprintf("中原人氏"); break;
			case 3 :  pp=sprintf("京城人氏"); break;
			case 4 :  pp=sprintf("西域人氏"); break;
			case 5 :  pp=sprintf("云南人氏"); break;
			case 6 :  pp=sprintf("成都人氏"); break;
			}
		str += sprintf("%s看起来好象是%s。\n",pro, pp);
		} 
		str += sprintf("%s看起来约%s多岁。\n", pro, chinese_number(obj->query("age") / 10 * 10));
	}
// 增加帮会的函数调用，可以看出玩家加入哪个帮会 adx
                        if (banghui)
                        str += pro + BANGHUI_D->query_banghui( banghui , bhrank );
	// If we both has family, check if we have any relations.
	if( obj!=me
	&&	mapp(fam = obj->query("family"))
	&&	mapp(my_fam = me->query("family")) 
	&&	fam["family_name"] == my_fam["family_name"] ) {
	
		if( fam["generation"]==my_fam["generation"] ) {
			if( (string)obj->query("gender") == "男性" ||
				(string)obj->query("gender") == "无性")
				str += sprintf( pro + "是你的%s%s。\n",
					my_fam["master_id"] == fam["master_id"] ? "": "同门",
					my_fam["enter_time"] > fam["enter_time"] ? "师兄": "师弟");
			else
				str += sprintf( pro + "是你的%s%s。\n",
					my_fam["master_id"] == fam["master_id"] ? "": "同门",
					my_fam["enter_time"] > fam["enter_time"] ? "师姐": "师妹");
		} else if( fam["generation"] < my_fam["generation"] ) {
			if( my_fam["master_id"] == obj->query("id") )
				str += pro + "是你的师父。\n";
			else if( my_fam["generation"] - fam["generation"] > 1 )
				str += pro + "是你的同门长辈。\n";
			else if( fam["enter_time"] < my_fam["enter_time"] )
				str += pro + "是你的师伯。\n";
			else
				str += pro + "是你的师叔。\n";
		} else {
			if( fam["generation"] - my_fam["generation"] > 1 )
				str += pro + "是你的同门晚辈。\n";
			else if( fam["master_id"] == me->query("id") )
				str += pro + "是你的弟子。\n";
			else
				str += pro + "是你的师侄。\n";
		}
	}

	if( obj->query("max_qi") )
		str += pro + COMBAT_D->eff_status_msg((int)obj->query("eff_qi") * 100 / (int)obj->query("max_qi")) + "\n";

	inv = all_inventory(obj);
	if( sizeof(inv) ) {
		inv = map_array(inv, "inventory_look", this_object(), obj->is_corpse()? 0 : 1 );
		inv -= ({ 0 });
		if( sizeof(inv) )
			str += sprintf( obj->is_corpse() ? "%s的遗物有：\n%s\n" : "只见%s：\n%s\n",
				pro, implode(inv, "\n") );
	}

	message("vision", BBLK+str+BBLK, me);

	if( obj!=me && living(obj)
	&& (((me_shen < 0) && (obj_shen > 0)) || ((me_shen > 0) && (obj_shen < 0)))
	&& (((me_shen - obj_shen) > ((int)obj->query("neili") * 20))
	|| ((obj_shen - me_shen) > ((int)obj->query("neili") * 20))))
	{
		write( obj->name() + "突然转过头来瞪你一眼。\n");
		if(obj->query("age") > 15 && me->query("age") > 15)
			COMBAT_D->auto_fight(obj, me, "berserk");
	}

	return 1;
}

string inventory_look(object obj, int flag)
{
	string str;
	if( obj->query("equipped") )
		str = "  "+ do_query(obj);
	else if( !flag )
		str = "    " + str;
	else
		return obj->query("short");

	return BBLK+str+BBLK;
}

string do_query(object obj)
{
	string str,units;

	units =obj->query("unit");
	str = obj->short();
	if (obj->query("armor_type"))
	switch( obj->query("armor_type") ) {
		case "cloth":
		case "armor":
			str = "身穿一"+ units + str;
			break;
		case "boots":
			str = "脚上穿着一" + units + str;
			break;
		case "head":
		case "neck":
		case "wrists":
		case "finger":
		case "hands":
			str ="戴着一"+ units + str;
			break;
		case "waist":
			str = "腰间绑得有一"+units+str;
			break;
		default:
			str = "装备着"+str; 
			}
	else
	if( obj->wield() )
		if (obj->query("skill_type")=="throwing")
		str ="身上带着"+str;
		else
		str ="手持一" + units + str;
	return BBLK+str+BBLK;
}

int look_room_item(object me, string arg)
{
	object env;
	mapping item, exits;

	if( !objectp(env = environment(me)) )
		return notify_fail("这里只有灰蒙蒙地一片，什么也没有。\n");
	if( mapp(item = env->query("item_desc")) && !undefinedp(item[arg]) ) 
	{
		if( stringp(item[arg]) )
			write(item[arg]);
		else if( functionp(item[arg]) )
			write((string)(*item[arg])(me));
		return 1;
	}
	if( mapp(exits = env->query("exits")) && !undefinedp(exits[arg]) ) 
	{
		if( objectp(env = find_object(exits[arg])) )
			look_room(me, env);
		else 
		{
			call_other(exits[arg], "???");
			look_room(me, find_object(exits[arg]));
		}
		return 1;
	}
	return notify_fail("你要看什么？\n");
}
string nocolor(string str2)
{
	//为了统一格式，可以把所有ansi颜色控制字符删除掉！这样来算长度！
	str2 = replace_string(str2, BLK,"");
	str2 = replace_string(str2, RED,"");
	str2 = replace_string(str2, GRN,"");
	str2 = replace_string(str2, YEL,"");
	str2 = replace_string(str2, BLU,"");
	str2 = replace_string(str2, MAG,"");
	str2 = replace_string(str2, CYN,"");
	str2 = replace_string(str2, WHT,"");
	str2 = replace_string(str2, HIR,"");
	str2 = replace_string(str2, HIG,"");
	str2 = replace_string(str2, HIY,"");
	str2 = replace_string(str2, HIB,"");
	str2 = replace_string(str2, HIM,"");
	str2 = replace_string(str2, HIC,"");
	str2 = replace_string(str2, HIW,"");
	str2 = replace_string(str2, NOR,"");
	str2 = replace_string(str2, BLINK,"");
	return str2;
}
string room_desc(object ob)
{
	//由于格式控制不熟悉，所以有一段持续格式化。
	string *line,result,tmp;
	int tag,i,j,tab;
	if(ob->query("no_desc")||ob->query("outdoors")||!this_player()->query("env/room_desc"))
		return "    "+ob->query("long");
	line=explode(ob->query("long"),"\n");
	if(!line)
		return "场景错误！请报告巫师。\n";
	result="┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
	tag=0;
	foreach(tmp in line)
	{
		if(!tag)
		{
			tmp="    "+tmp;
			tag=1;
		}
		//由于有字符值为97的字符存在，显示的时候必须排除97这个字符，不然显示不正常
		//使用这个循环判断第一个97出现的位置
		//清除颜色所占据的位置
		tmp=nocolor(tmp);
		tab=0;
		for(i=0;i<sizeof(tmp);i++)
		{
			if((int)tmp[i]==97)
				break;//i记录的才是显示的长度
			if(tmp[i]=='\t')
				tab++;
		}
		//write ("共有"+tab+"个Tab!"+i+"个字符!补充"+(68-i-tab*7+2)+"个空格。\n");
		tab=tab*7-2;
		if(tab<0) tab=0;
		if(sizeof(tmp)>68-tab)//处理过长字符串，采用直接截取的方法。
			tmp=tmp[0..64]+"....";
		for(j=68-i-tab;j>0;j--)
			tmp=tmp+" ";
		result=result+"┃"+tmp+"┃\n";
	}
	result=result+"┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n";
	return result;
}
	
int help()
{
	write(@HELP
指令格式: look [<物品>|<生物>|<方向>]
 
这个指令让你查看你所在的环境、某件物品、生物、或是方向。
 
HELP
);
	return 1;
}
