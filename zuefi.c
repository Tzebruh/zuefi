#include <uefi.h>

char* readLine() {
	int nchars = 0;
	int bsize = 8;
	char* buf = malloc(bsize);

	int exit = 0;
	while (exit == 0) {
		efi_input_key_t key;
		ST->ConIn->Reset(ST->ConIn, 0);
		while (ST->ConIn->ReadKeyStroke(ST->ConIn, &key) == EFI_NOT_READY);
		
		char c = key.UnicodeChar;
		if (c == '\0') continue; // Make escape do nothing
		if (c == '\b') {
			// Handle backspace
			if (nchars - 1 >= 0) {
				buf[--nchars] = '\0';
				printf("\b");
			}
			continue;
		}
		else if (c == '\r') c = '\0';
		else printf("%c", c);

		if (nchars + 1 > bsize) buf = realloc(buf, ++bsize);
		buf[nchars++] = c;

		if (c == '\0') exit = 1;
	}

	printf("\r\n");
	return buf;
}

void waitForKey() {
	ST->ConIn->Reset(ST->ConIn, 0);
	while (ST->ConIn->ReadKeyStroke(ST->ConIn, NULL) == EFI_NOT_READY);
}