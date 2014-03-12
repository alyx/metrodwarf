#include <pulse/simple.h>
#include <pulse/error.h>

pa_simple *s;
pa_simple_spec ss;

ss.format = PA_SAMPLE_S16NE;
ss.channels = 1;
ss.rate = 44100;

void audio_init(void)
{
    s = pa_simple_new(NULL, "Metrodwarf", PA_STREAM_PLAYBACK, NULL, "Metronome", &ss, NULL, NULL, NULL);
    if (s == NULL)
    {
        fprintf(stderr, "Unable to connect to PulseAudio server");
        exit(EXIT_FAILURE);
    }
}

void audio_write(const char * data, size_t bytes)
{
    int ret;
    ret = pa_simple_write(s, data, bytes, NULL);
}

void audio_die(void)
{
    pa_simple_free(s);
}

