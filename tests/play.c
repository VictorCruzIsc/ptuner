#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>

int main(int argc, char * argv[]){
	int i;
	int err;
	int dir;
	int rate;
	short buf[128];
	snd_pcm_t * playback_handle;
	snd_pcm_hw_params_t * hw_params;

	if((err = snd_pcm_open(&playback_handle, argv[1], SND_PCM_STREAM_PLAYBACK, 0)) < 0){
		fprintf(stderr, "Cannot open audio device %s (%s)\n", argv[1], snd_strerror(err));
		exit(1);
	}

	if((err = snd_pcm_hw_params_malloc(&hw_params)) < 0){
		fprintf(stderr, "Cannot allocate hardate parameter structure (%s)\n", snd_strerror(err));
		exit(1);
	}

	if((err = snd_pcm_hw_params_any(playback_handle, hw_params)) < 0){
		fprintf(stderr, "Cannot initialize hardware parameter structure (%s)\n", snd_strerror(err));
		exit(1);
	}

	if((err = snd_pcm_hw_params_set_access(playback_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0){
		fprintf(stderr, "Cannot set access type (%s)\n", snd_strerror(err));
		exit(1);
	}

	if((err = snd_pcm_hw_params_set_format(playback_handle, hw_params, SND_PCM_FORMAT_S16_LE)) < 0){
		fprintf(stderr, "Cannot set sample format (%s)\n", snd_strerror(err));
		exit(1);
	}

	rate = 44100;

	if((err = snd_pcm_hw_params_set_rate_near(playback_handle, hw_params, &rate, &dir)) < 0){
		fprintf(stderr, "Cannot set sample rate (%s)\n", snd_strerror(err));
		exit(1);
	}

	if((err = snd_pcm_hw_params_set_channels(playback_handle, hw_params, 2)) < 0){
		fprintf(stderr, "Cannot set channel count (%s)\n", snd_strerror(err));
		exit(1);
	}

	if((err = snd_pcm_hw_params(playback_handle, hw_params)) < 0){
		fprintf(stderr, "Cannot set parameters (%s)\n", snd_strerror(err));
		exit(1);
	}

	snd_pcm_hw_params_free(hw_params);

	if((err = snd_pcm_prepare(playback_handle)) < 0){
		fprintf(stderr, "Cannot prepare audio interface for use (%s)\n", snd_strerror(err));
		exit(1);
	}

	for(i = 0; i < 10; ++i){
		if((err = snd_pcm_writei(playback_handle, buf, 128)) != 128){
			fprintf(stderr, "Write to audio interface failed (%s)\n", snd_strerror(err));
			exit(1);
		}
	}

	snd_pcm_close(playback_handle);

	return 0;
}
