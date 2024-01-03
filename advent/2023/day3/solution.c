#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    FILE * file = fopen("file.txt", "r");

    if (!file) {
        printf("could not open file");
        return -1;
    }
    size_t sum = 0;
    size_t rowsize = 0;
    char c = getc(file);
    while (c != '\n') {
        rowsize++;
        c = getc(file);
    }
    fseek(file, 0, SEEK_END);
    size_t filesize = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *filecopy = (char*)malloc(sizeof(char) * filesize + rowsize * 2);
    size_t i = 0;
    for (; i < rowsize; i++) {
        filecopy[i] = '.';
    }
    filecopy[i] = '\n';
    while ((filecopy[++i] = getc(file)) != EOF) {
    }
    filecopy[++i] = '\n';
    for (; i <=filesize + rowsize; i++) {
        filecopy[i] = '.';
    }
    filecopy[filesize + rowsize + 1] = '\0';

    size_t length = strlen(filecopy);
    size_t current_num = 0;

    for (size_t j = 0; j < length; j++) {
        if (filecopy[j] == '*') {
            size_t ratio = 1;
            size_t num_of_nums = 0;
            size_t check_array[8] = {j-rowsize-2, j-rowsize-1, j-rowsize, j-1, j+1, j+rowsize, j+rowsize+1, j+rowsize+2};
            for (size_t k = 0; k < 8; k++) {
                size_t start = check_array[k];
                int backtrack_flag = 0;
                while(isdigit(filecopy[start])) {
                    start--;
                    backtrack_flag = 1;
                }
                if (backtrack_flag == 1) {
                    start++;
                    backtrack_flag = 0;
                }
                int num_flag = 0;
                while (isdigit(filecopy[start])) {
                    current_num = (current_num * 10) + (filecopy[start] - '0');
                    filecopy[start] = '.';
                    start++;
                    num_flag = 1;
                }
                if (num_flag == 1) {
                    num_of_nums++;
                }
                if(current_num != 0){
                    ratio *= current_num;
                }
                current_num = 0;
            }
            if (num_of_nums == 2) {
                sum += ratio;
            }
        }
    }
    printf("%d\n",sum);
    free(filecopy);
    fclose(file);
    return 0;
}
