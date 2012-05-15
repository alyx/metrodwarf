#define ALSA_PCM_NEW_HW_PARAMS_API
#include <alsa/asoundlib.h>

snd_pcm_t * handle;
snd_pcm_uframes_t frames;

void audio_init(void)
{
    int ret, dir;
    unsigned int rate;
    snd_pcm_hw_params_t * params;

    rate = 44100;
    frames = 32;
    ret = snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0);

    if (ret < 0)
    {
        fprintf(stderr, "Unable to open pcm device: %s\n", snd_strerror(ret));
        exit(EXIT_FAILURE);
    }

    snd_pcm_hw_params_alloca(&params);
    snd_pcm_hw_params_any(handle, params);
    snd_pcm_hw_params_set_access(handle, params, 
            SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);
    snd_pcm_hw_params_set_channels(handle, params, 2);
    snd_pcm_hw_params_set_rate_near(handle, params, &rate, &dir);
    snd_pcm_hw_params_set_period_size_near(handle, params, &frames, &dir);

    ret = snd_pcm_hw_params(handle, params);
    
    if (ret < 0)
    {
        fprintf(stderr, "unable to set hw parameters: %s\n", snd_strerror(ret));
        exit(EXIT_FAILURE);
    }

    snd_pcm_hw_params_get_period_size(params, &frames, &dir);
}

void audio_write(const char * data)
{
    int ret, size;

    ret = snd_pcm_writei(handle, data, frames);
    if (ret == -EPIPE)
        snd_pcm_prepare(handle);
    else if (ret < 0)
        fprintf(stderr, "Error from writei: %s\n", snd_strerror(ret));
}

void audio_die(void)
{
    snd_pcm_drain(handle);
    snd_pcm_close(handle);
}
