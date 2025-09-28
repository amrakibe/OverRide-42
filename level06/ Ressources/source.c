#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
int auth(char *username)
{
    size_t string_len;
    int i;
    int calculated_hash;

    string_len = strcspn(username, "\n");
    username[string_len] = '\0';

    string_len = strnlen(username, 0x20);
    if ((int)string_len < 6) {
        printf("Username must be at least 6 characters long\n");
        exit(1);
    }
            calculated_hash = ((int)username[3] ^ 0x1337U) + 0x5eeded;
            
            for (i = 0; i < (int)string_len; i++) {
                if (username[i] < ' ') {
                    return 1;
                }
                calculated_hash = calculated_hash + ((int)username[i] ^ calculated_hash) % 0x539;
            }
    return calculated_hash;
}

int main(void)
{
    int auth_result;

    char login_input[32];

    printf("-> Enter Login: ");
    fgets(login_input, 0x20, stdin);

    auth_result = auth(login_input);

    printf("-> serial: %d\n", auth_result);
}
