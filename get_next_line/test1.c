#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

char *readhh(int fd) {
    printf("Reading line\n");
    char *s = malloc(11 * sizeof(char)); // Allocate memory for 10 characters + '\0'
    if (!s)
        return NULL;

    int i = 0;
    int j;
    char c;
    while ((j = read(fd, &c, 1)) > 0) {
        if (c == '\n')
            break;
        if (c == '0') {
            s[i] = c;
            printf("%c", s[i]); // Debug: print each character
            i++;
        }
    }
    s[i] = '\0';
    printf("\n"); // Debug: print newline after each line read

    if (j == 0 && i == 0) { // If nothing is read and string is empty
        free(s);
        return NULL;
    }
    return s;
}

int main() {
    int p = 0;
    char *s[10]; // Fixed size array for 10 lines
    int fd = open("map", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    while (p < 10) { // Ensure index doesn't exceed array bounds
        s[p] = readhh(fd);
        if (s[p] == NULL) {
            printf("Error reading line %d\n", p);
            break;
        }
        printf("Line %d: %s\n", p, s[p]); // Print each line
        p++;
    }

    // Free allocated memory
    for (int i = 0; i < p; i++) {
        free(s[i]);
    }

    close(fd);
    return 0;
}
