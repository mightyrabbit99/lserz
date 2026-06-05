#ifndef SIMSRV_PARSER_H
#define SIMSRV_PARSER_H

#include <stdint.h>
#include <sys/types.h>
#include <stddef.h>

#include "simsrv.h"

ssize_t simsrv_msg_deserialize(struct simsrv_msg_s *p, uint8_t *data, size_t datasz);
ssize_t simsrv_msg_serialize(struct simsrv_msg_s *p, uint8_t *buf, size_t bufsz);

#endif  // SIMSRV_PARSER_H
