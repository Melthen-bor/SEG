#ifndef SEG_INTS
#define SEG_INTS
#include <inttypes.h>
struct seg_uint_list{
    uint64_t length;
    uint64_t capacity;
    uint64_t* data;
};
struct seg_int_list{
    uint64_t length;
    uint64_t capacity;
    int64_t* data;
};
struct seg_uint_list seg_create_uint_list(void);
struct seg_int_list seg_create_int_list(void);
void seg_add_uint(struct seg_uint_list*,uint64_t);
void seg_add_int(struct seg_int_list*,int64_t);
uint64_t seg_uint_at(struct seg_uint_list,uint64_t);
int64_t seg_int_at(struct seg_int_list,uint64_t);
void seg_set_uint(struct seg_uint_list,uint64_t,uint64_t);
void seg_set_int(struct seg_int_list,uint64_t,int64_t);
uint64_t seg_pop_uint(struct seg_uint_list*);
int64_t seg_pop_int(struct seg_int_list*);
uint64_t seg_remove_uint(struct seg_uint_list*,uint64_t);
int64_t seg_remove_int(struct seg_int_list*,uint64_t);
uint64_t seg_delete_uint(struct seg_uint_list*,uint64_t);
int64_t seg_delete_int(struct seg_int_list*,uint64_t);
void seg_destroy_uint_list(struct seg_uint_list*);
void seg_destroy_int_list(struct seg_int_list*);
#endif