/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: varint.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "varint.pb-c.h"
void   varint__init
                     (Varint         *message)
{
  static const Varint init_value = VARINT__INIT;
  *message = init_value;
}
size_t varint__get_packed_size
                     (const Varint *message)
{
  assert(message->base.descriptor == &varint__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t varint__pack
                     (const Varint *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &varint__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t varint__pack_to_buffer
                     (const Varint *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &varint__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Varint *
       varint__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Varint *)
     protobuf_c_message_unpack (&varint__descriptor,
                                allocator, len, data);
}
void   varint__free_unpacked
                     (Varint *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &varint__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor varint__field_descriptors[1] =
{
  {
    "value",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(Varint, value),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned varint__field_indices_by_name[] = {
  0,   /* field[0] = value */
};
static const ProtobufCIntRange varint__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor varint__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "varint",
  "Varint",
  "Varint",
  "",
  sizeof(Varint),
  1,
  varint__field_descriptors,
  varint__field_indices_by_name,
  1,  varint__number_ranges,
  (ProtobufCMessageInit) varint__init,
  NULL,NULL,NULL    /* reserved[123] */
};