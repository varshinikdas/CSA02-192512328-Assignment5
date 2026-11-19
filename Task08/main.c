#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct { int group_code; int units; } Stock;
int update_units(FILE *fp, int index, int units) {
    Stock s;
    if (!fp || index < 0) return 0;
    if (fseek(fp, (long)index * (long)sizeof(Stock), SEEK_SET) != 0) return 0;
    if (fread(&s, sizeof s, 1, fp) != 1) return 0;
    s.units = units;
    if (fseek(fp, -(long)sizeof(Stock), SEEK_CUR) != 0) return 0;
    return fwrite(&s, sizeof s, 1, fp) == 1;
}
int main(void) {
    FILE *fp = tmpfile();
    if (!fp) { perror("tmpfile"); return 1; }
    Stock initial[5] = {{1,40},{2,25},{3,12},{4,8},{5,30}};
    if (fwrite(initial, sizeof(Stock), 5, fp) != 5) { perror("fwrite"); fclose(fp); return 1; }
    printf("update record 3: %s\n", update_units(fp, 3, 20) ? "done" : "failed");
    printf("update record 9: %s\n", update_units(fp, 9, 20) ? "done" : "failed");
    rewind(fp); Stock s; while (fread(&s, sizeof s, 1, fp) == 1) printf("%d:%d ", s.group_code, s.units);
    putchar('\n'); fclose(fp);
    puts("Record 9 fails because it is outside the five-record file; failed read prevents write.");
    return 0;
}

