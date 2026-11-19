#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    char name[16];
    const char *input = argc > 1 ? argv[1] : "Varshini";
    /* Safe bounded input demonstration: never copy an unbounded argument. */
    if (snprintf(name, sizeof name, "%s", input) >= (int)sizeof name)
        printf("name truncated safely to: %s\n", name);
    else
        printf("name: %s\n", name);

    FILE *fp = fopen("missing_donor_data.txt", "r");
    if (!fp) { perror("fopen missing_donor_data.txt"); }
    else fclose(fp);

    if (argc > 2) { fprintf(stderr, "usage: %s [donor-name]\n", argv[0]); return 2; }
    puts("invalid/missing file handled without crashing");
    puts("Use fgets(buffer, sizeof buffer, stdin) for interactive fixed-buffer input.");
    puts("For getline: O(L) time and O(L) heap buffer; caller must free the buffer.");
    return 0;
}
