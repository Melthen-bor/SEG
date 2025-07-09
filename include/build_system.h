#ifndef SEG_BUILD_SYSTEM
#define SEG_BUILD_SYSTEM
#ifdef SEG_NOT_AS_LIB
#include <strings.h>
#else
#include <seg/strings.h>
#endif
struct seg_compiler_option{
    union{
        struct seg_string str;
        uint64_t index;
    } data;
    char type;
};
struct seg_compiler_options{
    uint64_t size;
    uint64_t capacity;
    struct seg_compiler_option* data;
};
struct seg_compiler{
    struct seg_string nomen;
    struct seg_string processed_ext;
    struct seg_compiler_options afterwards;
    char flags;
};
struct seg_program_language{
    struct seg_string nomen;
    struct seg_string ext;
    struct seg_string end_ext;
    struct seg_compiler_options opts;
    struct seg_compiler compiler;
};
struct seg_compiler_options seg_create_compiler_options(void);
void seg_add_compiler_option(struct seg_compiler_options*,struct seg_compiler_option);
void seg_add_string_option(struct seg_compiler_options*,struct seg_string);
void seg_add_string_option_no_copy(struct seg_compiler_options*,struct seg_string);
void seg_add_uint_option(struct seg_compiler_options*,uint64_t);
struct seg_string seg_process_options(struct seg_compiler_options,struct seg_string_list);
struct seg_compiler_option seg_pop_compiler_option(struct seg_compiler_options*);
uint64_t seg_get_compiler_option_amount(struct seg_compiler_options);
void seg_clear_compiler_options(struct seg_compiler_options*);
void seg_destroy_compiler_options(struct seg_compiler_options*);
struct seg_compiler seg_create_compiler(void);
struct seg_compiler seg_build_compiler_with_flags(struct seg_string,struct seg_string,struct seg_compiler_options,char);
struct seg_compiler seg_build_compiler(struct seg_string,struct seg_string,struct seg_compiler_options,char,char,char,char,char,char);
void seg_run_compiler(struct seg_compiler,struct seg_string,struct seg_string_list,struct seg_string_list);
void seg_destroy_compiler(struct seg_compiler*);
struct seg_program_language seg_build_program_language(struct seg_string,struct seg_string,struct seg_string,struct seg_compiler_options,struct seg_compiler);
void seg_compile_language(struct seg_program_language,struct seg_string,struct seg_string_list);
void seg_destroy_program_language(struct seg_program_language*);
#endif