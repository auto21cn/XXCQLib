// qhlist1000.c

inherit SKILL;
#include <ansi.h>;

mapping *quest = ({
        ([	"quest_1":		"黑老汉",
		"quest_2":		10,
                "quest_3":      "laohan",
        ]),
        ([	"quest_1":		"阿旺",
		"quest_2":		20,
                "quest_3":      "awang",
        ]),
      ([  "quest_1":      "王小二",
        "quest_2":   15,
                "quest_3":      "wang",
        ]),
        ([  "quest_1":      "翠花",
        "quest_2":      20,
                "quest_3":      "cuihua",
        ]),
        ([  "quest_1":      "李老太太",
        "quest_2":      "30",
                "quest_3":      "laotai",
        ]),
});

mapping query_quest()
{
        return quest[random(sizeof(quest))];
}
