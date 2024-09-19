#include <windows.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    // Read the whole file into memory
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *buffer = (char *)malloc(fsize + 1);
    fread(buffer, 1, fsize, file);
    buffer[fsize] = 0;
    fclose(file);

    // Convert UTF-8 to ANSI
    wchar_t *wideBuffer = (wchar_t *)malloc((fsize + 1) * sizeof(wchar_t));
    int wideSize = MultiByteToWideChar(CP_UTF8, 0, buffer, -1, wideBuffer, fsize + 1);
    char *ansiBuffer = (char *)malloc(wideSize * 2);
     WideCharToMultiByte(CP_ACP, 0, wideBuffer, -1, ansiBuffer, wideSize * 2, NULL, NULL);

    // Save the converted content back to the file
    FILE *newFile = fopen(filename, "wb");
    fwrite(ansiBuffer, 1, strlen(ansiBuffer), newFile);
    fclose(newFile);

    free(buffer);
    free(wideBuffer);
    free(ansiBuffer);

    printf("File has been converted to ANSI\n");

    return 0;
}