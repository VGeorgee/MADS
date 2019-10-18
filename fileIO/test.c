#include "storage.h"

int main(){
    FILE *fp = createfile("asd", "henlo");
    fprintf(fp, "%s", "HENLO");
    fclose(fp);
    fp = createfile("asd", "henlo");
    char buffer[40] = {0};
    fgets(buffer, 20, fp);
    printf("%s\n", buffer);
    return 0;
}