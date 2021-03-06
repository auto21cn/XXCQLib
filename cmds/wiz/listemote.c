//未对emote内部顺序排序
#define MASTER "/adm/obj/master"
#define MAX 40
inherit F_CLEAN_UP;
#define SPLIT "\n.\n"
#define EM_HEAD "\n.\nbegin:\n.\n"
int main(object me,string file)
{
	string *all_keys,key,str,item,fn;
	mapping emote;
	int i,j;
	if(!file||file=="")
		return notify_fail("用法：export 文件名\n");
	file=MASTER->make_path_absolute(file);
	write("准备输出emote数据到文件"+file+"里。\n");
	if(MASTER->valid_write(file,me,"write_file")==0)
		return notify_fail("你不能写该文件！输出失败！\n");
	if(file_size(file)!=-1)
		return notify_fail("档案已经存在！请先将其删除！\n");//可以多写判断的！
	all_keys=sort_array(EMOTE_D->query_all_emote(),1);
	str="";i=0;j=0;
	foreach(key in all_keys)
	{
		emote=EMOTE_D->query_emote(key);
		str+=EM_HEAD+key+"\n\n"SPLIT;
		foreach(item in keys(emote))
			switch(item)
			{
				case "updated":break;
				default:
					str+=item+":"+emote[item]+SPLIT;
			}
			str+="=======================================\n";
		if((++i%MAX)==0)
		{
			str=replace_string(str,EM_HEAD,"");
			str=replace_string(str,SPLIT,"");
			fn=file+(string)j;
			if(write_file(fn,str,1)==0)
				return notify_fail("输出到文件"+fn+"出错！\n");
			write("输出到 >>"+fn+"\n");
			str="";j++;
		}
	}
	str=replace_string(str,EM_HEAD,"");
	str=replace_string(str,SPLIT,"");
	fn=file+(string)j;
	if(write_file(fn,str,1)==0)
		return notify_fail("输出到文件"+fn+"出错！\n");
	write("输出到 >>"+fn+"\n");
	write("输出成功！>>"+file+"X\n");
	return 1;
}
