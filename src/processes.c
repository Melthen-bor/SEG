#include <processes.h>
#include <files.h>
#include <setup.h>
#include <stdlib.h>
struct seg_process seg_empty_process(void){
    return (struct seg_process){seg_empty_string(),seg_empty_string(),seg_empty_string(),seg_empty_string()};
}
struct seg_process seg_create_process(struct seg_string cmd){
    return (struct seg_process){seg_empty_string(),seg_empty_string(),seg_empty_string(),cmd};
}
void seg_attach_file_to_process(struct seg_process* this,struct seg_string name,char mode){
    switch(mode){
    case 0:
        if(!(this->input.data==0)) return;
        this->input=name;
        break;
    case 1:
    if(!(this->output.data==0)) return;
        this->output=name;
        break;
    case 2:
    if(!(this->error.data==0)) return;
        this->error=name;
        break;
    }
}
void seg_detach_file_from_process(struct seg_process* this,char mode){
    switch(mode){
    case 0:
        if(this->input.data==0) return;
        seg_destroy_string(&(this->input));
        break;
    case 1:
        if(this->output.data==0) return;
        seg_destroy_string(&(this->output));
        break;
    case 2:
        if(this->error.data==0) return;
        seg_destroy_string(&(this->error));
        break;
    }
}
void seg_pipe_input_to_process(struct seg_process proc,struct seg_string str){
    if(proc.input.data==0) return;
    struct seg_file file=seg_open(proc.input,1);
    seg_write(file,str);
    seg_close(&file);
    seg_destroy_file(&file);
}
struct seg_string seg_pipe_output_from_process(struct seg_process proc){
    if(proc.output.data==0) return seg_empty_string();
    struct seg_file file=seg_open(proc.output,0);
    struct seg_string out=seg_read(file);
    seg_close(&file);
    seg_destroy_file(&file);
    return out;
}
struct seg_string seg_pipe_errors_from_process(struct seg_process proc){
    if(proc.error.data==0) return seg_empty_string();
    struct seg_file file=seg_open(proc.error,0);
    struct seg_string out=seg_read(file);
    seg_close(&file);
    seg_destroy_file(&file);
    return out;
}
void seg_pipe_to_or_for_process(struct seg_process proc,struct seg_string* str,char mode){
    switch(mode){
    case 0:
        seg_pipe_input_to_process(proc,*str);
        break;
    case 1:
        *str=seg_pipe_output_from_process(proc);
        break;
    case 2:
        *str=seg_pipe_errors_from_process(proc);
        break;
    }
}
void seg_run_process(struct seg_process proc){
    if(!(proc.cmd.data)) return;
    struct seg_string temp=seg_empty_string();
    seg_concatenate(&temp,proc.cmd);
    struct seg_string temp_str=seg_empty_string();
    struct seg_file file=seg_empty_file();
    if(proc.output.data){
        file=seg_open(proc.output,1);
        seg_close(&file);
        seg_destroy_file(&file);
    }
    if(proc.error.data){
        file=seg_open(proc.error,1);
        seg_close(&file);
        seg_destroy_file(&file);
    }
    if(!(proc.input.data==0)){
        switch(seg_get_current_os()){
        case SEG_FREESTANDING:
            return;
        case SEG_WIN32:
        case SEG_WIN64:
            temp_str=seg_build_string(" 0<");
            break;
        default:
            return;
        }
        seg_concatenate(&temp,temp_str);
        seg_destroy_string(&temp_str);
        seg_concatenate(&temp,proc.input);
    }
    if(!(proc.output.data==0)){
        switch(seg_get_current_os()){
        case SEG_FREESTANDING:
            return;
        case SEG_WIN32:
        case SEG_WIN64:
            temp_str=seg_build_string(" 1>");
            break;
        default:
            return;
        }
        seg_concatenate(&temp,temp_str);
        seg_destroy_string(&temp_str);
        seg_concatenate(&temp,proc.output);
    }
    if(!(proc.error.data==0)){
        switch(seg_get_current_os()){
        case SEG_FREESTANDING:
            return;
        case SEG_WIN32:
        case SEG_WIN64:
            temp_str=seg_build_string(" 2>");
            break;
        default:
            return;
        }
        seg_concatenate(&temp,temp_str);
        seg_destroy_string(&temp_str);
        seg_concatenate(&temp,proc.error);
    }
    char* temp_c_str=seg_c_str(temp);
    system(temp_c_str);
    free(temp_c_str);
    seg_destroy_string(&temp);
}
void seg_run_process_with_args(struct seg_process proc,struct seg_string_list args){
    if(!(proc.cmd.data)) return;
    struct seg_string temp=seg_empty_string();
    seg_concatenate(&temp,proc.cmd);
    struct seg_string temp_str=seg_empty_string();
    struct seg_file file=seg_empty_file();
    if(proc.output.data){
        file=seg_open(proc.output,1);
        seg_close(&file);
        seg_destroy_file(&file);
    }
    if(proc.error.data){
        file=seg_open(proc.error,1);
        seg_close(&file);
        seg_destroy_file(&file);
    }
    if(seg_string_list_size(args)){
        temp_str=seg_join_strings(args,' ');
        seg_concatenate(&temp,temp_str);
        seg_destroy_string(&temp_str);
    }
    if(!(proc.input.data==0)){
        switch(seg_get_current_os()){
        case SEG_FREESTANDING:
            return;
        case SEG_WIN32:
        case SEG_WIN64:
            temp_str=seg_build_string(" 0<");
            break;
        default:
            return;
        }
        seg_concatenate(&temp,temp_str);
        seg_destroy_string(&temp_str);
        seg_concatenate(&temp,proc.input);
    }
    if(!(proc.output.data==0)){
        switch(seg_get_current_os()){
        case SEG_FREESTANDING:
            return;
        case SEG_WIN32:
        case SEG_WIN64:
            temp_str=seg_build_string(" 1>");
            break;
        default:
            return;
        }
        seg_concatenate(&temp,temp_str);
        seg_destroy_string(&temp_str);
        seg_concatenate(&temp,proc.output);
    }
    if(!(proc.error.data==0)){
        switch(seg_get_current_os()){
        case SEG_FREESTANDING:
            return;
        case SEG_WIN32:
        case SEG_WIN64:
            temp_str=seg_build_string(" 2>");
            break;
        default:
            return;
        }
        seg_concatenate(&temp,temp_str);
        seg_destroy_string(&temp_str);
        seg_concatenate(&temp,proc.error);
    }
    char* temp_c_str=seg_c_str(temp);
    system(temp_c_str);
    free(temp_c_str);
    seg_destroy_string(&temp);
}
void seg_destroy_process(struct seg_process* this){
    if(this->cmd.data==0) seg_destroy_string(&(this->cmd));
    if(this->input.data) seg_destroy_string(&(this->input));
    if(this->output.data) seg_destroy_string(&(this->output));
    if(this->error.data) seg_destroy_string(&(this->error));
}
struct seg_pipeline_args seg_internal_create_pipeline_arguments(void){
    return (struct seg_pipeline_args){0,0,0};
}
struct seg_pipeline_errors seg_internal_create_pipeline_errors(void){
    return (struct seg_pipeline_errors){0,0,0};
}
struct seg_pipeline seg_create_pipeline(void){
    return (struct seg_pipeline){seg_create_string_list(),seg_empty_string(),seg_empty_string(),seg_internal_create_pipeline_arguments(),seg_internal_create_pipeline_errors()};
}