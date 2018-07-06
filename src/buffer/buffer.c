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
#include "buffer.h"


/*!
 */
void buffer_init (buffer_t *bp, uint8_t *data, int16_t size)
{
    if (NULL != bp) {
        bp->bcb.head = 0;
        bp->bcb.tail = 0;
        bp->bcb.lock = BUFFER_UNLOCK;
        bp->bcb.opt = 0;

        bp->bcb.size = size;
        bp->buffer = data;
    }
}

/*!
 */
void buffer_reset (buffer_t *bp)
{
    if (NULL != bp) {
        bp->bcb.head = 0;
        bp->bcb.tail = 0;
    }
}


/*!
 */
int16_t buffer_next (buffer_t *bp, int16_t ind)
{
    return ((ind + 1) % bp->bcb.size);
}

/*!
 */
int16_t buffer_prev (buffer_t *bp, int16_t ind)
{
    return ((ind - 1) % bp->bcb.size);
}

/*!
 */
bool buffer_islocked (buffer_t *bp)
{
    if (NULL != bp) {
        return (bp->bcb.lock == BUFFER_LOCKED);
    }
    return (false);
}

/*!
 */
void buffer_push (buffer_t *bp, uint8_t data)
{
    if (NULL != bp) {
        if (! buffer_islocked(bp)) {
            bp->bcb.tail = buffer_next(bp, bp->bcb.tail);
            bp->buffer[ bp->bcb.tail ] = data;
        }
    }
}

uint8_t buffer_pop (buffer_t *bp)
{
    uint8_t data = 0;

    if (NULL != bp) {
        if (! buffer_islocked(bp)) {
            data = bp->buffer[ buffer_next(bp, bp->bcb.head) ];
            bp->buffer[ buffer_next(bp, bp->bcb.head) ] = '\0';
            bp->bcb.head = buffer_next(bp, bp->bcb.head);
        }
        else {
        	data = bp->buffer[ buffer_next(bp, bp->bcb.head) ];
        	bp->bcb.head = buffer_next(bp, bp->bcb.head);
        }
    }
    return (data);
}

uint8_t buffer_pop_back (buffer_t *bp)
{
    uint8_t data = 0;

    if (NULL != bp) {
        if (! buffer_islocked(bp)) {
            data = bp->buffer[ bp->bcb.tail ];
            bp->buffer[ bp->bcb.tail ] = '\0';
            bp->bcb.tail = buffer_prev(bp, bp->bcb.tail);
        }
    }
    return (data);
}


/*!
 */
void buffer_setlocked (buffer_t *bp)
{
    if (NULL != bp) {
        bp->bcb.lock = BUFFER_LOCKED;
    }
}

void buffer_setunlock (buffer_t *bp)
{
    if (NULL != bp) {
        bp->bcb.lock = BUFFER_UNLOCK;
    }
}


/*!
 */
void buffer_setopt (buffer_t *bp, uint8_t opt)
{
    if (NULL != bp) {
    	bp->bcb.opt = opt;
    }
}

uint8_t buffer_getopt (buffer_t *bp)
{
    uint8_t opt = 0;

    if (NULL != bp) {
        opt = (bp->bcb.opt);
    }
    return (opt);
}


/*!
 */
bool buffer_isempty (buffer_t *bp)
{
    return (bp->bcb.head == bp->bcb.tail);
}

bool buffer_isfull (buffer_t *bp)
{
    return (buffer_next(bp, bp->bcb.tail) == bp->bcb.head);
}



