// /d/murong/xiaozhou.c


#include <ansi.h>
#define SHIP_TO __DIR__"xd"
inherit ROOM;

void create()
{
        set("short", GRN "小舟" NOR);  
        set("long", @LONG
你掉进一叶小舟，最多也就能载三、四个人。一名家丁手持长竹篙，正
在船尾吃力地撑着船。
LONG);      
 
       set("no_fight", 1); 
       setup(); 
}
 
void init()
{ 
      object me = this_player();               
      call_out("do_bird", 10, me);  
      add_action("do_action", "");                             
}

int do_action(string arg)
{
       string action = query_verb();

       switch (action) {   
       	       case "l":
       	       case "look":	
               case "dazuo":
               case "exercise": 
               case "lian":
               case "tuna":
               case "kill":
               case "fight":
               case "steal":
               case "hit":
	       case "save":       
               case "quit":    
               case "drop":
               case "practice":
               write(HIY"\n这是一叶小舟，最多也就能载三、四个人。一名穿着质朴的中年船夫公手持\n"
"长竹篙，正在船尾吃力地撑着船。\n\n"NOR);
                       return 1;
       }
       return 0;
}

void do_bird()
{ 
	object me = this_player(); 
	mixed *local;

	local = localtime(time() * 60);
        if(environment(me))
        {  
        	write(HIW"\n船夫把船驶进了一片一望无际的荷花荡。\n\n"NOR);
	        if( local[2] < 5 && local[2] >= 2 )  
	        {
			write(YEL"\n流动的光辉之中，一切都失了正色。月光如流水一般，静静地泻在一片片的\n"
		           "荷叶和荷花上。薄薄的青雾浮起在荷花荡中。荷叶和荷花仿佛在牛乳中流过\n"
		           "一样；又象笼着青纱的梦。岸边弯弯的杨柳的稀疏的倩影，却又象是画在荷\n"
		           "叶上。\n\n"NOR); 
        	call_out("do_bird1", 10, this_object());		             
	        }
        	if( local[2] < 2 || local[2] >= 21 ) 
        	{
			write(BLU"\n你站在小舟之上，近可察湖的银容，远可观山的黛色。天上缀满了闪闪发光\n"
       			"的星星象细碎的流沙铺成的银河歇躺在青色的天宇上。有时被云护着，浅映\n"
			"出乳白的晕华；有时碧天无际，则偏浸着冰莹的青光。萧萧的夜风拂着你惺\n"
           		"忪的脸，感到轻微的瑟缩。\n\n"NOR);
        	call_out("do_bird1", 10, this_object());		             
	        }
        	if( local[2] < 8 && local[2] >= 5 )  
        	{
			write(HIM"\n东方的天空开始是沉重的。但一歇条一斜条鲜红的橘红色朝霞，越来越清楚\n"
           		"地出现在空中。东方的天色已渐渐发白，头上通过染有淡红色的飞翔白云看\n"
           		"得见浅蓝的天空；光亮轻盈的云在浮动。霞光辉映着朵朵的云片，透过死气\n"
           		"沉沉的迷雾现出来。\n\n"NOR);                                   
        	call_out("do_bird1", 10, this_object());		             
          	}
        	if( local[2] < 12 && local[2] >= 8 ) 
        	{
			write(RED"\n一眼望去, 满湖荷叶, 菱叶, 芦苇, 茭白, 都是一模一样, 兼之荷叶, 菱叶\n"
           		"在水面漂浮, 随时一阵风来, 便即变化百端, 就算此刻记得清清楚楚, 霎时\n"
           		"间局面便全然不同。镜子搬的水面，反射着银色的光。岸边的垂柳和白杨灵\n"
           		"化了似的耸立着。青草、芦苇和红的、白的、紫的花儿被高悬在天空的一轮\n"
           		"火热的太阳蒸晒着，空气里充满了甜醉的气息。\n\n"NOR);   
        	call_out("do_bird1", 10, this_object());		             
          	}
        	if( local[2] < 21 && local[2] >= 17 ) 
        	{
			write(HIY"\n西天泛着殷红色的晚霞。映在碧绿清澈的湖水上，漾着一片玫瑰色的光，远\n"
           		"远的霞光，刻刻的在变幻中，如霜枫、如榴火、如玛瑙、如琥珀，..... 随\n"
           		"着夕阳的逐渐西尘，天空的霞光渐渐淡下去了，深红地颜色变成了绯红，又\n"
           		"变为浅红，那突然显得高而远了地天空，呈现出一片肃穆地神色。\n\n"NOR);
        	call_out("do_bird1", 10, this_object());		             
        	}                
        	if( local[2] < 17 && local[2] >= 12 ) 
        	{
			write(GRN"\n曲曲折折的荷塘上面，弥望的是田田的叶子。层层的叶子中间，零星地点缀\n"
           		"着些白花，正如一粒粒的明珠，又如碧天里的星星，又如刚出浴的美人。微\n"
           		"风过处，送来屡屡清香，仿佛远处飘渺的歌声似的。\n\n"NOR);
        	call_out("do_bird1", 10, this_object());		             
         	}                                    
    	}
    	return;
}
void do_bird1()
{ 
	object me = this_player();   
    	mixed *local;

	local = localtime(time() * 60);
        if(environment(me)) 
        {  
		write(CYN"\n小舟在荷花荡中左拐右拐，一丛丛芦苇和荷花在你眼前晃过。\n\n"NOR);
        	if( local[2] < 5 && local[2] >= 2 ) 
        	{
			write(HIW"\n晨曦姗姗来迟，星星总是不肯离去。乳白色的蒸汽已从湖面上冉冉升起来。\n"
           		"不知那儿来的这么多飘渺透明的白纱！\n\n"NOR);
        	call_out("do_bird2", 10, this_object());		             
	        }
         	if( local[2] < 8 && local[2] >= 5 ) 
         	{
			write(CYN"\n雾现在已经缝合了。另有一道白色的扰混的奶气似的雾露还一卷一卷的卷起\n"
           		"来，绕着前面的芦苇，湿冷腻滞的在湖面团成几乎看不见的水玻璃球。然后\n"
           		"又兀自滩成一层粘雾，泛着白气。\n\n"NOR);         
        	call_out("do_bird2", 10, this_object());		             
           	}
          	if( local[2] < 12 && local[2] >=8 ) 
          	{
			write(GRN"\n绿盈盈的湖面上，几只微微抖动着白色翅膀的小舟，在湿润的微风中荡漾。\n"
		        "几只小燕子在湖面上飞来飞去。\n\n"NOR);
        	call_out("do_bird2", 10, this_object());		             
           	}
           	if( local[2] < 17 && local[2] >= 12 ) 
           	{          
			write(GRN"\n从不远处烟水蒙蒙的湖面上飘来一阵轻柔婉转的歌声，那是少女们在和歌嘻\n"
           		"笑，荡舟采莲。\n\n"NOR);
        	call_out("do_bird2", 10, this_object());		             
              	}             
           	if( local[2] < 21 && local[2] >= 17 ) 
           	{
			write(CYN"\n太阳落山了，它的分外红的强光从树梢头喷射出来，将云染成血色。西方红\n"
           		"灼灼地光闪烁着，湖水染成紫色，太阳足有一个脸盆大，起初盖着黄红色的\n"
           		"云，有时露出两道红线来，仿佛火神怒睁两眼。一会儿，天上立刻露出淡灰\n"
           		"色来，只在西方还有五彩余辉闪烁着。\n\n"NOR);
		call_out("do_bird2", 10, this_object());           	
           	}              
           	if( local[2] < 2 || local[2] >= 21 ) 
           	{
		write(CYN"\n这时万籁俱寂，在湖岸茂密的竹林间，连一声鸟语也听不到。绿的象碧琉璃\n"
           	"一般的湖水，有如一面大圆宝镜，湖上笼罩着一抹青烟，水面漂浮着三五扁\n"
           	"舟似近实远，似定时动，好象一幅山水画一般。\n\n"NOR);
        	call_out("do_bird2", 10, this_object());           	
           	}
      	}     
      	return;
}

void do_bird2()
{ 
        object me = this_player();
        if(environment(me)) 
        {
		write(YEL"\n小舟在芦苇和荷花荡中来回穿梭。\n\n"NOR);
        	call_out("wait", 10, this_object());
       	}     
       	return;
}

void wait()
{
        object me, room;      
        me = this_player();
        room = find_object(__DIR__"xd");
        if(!(room=find_object(__DIR__"xd")))
             room=load_object(__DIR__"xd");
        tell_object(me, CYN"\n你坐在小舟里面，欣赏着太湖的美丽景色，不知不觉中已到达了目的地。\n\n"NOR);
        tell_object(me, "    这里唯一的出口是 "HIG"out"NOR"。\n");

        this_object()->set("exits/out", __DIR__"xd");                             
        call_out("check", 20, this_object());
        return;
}

void check()
{
        object room, *ob;
        int i;

        if( room = find_object(__DIR__"xiaozhou1") ) {
                room->delete("exits/out");

                tell_room(room, "艄公轻声说道：“都下船吧，我也要回去了。”\n", ({}));
                ob = all_inventory(room);
                for(i = 0; i < sizeof(ob); i++) {
                        if (userp(ob[i])) {
                                if (!living(ob[i])) tell_room(room, "艄公把$N抬下了船。\n", ob[i]);
                                else tell_room(room, "$N听了艄公的话，乖乖地下了船。\n", ({ob[i]}));
                                ob[i]->move(SHIP_TO);
                                if (!living(ob[i])) tell_room(SHIP_TO, ob[i]->name() + "被抬下了船。\n", ({ob[i]}));
                                else tell_room(SHIP_TO, ob[i]->name() + "走下了船。\n", ({ob[i]}));
                        }
                }
                message("vision", "艄公把踏脚板收起来，把扁舟驶向江心。\n", room);
                return;
        }
}                                                             
                                                               
                              
                              