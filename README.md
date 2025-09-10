# ZUEFI

ZUEFI is a super simple library for POSIX-UEFI to do very basic things like reading input. It's primarily a library for my own use which is why the code isn't very polished, but I figured I might as well put it on GitHub to keep it safe and in case it ends up being useful to others.

## Usage

Just put zuefi.c and zuefi.h in the root directory of your project (same as your Makefile) and add `#include "zuefi.h"` to your main C file.

## Examples

```c
#include <uefi.h>
#include "zuefi.h"

int main(int argc, char** argv) {
    printf("Echo prompt. Type exit to exit\r\n");

    ST->ConOut->EnableCursor(ST->ConOut, 1);
    
    int exit = 0;
    while (exit == 0) {
        printf("> ");
        char* input = readLine();
        if (strcmp(input, "exit") == 0) exit = 1;
        else printf("%s\r\n", input);
        free(input);
    }

    return 0;
}
```
