// 函数列出命令，可以列出一个物件或一个程序被载入后可以调用的函数列表
// Write By JackyBoy@CuteRabbit Studio 1999/5/31

inherit F_CLEAN_UP;

int main(object me, string arg)
{
    object target;
    mixed  output;

    if( !arg ) target = me;
    if( arg == "here" ) target = environment(me);
    if( arg == "me" ) target = me;
    if( !target ) target = present(arg, me);
    if( !target ) target = present(arg, environment(me));
    if( !target ) target = load_object(resolve_path(me->query("cwd"), arg));
    
    if( !target ) return notify_fail("没有这个物品。\n");

    output = implode(({sprintf("Function list for %s",file_name(target))})+
          sort_array(
            map_array( functions( target ), (: sprintf("%-34s: %-34s",
                  (function_exists($1, $(target)) ?
                    function_exists($1, $(target)) :
                    "*PROTECTED*"), $1 ) :)), 1), "\n");
    me->start_more(output);
    return 1;
}

int help()
{
        write(@HELP
指令格式: flist [<物品名称>]

列出物品上存在的函数

HELP
        );
        return 1;
}
