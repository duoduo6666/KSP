/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: varint.proto */

#ifndef PROTOBUF_C_varint_2eproto__INCLUDED
#define PROTOBUF_C_varint_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003003 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _Varint Varint;


/* --- enums --- */


/* --- messages --- */

struct  _Varint
{
  ProtobufCMessage base;
  uint32_t value;
};
#define VARINT__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&varint__descriptor) \
    , 0 }


/* Varint methods */
void   varint__init
                     (Varint         *message);
size_t varint__get_packed_size
                     (const Varint   *message);
size_t varint__pack
                     (const Varint   *message,
                      uint8_t             *out);
size_t varint__pack_to_buffer
                     (const Varint   *message,
                      ProtobufCBuffer     *buffer);
Varint *
       varint__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   varint__free_unpacked
                     (Varint *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Varint_Closure)
                 (const Varint *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor varint__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_varint_2eproto__INCLUDED */
