#include <os_utils.h>
#include <setup.h>
#include <processes.h>
struct seg_string_list seg_get_files(void){
    struct seg_process process=seg_empty_process();
    switch(seg_get_current_os()){
    case SEG_WIN32:
    case SEG_WIN64:
        process=seg_create_process(seg_build_string("dir /B"));
        break;
    default:
        return seg_create_string_list();
    }
    seg_attach_file_to_process(&process,seg_build_string("seg_internal_temp_file"),1);
    seg_run_process(process);
    struct seg_string temp_string=seg_pipe_output_from_process(process);
    struct seg_string_list out=seg_split_string(temp_string,'\n');
    seg_destroy_string(&temp_string);
    seg_destroy_process(&process);
    return out;
}
struct seg_string_list seg_get_files_in_dir(struct seg_string dir){
    struct seg_string temp_string=seg_empty_string();
    temp_string=seg_build_string("cd/");
    seg_concatenate(&temp_string,dir);
    struct seg_string temp=seg_build_string("&&");
    seg_concatenate(&temp_string,temp);
    seg_destroy_string(&temp);
    switch(seg_get_current_os()){
    case SEG_WIN32:
    case SEG_WIN64:
        temp=seg_build_string("dir /B");
        break;
    default:
        seg_destroy_string(&temp_string);
        return seg_create_string_list();
    }
    seg_concatenate(&temp_string,temp);
    seg_destroy_string(&temp);
    struct seg_process process=seg_create_process(temp_string);
    seg_attach_file_to_process(&process,seg_build_string("seg_internal_temp_file"),1);
    seg_run_process(process);
    temp_string=seg_pipe_output_from_process(process);
    struct seg_string_list out=seg_split_string(temp_string,'\n');
    seg_destroy_string(&temp_string);
    seg_destroy_process(&process);
    return out;
}
struct seg_string seg_getcwd(void){
    struct seg_process process=seg_empty_process();
    switch(seg_get_current_os()){
    case SEG_WIN32:
    case SEG_WIN64:
        process=seg_create_process(seg_build_string("cd"));
        break;
    case SEG_LINUX:
    case SEG_UNIX:
    case SEG_MAC:
        process=seg_create_process(seg_build_string("pwd"));
        break;
    default:
        return seg_empty_string();
    }
    seg_attach_file_to_process(&process,seg_build_string("seg_internal_temp_file"),1);
    seg_run_process(process);
    struct seg_string temp=seg_pipe_output_from_process(process);
    struct seg_string_list temp_list=seg_split_string(temp,'\n');
    struct seg_string out=seg_copy_string(seg_string_at(temp_list,0));
    seg_destroy_process(&process);
    seg_destroy_string_list(&temp_list);
    seg_destroy_string(&temp);
    return out;
}