#include "stdlib.h"
#include "stdio.h"
#include "strings.h"

#include "zmq.h"

int msg_recv_cmp (zmq_msg_t *msg_, void *s_, const char* group_, const char* body_)
{
    int rc = zmq_msg_init (msg_);
    if (rc != 0)
        return -1;

    int recv_rc = zmq_msg_recv (msg_, s_, 0);
    if (recv_rc == -1) {
        zmq_msg_close(msg_);
        return -1;
    }

    if (strcmp (zmq_msg_group (msg_), group_) != 0)
    {
        zmq_msg_close (msg_);
        return -1;
    }

    char * body = (char*) malloc (sizeof(char) * (zmq_msg_size (msg_) + 1));
    memcpy (body, zmq_msg_data (msg_), zmq_msg_size (msg_));
    body [zmq_msg_size (msg_)] = '\0';

    if (strcmp (body, body_) != 0)
    {
        zmq_msg_close (msg_);
        free(body);
        return -1;
    }

    zmq_msg_close (msg_);
    free (body);
    return recv_rc;
}

int main (void)
{
  void *ctx = zmq_ctx_new ();
  void *dish = zmq_socket (ctx, ZMQ_DISH);

  zmq_bind (dish, "udp://*:5556");
  zmq_join (dish, "ch1");

  printf("Connected\n");

  while (1)
  {
    zmq_msg_t msg;
    zmq_msg_init (&msg);
    zmq_msg_recv (&msg, dish, 0);

    char body[100];
    memcpy (body, zmq_msg_data (&msg), zmq_msg_size (&msg));
    body [zmq_msg_size (&msg)] = '\0';

    printf("%s: %s\n", zmq_msg_group(&msg), body);
    zmq_msg_close(&msg);
  }

  return 0 ;
}
