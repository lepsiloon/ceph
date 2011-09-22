#ifndef CEPH_RGW_CLS_API_H
#define CEPH_RGW_CLS_API_H

#include <map>

#include "include/types.h"
#include "include/utime.h"

struct rgw_bucket_dir_entry {
  std::string name;
  uint8_t category;
  uint64_t size;
  utime_t mtime;
  string etag;
  string owner;
  string owner_display_name;
  uint64_t epoch;

  void encode(bufferlist &bl) const {
    __u8 struct_v = 1;
    ::encode(struct_v, bl);
    ::encode(name, bl);
    ::encode(mtime, bl);
    ::encode(epoch, bl);
    ::encode(etag, bl);
    ::encode(owner, bl);
    ::encode(owner_display_name, bl);
  }
  void decode(bufferlist::iterator &bl) {
    __u8 struct_v;
    ::decode(struct_v, bl);
    ::decode(name, bl);
    ::decode(mtime, bl);
    ::decode(epoch, bl);
    ::decode(etag, bl);
    ::decode(owner, bl);
    ::decode(owner_display_name, bl);
  }
};
WRITE_CLASS_ENCODER(rgw_bucket_dir_entry)

struct rgw_bucket_category_stats {
  uint64_t total_size;
  uint64_t total_size_rounded;
  uint64_t num_entries;

  void encode(bufferlist &bl) const {
    __u8 struct_v = 1;
    ::encode(struct_v, bl);
    ::encode(total_size, bl);
    ::encode(num_entries, bl);
  }
  void decode(bufferlist::iterator &bl) {
    __u8 struct_v;
    ::decode(struct_v, bl);
    ::decode(total_size, bl);
    ::decode(num_entries, bl);
  }
};
WRITE_CLASS_ENCODER(rgw_bucket_category_stats)

struct rgw_bucket_dir_header {
  map<uint8_t, rgw_bucket_category_stats> stats;

  void encode(bufferlist &bl) const {
    __u8 struct_v = 1;
    ::encode(struct_v, bl);
    ::encode(stats, bl);
  }
  void decode(bufferlist::iterator &bl) {
    __u8 struct_v;
    ::decode(struct_v, bl);
    ::decode(stats, bl);
  }
};
WRITE_CLASS_ENCODER(rgw_bucket_dir_header)

struct rgw_bucket_dir {
  struct rgw_bucket_dir_header header;
  std::map<string, struct rgw_bucket_dir_entry> m;

  void encode(bufferlist &bl) const {
    __u8 struct_v = 1;
    ::encode(struct_v, bl);
    ::encode(header, bl);
    ::encode(m, bl);
  }
  void decode(bufferlist::iterator &bl) {
    __u8 struct_v;
    ::decode(struct_v, bl);
    ::decode(header, bl);
    ::decode(m, bl);
  }
};
WRITE_CLASS_ENCODER(rgw_bucket_dir)

enum modify_op {
  CLS_RGW_OP_ADD = 0,
  CLS_RGW_OP_DEL = 1,
};

struct rgw_cls_obj_op
{
  uint8_t op;
  struct rgw_bucket_dir_entry entry;

  void encode(bufferlist &bl) const {
    __u8 struct_v = 1;
    ::encode(struct_v, bl);
    ::encode(op, bl);
    ::encode(entry, bl);
  }
  void decode(bufferlist::iterator &bl) {
    __u8 struct_v;
    ::decode(struct_v, bl);
    ::decode(op, bl);
    ::decode(entry, bl);
  }
};
WRITE_CLASS_ENCODER(rgw_cls_obj_op)

struct rgw_cls_list_op
{
  string start_obj;
  uint32_t num_entries;

  void encode(bufferlist &bl) const {
    __u8 struct_v = 1;
    ::encode(struct_v, bl);
    ::encode(start_obj, bl);
    ::encode(num_entries, bl);
  }
  void decode(bufferlist::iterator &bl) {
    __u8 struct_v;
    ::decode(struct_v, bl);
    ::decode(start_obj, bl);
    ::decode(num_entries, bl);
  }
};
WRITE_CLASS_ENCODER(rgw_cls_list_op)

struct rgw_cls_list_ret
{
  rgw_bucket_dir dir;
  bool is_truncated;

  void encode(bufferlist &bl) const {
    __u8 struct_v = 1;
    ::encode(struct_v, bl);
    ::encode(dir, bl);
    ::encode(is_truncated, bl);
  }
  void decode(bufferlist::iterator &bl) {
    __u8 struct_v;
    ::decode(struct_v, bl);
    ::decode(dir, bl);
    ::decode(is_truncated, bl);
  }
};
WRITE_CLASS_ENCODER(rgw_cls_list_ret)

#endif
