// Item yaochu.c  
// Created by Zeus 1999.7.30
// Modified by Zeus 1999.7.31
// 
// 

inherit ITEM;

string* medrooms = ({
        "/d/wenjia/caodi",
        "/d/wenjia/dayuan",
        "/d/wenjia/houyuan",
        "/d/wenjia/huoroad1",
        "/d/wenjia/huoroad2",
        "/d/wenjia/huoroad3",
        "/d/wenjia/huoroad4",
        "/d/wenjia/huoroad5",
        "/d/wenjia/huoroad6",
        "/d/wenjia/huoroad7",
        "/d/wenjia/huoroad8",
        "/d/wenjia/shulin1",
        "/d/wenjia/shulin2",
        "/d/wenjia/shanlu1",
        "/d/wenjia/shanlu2",
        "/d/wenjia/shanlu3",
        "/d/wenjia/shanlu4",
        "/d/wenjia/siroad1",
        "/d/wenjia/siroad2",
        "/d/wenjia/siroad3",
        "/d/wenjia/siroad4",
        "/d/wenjia/siroad5",
        "/d/wenjia/siroad6",
        "/d/wenjia/yaotian1",
        "/d/wenjia/yaotian2",
        "/d/wenjia/yaotian3",
        "/d/wenjia/yaotian4",
        "/d/wenjia/yaotian5",
        "/d/wenjia/yaotian6",
        "/d/wenjia/yaotian7",
});

string* medsources = ({
        "chihuohe",
        "mushugen",
        "fanmubie",
        "chiaisu", 
        "duanchangcao", 
        "hedinghong", 
        "kongquedan", 
});

string* chinesemedsources = ({
        "赤火蝎",
        "木薯根",
        "番木鳖",
        "赤矮栗",
        "断肠草",
        "鹤顶红",
        "孔雀胆",
});

void init();
int do_wa(string arg);

void create()
{
        set_name( "药锄",({ "yao chu"}));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long","这是一把药锄。\n");
                set("value", 100);
                set("material", "iron");
        }
}

void init()
{
        add_action("do_wa", "wa");
}

int do_wa(string arg)
{
        object me,room,obj;
        int med1,med2,med3,medroom1,medroom2,medroom3,i;
        string now_place;

        me=this_player();
        room=environment(me);
        now_place=file_name(room);
        if (wizardp(me)){
        message_vision("本次地点是"+medrooms[me->query_temp("taskxiao/medroom1")]
                              +"、"+medrooms[me->query_temp("taskxiao/medroom2")]
                              +"、"+medrooms[me->query_temp("taskxiao/medroom3")]+"\n",me);
        message_vision("现在你在"+now_place+"。\n",me);}
        if ( now_place==medrooms[me->query_temp("taskxiao/medroom1")]
            && !me->query_temp("taskxiao/meddone1"))
        {
                message_vision("$N拿起药锄努力的在地上挖起来。\n",me);
                message_vision("$N挖到一棵"+chinesemedsources[me->query_temp("taskxiao/med1")]+"。\n",me);
                me->set_temp("taskxiao/meddone1",1);
                obj=new("/d/wenjia/task_xiao/obj/"+medsources[me->query_temp("taskxiao/med1")]);
                obj->move(me);
                return 1;
		}

		if ( now_place==medrooms[me->query_temp("taskxiao/medroom2")]
            && !me->query_temp("taskxiao/meddone2"))
        {
                message_vision("$N拿起药锄努力的在地上挖起来。\n",me);
                message_vision("$N挖到一棵"+chinesemedsources[me->query_temp("taskxiao/med2")]+"。\n",me);
                me->set_temp("taskxiao/meddone2",1);
                obj=new("/d/wenjia/task_xiao/obj/"+medsources[me->query_temp("taskxiao/med2")]);
                obj->move(me);
                return 1;
		}

		if ( now_place==medrooms[me->query_temp("taskxiao/medroom3")]
            && !me->query_temp("taskxiao/meddone3"))
        {
                message_vision("$N拿起药锄努力的在地上挖起来。\n",me);
                message_vision("$N挖到一棵"+chinesemedsources[me->query_temp("taskxiao/med3")]+"。\n",me);
                me->set_temp("taskxiao/meddone3",1);
                obj=new("/d/wenjia/task_xiao/obj/"+medsources[me->query_temp("taskxiao/med3")]);
                obj->move(me);
          		return 1;
		}
        message_vision("$N挖了半天什么也没挖到。\n",me);
		return 1;
}
