#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define max(a,b) a > b ? a : b
int main(){

    FILE *file = fopen("./file.txt","r");
    if (!file) {
        printf("file does not exist!");
        return -1;
    }
    fseek(file, 0, SEEK_END);
    size_t filesize = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *filecopy = (char*)malloc(sizeof(char) * filesize);
    char c = getc(file);
    size_t i = 0;
    while (c != -1) {
        filecopy[i] = c;
        i++;
        c = getc(file);
    }
    filecopy[filesize] = '\0';
    size_t sum = 0;
    size_t current_line = 1;
    size_t max_red = 12;
    size_t max_green = 13;
    size_t max_blue = 14;
    size_t current_red = 0;
    size_t current_green = 0;
    size_t current_blue = 0;
    size_t current_int = 0;
    for (size_t i = 8; i < filesize; i++) {
        if (isdigit(filecopy[i])) {
            current_int = (current_int * 10) + (filecopy[i] - '0');
            //printf("current int:%d\n", current_int);
        }
        else{
                switch (filecopy[i]) {
                    case 'r':
                        current_red = max(current_int, current_red);
                        //printf("red: %d, green: %d, blue: %d.\n",current_red, current_green, current_blue);
                        current_int = 0;
                        i += 2;
                        break;
                    case 'g':
                        current_green = max(current_int, current_green);
                        current_int = 0;
                        i += 4;
                        break; 
                    case 'b':
                        current_blue = max(current_int, current_blue);
                        current_int = 0;
                        i += 3;
                        break;
                    case '\n':
                    case '\0':
                        //if(current_red && current_blue && current_green && current_red <= max_red && current_blue <= max_blue && current_green <= max_green){
                            sum += current_red * current_green * current_blue;
                          //  printf("line %d valid.\n", current_line);
                        //}
                        i += 8;
                        current_line++;
                        current_green = 0;
                        current_red = 0;
                        current_blue = 0;
                        current_int = 0;
                        break;
                    default:
                        break;
            }
        }
    }
    printf("%d\n",sum);
    free(filecopy);
    fclose(file);
    return 0;
}
