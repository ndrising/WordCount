#include <stdio.h>
#include <stdlib.h>


// 函数用于统计字符数
int count_characters(FILE *file) {
    int count = 0;
    char ch;
    // 逐个读取文件中的字符，直到文件结束
    while ((ch = fgetc(file)) != EOF) {
        // 每读取一个字符，字符数加一
        count++;
    }
    return count;
}

// 函数用于统计单词数
int count_words(FILE *file) {
    int count = 0;
    int inWord = 0; // 标记是否处于单词中
    char ch;
    // 逐个读取文件中的字符，直到文件结束
    while ((ch = fgetc(file)) != EOF) {
        // 判断当前字符是否是单词分隔符（空格或逗号）
        if (ch == ' ' || ch == ',') {
            // 如果处于单词中，单词数加一，并将 inWord 设为 0
            if (inWord) {
                count++;
                inWord = 0;
            }
        } else {
            // 如果当前字符不是单词分隔符，将 inWord 设为 1
            inWord = 1;
        }
    }
    // 如果文件以非单词分隔符结尾，则最后一个单词没有统计到，需要额外加一
    if (inWord) {
        count++;
    }
    return count;
}

int main(int argc, char *argv[]) {
    // 省略参数检查部分

    char *option = argv[1]; // 获取参数 -c 或 -w
    char *filename = argv[2]; // 获取文件名

    FILE *file = fopen(filename, "r"); // 打开文件，以只读方式打开
    if (file == NULL) {
        // 如果打开文件失败，输出错误信息并退出程序
        printf("Error opening file.\n");
        return 1;
    }

    int count;
    if (strcmp(option, "-c") == 0) {
        // 如果参数是 -c，调用统计字符数的函数
        count = count_characters(file);
        printf("字符数：%d\n", count);
    } else if (strcmp(option, "-w") == 0) {
        // 如果参数是 -w，调用统计单词数的函数
        count = count_words(file);
        printf("单词数：%d\n", count);
    } else {
        // 如果参数既不是 -c 也不是 -w，输出错误信息并退出程序
        printf("Invalid option. Please use -c or -w.\n");
        return 1;
    }

    fclose(file); // 关闭文件
    return 0;
}