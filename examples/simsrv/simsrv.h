#ifndef SIMSRV_H
#define SIMSRV_H

#include <stdlib.h>

struct simsrv_ioctl_s {
  uint16_t cmd;
  uint8_t *data;
  size_t len;
};

static inline void destroy_simsrv_ioctl_s(struct simsrv_ioctl_s *p) {
  if (p == NULL) return;
  free(p->data);
}

struct simsrv_traffic_s {

};

static inline void destroy_simsrv_traffic_s(struct simsrv_traffic_s *p) {
  if (p == NULL) return;
}

typedef enum {
  simsrv_msgtyp_init,
  simsrv_msgtyp_traffic,
  simsrv_msgtyp_ioctl_request,
  simsrv_msgtyp_ioctl_reply,
  _simsrv_msgtyp_max,
} simsrv_msgtyp_t;

struct simsrv_msg_s {
  simsrv_msgtyp_t typ;
  union {
    struct simsrv_ioctl_s ioctl;
    struct simsrv_traffic_s traffic;
  };
};

static inline void destroy_simsrv_msg_s(struct simsrv_msg_s *p) {
  if (p == NULL) return;
  switch (p->typ) {
    case simsrv_msgtyp_traffic:
      destroy_simsrv_traffic_s(&p->traffic);
      break;
    case simsrv_msgtyp_ioctl_request:
    case simsrv_msgtyp_ioctl_reply:
      destroy_simsrv_ioctl_s(&p->ioctl);
      break;
    default:
      break;
  }
}

#endif  // SIMSRV_H
