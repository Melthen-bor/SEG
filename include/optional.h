#ifndef SEG_OPTIONAL
#define SEG_OPTIONAL
#ifdef SEG_NOT_AS_LIB
#include <setup.h>
#else
#include <seg/setup.h>
#endif
#define seg_create_optional(type) \
struct seg_ ## type ## _optional{ \
    type value; \
    char exists; \
}
#define seg_create_optional_struct(type) \
struct seg_ ## type ## _optional{ \
    struct type value; \
    char exists; \
}
#define seg_create_optional_seg(type) \
struct seg_ ## type ## _optional{ \
    seg_ ## type value; \
    char exists; \
}
#define seg_create_optional_seg_struct(type) \
struct seg_ ## type ## _optional{ \
    struct seg_ ## type value; \
    char exists; \
}
#endif