#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void clear_stdin(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

unsigned int get_unum(void)
{
    unsigned int input = 0;
    if (scanf("%u", &input) != 1) {
        clear_stdin();
        return 0;
    }
    clear_stdin();
    return input;
}

void decrypt(unsigned int key)
{  
    printf("Key: %u\n", key);
    char encrypted[] = "Q}|u`sfg~sf{}|a3";
    size_t len = strlen(encrypted);

    
    unsigned char k = (unsigned char)key;

    for (size_t i = 0; i < len; i++) {
        encrypted[i] = encrypted[i] ^ k;
    }

    if (strcmp(encrypted, "Congratulations!") == 0) {
        system("/bin/sh");
    } else {
        puts("\nInvalid Password");
    }
}

void test(unsigned int input, unsigned int constant)
{
    unsigned int difference = constant - input;

    switch (difference)
    {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
            decrypt(difference);
            return;
        default:
            decrypt((unsigned int)(rand() & 0xFF));
            return;
    }
}

/* Main function */
int main(void)
{
    unsigned int user_input;

    srand((unsigned int)time(NULL));

    puts("***********************************");
    puts("*\t\tlevel03\t\t**");
    puts("***********************************");

    printf("Password: ");
    fflush(stdout);

    user_input = get_unum();

    test(user_input, 322424845);

    return 0;
}
