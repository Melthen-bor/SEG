#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include <ints.h>
struct seg_string seg_empty_string(void){
    return (struct seg_string){0,0,0};
}
struct seg_string seg_reserve_string(uint64_t capacity){
    return (struct seg_string){0,capacity,malloc(capacity)};
}
void seg_increase_string_capacity(struct seg_string* this,uint64_t capacity){
    this->capacity+=capacity;
    this->data=realloc(this->data,this->capacity);
}
void seg_add_char(struct seg_string* this,char thing){
    if(this->capacity==0){
        this->capacity=1;
        this->length=1;
        this->data=malloc(1);
        *(this->data)=thing;
    }
    else if(this->length<this->capacity){
        *(this->data+this->length)=thing;
        this->length++;
    } else{
        this->capacity++;
        this->data=realloc(this->data,this->capacity);
        *(this->data+this->length)=thing;
        this->length++;
    }
}
char seg_char_at(struct seg_string str,uint64_t index){
    if(index>str.length) return 0;
    return *(str.data+index);
}
struct seg_string seg_build_string(char* c_str){
    struct seg_string out=seg_empty_string();
    if(c_str==0) return out;
    uint64_t count=0;
    while(*(c_str+count)) seg_add_char(&out,*(c_str+(count++)));
    return out;
}
void seg_concatenate(struct seg_string* this,struct seg_string other){
    if(!(other.length)) return;
    uint64_t count=0;
    if(other.length>(this->capacity-this->length)) seg_increase_string_capacity(this,other.length-(this->capacity-this->length));
    while(count<other.length) seg_add_char(this,*(other.data+(count++)));
}
void seg_concatenate_c_str(struct seg_string* this,char* other){
    if(!(*other)) return;
    struct seg_string temp=seg_build_string(other);
    seg_concatenate(this,temp);
    seg_destroy_string(&temp);
}
void seg_move_string(struct seg_string* this,struct seg_string* dest){
    seg_clear_string(dest);
    seg_concatenate(dest,*this);
    seg_destroy_string(this);
}
uint64_t seg_string_size(struct seg_string str){
    return str.length;
}
uint64_t seg_string_cap(struct seg_string str){
    return str.capacity;
}
struct seg_string seg_copy_string(struct seg_string str){
    struct seg_string out=seg_reserve_string(str.length);
    uint64_t count=0;
    while(count<str.length) seg_add_char(&out,*(str.data+(count++)));
    return out;
}
void seg_copy_string_into(struct seg_string* this,struct seg_string str){
    seg_clear_string(this);
    seg_concatenate(this,str);
}
void seg_clear_string(struct seg_string* this){
    this->length=0;
}
void seg_display_string(struct seg_string str){
    uint64_t count=0;
    while(count<str.length) putchar(*(str.data+(count++)));
}
char seg_pop_char(struct seg_string* this){
    if((this->data==0)||(this->length==0)) return 0;
    this->length--;
    return *(this->data+this->length);
}
void seg_set_char(struct seg_string str,uint64_t index,char chr){
    if(!(index<str.length)) return;
    *(str.data+index)=chr;
}
char seg_remove_char(struct seg_string* this,uint64_t index){
    if(!(index<this->length)) return 0;
    char out=*(this->data+index);
    this->length--;
    *(this->data+index)=*(this->data+this->length);
    return out;
}
char seg_delete_char(struct seg_string* this,uint64_t index){
    if(!(index<this->length)) return 0;
    char out=*(this->data+index);
    uint64_t count=index+1;
    while(count<this->length){
        *(this->data+count-1)=*(this->data+count);
        count++;
    }
    this->length--;
    return out;
}
char* seg_c_str(struct seg_string str){
    char* out=malloc(str.length+1);
    *(out+str.length)=0;
    uint64_t count=0;
    while(count<str.length){
        *(out+count)=*(str.data+count);
        count++;
    }
    return out;
}

char seg_cmp_strings(struct seg_string str,struct seg_string str2){
    if(!(str.length==str2.length)) return 0;
    uint64_t count=0;
    while(count<str.length){
         if(!(seg_char_at(str,count)==seg_char_at(str2,count))) return 0;
         count++;
    }
    return 1;
}
char seg_cmp_string_c_str(struct seg_string str,char* c_str){
    uint64_t count=0;
    while(count<str.length){
        if(!(count[c_str])) return 0;
        if(!(count[str.data]==count[c_str])) return 0;
        count++;
    }
    if(count[c_str]) return 0;
    return 1;
}
uint64_t seg_uint_from_string(struct seg_string str){
    uint64_t out=0;
    uint64_t count=0;
    while(count<str.length){
        out*=10;
        switch(seg_char_at(str,count)){
        case '1':
            out++;
            break;
        case '2':
            out+=2;
            break;
        case '3':
            out+=3;
            break;
        case '4':
            out+=4;
            break;
        case '5':
            out+=5;
            break;
        case '6':
            out+=6;
            break;
        case '7':
            out+=7;
            break;
        case '8':
            out+=8;
            break;
        case '9':
            out+=9;
            break;
        }
        count++;
    }
    return out;
}
struct seg_string seg_string_from_uint(uint64_t uint){
    uint64_t out=0;
}
void seg_destroy_string(struct seg_string* this){
    if(this->capacity) free(this->data);
    this->length=0;
    this->capacity=0;
    this->data=0;
}
struct seg_string_list seg_create_string_list(void){
    return (struct seg_string_list){0,0,0};
}
struct seg_string_list seg_build_string_list(int argv,char** argc){
    struct seg_string_list out=seg_create_string_list();
    uint64_t count=0;
    while(count<argv) seg_add_string_no_copy(&out,seg_build_string(*(argc+(count++))));
    return out;
}
void seg_add_string(struct seg_string_list* this,struct seg_string str){
    if(this->capacity==0){
        this->capacity=1;
        this->length=1;
        this->data=malloc(sizeof(struct seg_string));
        *(this->data)=seg_copy_string(str);
    } else if(this->length<this->capacity){
        *(this->data+this->length)=seg_copy_string(str);
        this->length++;
    } else{
        this->capacity++;
        this->data=realloc(this->data,this->capacity*sizeof(struct seg_string));
        *(this->data+this->length)=seg_copy_string(str);
        this->length++;
    }
}
void seg_add_string_no_copy(struct seg_string_list* this,struct seg_string str){
    if(this->capacity==0){
        this->capacity=1;
        this->length=1;
        this->data=malloc(sizeof(struct seg_string));
        *(this->data)=str;
    } else if(this->length<this->capacity){
        *(this->data+this->length)=str;
        this->length++;
    } else{
        this->capacity++;
        this->data=realloc(this->data,this->capacity*sizeof(struct seg_string));
        *(this->data+this->length)=str;
        this->length++;
    }
}
struct seg_string seg_string_at(struct seg_string_list list,uint64_t index){
    if(!(index<list.length)) return seg_empty_string();
    return *(list.data+index);
}
void seg_set_string(struct seg_string_list list,uint64_t index,struct seg_string str){
    if(!(index<list.length)) return;
    *(list.data+index)=str;
}
void seg_set_string_data(struct seg_string_list list,uint64_t index,struct seg_string str){
    if(!(index<list.length)) return;
    seg_copy_string_into(list.data+index,str);
}
struct seg_string seg_pop_string(struct seg_string_list* this){
    if(this==0||this->data==0) return seg_empty_string();
    this->length--;
    return *(this->data+this->length);
}
struct seg_string seg_remove_string(struct seg_string_list* this,uint64_t index){
    if(!(index<this->length)) return seg_empty_string();
    struct seg_string out=seg_string_at(*this,index);
    this->length--;
    *(this->data+index)=*(this->data+this->length);
    return out;
}
struct seg_string seg_delete_string(struct seg_string_list* this,uint64_t index){
    if((index<this->length)) return seg_empty_string();
    struct seg_string out=seg_string_at(*this,index);
    uint64_t count=index+1;
    while(count<this->length){
        *(this->data+count-1)=*(this->data+count);
        count++;
    }
    this->length--;
    return out;
}
struct seg_string_list seg_split_string(struct seg_string str,char thing){
    struct seg_string_list out=seg_create_string_list();
    struct seg_string temp=seg_empty_string();
    uint64_t count=0;
    while(count<str.length){
        if(*(str.data+count)==thing){
            seg_add_string(&out,temp);
            seg_clear_string(&temp);
        } else seg_add_char(&temp,*(str.data+count));
        count++;
    }
    if(temp.length>0) seg_add_string(&out,temp);
    seg_destroy_string(&temp);
    return out;
}
uint64_t seg_string_list_size(struct seg_string_list list){
    return list.length;
}
uint64_t seg_string_list_cap(struct seg_string_list list){
    return list.capacity;
}
struct seg_string seg_join_strings(struct seg_string_list list,char thing){
    if(list.length==0) return seg_empty_string();
    struct seg_string out=seg_copy_string(*(list.data));
    uint64_t count=1;
    while(count<list.length){
        seg_add_char(&out,thing);
        seg_concatenate(&out,*(list.data+count));
        count++;
    }
    return out;
}
struct seg_string seg_join_strings_raw(struct seg_string_list list){
    if(!(list.length)) return seg_empty_string();
    struct seg_string out=seg_empty_string();
    uint64_t count=0;
    while(count<list.length) seg_concatenate(&out,(count++)[list.data]);
    return out;
}
struct seg_string seg_join_strings_range(struct seg_string_list list,char chr,uint64_t min,uint64_t max){
    if((min<(max+1)&&(min<list.length))) return seg_empty_string();
    struct seg_string out=seg_copy_string(seg_string_at(list,min));
    uint64_t count=min+1;
    while(count<(list.length<(max+1)?list.length:(max+1))){
        seg_add_char(&out,chr);
        seg_concatenate(&out,seg_string_at(list,count));
        count++;
    }
    return out;
}
struct seg_string seg_join_strings_range_raw(struct seg_string_list list,uint64_t min,uint64_t max){
    if((min<(max+1)&&(min<list.length))) return seg_empty_string();
    struct seg_string out=seg_empty_string();
    uint64_t count=min;
    while(count<(list.length<(max+1)?list.length:(max+1))) seg_concatenate(&out,(count++)[list.data]);
    return out;
}
void seg_prefix_strings(struct seg_string_list* this,struct seg_string prefix){
    struct seg_string temp=seg_empty_string();
    uint64_t current_str=0;
    while(current_str<this->length){
        seg_concatenate(&temp,prefix);
        seg_concatenate(&temp,current_str[this->data]);
        seg_clear_string(current_str+this->data);
        seg_concatenate((current_str++)+this->data,temp);
        seg_clear_string(&temp);
    }
    seg_destroy_string(&temp);
}
void seg_prefix_strings_c_str(struct seg_string_list* this,char* prefix){
    struct seg_string temp=seg_build_string(prefix);
    seg_prefix_strings(this,temp);
    seg_destroy_string(&temp);
}
struct seg_string seg_prefix_and_join_strings(struct seg_string_list* this,struct seg_string prefix,char chr){
    seg_prefix_strings(this,prefix);
    return seg_join_strings(*this,chr);
}
struct seg_string seg_prefix_and_join_strings_raw(struct seg_string_list* this,struct seg_string prefix){
    seg_prefix_strings(this,prefix);
    return seg_join_strings_raw(*this);
}
struct seg_string seg_prefix_c_str_and_join_strings(struct seg_string_list* this,char* prefix,char chr){
    seg_prefix_strings_c_str(this,prefix);
    return seg_join_strings(*this,chr);
}
struct seg_string seg_prefix_c_str_and_join_strings_raw(struct seg_string_list* this,char* prefix){
    seg_prefix_strings_c_str(this,prefix);
    return seg_join_strings_raw(*this);
}
void seg_add_c_str(struct seg_string_list* this,char* c_str){
    seg_add_string_no_copy(this,seg_build_string(c_str));
}
void seg_copy_string_into_index(struct seg_string_list* this,uint64_t index,struct seg_string str){
    if(!(index<this->length)) return;
    seg_copy_string_into(this->data+index,str);
}
void seg_destroy_string_list(struct seg_string_list* this){
    uint64_t count=0;
    while(count<this->length){
        seg_destroy_string(this->data+count);
        count++;
    }
    if(this->capacity) free(this->data);
    this->length=0;
    this->capacity=0;
    this->data=0;
}
uint64_t seg_match_string(struct seg_string str,struct seg_string_list list){
    uint64_t count=0;
    while(count<list.length){
        if(seg_cmp_strings(str,seg_string_at(list,count))) break;
        count++;
    }     
    return count;
}