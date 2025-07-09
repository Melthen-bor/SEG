#ifndef SEG_VARS
#define SEG_VARS
#ifdef SEG_NOT_AS_LIB
#include <strings.h>
#else
#include <seg/strings.h>
#endif
struct seg_variable{
    struct seg_string name;
    uint64_t type;
    uint64_t index;
};
struct seg_var_list{
    uint64_t length;
    uint64_t capacity;
    struct seg_variable* data;
};
struct seg_variable seg_empty_variable(void);
struct seg_variable seg_build_variable(struct seg_string,uint64_t,uint64_t);
char seg_var_hath_name(struct seg_variable,struct seg_string);
void seg_destroy_variable(struct seg_variable*);
struct seg_var_list seg_create_var_list(void);
void seg_add_var(struct seg_var_list*,struct seg_variable);
struct seg_variable seg_var_at(struct seg_var_list,uint64_t);
char seg_doth_var_exist(struct seg_var_list,struct seg_string);
uint64_t seg_find_var(struct seg_var_list,struct seg_string);
void seg_destroy_var_list(struct seg_var_list*);
#endif