#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 统计字符数（包括空格、制表符、换行符）
int count_chars(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: Cannot open file %s\n", filename);
        return -1;
    }
    
    int count = 0;
    int ch;
    while ((ch = fgetc(fp)) != EOF) {
        count++;
    }
    
    fclose(fp);
    return count;
}

// 统计单词数（由空格或逗号分割）
int count_words(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: Cannot open file %s\n", filename);
        return -1;
    }
    
    int count = 0;
    int in_word = 0;  // 标记是否在单词中
    int ch;
    
    while ((ch = fgetc(fp)) != EOF) {
        // 单词分隔符：空格、逗号、换行、制表符
        if (ch == ' ' || ch == ',' || ch == '\n' || ch == '\t' || ch == '\r') {
            if (in_word) {
                count++;
                in_word = 0;
            }
        } else {
            in_word = 1;
        }
    }
    
    // 处理文件末尾的单词
    if (in_word) {
        count++;
    }
    
    fclose(fp);
    return count;
}

int main(int argc, char *argv[]) {
    // 检查参数数量
    if (argc != 3) {
        printf("Usage: wordCount.exe -c|-w <input_file_name>\n");
        printf("  -c: Count characters\n");
        printf("  -w: Count words\n");
        return 1;
    }
    
    const char *param = argv[1];
    const char *filename = argv[2];
    
    if (strcmp(param, "-c") == 0) {
        int result = count_chars(filename);
        if (result >= 0) {
            printf("字符数：%d\n", result);
        }
    } else if (strcmp(param, "-w") == 0) {
        int result = count_words(filename);
        if (result >= 0) {
            printf("单词数：%d\n", result);
        }
    } else {
        printf("Error: Invalid parameter. Use -c or -w\n");
        return 1;
    }
    
    return 0;
}