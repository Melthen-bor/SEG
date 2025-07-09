#include <ints.h>
#include <stdlib.h>
struct seg_uint_list seg_create_uint_list(void){
    return (struct seg_uint_list){0,0,0};
}
struct seg_int_list seg_create_int_list(void){
    return (struct seg_int_list){0,0,0};
}
void seg_add_uint(struct seg_uint_list* this,uint64_t uint){
    if(this->capacity==0){
        this->capacity++;
        this->length++;
        this->data=malloc(sizeof(uint64_t));
        *(this->data)=uint;
    } else if(this->length<this->capacity){
        *(this->data+this->length)=uint;
        this->length++;
    } else{
        this->capacity++;
        this->data=realloc(this->data,sizeof(uint64_t)*this->capacity);
        *(this->data+this->length)=uint;
        this->length++;
    }
}
void seg_add_int(struct seg_int_list* this,int64_t sint){
    if(this->capacity==0){
        this->capacity++;
        this->length++;
        this->data=malloc(sizeof(int64_t));
        *(this->data)=sint;
    } else if(this->length<this->capacity){
        *(this->data+this->length)=sint;
        this->length++;
    } else{
        this->capacity++;
        this->data=realloc(this->data,sizeof(int64_t)*this->capacity);
        *(this->data+this->length)=sint;
        this->length++;
    }
}
uint64_t seg_uint_at(struct seg_uint_list list,uint64_t index){
    if(!(index<list.length)) return 0;
    return *(list.data+index);
}
int64_t seg_int_at(struct seg_int_list list,uint64_t index){
    if(!(index<list.length)) return 0;
    return *(list.data+index);
}
void seg_set_uint(struct seg_uint_list list,uint64_t index,uint64_t uint){
    if(!(index<list.length)) return;
    *(list.data+index)=uint;
}
void seg_set_int(struct seg_int_list list,uint64_t index,int64_t sint){
    if(!(index<list.length)) return;
    *(list.data+index)=sint;
}
uint64_t seg_pop_uint(struct seg_uint_list* this){
    if(!(this->length)) return 0;
    this->length--;
    return *(this->data+this->length);
}
int64_t seg_pop_int(struct seg_int_list* this){
    if(!(this->length)) return 0;
    this->length--;
    return *(this->data+this->length);
}
uint64_t seg_remove_uint(struct seg_uint_list* this,uint64_t index){
    if(!(index<this->length)) return 0;
    uint64_t out=*(this->data+index);
    this->length--;
    *(this->data+index)=*(this->data+this->length);
    return out;
}
int64_t seg_remove_int(struct seg_int_list* this,uint64_t index){
    if(!(index<this->length)) return 0;
    int64_t out=*(this->data+index);
    this->length--;
    *(this->data+index)=*(this->data+this->length);
    return out;
}
uint64_t seg_delete_uint(struct seg_uint_list* this,uint64_t index){
    if(!(index<this->length)) return 0;
    uint64_t out=*(this->data+index);
    uint64_t count=index+1;
    while(count<this->length){
        *(this->data+count-1)=*(this->data+count);
        count++;
    }
    this->length--;
    return out;
}
int64_t seg_delete_int(struct seg_int_list* this,uint64_t index){
    if(!(index<this->length)) return 0;
    int64_t out=*(this->data+index);
    uint64_t count=index+1;
    while(count<this->length){
        *(this->data+count-1)=*(this->data+count);
        count++;
    }
    this->length--;
    return out;
}
void seg_destroy_uint_list(struct seg_uint_list* this){
    if(this->capacity) free(this->data);
    this->data=0;
    this->length=0;
    this->capacity=0;
}
void seg_destroy_int_list(struct seg_int_list* this){
    if(this->capacity) free(this->data);
    this->data=0;
    this->length=0;
    this->capacity=0;
}