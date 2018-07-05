#ifndef BUFFER_H
#define BUFFER_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>


/*!
 */
#define BUFFER_UNLOCK                               (0)
#define BUFFER_LOCKED                               (1)


/*!
 */
struct buffer_cb_s {
    int16_t head;
    int16_t tail;
    int16_t size;
    int8_t  lock;
    uint8_t opt;
};
typedef struct buffer_cb_s  bcb_t;

/*!
 */
struct buffer_s {
    bcb_t   bcb;
    uint8_t *buffer;
};
typedef struct buffer_s     buffer_t;


/*!
 */
void buffer_init (buffer_t *, uint8_t *, int16_t);
void buffer_reset (buffer_t *);

int16_t buffer_next (buffer_t *, int16_t);
int16_t buffer_prev (buffer_t *, int16_t);

/*!
 */
void buffer_push (buffer_t *, uint8_t);
uint8_t buffer_pop (buffer_t *);
uint8_t buffer_pop_back (buffer_t *);

/*!
 */
void buffer_setlocked (buffer_t *);
void buffer_setunlock (buffer_t *);
bool buffer_islocked (buffer_t *);

/*!
 */
void buffer_setopt (buffer_t *, uint8_t);
uint8_t buffer_getopt (buffer_t *);

/*!
 */
bool buffer_isempty (buffer_t *);
bool buffer_isfull (buffer_t *);


#endif/*BUFFER_H*/
