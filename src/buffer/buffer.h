/*!
    Copyright (c) 2018, halto
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met: 

    1. Redistributions of source code must retain the above copyright notice,
       this list of conditions and the following disclaimer. 
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution. 

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
    ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

    The views and conclusions contained in the software and documentation are those
    of the authors and should not be interpreted as representing official policies, 
    either expressed or implied, of the FreeBSD Project.
 */
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
