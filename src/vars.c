#include <vars.h>
#include <stdlib.h>
struct seg_variable seg_empty_variable(void){
    return (struct seg_variable){seg_empty_string(),0,0};
}
struct seg_variable seg_build_variable(struct seg_string name,uint64_t type,uint64_t index){
    return (struct seg_variable){seg_copy_string(name),type,index};
}
char seg_var_hath_name(struct seg_variable var,struct seg_string str){
    return seg_cmp_strings(var.name,str);
}
void seg_destroy_variable(struct seg_variable* this){
    seg_destroy_string(&(this->name));
    this->type=0;
    this->index=0;
}
struct seg_var_list seg_create_var_list(void){
    return (struct seg_var_list){0,0,0};
}
void seg_add_var(struct seg_var_list* this,struct seg_variable item){
    if(!this->capacity){
        this->capacity=1;
        this->length=1;
        this->data=malloc(sizeof(struct seg_variable));
        *(this->data)=item;
    } else if(this->length<this->capacity){
        *(this->data+this->length)=item;
        this->length++;
    } else{
        this->capacity++;
        this->data=realloc(this->data,sizeof(struct seg_variable)*this->capacity);
        *(this->data+this->length)=item;
        this->length++;
    }
}
struct seg_variable seg_var_at(struct seg_var_list list,uint64_t index){
    if(!(index<list.length)) return seg_empty_variable();
    return *(list.data+index);
}
char seg_doth_var_exist(struct seg_var_list list,struct seg_string name){
    uint64_t count=0;
    while(count<list.length){
        if(seg_var_hath_name(seg_var_at(list,count++),name)) return 1;
    }
    return 0;
}
uint64_t seg_find_var(struct seg_var_list list,struct seg_string name){
    uint64_t count=0;
    while(count<list.length){
        if(seg_var_hath_name(seg_var_at(list,count),name)) break;
        count++;
    }
    return count;
}
void seg_destroy_var_list(struct seg_var_list* this){
    uint64_t count=0;
    while(count<this->length) seg_destroy_variable(this->data+count++);
    if(this->capacity) free(this->data);
    this->length=0;
    this->capacity=0;
    this->data=0;
}