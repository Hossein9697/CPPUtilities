#include "convertor/type/UnicodeWindows1256.hpp"
#include <iostream>

UnicodeWindows1256::UnicodeWindows1256()
{
    // Persian
    unicode_win1256.insert(std::pair<int, int>(0x067E, 129)); // پ
    unicode_win1256.insert(std::pair<int, int>(0x0686, 141)); // چ
    unicode_win1256.insert(std::pair<int, int>(0x0698, 142)); // ژ
    unicode_win1256.insert(std::pair<int, int>(0x06AF, 144)); // گ
    unicode_win1256.insert(std::pair<int, int>(0x06A9, 152)); // ک
    unicode_win1256.insert(std::pair<int, int>(0x0622, 194)); // آ
    unicode_win1256.insert(std::pair<int, int>(0x0627, 199)); // ا
    unicode_win1256.insert(std::pair<int, int>(0x0628, 200)); // ب
    unicode_win1256.insert(std::pair<int, int>(0x062A, 202)); // ت
    unicode_win1256.insert(std::pair<int, int>(0x062B, 203)); // ث
    unicode_win1256.insert(std::pair<int, int>(0x062C, 204)); // ج
    unicode_win1256.insert(std::pair<int, int>(0x062D, 205)); // ح
    unicode_win1256.insert(std::pair<int, int>(0x062E, 206)); // خ
    unicode_win1256.insert(std::pair<int, int>(0x062F, 207)); // د
    unicode_win1256.insert(std::pair<int, int>(0x0630, 208)); // ذ
    unicode_win1256.insert(std::pair<int, int>(0x0631, 209)); // ر
    unicode_win1256.insert(std::pair<int, int>(0x0632, 210)); // ز
    unicode_win1256.insert(std::pair<int, int>(0x0633, 211)); // س
    unicode_win1256.insert(std::pair<int, int>(0x0634, 212)); // ش
    unicode_win1256.insert(std::pair<int, int>(0x0635, 213)); // ص
    unicode_win1256.insert(std::pair<int, int>(0x0636, 214)); // ض
    unicode_win1256.insert(std::pair<int, int>(0x0637, 216)); // ط

    unicode_win1256.insert(std::pair<int, int>(0x0639, 218)); // ع
    unicode_win1256.insert(std::pair<int, int>(0x063A, 219)); // غ

    unicode_win1256.insert(std::pair<int, int>(0x0622, 192)); // آ

    unicode_win1256.insert(std::pair<int, int>(0x0638, 217)); // ظ
    unicode_win1256.insert(std::pair<int, int>(0x0641, 221)); // ف
    unicode_win1256.insert(std::pair<int, int>(0x0642, 222)); // ق
    unicode_win1256.insert(std::pair<int, int>(0x0643, 223)); // ک
    unicode_win1256.insert(std::pair<int, int>(0x0644, 225)); // ل
    unicode_win1256.insert(std::pair<int, int>(0x0645, 227)); // م
    unicode_win1256.insert(std::pair<int, int>(0x0646, 228)); // ن
    unicode_win1256.insert(std::pair<int, int>(0x0647, 229)); // هه
    unicode_win1256.insert(std::pair<int, int>(0x0648, 230)); // و
    unicode_win1256.insert(std::pair<int, int>(0x0649, 236)); // ی
    unicode_win1256.insert(std::pair<int, int>(0x064A, 237)); // ي
    unicode_win1256.insert(std::pair<int, int>(0x06C1, 192)); // ه
    unicode_win1256.insert(std::pair<int, int>(0x0621, 193)); // ء
    unicode_win1256.insert(std::pair<int, int>(0x0623, 195)); // أ
    unicode_win1256.insert(std::pair<int, int>(0x0624, 196)); // ؤ
    unicode_win1256.insert(std::pair<int, int>(0x0625, 197)); // إ
    unicode_win1256.insert(std::pair<int, int>(0x0626, 198)); // ئ
    unicode_win1256.insert(std::pair<int, int>(0x0629, 201)); // ة
    unicode_win1256.insert(std::pair<int, int>(0x0020, 32));  // space
    unicode_win1256.insert(std::pair<int, int>(0x06CC, 237)); // ی
    unicode_win1256.insert(std::pair<int, int>(0x061F, 191)); // ؟
    unicode_win1256.insert(std::pair<int, int>(0x060C, 161)); // و

    //	unicode_win1256.insert(std::pair<int, int>(0x0077, 129));

    // English
    //  		0x41	0x0041	#LATIN CAPITAL LETTER A
    unicode_win1256.insert(std::pair<int, int>(0x0041, 0x41));
    // 		0x42	0x0042	#LATIN CAPITAL LETTER B
    unicode_win1256.insert(std::pair<int, int>(0x0042, 0x42));
    // 		0x43	0x0043	#LATIN CAPITAL LETTER C
    unicode_win1256.insert(std::pair<int, int>(0x0043, 0x43));
    // 		0x44	0x0044	#LATIN CAPITAL LETTER D
    unicode_win1256.insert(std::pair<int, int>(0x0044, 0x44));
    // 		0x45	0x0045	#LATIN CAPITAL LETTER E
    unicode_win1256.insert(std::pair<int, int>(0x0045, 0x45));
    // 		0x46	0x0046	#LATIN CAPITAL LETTER F
    unicode_win1256.insert(std::pair<int, int>(0x0046, 0x46));
    // 		0x47	0x0047	#LATIN CAPITAL LETTER G
    unicode_win1256.insert(std::pair<int, int>(0x0047, 0x47));
    // 		0x48	0x0048	#LATIN CAPITAL LETTER H
    unicode_win1256.insert(std::pair<int, int>(0x0048, 0x48));
    // 		0x49	0x0049	#LATIN CAPITAL LETTER I
    unicode_win1256.insert(std::pair<int, int>(0x0049, 0x49));
    // 		0x4A	0x004A	#LATIN CAPITAL LETTER J
    unicode_win1256.insert(std::pair<int, int>(0x004A, 0x4A));
    // 		0x4B	0x004B	#LATIN CAPITAL LETTER K
    unicode_win1256.insert(std::pair<int, int>(0x004B, 0x4B));
    // 		0x4C	0x004C	#LATIN CAPITAL LETTER L
    unicode_win1256.insert(std::pair<int, int>(0x004C, 0x4C));
    // 		0x4D	0x004D	#LATIN CAPITAL LETTER M
    unicode_win1256.insert(std::pair<int, int>(0x004D, 0x4D));
    // 		0x4E	0x004E	#LATIN CAPITAL LETTER N
    unicode_win1256.insert(std::pair<int, int>(0x004E, 0x4E));
    // 		0x4F	0x004F	#LATIN CAPITAL LETTER O
    unicode_win1256.insert(std::pair<int, int>(0x004F, 0x4F));
    // 		0x50	0x0050	#LATIN CAPITAL LETTER P
    unicode_win1256.insert(std::pair<int, int>(0x0050, 0x50));
    // 		0x51	0x0051	#LATIN CAPITAL LETTER Q
    unicode_win1256.insert(std::pair<int, int>(0x0051, 0x51));
    // 		0x52	0x0052	#LATIN CAPITAL LETTER R
    unicode_win1256.insert(std::pair<int, int>(0x0052, 0x52));
    // 		0x53	0x0053	#LATIN CAPITAL LETTER S
    unicode_win1256.insert(std::pair<int, int>(0x0053, 0x53));
    // 		0x54	0x0054	#LATIN CAPITAL LETTER T
    unicode_win1256.insert(std::pair<int, int>(0x0054, 0x54));
    // 		0x55	0x0055	#LATIN CAPITAL LETTER U
    unicode_win1256.insert(std::pair<int, int>(0x0055, 0x55));
    // 		0x56	0x0056	#LATIN CAPITAL LETTER V
    unicode_win1256.insert(std::pair<int, int>(0x0056, 0x56));
    // 		0x57	0x0057	#LATIN CAPITAL LETTER W
    unicode_win1256.insert(std::pair<int, int>(0x0057, 0x57));
    // 		0x58	0x0058	#LATIN CAPITAL LETTER X
    unicode_win1256.insert(std::pair<int, int>(0x0058, 0x58));
    // 		0x59	0x0059	#LATIN CAPITAL LETTER Y
    unicode_win1256.insert(std::pair<int, int>(0x0059, 0x59));
    // 		0x5A	0x005A	#LATIN CAPITAL LETTER Z
    unicode_win1256.insert(std::pair<int, int>(0x005A, 0x5A));
    // 		0x61	0x0061	#LATIN SMALL LETTER A
    unicode_win1256.insert(std::pair<int, int>(0x0061, 0x61));
    // 		0x62	0x0062	#LATIN SMALL LETTER B
    unicode_win1256.insert(std::pair<int, int>(0x0062, 0x62));
    // 		0x63	0x0063	#LATIN SMALL LETTER C
    unicode_win1256.insert(std::pair<int, int>(0x0063, 0x63));
    // 		0x64	0x0064	#LATIN SMALL LETTER D
    unicode_win1256.insert(std::pair<int, int>(0x0064, 0x64));
    // 		0x65	0x0065	#LATIN SMALL LETTER E
    unicode_win1256.insert(std::pair<int, int>(0x0065, 0x65));
    // 		0x66	0x0066	#LATIN SMALL LETTER F
    unicode_win1256.insert(std::pair<int, int>(0x0066, 0x66));
    // 		0x67	0x0067	#LATIN SMALL LETTER G
    unicode_win1256.insert(std::pair<int, int>(0x0067, 0x67));
    // 		0x68	0x0068	#LATIN SMALL LETTER H
    unicode_win1256.insert(std::pair<int, int>(0x0068, 0x68));
    // 		0x69	0x0069	#LATIN SMALL LETTER I
    unicode_win1256.insert(std::pair<int, int>(0x0069, 0x69));
    // 		0x6A	0x006A	#LATIN SMALL LETTER J
    unicode_win1256.insert(std::pair<int, int>(0x006A, 0x6A));
    // 		0x6B	0x006B	#LATIN SMALL LETTER K
    unicode_win1256.insert(std::pair<int, int>(0x006B, 0x6B));
    // 		0x6C	0x006C	#LATIN SMALL LETTER L
    unicode_win1256.insert(std::pair<int, int>(0x006C, 0x6C));
    // 		0x6D	0x006D	#LATIN SMALL LETTER M
    unicode_win1256.insert(std::pair<int, int>(0x006D, 0x6D));
    // 		0x6E	0x006E	#LATIN SMALL LETTER N
    unicode_win1256.insert(std::pair<int, int>(0x006E, 0x6E));
    // 		0x6F	0x006F	#LATIN SMALL LETTER O
    unicode_win1256.insert(std::pair<int, int>(0x006F, 0x6F));
    // 		0x70	0x0070	#LATIN SMALL LETTER P
    unicode_win1256.insert(std::pair<int, int>(0x0070, 0x70));
    // 		0x71	0x0071	#LATIN SMALL LETTER Q
    unicode_win1256.insert(std::pair<int, int>(0x0071, 0x71));
    // 		0x72	0x0072	#LATIN SMALL LETTER R
    unicode_win1256.insert(std::pair<int, int>(0x0072, 0x72));
    // 		0x73	0x0073	#LATIN SMALL LETTER S
    unicode_win1256.insert(std::pair<int, int>(0x0073, 0x73));
    // 		0x74	0x0074	#LATIN SMALL LETTER T
    unicode_win1256.insert(std::pair<int, int>(0x0074, 0x74));
    // 		0x75	0x0075	#LATIN SMALL LETTER U
    unicode_win1256.insert(std::pair<int, int>(0x0075, 0x75));
    // 		0x76	0x0076	#LATIN SMALL LETTER V
    unicode_win1256.insert(std::pair<int, int>(0x0076, 0x76));
    // 		0x77	0x0077	#LATIN SMALL LETTER W
    unicode_win1256.insert(std::pair<int, int>(0x0077, 119));
    // 		0x78	0x0078	#LATIN SMALL LETTER X
    unicode_win1256.insert(std::pair<int, int>(0x0078, 0x78));
    // 		0x79	0x0079	#LATIN SMALL LETTER Y
    unicode_win1256.insert(std::pair<int, int>(0x0079, 0x79));
    // 		0x7A	0x007A	#LATIN SMALL LETTER Z
    unicode_win1256.insert(std::pair<int, int>(0x007A, 0x7A));
    // 		0x30	0x0030	#DIGIT ZERO
    unicode_win1256.insert(std::pair<int, int>(0x0030, 0x30));
    // 		0x31	0x0031	#DIGIT ONE
    unicode_win1256.insert(std::pair<int, int>(0x0031, 0x31));
    // 		0x32	0x0032	#DIGIT TWO
    unicode_win1256.insert(std::pair<int, int>(0x0032, 0x32));
    // 		0x33	0x0033	#DIGIT THREE
    unicode_win1256.insert(std::pair<int, int>(0x0033, 0x33));
    // 		0x34	0x0034	#DIGIT FOUR
    unicode_win1256.insert(std::pair<int, int>(0x0034, 0x34));
    // 		0x35	0x0035	#DIGIT FIVE
    unicode_win1256.insert(std::pair<int, int>(0x0035, 0x35));
    // 		0x36	0x0036	#DIGIT SIX
    unicode_win1256.insert(std::pair<int, int>(0x0036, 0x36));
    // 		0x37	0x0037	#DIGIT SEVEN
    unicode_win1256.insert(std::pair<int, int>(0x0037, 0x37));
    // 		0x38	0x0038	#DIGIT EIGHT
    unicode_win1256.insert(std::pair<int, int>(0x0038, 0x38));
    // 		0x39	0x0039	#DIGIT NINE
    unicode_win1256.insert(std::pair<int, int>(0x0039, 0x39));
    // 0x20	0x0020	#SPACE
    unicode_win1256.insert(std::pair<int, int>(0x0020, 0x20));
    // 0xB7	0x00B7	#MIDDLE DOT
    unicode_win1256.insert(std::pair<int, int>(0x00B7, 0xB7));
    // 0x2B	0x002B	#PLUS SIGN
    unicode_win1256.insert(std::pair<int, int>(0x002B, 0x2B));
    // 0x03	0x0003	#END OF TEXT
    unicode_win1256.insert(std::pair<int, int>(0x0003, 0x03));
    // 0x2E	0x002E	#FULL STOP
    unicode_win1256.insert(std::pair<int, int>(0x002E, 0x2E));
    // 3A	58
    unicode_win1256.insert(std::pair<int, int>(0x003A, 58));
    // ASTERISK *
    unicode_win1256.insert(std::pair<int, int>(0x002A, 42));
    // PLUS SIGN +
    unicode_win1256.insert(std::pair<int, int>(0x002B, 43));
    // COMMA ,
    unicode_win1256.insert(std::pair<int, int>(0x002C, 44));
    // HYPHEN - MINUS -
    unicode_win1256.insert(std::pair<int, int>(0x002D, 45));
    // HYPHEN - EQUAL =
    unicode_win1256.insert(std::pair<int, int>(0x003D, 61));
    // FULL STOP	.
    unicode_win1256.insert(std::pair<int, int>(0x002E, 46));
    // SOLIDUS /
    unicode_win1256.insert(std::pair<int, int>(0x002F, 47));
}

UnicodeWindows1256::~UnicodeWindows1256() { unicode_win1256.clear(); }

void UnicodeWindows1256::convert(const std::wstring wstr, std::string& str)
{
    str = "";
    auto index = 0;
    for (auto i = 0; i < wstr.size(); i++)
    {
        if (auto ch = unicode_win1256[wstr[i]])
            str.insert(index++, 1, ch);
    }
}
