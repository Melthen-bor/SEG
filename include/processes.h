#ifndef SEG_PROCESSES
#define SEG_PROCESSES
#ifdef SEG_NOT_AS_LIB
#include <strings.h>
#else
#include <seg/strings.h>
#endif
struct seg_process{
    struct seg_string input;
    struct seg_string output;
    struct seg_string error;
    struct seg_string cmd;
};
struct seg_pipeline_arg{
    struct seg_string value;
    uint64_t process;
};
struct seg_pipeline_error{
    struct seg_string value;
    uint64_t process;
};
struct seg_pipeline_args{
    uint64_t size;
    uint64_t capacity;
    struct seg_pipeline_arg* data;
};
struct seg_pipeline_errors{
    uint64_t size;
    uint64_t capacity;
    struct seg_pipeline_error* data;
};
struct seg_pipeline{
    struct seg_string_list cmds;
    struct seg_string input;
    struct seg_string output;
    struct seg_pipeline_args arguments;
    struct seg_pipeline_errors errors;
    uint64_t next_error;
    uint64_t last_error_from;
    uint64_t error_amount;
};
struct seg_process seg_empty_process(void);
struct seg_process seg_create_process(struct seg_string);
void seg_attach_file_to_process(struct seg_process*,struct seg_string,char);
void seg_detach_file_from_process(struct seg_process*,char);
void seg_pipe_input_to_process(struct seg_process,struct seg_string);
struct seg_string seg_pipe_output_from_process(struct seg_process);
struct seg_string seg_pipe_errors_from_process(struct seg_process);
void seg_pipe_to_or_from_process(struct seg_process,struct seg_string*,char);
void seg_run_process(struct seg_process);
void seg_run_process_with_args(struct seg_process,struct seg_string_list);
void seg_destroy_process(struct seg_process*);
struct seg_pipeline seg_create_pipeline(void);
void seg_clear_pipeline_args(struct seg_pipeline*);
void seg_add_pipeline_arg(struct seg_pipeline*,struct seg_pipeline_arg);
void seg_attach_file_to_pipeline(struct seg_pipeline*,struct seg_string,char);
void seg_detach_file_from_pipeline(struct seg_pipeline*,char);
void seg_pipe_input_to_pipeline(struct seg_pipeline,struct seg_string);
struct seg_string seg_pipe_output_from_pipeline(struct seg_pipeline);
struct seg_string seg_pipe_error_from_pipeline(struct seg_pipeline);
void seg_pipe_to_or_from_pipline(struct seg_pipeline,struct seg_string*,char);
void seg_attach_file(void*,char,struct seg_string,char);
void seg_detach_file(void*,char,char);
void seg_pipe_input(void*,char,struct seg_string);
struct seg_string seg_pipe_output(void*,char);
struct seg_string seg_pipe_error(void*,char);
void seg_pipe(void*,char,struct seg_string*,char);
#endif