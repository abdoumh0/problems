#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char *digits[] = {"one",
                      "two",
                      "three",
                      "four",
                      "five",
                      "six",
                      "seven",
                      "eight",
                      "nine"};

    FILE *file = fopen("file.txt", "r");
    if (!file)
    {
        printf("failed to open file.\n");
        return -1;
    }
    fseek(file, 0, SEEK_END);

    size_t filesize = ftell(file);

    char *copy = (char *)malloc(sizeof(char) * filesize);
    fseek(file, 0, SEEK_SET);
    unsigned int flines = 0;
    unsigned int lines = 0;

    int i = 0;
    while ((copy[i++] = getc(file)) != EOF)
    {
        continue;
    }

    copy[i] = '\0';
    // printf("%s", copy);
    int first_digit = 0;
    int last_digit;
    int sum = 0;
    for (size_t i = 0; i < filesize; i++)
    {

        if (isdigit(copy[i]))
        {
            if (first_digit == 0)
            {
                first_digit = copy[i] - '0';
            }
            last_digit = copy[i] - '0';
        }
        else
        {
            int j = 0;
            while (j < 9)
            {

                int curlen = strlen(digits[j]);
                char *str = (char *)malloc((sizeof(char) * curlen) + 1);
                for (size_t t = i; t < i + curlen; t++)
                {
                    str[t - i] = copy[t];
                }
                str[curlen] = '\0';
                if (!strcmp(str, digits[j]))
                {
                    if (first_digit == 0)
                    {
                        first_digit = j + 1;
                        i += curlen - 1;
                    }
                    last_digit = j + 1;
                    break;
                }
                else
                {
                    j++;
                }
            }
        }

        if (copy[i] == '\n' || copy[i] == '\0')
        {
            sum += (first_digit * 10) + last_digit;
            // printf("%d%d\n", first_digit, last_digit);

            first_digit = 0;
            last_digit = 0;
        }
    }
    printf("%d\n", sum);

    fclose(file);
    free(copy);
    return 0;
}
