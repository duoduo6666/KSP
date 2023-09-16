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
void   uint32__init
                     (Uint32         *message)
{
  static const Uint32 init_value = UINT32__INIT;
  *message = init_value;
}
size_t uint32__get_packed_size
                     (const Uint32 *message)
{
  assert(message->base.descriptor == &uint32__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t uint32__pack
                     (const Uint32 *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &uint32__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t uint32__pack_to_buffer
                     (const Uint32 *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &uint32__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Uint32 *
       uint32__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Uint32 *)
     protobuf_c_message_unpack (&uint32__descriptor,
                                allocator, len, data);
}
void   uint32__free_unpacked
                     (Uint32 *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &uint32__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   float__init
                     (Float         *message)
{
  static const Float init_value = FLOAT__INIT;
  *message = init_value;
}
size_t float__get_packed_size
                     (const Float *message)
{
  assert(message->base.descriptor == &float__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t float__pack
                     (const Float *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &float__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t float__pack_to_buffer
                     (const Float *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &float__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Float *
       float__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Float *)
     protobuf_c_message_unpack (&float__descriptor,
                                allocator, len, data);
}
void   float__free_unpacked
                     (Float *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &float__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   double__init
                     (Double         *message)
{
  static const Double init_value = DOUBLE__INIT;
  *message = init_value;
}
size_t double__get_packed_size
                     (const Double *message)
{
  assert(message->base.descriptor == &double__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t double__pack
                     (const Double *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &double__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t double__pack_to_buffer
                     (const Double *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &double__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Double *
       double__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Double *)
     protobuf_c_message_unpack (&double__descriptor,
                                allocator, len, data);
}
void   double__free_unpacked
                     (Double *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &double__descriptor);
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
static const ProtobufCFieldDescriptor uint32__field_descriptors[1] =
{
  {
    "value",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(Uint32, value),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned uint32__field_indices_by_name[] = {
  0,   /* field[0] = value */
};
static const ProtobufCIntRange uint32__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor uint32__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "uint32",
  "Uint32",
  "Uint32",
  "",
  sizeof(Uint32),
  1,
  uint32__field_descriptors,
  uint32__field_indices_by_name,
  1,  uint32__number_ranges,
  (ProtobufCMessageInit) uint32__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor float__field_descriptors[1] =
{
  {
    "value",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_FLOAT,
    0,   /* quantifier_offset */
    offsetof(Float, value),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned float__field_indices_by_name[] = {
  0,   /* field[0] = value */
};
static const ProtobufCIntRange float__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor float__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "float",
  "Float",
  "Float",
  "",
  sizeof(Float),
  1,
  float__field_descriptors,
  float__field_indices_by_name,
  1,  float__number_ranges,
  (ProtobufCMessageInit) float__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor double__field_descriptors[1] =
{
  {
    "value",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_DOUBLE,
    0,   /* quantifier_offset */
    offsetof(Double, value),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned double__field_indices_by_name[] = {
  0,   /* field[0] = value */
};
static const ProtobufCIntRange double__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor double__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "double",
  "Double",
  "Double",
  "",
  sizeof(Double),
  1,
  double__field_descriptors,
  double__field_indices_by_name,
  1,  double__number_ranges,
  (ProtobufCMessageInit) double__init,
  NULL,NULL,NULL    /* reserved[123] */
};
