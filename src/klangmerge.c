#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>


int main(int argc,char *argv[]) {
if (argc <= 1) {
	system("emerge");
	return 0;
};

int is_it_emerge = system("which emerge > /dev/null 2>&1");

// old int is_aplay_installed = system("which aplay > /dev/null 2>&1");


if (is_it_emerge == 0) {
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		printf("SDL could not initialize : Press any key to start emerge or Ctrl + C to abort.\n");
		getchar();
		}
		
	SDL_AudioSpec wavSpec; //Loads file at the beginning so you will be warned for sure
	Uint8* wavBuffer;
	Uint32 wavLength;
	if (SDL_LoadWAV("metal-pipe-clang.wav", &wavSpec, &wavBuffer, &wavLength) == NULL) {
		printf("Error while loading sound file : %s\n", SDL_GetError());
		SDL_FreeWAV(wavBuffer);
		SDL_Quit();
		return 1;
	}
	
	SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
	if (deviceId == 0) {
	printf("Error while opening audio device : %s\n", SDL_GetError());
	SDL_FreeWAV(wavBuffer);
	SDL_Quit();
	return 1;
	}
	
	
	/* old   if (is_aplay_installed == 0) {*/
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
	
	SDL_QueueAudio(deviceId, wavBuffer, wavLength);
	SDL_PauseAudioDevice(deviceId, 0);
	
	SDL_Delay(3000); //adjust to your file's size (in milliseconds)
	
	
	SDL_CloseAudioDevice(deviceId);
	SDL_FreeWAV(wavBuffer);
	SDL_Quit();
    	
	// old             system("aplay metal-pipe-clang.wav");
	/* old   } else {
	printf("Sorry, please install aplay.\n");
	}*/
	} else {
	printf("You don't have emerge. Use Gentoo Linux, it's so easy to set up.\n");
	}
	return 0;
}

