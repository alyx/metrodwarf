#ifndef METRODWARF_H
#define METRODWARF_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

/* audio functions */
extern void audio_init(void);
extern void audio_write(const char * data, size_t bytes);
extern void audio_die(void);

/* base64 functions */
extern unsigned char * base64_encode(const unsigned char *str, int length);
extern unsigned char * base64_decode(const unsigned char *str, int length, int *ret);

#endif /* METRODWARF_H */
