#include <files.h>
#include <stdlib.h>
struct seg_file seg_empty_file(void){
    return (struct seg_file){seg_empty_string(),0,0};
}
char* seg_internal_get_mode_tag(char mode){
    switch(mode){
    case 0:
        return "r";
    case 1:
        return "w";
    case 2:
        return "a";
    case 3:
        return "r+";
    case 4:
        return "w+";
    case 5:
        return "a+";
    default:
        return 0;
    }
}
struct seg_file seg_open(struct seg_string name,char mode){
    char* temp_name=seg_c_str(name);
    struct seg_file out={name,mode,fopen(temp_name,seg_internal_get_mode_tag(mode))};
    free(temp_name);
    return out;
}
char seg_get_char(struct seg_file file){
    if(feof(file.ptr)) return 0;
    return getc(file.ptr);
}
void seg_put_char(struct seg_file file,char chr){
    putc(chr,file.ptr);
}
struct seg_string seg_read(struct seg_file file){
    struct seg_string out=seg_empty_string();
    char temp;
    while(1){
        temp=seg_get_char(file);
        if((!temp)&&feof(file.ptr)) break;
        seg_add_char(&out,temp);
    }
    return out;
}
struct seg_string seg_read_until(struct seg_file file,char chr){
    struct seg_string out=seg_empty_string();
    char temp;
    while(1){
        temp=seg_get_char(file);
        if(((!temp)&&feof(file.ptr))||(temp==chr)) break;
        seg_add_char(&out,temp);
    }
    return out;
}
struct seg_string seg_read_line(struct seg_file file){
    struct seg_string out=seg_empty_string();
    char temp;
    while(1){
        temp=seg_get_char(file);
        if(((!temp)&&feof(file.ptr))||(temp==10)) break;
        seg_add_char(&out,temp);
    }
    return out;
}
char seg_end_of_file(struct seg_file file){
    return feof(file.ptr);
}
struct seg_string_list seg_read_lines(struct seg_file file){
    struct seg_string_list out=seg_create_string_list();
    while(!feof(file.ptr)) seg_add_string(&out,seg_read_line(file));
    return out;
}
void seg_write(struct seg_file file,struct seg_string str){
    uint64_t count=0;
    while(count<str.length) seg_put_char(file,seg_char_at(str,count++));
}
void seg_write_line(struct seg_file file,struct seg_string str){
    uint64_t count=0;
    while(count<str.length) seg_put_char(file,seg_char_at(str,count++));
    putc(10,file.ptr);
}
void seg_close(struct seg_file* this){
    if(this->ptr==0) return;
    fclose(this->ptr);
    this->ptr=0;
    this->mode=0;
}
void seg_reopen(struct seg_file* this,char mode){
    if(this->ptr==0) return;
    char* c_name=seg_c_str(this->name);
    this->ptr=fopen(c_name,seg_internal_get_mode_tag(mode));
    free(c_name);
    this->mode=mode;
}
char seg_is_file_open(struct seg_file file){
    return (!((uint64_t)(file.ptr)==0));
}
void seg_destroy_file(struct seg_file* this){
    seg_close(this);
    seg_destroy_string(&(this->name));
}