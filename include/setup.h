#ifndef SEG_SETUP
#define SEG_SETUP
#define seg_static_assert(MSG) unsigned char assert_var[0-__LINE__]={ ## MSG ## };
#include <inttypes.h>
#include <stddef.h>
struct seg_error{
    uint64_t type;
    uint64_t code;
};
enum seg_os_type{
    SEG_FREESTANDING,
    SEG_WIN32,
    SEG_WIN64,
    SEG_LINUX,
    SEG_ANDROID,
    SEG_UNIX,
    SEG_MAC,
    SEG_WINDOWS
};
enum seg_architecture_type{
    SEG_UNKNOWN,
    SEG_x86,
    SEG_x86_64,
    SEG_ARM
};
enum seg_compiler_type{
    SEG_NOT_KNOWN,
    SEG_GCC,
    SEG_MSVC,
    SEG_CLANG,
    SEG_MINGW_32,
    SEG_MINGW_64
};
struct seg_compiler_version{
    uint64_t major;
    uint64_t minor;
    uint64_t patch;
};
enum seg_bit_width{
    SEG_UNKNOWN_BITS,
    SEG_BIT_8,
    SEG_BIT_16,
    SEG_BIT_32,
    SEG_BIT_64
};
enum seg_os_type seg_get_current_os(void);
char* seg_get_current_os_name(void);
char* seg_get_os_name(enum seg_os_type);
enum seg_compiler_type seg_get_current_compiler(void);
char* seg_get_current_compiler_name(void);
char* seg_get_compiler_name(enum seg_compiler_type);
struct seg_compiler_version seg_get_current_compiler_version(void);
enum seg_bit_width seg_get_bit_width(void);
#endif