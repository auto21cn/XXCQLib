// Room: /d/playtown/miao.c
// Build 199.12.10 bmw

inherit ROOM;

void create()
{
	set("short", "关公庙");
	set("long", @LONG
你步入关公庙，一眼便看见一尊长髯枣面的关公像，八尺
高的身躯显得威严无比。天下百姓为了纪念这位功高盖主的关
将，许多地方都有纪念他的庙宇，听说百试百灵。只见关公像
前是一张香案，上面有几柱香冉冉飘起。在你的正面前摆着一
个蒲团(putuan)，右面有个算命先生闭着眼睛，嘴里不知道在
哼着什么。
LONG );

	set("item_desc",([
		"putuan":"这是一个小蒲团，专供人下跪用。\n",
	]));
	
	set("exits", ([
		"west"  : __DIR__"road7",
		"east"  : __DIR__"road18",
		"north"  : __DIR__"biwuchang",
		"south"  : __DIR__"liaotianshi",
	]));
	setup();
	replace_program(ROOM);
}
