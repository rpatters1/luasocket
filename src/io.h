#ifndef IO_H
#define IO_H

#include <stdio.h>

/* IO error codes */
enum {
    IO_DONE,         /* operation completed successfully */
    IO_TIMEOUT,      /* operation timed out */
    IO_CLOSED,       /* the connection has been closed */
    IO_ERROR,        /* something wrong... */
    IO_REFUSED,      /* transfer has been refused */
    IO_LIMITED       /* maximum number of bytes reached */
};

/* interface to send function */
typedef int (*p_send) (
    void *ctx,          /* context needed by send */ 
    const char *data,   /* pointer to buffer with data to send */
    size_t count,       /* number of bytes to send from buffer */
    size_t *sent,       /* number of bytes sent uppon return */
    int timeout         /* number of miliseconds left for transmission */
);
 
/* interface to recv function */
typedef int (*p_recv) (
    void *ctx,          /* context needed by recv */ 
    char *data,         /* pointer to buffer where data will be writen */
    size_t count,       /* number of bytes to receive into buffer */
    size_t *got,        /* number of bytes received uppon return */
    int timeout         /* number of miliseconds left for transmission */
);

/* IO driver definition */
typedef struct t_io_ {
    void *ctx;          /* context needed by send/recv */
    p_send send;        /* send function pointer */
    p_recv recv;        /* receive function pointer */
} t_io;
typedef t_io *p_io;

void io_init(p_io io, p_send send, p_recv recv, void *ctx);

#endif /* IO_H */