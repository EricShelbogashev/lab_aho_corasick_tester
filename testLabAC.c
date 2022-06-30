#include "testLab.h"
#include <stdio.h>
#include <stdbool.h>

static int testN = 0;
static int seedN = 0;

static const struct {
    const char *const in, *const out[1];
    int n;
} testInOut[] = {{"13\n{\"row1\":\"The table header\", \"row2\":\"The table body\", \"row3\":\"with two columns\"}\n<table>\n    <thead>\n        <tr>\n            <th colspan=\"2\">{row1}</th>\n        </tr>\n    </thead>\n    <tbody>\n        <tr>\n            <td>{row2}</td>\n            <td>{row3}</td>\n        </tr>\n    </tbody>\n</table>",                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  {"<table>\n    <thead>\n        <tr>\n            <th colspan=\"2\">The table header</th>\n        </tr>\n    </thead>\n    <tbody>\n        <tr>\n            <td>The table body</td>\n            <td>with two columns</td>\n        </tr>\n    </tbody>\n</table>"}, 1},
                 {"16\n{\"title\":\"Group 21200\", \"dateTitle\":\"Date\", \"disTitle\":\"Discipline\", \"time\":\"16:20\", \"date\":\"11th June\\nSaturday\", \"tutor\":\"Surnamovich N.\", \"room\": \"Aud. 3107\", \"data-original-title\": \"Mathematical logic & software development\"}\n<h1>{title}</h1>\n<tbody>\n<tr><th>{dateTitle}</th><th>{disTitle}</th></tr>\n<tr>\n<td><div class=\"cell\">\n{time} <br>\n{date} <br>\n</div></td>\n<td>\n<div class=\"cell\">\n<span class=\"type k\" data-toggle=\"tooltip\" data-placement=\"right\" title=\"\" data-original-title=\"consultation\">cons</span>                        <div class=\"subject\" data-toggle=\"tooltip\" data-placement=\"top\" title=\"\" data-original-title={data-original-title}>{short title}</div><div class=\"room\">{room}</a></div>\n<span class=\"tutor\">{tutor}</span>\n</div></td></tr>",                                                                                                                        {"<h1>Group 21200</h1>\n<tbody>\n<tr><th>Date</th><th>Discipline</th></tr>\n<tr>\n<td><div class=\"cell\">\n16:20 <br>\n11th June\nSaturday <br>\n</div></td>\n<td>\n<div class=\"cell\">\n<span class=\"type k\" data-toggle=\"tooltip\" data-placement=\"right\" title=\"\" data-original-title=\"consultation\">cons</span>                        <div class=\"subject\" data-toggle=\"tooltip\" data-placement=\"top\" title=\"\" data-original-title=Mathematical logic & software development>{short title}</div><div class=\"room\">Aud. 3107</a></div>\n<span class=\"tutor\">Surnamovich N.</span>\n</div></td></tr>"}, 1},
                 {"1\n{\"съешь\" :\"Eat\", \"же\": \"\", \"ещё\":\"some more\" \"этих\":\"of these\", \"мягких\":\"soft\", \"французских\":\"French\", \"булок,\":\"rolls,\", \"да\":\"and\" ,\"выпей\":\"drink\" \"чаю\":\"some tea\"}\n{съешь} {же}{ещё} {этих} {мягких} {французских} {булок,} {да} {выпей} {чаю}.",                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       {"Eat some more of these soft French rolls, and drink some tea."}, 1},
                 {"11\n{\"image_width\":\"100\", \"image_src\":\"image.png\"}\n<html lang=\"en\">\n  <head>\n    <title>Img Align Attribute</title>\n  </head>\n  <body>\n    <p>\n      {image_text}\n      <img src=\"{image_src}\" alt=\"Image\" width=\"{image_width}\" />\n    </p>\n  </body>\n</html>",                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                {"<html lang=\"en\">\n  <head>\n    <title>Img Align Attribute</title>\n  </head>\n  <body>\n    <p>\n      {image_text}\n      <img src=\"image.png\" alt=\"Image\" width=\"100\" />\n    </p>\n  </body>\n</html>"}, 1},
                 {"16\n{\"username\":\"qwerty\", \"password\":\"йцукен123\", \"options\":\"<option value=\\\"Option1\\\"></option>\\n	<option value=\\\"Option2\\\"></option>\\n	<option value=\\\"Option3\\\"></option>\"}\n<form>\n  <label for=\"username\">{username}</label>\n  <input type=\"text\" name=\"username\" id=\"username\" />\n  <label for=\"password\">{password}</label>\n  <input type=\"password\" name=\"password\" id=\"password\" />\n  <input list=\"Options\" />\n  <datalist id=\"Options\">\n	{options}\n  </datalist>\n  <datalist id=\"Options\">\n	{options}\n  </datalist>\n  <input type=\"submit\" value=\"Submit\" />\n  <input type=\"color\" />\n  <input type=\"checkbox\" name=\"correct\" value=\"correct\" />Correct\n</form>\n",                                                                                                                                                                                                                       {"<form>\n  <label for=\"username\">qwerty</label>\n  <input type=\"text\" name=\"username\" id=\"username\" />\n  <label for=\"password\">йцукен123</label>\n  <input type=\"password\" name=\"password\" id=\"password\" />\n  <input list=\"Options\" />\n  <datalist id=\"Options\">\n	<option value=\"Option1\"></option>\n	<option value=\"Option2\"></option>\n	<option value=\"Option3\"></option>\n  </datalist>\n  <datalist id=\"Options\">\n	<option value=\"Option1\"></option>\n	<option value=\"Option2\"></option>\n	<option value=\"Option3\"></option>\n  </datalist>\n  <input type=\"submit\" value=\"Submit\" />\n  <input type=\"color\" />\n  <input type=\"checkbox\" name=\"correct\" value=\"correct\" />Correct\n</form>\n"}, 1},
                 {"21\n{\"username\":\"qwerty\", \"password\":\"йцукен123\", \"options\":\"<option value=\\\"Option1\\\"></option>\\n	<option value=\\\"Option2\\\"></option>\\n	<option value=\\\"Option3\\\"></option>\"}\n<article class=\"{article_class}\">\n  <h2>{article_title}</h2>\n  <section class=\"main\">\n    <h3>{article_main_title}</h3>\n    <p>{article_main_subtitle}</p>\n  </section>\n  <section class=\"{article_comments_section}\">\n    <h3>{article_comments_section_title}</h3>\n    <article class=\"{article_comments_section_class}\">\n      <h4>{comment_title}</h4>\n      <p>{comment_subtitle}</p>\n      <footer>\n        <p>\n          Posted on\n          <time datetime=\"{comment_hint_time}\">{comment_visible_time}</time>\n          {comment_author}\n        </p>\n      </footer>\n    </article>\n  </section>\n</article>",                                                                                                                      {"bad template"}, 1},
                 {"21\n{\"article_class\":\"main_сlass\", \"article_title\":\"Интересные символы юникода\", \"article_main_title\":\"Ӡ𐌀Ґo𐌋oв⭕к\", \"article_comments_section_title\":\"コメント\", \"comment_title\":\"мен қуаныштымын!\", \"comment_hint_time\":\"2022-06-23 11:41\", \"comment_author\":\"ਆਦਮ\", \"comment_visible_time\":\"Jule 23\"}\n<article class=\"{article_class}\">\n  <h2>{article_title}</h2>\n  <section class=\"main\">\n    <h3>{article_main_title}</h3>\n    <p>{article_main_subtitle}</p>\n  </section>\n  <section class=\"{article_comments_section}\">\n    <h3>{article_comments_section_title}</h3>\n    <article class=\"{article_comments_section_class}\">\n      <h4>{comment_title}</h4>\n      <p>{comment_subtitle}</p>\n      <footer>\n        <p>\n          Posted on\n          <time datetime=\"{comment_hint_time}\">{comment_visible_time}</time>\n          {comment_author}\n        </p>\n      </footer>\n    </article>\n  </section>\n</article>", {"<article class=\"main_сlass\">\n  <h2>Интересные символы юникода</h2>\n  <section class=\"main\">\n    <h3>Ӡ𐌀Ґo𐌋oв⭕к</h3>\n    <p>{article_main_subtitle}</p>\n  </section>\n  <section class=\"{article_comments_section}\">\n    <h3>コメント</h3>\n    <article class=\"{article_comments_section_class}\">\n      <h4>мен қуаныштымын!</h4>\n      <p>{comment_subtitle}</p>\n      <footer>\n        <p>\n          Posted on\n          <time datetime=\"2022-06-23 11:41\">Jule 23</time>\n          ਆਦਮ\n        </p>\n      </footer>\n    </article>\n  </section>\n</article>"}, 1},
                 {"2\n{\"{{{{{{{{{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}}}}}}}}\":\"\\\"\\\"\\\"\\\"\\\"\\\"\\\"\\\"\\\"\\\"\\\"\\\"\\\"\\\"\\\"\\\"\\\"\\\"\\\"\\\"\\\"\\\"\\\"\\\"\\\"\\\"\\\"\\\"\\\"\"}\n{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}\n{{{{{{{{{{{{{{{{{{{{{{{{}}}{{{{{{{{{{{{{{{{{{{{{{{{}}}}}}}{{{{{{{{{{{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}",                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               {"{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}\n{{{{{{{{{{{{{{{{{{{{{{{{}}}{{{{{{{{{{{{{{{{{{{{{{{{}}}}}}}{\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}"}, 1},
                 {"2\n{\"\\t\":\"\\t\", \"\\n\":\"\\n\"}\n 	 	{\\t} 	 	 	 	 {\\n}\n\\n \\t		   {\\t}.",                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               {" 	 		 	 	 	 	 \n\n\\n \\t		   	."}, 1},};

// Сид задаёт узор файла;
// extra[0] - количество символов во входной строке;
// extra[1] - длина ключей;

// key генерируется, value - key, записанный с конца.
// Количество ключей считается как extra[0] / extra[1] / 4 (в коде обозначено переменной stringCount).

// 30.06.22 7:53 внес изменения в размеры тестов, память увеличилась до 142.5 мб (вероятно, очень много, но не знаю,
// какие пределы адекватны. Вероятно, стоит пересмотреть методы хранения временных строк с RAM в ROM).

static const struct {
    const char *const seed, *const extra[2];
    int n;
} seedList[] = {{"*******",      "100",     "5"}, // Упрощенные версии тестов, содержащие помимо ключей лишь '*'.
                {"************", "2000",    "5"},
                {"*$Oh~H4wQlt1", "11982",   "283"},
                {"Ije~gcFCpWST", "12357",   "310"},
                {"$~bA4#~mcL~S", "10508",   "191"},
                {"vpYXR01G*gJ1", "12658",   "387"},
                {"?*3QxGjN7h%L", "15630",   "507"},
                {"T9@l|VT4$zlV", "14861",   "526"},
                {"K8DXyEL7rby~", "15620",   "475"},
                {"WqZTbu%dG#hz", "10848",   "177"},
                {"$Mmi*DHnXoAo", "10697",   "178"},
                {"mHqkaI7Du0HI", "19868",   "911"},
                {"5LE0Plc$~4BL", "15077",   "470"},
                {"hBS6*ejE~cxX", "18169",   "781"},
                {"vjLdI~jIA%9Y", "15852",   "653"},
                {"tY~~x%p@fb7Q", "16120",   "675"},
                {"aJrIFF%FbF$7", "18850",   "774"},
                {"F~HteQAeS7hB", "15265",   "517"},
                {"ME3~BPu2r{7Y", "13827",   "387"},
                {"}}PG~dV~Ty#w", "18677",   "888"},
                {"?q~Q~oO3gPea", "13949",   "456"},
                {"*X6gx~vVNYCl", "12520",   "300"},
                {"A{1ovMc?tUJ1", "18354",   "795"},
                {"D*6KW$u5Wk}o", "10219",   "183"},
                {"d~QYTj%8ay4o", "12287",   "305"},
                {"7wlME9IN81hk", "16019",   "615"},
                {"h0lzfPFc~~OT", "13026",   "334"},
                {"|YoyCfKX2A5T", "19820",   "737"},
                {"HFkT92ahw@fT", "10379",   "147"},
                {"|F|GG@3C5X9O", "17139",   "702"},
                {"|%pguSa3nQ7Z", "13498",   "365"},
                {"~HNkNty0}BSu", "13767",   "442"},
                {"fOEC24L|fhP0", "15403",   "461"},
                {"t4?6Ww}~$S*w", "17520",   "731"},
                {"LBk8FOt??Xbv", "10075",   "171"},
                {"iiKOGsA$fFS~", "13205",   "399"},
                {"kaMF~2pWXwjY", "10961",   "210"},
                {"lLXJ5gK|jteT", "17450",   "725"},
                {"4ks2h?S5$wxA", "18379",   "863"},
                {"Qe%GCHg2HqLx", "10902",   "222"},
                {"8aW4Uyr%WS0v", "16455",   "602"},
                {"8aW4Uyr%WS0v", "2100000", "50"}};

int strToInt(const char *str) {
    int val = 0;
    unsigned int strLen = strlen(str);
    for (int i = 0; i < strLen; ++i) {
        val = val * 10 + str[i] - '0';
    }
    return val;
}

char *intToStr(int val) {
    char tmp[5];
    char *string = malloc(5);
    char index = 0;
    while (val > 0) {
        tmp[index++] = (char) (val % 10);
        val = val / 10;
    }
    string[index] = '\0';
    for (int i = 0; i < index; ++i) {
        string[index - 1 - i] = (char) (tmp[i] + '0');
    }
    return string;
}

static void createStringBySeed(FILE *file, bool isIn) {
    int extra0 = strToInt(seedList[seedN].extra[0]);
    int extra1 = strToInt(seedList[seedN].extra[1]);
    int quotesCount = extra0 / extra1;
    if (quotesCount % 2 != 0)
        quotesCount -= 1;
    int stringCount = quotesCount / 4;
    if (isIn) {
        fprintf(file, "%d\n", stringCount);
    }
    int range = '\\' - '0' - 1;
    char *ordNum;
    unsigned int digits;
    unsigned int seedSize = strlen(seedList[0].seed);
    char pattern[stringCount][extra1 + 1];
    for (int i = 0; i < stringCount; ++i) {
        ordNum = intToStr(i);
        digits = strlen(ordNum);
        for (int j = 0; j < extra1 - digits; ++j) {
            pattern[i][j] = (char) (((i * extra1 + j) * seedList[seedN].seed[j % seedSize] + (i * extra1 + j)) % range +
                                    '0');
        }
        for (int j = 0; j < digits; ++j) {
            pattern[i][extra1 - digits + j] = ordNum[j];
        }
        pattern[i][extra1] = '\0';
    }
    free(ordNum);
    if (isIn) {
        fprintf(file, "{");
        for (int i = 0; i < stringCount; ++i) {
            fprintf(file, "\"%s\":\t\"", pattern[i]);
            for (int j = 0; j < extra1; ++j) {
                putc(pattern[i][extra1 - 1 - j], file);
            }
            fprintf(file, "\",\t");
        }
        fprintf(file, "}\n");
    }
    int dist = ((extra0 - stringCount * extra1) / stringCount - 1) / 1.2 / 2;
    int patternNum = 0;
    int cursor = 0;
    while (cursor < extra0) {
        for (int i = 0; i < dist && cursor < extra0; ++i) {
            putc(seedList[seedN].seed[i * (patternNum + i) % seedSize], file);
            cursor += 1;
            if (cursor >= extra0)
                return;
        }
        if (patternNum < stringCount) {
            if (isIn) {
                putc('{', file);
                fprintf(file, "%s", pattern[patternNum++]);
                putc('}', file);
                cursor += extra1 + 2;
            } else {
                for (int j = 0; j < extra1; ++j) {
                    putc(pattern[patternNum][extra1 - 1 - j], file);
                }
                patternNum++;
                cursor += extra1 + 2;
            }
        }
        for (int i = 0; i < dist - 1 && cursor < extra0; ++i) {
            putc(seedList[seedN].seed[i * 2 * patternNum % seedSize], file);
            cursor += 1;
            if (cursor >= extra0)
                return;
        }
        if (patternNum < stringCount) {
            putc('\n', file);
            cursor += 1;
        }
    }
}

static int FeedFromArray(void) {
    FILE *const in = fopen("in.txt", "w+");
    if (in == NULL) {
        printf("can't create in.txt. No space on disk?\n");
        return -1;
    }
    if (testN < sizeof(testInOut) / sizeof(testInOut[0]))
        fprintf(in, "%s", testInOut[testN].in);
    else {
        createStringBySeed(in, true);
    }
    fclose(in);
    return 0;
}

static int CheckFromArray(void) {
    FILE *const out = fopen("out.txt", "r");
    if (out == NULL) {
        printf("can't open out.txt\n");
        testN++;
        return -1;
    }
    const char *status = Pass;
    if (testN < sizeof(testInOut) / sizeof(testInOut[0])) {
        char perm[1024];
        for (int i = 0; i < testInOut[testN].n; ++i) {
            status = ScanChars(out, sizeof(perm), perm);
            const size_t refLen = strlen(testInOut[testN].out[i]);
            for (int j = 0; j < refLen; ++j) {
                if (perm[j] != testInOut[testN].out[i][j]) {
                    break;
                }
            }
            if (status == Pass && strncmp(testInOut[testN].out[i], perm, refLen) != 0) {
                status = Fail;
                printf("wrong output -- ");
                break;
            }
        }
    } else {
        FILE *tmp = fopen(".testerTmpSRC", "wb+");
        createStringBySeed(tmp, false);
        int extra0 = strToInt(seedList[seedN].extra[0]);
        fseek(tmp, 0, SEEK_SET);
        for (int i = 0; i < extra0; ++i) {
            if (getc(tmp) != getc(out)) {
                status = Fail;
                printf("wrong output -- ");
                break;
            }
        }
        fclose(tmp);
        remove(".testerTmpSRC");
    }
    if (status == Pass && HaveGarbageAtTheEnd(out)) {
        status = Fail;
    }
    fclose(out);
    printf("%s\n", status);
    ++testN;
    seedN = (int) (testN - (sizeof(testInOut) / sizeof(testInOut[0])));
    return status == Fail;
}

TLabTest GetLabTest(int testIdx) {
    (void) testIdx;
    TLabTest labTest = {FeedFromArray, CheckFromArray};
    return labTest;
}

int GetTestCount(void) {
    return sizeof(testInOut) / sizeof(testInOut[0]) + sizeof(seedList) / sizeof(seedList[0]);
}

const char *GetTesterName(void) {
    return "Lab Web Engine";
}

int GetTestTimeout() {
    return 3000;
}

size_t GetTestMemoryLimit() {
    return 9961472 * 15; // 9.5 * 15 = 142.5 Mb
}