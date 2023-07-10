#include <stdio.h>
#include <stdlib.h>

int main() {
    //Open a new C file for writing
    FILE *file = fopen("newprogram.c", "w");

    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    //Write the contents of the new C program
    fprintf(file, "#include <stdio.h>\n");
    fprintf(file, "int main() {\n");
    fprintf(file, "    printf(\"Hello, World!\\n\");\n");
    fprintf(file, "    return 0;\n");
    fprintf(file, "}\n");

    //Close the file
    fclose(file);

    //Execute the new program through PowerShell
    system("powershell.exe gcc newprogram.c -o newprogram.exe");
    system("powershell.exe ./newprogram.exe");
    //Or
    //system("powershell.exe gcc newprogram.c");
    //system("powershell.exe ./a.exe");
  
    return 0;
}
