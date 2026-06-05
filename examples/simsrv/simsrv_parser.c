#include "simsrv_parser.h"
#include "lserz.h"

SZFDECL_STATIC(struct, simsrv_traffic_s, p) {
  return 0;
}

SZFDECL_STATIC(struct, simsrv_ioctl_s, p) {
  szcv(szc_dtyp_o3, p->cmd);
  szclvp(szc_dtyp_o3, p->len, (size_t)100, p->data);
  return 0;
}

SZFDECL_STATIC(struct, simsrv_msg_s, p) {
  szcv(szc_dtyp_o3, p->typ);
  switch (p->typ) {
    case simsrv_msgtyp_traffic:
      szcfn(simsrv_traffic_s, &p->traffic);
      break;
    case simsrv_msgtyp_ioctl_request:
    case simsrv_msgtyp_ioctl_reply:
      szcfn(simsrv_ioctl_s, &p->ioctl);
      break;
  }
  return 0;
}

ssize_t simsrv_msg_deserialize(struct simsrv_msg_s *p, uint8_t *data, size_t datasz) {
  size_t ll;
  SZFREAD(simsrv_msg_s, ll, p, data, datasz);
  return ll;
}

ssize_t simsrv_msg_serialize(struct simsrv_msg_s *p, uint8_t *buf, size_t bufsz) {
  size_t ll;
  SZFWRITE(simsrv_msg_s, ll, p, buf, bufsz);
  return ll;
}
