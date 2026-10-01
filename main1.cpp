#include <iostream>
#include <cstring>
using namespace std;

int my_strlen(const char *str) {
    /**
     * 统计字符串的长度，太简单了。
     */

    // IMPLEMENT YOUR CODE HERE
    int len = 0;
    while (str[len] !='\0'){
        len++;
    }
    return len ;
}


void test_strlen() {
    std::cout << "开始测试函数 << my_strlen >> ..." << std::endl;
    const char *strs[] = {
        "123456", "", "hello world!"
    };

    bool pass = true;
    for (int i = 0; i < 3; i++)
        if (strlen(strs[i]) != my_strlen(strs[i])) {
            std::cout << "未通过，错误的输入为" << strs[i] << std::endl;
            pass = false;
            break;
        }

    if (pass) {
        std::cout << "通过" << std::endl;
    }
    std::cout << std::endl << std::endl;
}

int main() {
    std::cout << "开始测试函数 << my_strlen >> ..." << std::endl;
    test_strlen();
    return 0;
}