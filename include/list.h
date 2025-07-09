#ifdef SEG_LISTS
#define SEG_LISTS
#ifdef SEG_NOT_AS_LIB
#include <setup.h>
#else
#include <seg/setup.h>
#endif
#include <inttypes.h>
#define seg_create_named_list(type,name) \
# ## ifndef SEG_ ## type ## _LIST \
# ## define SEG_ ## type ## _LIST \
# ## define SEG_ ## type ## _LIST_AS_ ## name \
struct seg_ ## name{ \
    uint64_t size; \
    uint64_t capacity; \
# ## ifdef SEG_STRUCT_CONTENTS \
    struct type* ptr; \
# ## else \
    type* ptr; \
# ## endif \
}; \
struct seg_ ## name seg_create_ ## name(void); \
struct seg_ ## name seg_ ## name ## _reserve(uint64_t); \
# ## ifdef SEG_STRUCT_CONTENTS \
void seg_add_ ## type(struct seg_ ## name*,struct type); \
struct type seg_ ## type ## _at(struct seg_ ## name,uint64_t); \
void seg_set_ ## type(struct seg_ ## name,uint64_t,struct type); \
struct type seg_pop_ ## type(struct seg_ ## name*); \
struct type seg_remove_ ## type(struct seg_ ## name*,uint64_t); \
struct type seg_delete_ ## type(struct seg_ ## name*,uint64_t); \
# ## else \
void seg_add_ ## type(struct seg_ ## name*,type); \
type seg_ ## type ## _at(struct seg_ ## name,uint64_t); \
void seg_set_ ## type(struct seg_ ## name,uint64_t,type); \
type seg_pop_ ## type(struct seg_ ## name*); \
type seg_remove_ ## type(struct seg_ ## name*,uint64_t); \
type seg_delete_ ## type(struct seg_ ## name*,uint64_t); \
# ## endif \
void seg_destroy_ ## name(struct seg_ ## name*); \
# ## else \
seg_static_assert(type ## _list_already_exists) \
# ## endif
#define seg_create_list(type) seg_create_named_list(type,type ## _list)
#define seg_impl_named_list(type,name) \
# ## ifdef SEG_ ## type ## _LIST_AS_ ## name \
# ## ifndef SEG_ ## type ## _LIST_AS_ ## name ## _IMPLEMENTED \
# ## define SEG_ ## type ## _LIST_AS_ ## name ## _IMPLEMENTED \
struct seg_ ## name seg_create_ ## name ## (void){ \
    return (struct seg_ ## name){0,0,0}; \
} \
struct seg_ ## name seg_ ## name ## _reserve(uint64_t amount){ \
# ## ifdef SEG_STRUCT_CONTENTS \
    return (struct seg_ ## name){amount,amount,malloc(sizeof(struct type)*amount)}; \
# ## else \
    return (struct seg_ ## name){amount,amount,malloc(sizeof(type)*amount)}; \
# ## endif \
} \
void seg_add_ ## type(struct seg_ ## name* this,type item){ \
    if(this->capacity==0){ \
        this->capacity++; \
        this->length++; \
# ## ifdef SEG_STRUCT_CONTENTS \
        this->ptr=malloc(sizeof(struct type)); \
# ## else \
        this->ptr=malloc(sizeof(type)); \
# ## endif \
        *(this->ptr)=item; \
    } else if(this->length<this->capacity){ \
        *(this->ptr+this->length)=item; \
        this->length++; \
    } else{ \
        this->capacity++; \
# ## ifdef SEG_STRUCT_CONTENTS \
        this->ptr=realloc(this->ptr,sizeof(struct type)*this->capacity); \
# ## else \
        this->ptr=realloc(this->ptr,sizeof(type)*this->capacity); \
# ## endif \
        *(this->ptr+this->length)=item; \
        this->length++; \
    } \
} \
type seg_ ## type ## _at(struct seg_ ## name list,uint64_t index){ \
# ## ifdef SEG_STRUCT_CONTENTS \
    if(!(index<list.length)) return (struct type){0}; \
# ## else \
    if(!(index<list.length)) return (type){0}; \
# ## endif \
    return *(list.ptr+index); \
} \
void seg_set_ ## type(struct seg_ ## name list,uint64_t index,type item){ \
    if(!(index<list.length)) return; \
    *(list.ptr+index)=item; \
} \
type seg_pop_ ## type(struct seg_ ## name* this){ \
# ## ifdef SEG_STRUCT_CONTENTS \
    if(!(this->length)) return (struct type){0}; \
# ## else \
    if(!(this->length)) return (type){0}; \
# ## endif \
    this->length--; \
    type out=*(this->ptr+this->length); \
    return out; \
} \
type seg_remove_ ## type(struct seg_ ## name* this,uint64_t index){ \
# ## ifdef SEG_STRUCT_CONTENTS \
    if(!(index<this->length)) return (struct type){0}; \
# ## else \
    if(!(index<this->length)) return (type){0}; \
# ## endif \
    type out=*(this->ptr+index); \
    this->length--; \
    *(this->ptr+index)=*(this->ptr+this->length); \
    return out; \
} \
type seg_delete_ ## type(struct seg_ ## name* this,uint64_t index){ \
# ## ifdef SEG_STRUCT_CONTENTS \
    if(!(index<this->length)) return (struct type){0}; \
# ## else \
    if(!(index<this->length)) return (type){0}; \
# ## endif \
    type out=*(this->ptr+index); \
    uint64_t count=index+1; \
    while(count<this->length){ \
        *(this->ptr+count-1)=*(this->ptr+count); \
        count++; \
    } \
    this->length--; \
    return out; \
} \
void seg_destroy_ ## name(struct seg_ ## name* this){ \
# ## ifdef SEG_DESTROY_CONTENTS \
    uint64_t count=0; \
    while(count<this->length){ seg_destroy_ ## type(this->ptr+(count++)); \
# ## endif \
    this->length=0; \
    this->capacity=0; \
    free(this->ptr); \
    this->ptr=0; \
} \
# ## else \
seg_static_assert(type ## _list_already_implemented_as_ ## name) \
# ## endif \
# ## else \
seg_static_assert(type ## _list_does_not_exist) \
# ## endif
#define seg_impl_list(type) seg_impl_named_list(type,type ## _list)
#endif