#include "stdlib.h"
#include "strings.h"
#include "sys/select.h"

#include "zmq.h"

int msg_send (zmq_msg_t *msg_, void *s_, const char* group_, const char* body_)
{
    int rc = zmq_msg_init_size (msg_, strlen (body_));
    if (rc != 0)
        return rc;

    memcpy (zmq_msg_data (msg_), body_, strlen (body_));

    rc = zmq_msg_set_group (msg_, group_);
    if (rc != 0) {
        zmq_msg_close (msg_);
        return rc;
    }

    rc = zmq_msg_send (msg_, s_, 0);

    zmq_msg_close (msg_);

    return rc;
}

int main (void)
{
    void *ctx = zmq_ctx_new ();
    void *radio = zmq_socket (ctx, ZMQ_RADIO);

    zmq_connect (radio, "udp://127.0.0.1:5556");

    while(1)
    {
        zmq_msg_t msg;
        msg_send (&msg, radio, "ch1", "Hello World!");
        printf("Sent\n");

        struct timeval tv;
        tv.tv_sec = 1;
        tv.tv_usec = 0;
        select(0, NULL, NULL, NULL, &tv);
    }

    return 0 ;
}
