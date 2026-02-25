#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char *argv[]) {
if (argc <= 1) {
	system("emerge");
	return 0;
};

int is_it_emerge = system("which emerge > /dev/null 2>&1");

int is_aplay_installed = system("which aplay > /dev/null 2>&1");


if (is_it_emerge == 0) {
	if (is_aplay_installed == 0) {
	size_t total_length = 0;
	for (int i = 1; i < argc; i++) {
		total_length += strlen(argv[i]) + 1; 
    	}
    	total_length += strlen("emerge ");
    	
    	char *result = malloc(total_length + 1);
    	if (result == NULL) return 1;
  	result[0] = '\0';
  	
  	strcat(result, "emerge ");
  	for (int i = 1; i < argc; i++) {
        strcat(result, argv[i]);
        if (i < argc - 1) {
            strcat(result, " ");
        }
    }

	printf("%s\n", result);
	
	system(result);
	free(result);
    	
	system("aplay metal-pipe-clang.wav");
	} else {
	printf("Sorry, please install aplay.\n");
	}
	} else {
	printf("You don't have emerge. Use Gentoo Linux, it's so easy to set up.\n");
	}
	return 0;
}

