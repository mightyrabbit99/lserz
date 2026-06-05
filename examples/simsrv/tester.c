#include "simsrv_parser.h"
#include <stdio.h>
#include <ctype.h>
static void hexdump_1(const char *title, const unsigned char *d, size_t datalen, int (*fpnt)(const char *format, ...)) {
	size_t i, j = 0;

	fpnt("%s:\n", title);
	for (i = 0; i < datalen; i += j) {
		fpnt("[%4zu]: ", i);
		for (j = 0; j < 16 && i + j < datalen; j++) fpnt("%02x ", d[i + j]);
		while (j++ < 16) fpnt("   ");
		fpnt("|");
		for (j = 0; j < 16 && i + j < datalen; j++)
			fpnt("%c", isprint(d[i + j]) ? d[i + j] : '.');
		fpnt("|\n");
	}
}
#define hexdump(title, d, len) hexdump_1(title, d, len, printf)

int main(void) {
  size_t sz;
  uint8_t buf[200];

  struct simsrv_msg_s msg1 = (struct simsrv_msg_s){
    .typ = simsrv_msgtyp_ioctl_request,
    .ioctl = (struct simsrv_ioctl_s){
      .cmd = 101,
      .data = "hello",
      .len = 5,
    },
  };
  sz = simsrv_msg_serialize(&msg1, buf, sizeof(buf));
  if (sz == (size_t)-1) {
    printf("write error!\n");
    return 1;
  }
  hexdump("buf", buf, sz);


  struct simsrv_msg_s msg2 = (struct simsrv_msg_s){0};
  sz = simsrv_msg_deserialize(&msg2, buf, sz);
  if (sz == (size_t)-1) {
    printf("read error!\n");
    return 1;
  }
  printf("msgtyp=%d\n", msg2.typ);
  printf("cmd=%.4x, datalen=%ld, data: ", msg2.ioctl.cmd, msg2.ioctl.len);
  for (size_t i = 0; i < msg2.ioctl.len; i++)
    printf(" %.2x", msg2.ioctl.data[i]);
  printf("\n");
  destroy_simsrv_msg_s(&msg2);
  return 0;
}
