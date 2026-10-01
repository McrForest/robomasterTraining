#include <iostream>
#include <cstring>
using namespace std;

// 练习2，实现库函数strcat

    /**
     * 将字符串str_2拼接到str_1之后，我们保证str_1指向的内存空间足够用于添加str_2。
     * 注意结束符'\0'的处理。
     */

    // IMPLEMENT YOUR CODE HERE
    char* my_strcat(char *dest, const char *src) {
    // 第一步：找到 dest 的结尾（'\0' 的位置）
        int i = 0;
        while (dest[i] != '\0') {
            i++;
        }

    // 第二步：把 src 逐个字符拷过去
        int j = 0;
        while (src[j] != '\0') {
            dest[i] = src[j];
            i++;
            j++;
        }

    // 第三步：手动补上结束符
        dest[i] = '\0';

        return dest;
    }


void test_strcat() {
    std::cout << "开始测试函数 << my_strcat >> ..." << std::endl;

    int n = 2000;
    // 来源：电影《绿皮书》
    char str1[n] =
    "Dear Dolores\n"
    "When I think of you, I'm reminded of the beautiful plains of Iowa. The distance \n"
    "between us is breaking my spirit. My time and experiences without you are meaningless\n"
    "to me. ";

    char str2[n] =
    "Falling in love with you was the easiest thing I have ever done. Nothing \n"
    "matters to me but you. And everyday I am alive, I'm aware of this. I loved you the day \n"
    "I met you, I love you today... And I will love you to rest of my life.";

    char str1_tmp[n], str2_tmp[n];
    strcpy(str1_tmp, str1), strcpy(str2_tmp, str2);

    strcat(str1, str2);
    my_strcat(str1_tmp, str2_tmp);

    if (!strcmp(str1, str1_tmp)) {
        std::cout << "通过" << std::endl;
    } else {
        std::cout << "未通过" << std::endl;
    }
    std::cout << std::endl << std::endl;
    int a = 0;
    while (str1[a] != '\0') {
        cout << str1[a];
        a++;
    }
}

int main() {
    std::cout << "开始测试函数 << my_strcat >> ..." << std::endl;
    test_strcat();
}