inherit F_CLEAN_UP;
int help();
int main(object me, string arg)
{
	string key, chinz;

	if( !arg || arg=="" )
		return help();
	if( sscanf(arg, "%s==%s", key, chinz)==2 ) {
		CHINESE_D->add_translate(key, chinz);
		write( "增加对照："+key + " == " + chinz + "\nOk.\n");
		return 1;
	}
//else部分由jackyboy@cctx增加
	else
		if(arg!=CHINESE_D->chinese(arg))
		{
			write("删除对照："+arg+"<==>"+CHINESE_D->chinese(arg)+"\n");
			CHINESE_D->remove_translate(arg);
			return 1;
		}
		else
			return help();
}			

int help()
{
	write ( @HELP
增加对照：chinese <英文>==<中文>
删除对照：chinese <英文>
HELP
	);
	return 1 ;
}
