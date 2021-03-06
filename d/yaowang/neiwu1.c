// Room: 汴梁药局
// By 山猫adx @ 宁波小雪 17:00 99-10-26

inherit ROOM;

object shop_box;

void create()
{
	set("short", "内屋");
	set("long", @LONG
这里是回春堂专门出售药王庄弟子精心炮制的成药的地方。
药王谷有许多技艺高超的弟子，他们有时会炮制一些成药
就放在这里出售，疗效比一般的药材效果更佳。
LONG );
	set("area", "汴梁东");
	set("areb", "回春堂");
	set("no_clean_up", 1);
	set("no_fight", 1);
	set("exits", ([
		"east" : __DIR__"nanting",
	]));
	set("objects", ([
		__DIR__"npc/huoji2" : 1,
	]));
	setup();
}

void init()
{
	add_action("do_sell", "寄售");
	add_action("do_sell", "jishou");
	add_action("do_buy", "buy");
	add_action("do_list", "list");
}

object findbox()
{
    if(shop_box && environment(shop_box)==this_object()) 
      return shop_box;

    shop_box=new(__DIR__"npc/obj/shopbox");
    shop_box->move(this_object());
    return shop_box;
}

int query_max_items() {return 50;}
string get_name(string str);

string value_string(int value)
{
	if( value < 1 ) value = 1;
	else if( value < 100 )
		return chinese_number(value) + "文钱";
	else
		return chinese_number(value/100) + "两"
			+ (value%100? "又" + chinese_number(value%100) + "文钱": "");
}

void pay_player(object who, int amount)
{
	object ob;

	if( amount < 1 ) amount = 1;
	if( amount/100 ) {
		ob = new(SILVER_OB);
		ob->set_amount(amount/100);
		ob->move(who);
		amount %= 100;
	}
	if( amount ) {
		ob = new(COIN_OB);
		ob->set_amount(amount);
		ob->move(who);
	}
}

int do_sell(string arg)
{
   object ob;
   int value, sale;
   string obj_file;
   int i, oldnum;
   string index;

   if( this_player()->is_busy() )
     return notify_fail("你现在正忙着呢。\n");

   if( !arg || !(ob = present(arg, this_player())) )
     return notify_fail("你要寄售什么药品？\n");

   if( ob->query("money_id") )   return notify_fail("你要卖「钱」？\n");
   value = ob->query("value");
   sale=ob->query_temp("sale_price");
   if(sale>0 && sale<value) value=sale;
   if( !ob->query("yaowang") ) return notify_fail("这个东西，不适合在这里寄售！\n");
   if( !value ) return notify_fail("这是你炮制的药品吗？这个东西没用！\n");

   message_vision("$N拿出一"+ ob->query("unit") + ob->query("name") +"交给卖药伙计寄售。"+
		"得了"+value_string(value*90/100)+"。\n", this_player());

        index=ob->query("name")+"("+ob->query("id")+")";

   if(!findbox()->query_temp("goods/"+index) ){
           findbox()->set_temp("goods/"+index, ob);
      findbox()->set_temp("numbers/"+index, 1);
      ob->move(findbox());
   }
   else {
      oldnum = findbox()->query_temp("numbers/"+index);
           findbox()->set_temp("numbers/"+index, oldnum+1);
      destruct(ob);
   }

   this_player()->start_busy(1);
   pay_player(this_player(), value * 90 / 100);

   return 1;
}

int do_list(string arg)
{
   mapping goods;
   string list, *name;
   int i;
   string tlist;
   object me=this_player();

   if( !mapp(goods = findbox()->query_temp("goods")) )
     return notify_fail("这里目前没有药品寄售。\n");
   name = keys(goods);
   if(!sizeof(goods)) 
     return notify_fail("这里目前没有药品寄售。\n");

   if( !arg )   {
      list = "你可以购买下列这些药品：\n";
      write(list);
      i=sizeof(goods);
      while(i--) {
             if(!goods[name[i]]) {
          findbox()->delete_temp("numbers/"+name[i]);
          findbox()->delete_temp("goods/"+name[i]);
          continue;
             }
        //mon 2/4/98 because some items may destruct themselves
        //after being sold.

        tlist = get_name(name[i]);
        list = sprintf("%-30s：%-20s：还剩%s%s\n", tlist,
          value_string(goods[name[i]]->query("value")),
          chinese_number(findbox()->query_temp("numbers/"+name[i])),
          goods[name[i]]->query("unit") );
              write(list);
      }
   }
   else if( arg == "book" )  {
     list = "";
     i=sizeof(goods);
     while(i--) {
             if(!goods[name[i]]) {
          findbox()->delete_temp("numbers/"+name[i]);
          findbox()->delete_temp("goods/"+name[i]);
          continue;
             }

           if( mapp(goods[name[i]]->query("skill")) )   {
           tlist = get_name(name[i]);
           list += sprintf("%-30s：%-20s：还剩%s%s\n", tlist,
             value_string(goods[name[i]]->query("value")),
             chinese_number(findbox()->query_temp("numbers/"+name[i])),
             goods[name[i]]->query("unit") );
      }
     }
      if( list == "" )
      write("这里目前没有这种药品。\n");
      else {
   list = "你可以购买下列这些药品：\n"+list;
   me->start_more(list);
      }
   }
   else if( arg == "drug" )  {
     list = "";
     i=sizeof(goods);
     while(i--) {
             if(!goods[name[i]]) {
          findbox()->delete_temp("numbers/"+name[i]);
          findbox()->delete_temp("goods/"+name[i]);
          continue;
             }
      if( goods[name[i]]->query("drug_type") )   {
           tlist = get_name(name[i]);
           list += sprintf("%-30s：%-20s：还剩%s%s\n", tlist,
             value_string(goods[name[i]]->query("value")),
             chinese_number(findbox()->query_temp("numbers/"+name[i])),
             goods[name[i]]->query("unit") );
      }
     }
      if( list == "" )
      write("这里目前没有药品寄售。\n");
      else {
   list = "你可以购买下列这些药品：\n"+list;
   me->start_more(list);
      }
   }
   else if( arg == "axe" || arg == "blade" || arg == "dagger" || 
   arg == "fork" || arg == "hammer" || arg == "spear" || arg == "mace" || arg == "rake" ||
   arg == "staff" || arg == "stick" || arg == "sword" || arg == "whip" ||
   arg == "throwing" )  {
     list = "";
     i=sizeof(goods);
     while(i--) {
             if(!goods[name[i]]) {
          findbox()->delete_temp("numbers/"+name[i]);
          findbox()->delete_temp("goods/"+name[i]);
          continue;
             }

      if( goods[name[i]]->query("skill_type") == arg )   {
           tlist = get_name(name[i]);
           list += sprintf("%-30s：%-20s：还剩%s%s\n", tlist,
             value_string(goods[name[i]]->query("value")),
             chinese_number(findbox()->query_temp("numbers/"+name[i])),
             goods[name[i]]->query("unit") );
      }
     }
      if( list == "" )
      write("这里目前没有这种药品寄售。\n");
      else {
   list = "你可以购买下列这些东西：\n"+list;
   me->start_more(list);
      }
   }
   else if( arg == "archery" )  {
     list = "";
     i=sizeof(goods);
     while(i--) {
             if(!goods[name[i]]) {
          findbox()->delete_temp("numbers/"+name[i]);
          findbox()->delete_temp("goods/"+name[i]);
          continue;
             }
      if( goods[name[i]]->query("apply/skill_type") == arg )   {
           tlist = get_name(name[i]);
           list += sprintf("%-30s：%-20s：还剩%s%s\n", tlist,
             value_string(goods[name[i]]->query("value")),
             chinese_number(findbox()->query_temp("numbers/"+name[i])),
             goods[name[i]]->query("unit") );
      }
     }
      if( list == "" )
      write("这里目前没有这种药品寄售。\n");
      else {
   list = "你可以购买下列这些药品：\n"+list;
   me->start_more(list);
      }
   }
   else if( arg == "armor" || arg == "boots" || arg == "cloth" ||
    arg == "finger" || arg == "hands" || arg == "head" || arg == "neck" ||
    arg == "shield" || arg == "surcoat" || arg == "waist" ||
    arg == "wrists" )   {
     list = "";
     i=sizeof(goods);
     while(i--) {
             if(!goods[name[i]]) {
          findbox()->delete_temp("numbers/"+name[i]);
          findbox()->delete_temp("goods/"+name[i]);
          continue;
             }
      if( goods[name[i]]->query("armor_type") == arg ) {
           tlist = get_name(name[i]);
           list += sprintf("%-30s：%-20s：还剩%s%s\n", tlist,
             value_string(goods[name[i]]->query("value")),
             chinese_number(findbox()->query_temp("numbers/"+name[i])),
             goods[name[i]]->query("unit") );
      }
     }
      if( list == "" )
      write("这里目前没有这种药品寄售。\n");
      else {
   list = "你可以购买下列这些药品：\n"+list;
   me->start_more(list);
      }
   }
   else   {
     list = "";
     i=sizeof(goods);
     while(i--) {
             if(!goods[name[i]]) {
          findbox()->delete_temp("numbers/"+name[i]);
          findbox()->delete_temp("goods/"+name[i]);
          continue;
             }
      if( member_array(arg, goods[name[i]]->parse_command_id_list()) != -1 )   {
           tlist = get_name(name[i]);
           list += sprintf("%-30s：%-20s：还剩%s%s\n", tlist,
             value_string(goods[name[i]]->query("value")),
             chinese_number(findbox()->query_temp("numbers/"+name[i])),
             goods[name[i]]->query("unit") );
      }
     }
      if( list == "" )
      write("这里目前没有这种药品寄售。\n");
      else {
   list = "你可以购买下列这些药品：\n"+list;
   me->start_more(list);
      }
   }

   return 1;
}

int do_buy(string arg)
{
   mapping goods;
   string *name;
   string fname;
   object obj_file, ob;
   int value, oldnum, afford, order;
   int i, j;
   object* inv;
   string arg1, arg2;

   if( this_player()->is_busy() )
     return notify_fail("你现在正忙着呢。\n");

   if( !arg )  {
      write("指令格式：buy <某物>\n");
      return 1;
   }

   // players are used to the "buy sth from sb" format.
   if( sscanf(arg, "%s from %s", arg1, arg2) == 2 )   {
     arg = arg1;
   }

   if( sscanf(arg, "%s %d", fname, order) != 2 )   {
     fname = arg;
     order = 1;
   }

   if( !mapp(goods = findbox()->query_temp("goods")) )
     return notify_fail("当铺目前没有任何货物可卖。\n");
   name = keys(goods);
   if(!sizeof(goods)) 
     return notify_fail("当铺目前没有任何货物可卖。\n");

   j = 0;
   i=sizeof(name);
   while(i--) {
          if(!goods[name[i]]) continue;
     if( member_array(fname, 
         goods[name[i]]->parse_command_id_list()) != -1 )  {
        j++;    
     }
     if( j == order )   {
       obj_file = goods[name[i]];
          value = obj_file->query("value"); 
          if( !(afford=this_player()->can_afford(value)) )  {
             write("你没有足够的钱。\n");
             return 1; 
          }

       ob = new( base_name( obj_file ) ); 
       ob->set_name(obj_file->query("name"),
         obj_file->parse_command_id_list());
         //so that the bought item would be the
         //same as the one on sale.

          if(!ob->move(this_player()))
         return 0;

          this_player()->start_busy(1);

       arg = obj_file->query("name")+
         "("+obj_file->query("id")+")";
          oldnum = findbox()->query_temp("numbers/"+arg);
          if(oldnum == 1)  {
              destruct(obj_file);
           findbox()->delete_temp("numbers/"+arg);
           findbox()->delete_temp("goods/"+arg);
          }
          else    {
           findbox()->set_temp("numbers/"+arg, oldnum-1); 
       }

          this_player()->pay_money(value);
     
          message_vision("$N买下一" +
        ob->query("unit") + ob->query("name") + "。\n", this_player() );

       this_player()->save();
       return 1;
     }
   }

   write("这里目前没有这种药品寄售。\n");

   return 1;
}


string get_name(string str)
{
    string str1, str2;

    while(sscanf(str,"%s %*sm%s",str1,str2)==3)
   str=str1+str2;
    return str;
}

int clean_up()  
{
      return 0;
}
