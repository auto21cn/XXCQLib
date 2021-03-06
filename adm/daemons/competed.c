// competed.c
// create by netplay@cctxII 
/*
参加比赛的选手得分共有以下几种情况：
A、双方EXP大致在一个等级
        1、双方均上榜和双方均不上榜 胜：300 负：0
        2、一方上榜，一方未上  
                上榜者--未上榜者
                胜：200   胜：300
                负：-50   负：0

B、双方EXP不相等（如相差太大，则禁止比武）
        1、双方均上榜和双方均不上榜情况  
                EXP高者--EXP低者
                胜：200    胜：300      
                负：0      负：0        
       2、一方上榜，一方未上
                EXP高上榜--EXP低未上榜
                胜：0         胜：400
                负：-300        负：0

                EXP高未上榜--EXP低上榜
                胜：200         胜：200
                负：-50         负：-50

注：以上上榜为排名前50位者
*/


inherit F_SAVE;
inherit F_DBASE;
int sort_fighter(object);
int query_place(object);
string *get_tops();
int wincom( string,string);
mapping top;

void create()
{	
	seteuid(getuid());
	set("channel_id","比武精灵");
    if( !restore() && !mapp(top) )
        top = ([]);
}

string query_save_file() { return DATA_DIR + "topd"; }

void fighter_place(object winner,object loser)
{
	
	int wtag=0,ltag=0;
	int wexp,lexp;
	int wplace,lplace;
	object win_body,los_body;
	win_body=winner->query_temp("link_ob");
	los_body=loser->query_temp("link_ob");
	//查询比武双方是否是上榜人员
	wtag=query_place(winner);
	ltag=query_place(loser);
	
	//查询比武双方的EXP
	wexp=winner->query("combat_exp");
	lexp=loser->query("combat_exp");

	//接下来将相应的给各人的积分添加和减少
	if( (wexp+=wexp/2 > lexp) && (lexp+=lexp/2 > wexp) )//exp相对一样
	{	if( (wtag && ltag) || (!wtag && !ltag) )//双方均上榜或不上榜
		win_body->add("jifen",300);
		if(wtag && !ltag)//胜者上榜，负者没上
		win_body->add("jifen",200);
		if(ltag && !wtag)//负者上榜，胜者没上
		{win_body->add("jifen",300);los_body->add("jifen",-50);}
	}else //exp相对不一样
	{
			if((wtag && ltag) || (!wtag && !ltag))//双方均上榜或不上榜
			if( lexp+=lexp/2 <= wexp ) //胜者EXP大的情况
				win_body->add("jifen",200);
			else win_body->add("jifen",300);//胜者EXP小
			if(wtag && !ltag)//胜者上榜，负者没上
			if( wexp+=wexp/2 <= lexp ) //胜者EXP小的情况
			win_body->add("jifen",200);
			else los_body->add("jifen",-50);

			if(ltag && !wtag)//负者上榜，胜者没上
			if( wexp+=wexp/2 <= lexp ) //胜者EXP小的情况
			{win_body->add("jifen",400);los_body->add("jifen",-300);}
			else//胜者EXP大
			{win_body->add("jifen",200);los_body->add("jifen",-50);}
	}
	win_body->add("win",1);
	los_body->add("loss",1);

	wplace=sort_fighter(win_body);
	lplace=sort_fighter(los_body);
	
	//CHANNEL_D->do_channel( this_object(), "debug",
	//sprintf("胜利者，第%d名，失败者，第%d名\n",wplace,lplace));
	
	save();
	win_body->save();
	los_body->save();
	winner->save();
	loser->save();
}

int sort_fighter(object body)
{
	string *name;
	int jf,ave_jf;
	int win,loss;
	int i;
	//取得ob的积分
	jf=body->query("jifen");
	win=body->query("win");
	loss=body->query("loss");
	ave_jf=jf/(win+loss);
//debug
	//CHANNEL_D->do_channel( this_object(), "debug",
	//		sprintf("%s胜利%d次、失败%d次、总积分%d\n",body->query("id"),win,loss,jf));
	//取得在榜人员的名单，该名单按积分排序
	if (mapp(top))
	{
		name=keys(top);
		i=sizeof(name);
		if(i==0 && ave_jf>0)//如果积分榜不为空的话
		{top=( [body->query("id"): ave_jf] );
		//debug
		//CHANNEL_D->do_channel( this_object(), "debug",
		//	sprintf("%s的平均积分为%d\n",body->query("id"),ave_jf));
		return 1;
		}
		if(i<50 && ave_jf>0){
		top[body->query("id")]=ave_jf;//人数不满50，直接加入
		//debug
		//CHANNEL_D->do_channel( this_object(), "debug",
		//	sprintf("%s的平均积分为%d\n",body->query("id"),ave_jf));
		return query_place(body);} 
		else
		{
		name=get_tops();
		if(ave_jf>top[name[0]]){
			map_delete(top,name[0]);
			top[body->query("id")]=ave_jf;
			//debug
			//CHANNEL_D->do_channel( this_object(), "debug",
			//sprintf("%s的平均积分为%d\n",body->query("id"),ave_jf));
			return query_place(body);
			}

		}
	}
	
}
//查询OB的排名，如果没上榜，返回0，上榜，返回名次。	
int query_place(object ob)
{
		string *name;
		string id;
		int i;

		id=ob->query("id");
		name=get_tops();
		for(i=0;i<50;i++)
		{
		if (id==name[i]) 
				{return i+1;break;}
		}
		return 0;
}
//该函数将按返回排行榜的人员名单
string *get_tops()
{	
	string *name;
	string str;
	int i,j,z;

	if(mapp(top))
	name=keys(top);

	z=sizeof(name);
	for(j=0;j<z-1;j++)
	for(i=0;i<(z-j)-1;i++)
	{	if(top[name[i]]<top[name[i+1]])
		{str=name[i];name[i]=name[i+1];name[i+1]=str;}
		if(top[name[i]]==top[name[i+1]])//积分相同
			if(wincom(name[i],name[i+1]))
			{str=name[i];name[i]=name[i+1];name[i+1]=str;}
	}
	return name;
}

int wincom( string id1,string id2)
{
	object ob1,ob2;
	int i;
	ob1 = new(LOGIN_OB);
	ob1->set("id", id1);
	
	ob2 = new(LOGIN_OB);
	ob2->set("id", id2);
	
	if(ob1->restore() && ob2->restore())
		i=ob2->query("win") - ob1->query("win");
	destruct(ob1);
	destruct(ob2);
	return i;
}


string user_fight_info(string name)
{
	object ob;
	string msg;
		
	
	ob = new(LOGIN_OB);
	ob->set("id", name);
	if( !ob->restore() ) 
		return "神秘人。\n";
	
	msg = sprintf("%-25s出场：%s次  胜：%s次  败：%s次 \n",
		  ob->query("name")+"("+ob->query("id")+")",
		  chinese_number(ob->query("win")+ob->query("loss")),
		  chinese_number(ob->query("win")),
		  chinese_number(ob->query("loss")),
		   );
	destruct(ob);

	return msg;
}