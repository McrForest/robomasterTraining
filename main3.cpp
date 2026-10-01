#include <iostream>
#include <cstring>

char* my_strstr(char *s, char *p) {
    /**
     * 在字符串s中搜索字符串p，如果存在就返回第一次找到的地址，不存在就返回空指针(0)。
     * 例如：
     * s = "123456", p = "34"，应该返回指向字符'3'的指针。
     */

    // IMPLEMENT YOUR CODE HERE

    int i = 0;
    while (s[i] != '\0') {
        // 每次从 haystack[i] 开始，尝试和 needle 逐个字符匹配
        int j = 0;
        while (s[i + j] != '\0' && p[j] != '\0') {
            if (s[i + j] != p[j]) {
                break;  // 有一个字符不匹配，放弃这次尝试
            }
            j++;
        }
        // 如果 needle[j] 走到了 '\0'，说明 needle 的每一个字符都匹配成功了
        if (p[j] == '\0') {
            return (char *)(s + i);
        }
        i++;  // 否则 haystack 起始位置往后挪一位，重新试
    }

    return 0; // 整个 haystack 都试完了也没找到
}

void test_strstr() {
    std::cout << "开始测试函数 << my_strstr >> ..." << std::endl;

    char *s = "jaldjqionekqnwjsfjdviozdfaier234WDAJdlDAKDie3j";
    char *p[] = {"wjsfjdvioz", "qqqqq",  "j"};

    bool pass = true;
    for (int i = 0; i < 3; i++)
        if (strstr(s, p[i]) != my_strstr(s, p[i])) {
            std::cout << "未通过，错误的子串为" << p[i] << std::endl;
            pass = false;
            break;
        }

    if (pass) {
        std::cout << "通过" << std::endl;
    }
    std::cout << std::endl << std::endl;
}

int main() {
    std::cout << "开始测试函数 << my_strstr >> ..." << std::endl;
    test_strstr();
}
