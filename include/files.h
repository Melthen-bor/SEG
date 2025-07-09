#ifndef SEG_FILES
#define SEG_FILES
#ifdef SEG_NOT_AS_LIB
#include <strings.h>
#else
#include <seg/strings.h>
#endif
#include <stdio.h>
struct seg_file{
    struct seg_string name;
    //uint64_t ext;
    char mode;
    FILE* ptr;
};
enum seg_file_mode:char{
    SEG_READ,
    SEG_WRITE,
    SEG_APPEND,
    SEG_READ_AND,
    SEG_WRITE_AND,
    SEG_APPEND_AND,
    SEG_READ_EXT=8,
    SEG_WRITE_EXT,
    SEG_APPEND_EXT,
    SEG_READ_AND_EXT,
    SEG_WRITE_AND_EXT,
    SEG_APPEND_AND_EXT
};
struct seg_file seg_empty_file(void);
struct seg_file seg_open(struct seg_string,char);
char seg_get_char(struct seg_file);
void seg_put_char(struct seg_file,char);
struct seg_string seg_read(struct seg_file);
struct seg_string seg_read_until(struct seg_file,char);
struct seg_string seg_read_line(struct seg_file);
struct seg_string_list seg_read_lines(struct seg_file);
void seg_write(struct seg_file,struct seg_string);
void seg_write_line(struct seg_file,struct seg_string);
void seg_reopen(struct seg_file*,char);
void seg_close(struct seg_file*);
char seg_is_file_open(struct seg_file);
char seg_end_of_file(struct seg_file);
void seg_destroy_file(struct seg_file*);
#endif