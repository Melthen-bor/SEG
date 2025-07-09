#ifndef SEG_OS_UTILS
#define SEG_OS_UTILS
#ifdef SEG_NOT_AS_LIB
#include <strings.h>
#else
#include <seg/strings.h>
#endif
struct seg_string_list seg_get_files(void);
struct seg_string_list seg_get_files_in_dir(struct seg_string);
struct seg_string seg_getcwd(void);
#endif
