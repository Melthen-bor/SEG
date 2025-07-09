#include <setup.h>
#include <stdlib.h>
struct {
    enum seg_os_type current_os;
    enum seg_architecture_type current_architecture;
    enum seg_compiler_type current_compiler;
    enum seg_bit_width current_bit_width;
    struct seg_compiler_version current_compiler_version;
    void*(*alloc_memory)(size_t);
    void(*free_memory)(void*);
    void*(*realloc_memory)(void*,size_t);
    void*(*list_alloc_memory)(size_t,size_t);
    uint64_t error_amount;
    uint64_t error_capacity;
    struct seg_error* errors;
    char** os_name_list;
    char** compiler_name_list;
} seg_internal_environment={
    #if defined(_WIN64)||(defined(WINDOWS)&&defined(BIT_64))
    SEG_WIN64,
    #elif defined(_WIN32)||(defined(WINDOWS)&&defined(BIT_32))
    SEG_WIN32,
    #elif defined(WINDOWS)
    SEG_WINDOWS,
    #elif defined(__ANDROID__)||defined(ANDROID)
    SEG_ANDROID,
    #elif defined(__LINUX__)||defined(LINUX)
    SEG_LINUX,
    #elif defined(__UNIX__)||defined(UNIX)
    SEG_UNIX,
    #elif defined(__APPLE__)||defined(__MACH__)||defined(APPLE)||defined(MACOS)
    SEG_MAC,
    #else
    SEG_FREESTANDING,
    #endif
    SEG_UNKNOWN,
    #ifdef _MSC_VER
    SEG_MSVC,
    #elif defined(__MINGW64__)
    SEG_MINGW_64,
    #elif defined(__MING32__)
    SEG_MINGW_32,
    #elif defined(__GNUC__)
    SEG_GCC,
    #elif defined(__clang__)
    SEG_CLANG,
    #else
    SEG_NOT_KNOWN,
    #endif
    #if defined(BITS_64)||defined(_WIN64)
    SEG_BIT_64,
    #elif defined(BITS_32)||defined(_WIN32)
    SEG_BIT_32,
    #elif defined(BITS_16)
    SEG_BIT_16,
    #elif defined(BITS_8)
    SEG_BIT_8,
    #else
    SEG_UNKNOWN_BITS,
    #endif
    #ifdef _MSC_VER
    {
        _MSC_VER,
        0,
        0
    },
    #elif defined(__MINGW64__)
    {
        __MINGW64_VERSION_MAJOR,
        __MINGW64_VERSION_MINOR,
        0
    },
    #elif defined(__MINGW32__)
    {
        __MINGW32_MAJOR_VERSION,
        __MINGW32_MINOR_VERSION,
        0
    },
    #elif defined(__GNUC__)
    {
        __GNUC__,
        __GNUC_MINOR__,
        __GNUC_PATCHLEVEL__
    },
    #elif defined(__clang__)
    {
        __clang_major__,
        __clang_minor__,
        __clang_patchlevel__
    },
    #else
    {0,0,0},
    #endif
    malloc,
    free,
    realloc,
    calloc,
    0,
    0,
    0,
    (char**)(char*[]){
        "none",
        "windows 32 bit",
        "windows 64 bit",
        "linux",
        "android",
        "unix",
        "mac",
        "windows"
    },
    (char**)(char*[]){
        "unknown",
        "gcc",
        "msvc",
        "clang",
        "mingw 32 bit",
        "mingw 64 bit"
    }
};
enum seg_os_type seg_get_current_os(void){
    return seg_internal_environment.current_os;
}
char* seg_get_current_os_name(void){
    return seg_internal_environment.os_name_list[seg_internal_environment.current_os];
}
char* seg_get_os_name(enum seg_os_type os){
    return seg_internal_environment.os_name_list[os];
}
enum seg_compiler_type seg_get_current_compiler(void){
    return seg_internal_environment.current_compiler;
}
char* seg_get_current_compiler_name(void){
    return seg_internal_environment.compiler_name_list[seg_internal_environment.current_compiler];
}
char* seg_get_compiler_name(enum seg_compiler_type compiler){
    return seg_internal_environment.compiler_name_list[compiler];
}
struct seg_compiler_version seg_get_current_compiler_version(void){
    return seg_internal_environment.current_compiler_version;
}
enum seg_bit_width seg_get_bit_width(void){
    return seg_internal_environment.current_bit_width;
}