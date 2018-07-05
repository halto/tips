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



