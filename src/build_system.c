#include <build_system.h>
#include <bits.h>
#include <processes.h>
#include <setup.h>
#include <os_utils.h>
#include <stdlib.h>
struct seg_compiler_options seg_create_compiler_options(void){
    return (struct seg_compiler_options){0,0,0};
}
void seg_add_compiler_option(struct seg_compiler_options* this,struct seg_compiler_option opt){
    if(!(this->capacity)){
        this->capacity=1;
        this->data=malloc(sizeof(struct seg_compiler_option));
    }  else if(this->size==this->capacity) this->data=realloc(this->data,sizeof(struct seg_compiler_option)*++this->capacity);
    (this->size++)[this->data]=opt;
}
void seg_add_string_option(struct seg_compiler_options* this,struct seg_string opt){
    seg_add_compiler_option(this,(struct seg_compiler_option){seg_copy_string(opt),2});
}
void seg_add_uint_option(struct seg_compiler_options* this,uint64_t opt){
    seg_add_compiler_option(this,(struct seg_compiler_option){opt,1});
}
void seg_add_string_option_no_copy(struct seg_compiler_options* this,struct seg_string opt){
    seg_add_compiler_option(this,(struct seg_compiler_option){opt,0});
}
struct seg_string seg_process_options(struct seg_compiler_options opts,struct seg_string_list list){
    struct seg_string out=seg_empty_string();
    uint64_t current_opt=0;
    while(current_opt<opts.size){
        if(current_opt) seg_add_char(&out,' ');
        switch(current_opt[opts.data].type){
        case 0:
        case 2:
            seg_concatenate(&out,current_opt[opts.data].data.str);
            break;
        case 1:
            seg_concatenate(&out,seg_string_at(list,current_opt[opts.data].data.index));
        }
        current_opt++;
    }
}
uint64_t seg_get_compiler_option_amount(struct seg_compiler_options opts){
    return opts.size;
}
struct seg_compiler_option seg_pop_compiler_option(struct seg_compiler_options* this){
    if(!(this->size)) return (struct seg_compiler_option){0,0};
    return (--this->size)[this->data];
}
void seg_clear_compiler_options(struct seg_compiler_options* this){
    while(this->size>0){
        switch((--this->size)[this->data].type){
        case 2:
            seg_destroy_string(&this->size[this->data].data.str);
            break;
        default:
            break;
        }
    }
    this->capacity=0;
}
void seg_destroy_compiler_options(struct seg_compiler_options* this){
    seg_clear_compiler_options(this);
    free(this->data);
    this->data=0;
}
struct seg_compiler seg_create_compiler(void){
    return (struct seg_compiler){seg_empty_string(),seg_empty_string(),seg_create_compiler_options(),0};
}
struct seg_compiler seg_build_compiler_with_flags(struct seg_string name,struct seg_string out_ext,struct seg_compiler_options next_process,char flags){
    return (struct seg_compiler){name,out_ext,next_process,flags};
}
struct seg_compiler seg_build_compiler(struct seg_string name,struct seg_string out_ext,struct seg_compiler_options next_process,char use_libs,char use_includes,char use_name,char mark_os,char mark_word_size,char use_ms){
    char flags=0;
    seg_set_bit(&flags,0,use_libs);
    seg_set_bit(&flags,1,use_includes);
    seg_set_bit(&flags,2,use_name);
    seg_set_bit(&flags,3,mark_os);
    seg_set_bit(&flags,4,mark_word_size);
    seg_set_bit(&flags,5,use_ms);
    return (struct seg_compiler){name,out_ext,next_process,flags};
}
void seg_run_compiler(struct seg_compiler comp,struct seg_string project_name,struct seg_string_list srcs,struct seg_string_list libs){
    struct seg_string cmd=seg_copy_string(comp.nomen);
    struct seg_string temp=seg_empty_string();
    if(seg_get_bit(comp.flags,2)){
        if(seg_get_bit(comp.flags,5)) seg_concatenate_c_str(&cmd," /Fe");
        else seg_concatenate_c_str(&cmd," -o");
        seg_concatenate(&cmd,project_name);
    }
    if(seg_get_bit(comp.flags,0)){
        if(seg_get_bit(comp.flags,5)) temp=seg_prefix_c_str_and_join_strings_raw(&libs," /link/DEFAULTLIB");
        else temp=seg_prefix_c_str_and_join_strings_raw(&libs," -l");
        seg_concatenate(&cmd,temp);
        seg_destroy_string(&temp);
        if(libs.length){
            if(seg_get_bit(comp.flags,5)) seg_concatenate_c_str(&cmd," /link/LIBPATH");
            else seg_concatenate_c_str(&cmd," -L");
            temp=seg_getcwd();
            seg_concatenate(&cmd,temp);
            seg_destroy_string(&temp);
            seg_concatenate_c_str(&cmd,"/libs");
        }
    }
    if(seg_get_bit(comp.flags,1)){
        if(seg_get_bit(comp.flags,5)) seg_concatenate_c_str(&cmd," /I");
        else seg_concatenate_c_str(&cmd,"-I");
        temp=seg_getcwd();
        seg_concatenate(&cmd,temp);
        seg_destroy_string(&temp);
        seg_concatenate_c_str(&cmd,"/include");
    }
    if(seg_get_bit(comp.flags,3)){
        if(seg_get_bit(comp.flags,5)) seg_concatenate_c_str(&cmd," /D");
        else seg_concatenate_c_str(&cmd," -d");
        switch(seg_get_current_os()){
        case SEG_WIN32:
        case SEG_WIN64:
        case SEG_WINDOWS:
            seg_concatenate_c_str(&cmd,"WINDOWS");
            break;
        default:
            break;
        }
    }
    if(seg_get_bit(comp.flags,4)){
        if(seg_get_bit(comp.flags,5)) seg_concatenate_c_str(&cmd," /D");
        else seg_concatenate_c_str(&cmd," -d");
        switch(seg_get_current_os()){
        case SEG_WIN32:
            seg_concatenate_c_str(&cmd,"BITS_32");
            break;
        case SEG_WIN64:
            seg_concatenate_c_str(&cmd,"BITS_64");
            break;
        default:
            switch(seg_get_bit_width()){
            case SEG_BIT_8:
                seg_concatenate_c_str(&cmd,"BITS_8");
                break;
            case SEG_BIT_16:
                seg_concatenate_c_str(&cmd,"BITS_16");
                break;
            case SEG_BIT_32:
                seg_concatenate_c_str(&cmd,"BITS_32");
                break;
            case SEG_BIT_64:
                seg_concatenate_c_str(&cmd,"BITS_64");
            }
        }
    }
}
void seg_destroy_compiler(struct seg_compiler* this){
    if(this->nomen.data) seg_destroy_string(&(this->nomen));
    if(this->processed_ext.data) seg_destroy_string(&(this->processed_ext));
    if(this->afterwards.data) seg_destroy_compiler_options(&(this->afterwards));
    this->flags=0;
}