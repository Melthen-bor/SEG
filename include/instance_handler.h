#ifndef SEG_INSTANCE_HANDLER
#define SEG_INSTANCE_HANDLER
#ifdef SEG_NOT_AS_LIB
#include <strings.h>
#include <setup.h>
#else
#include <seg/strings.h>
#include <seg/setup.h>
#endif
enum seg_window_display_mode{
    SEG_MINIMIZE,
    SEG_MAXIMIZE,
    SEG_NORMAL
};
enum seg_key_types{
    SEG_KEY_UNKNOWN,
    SEG_KEY_0,
    SEG_KEY_1,
    SEG_KEY_2,
    SEG_KEY_3,
    SEG_KEY_4,
    SEG_KEY_5,
    SEG_KEY_6,
    SEG_KEY_7,
    SEG_KEY_8,
    SEG_KEY_9,
    SEG_KEY_A,
    SEG_KEY_B,
    SEG_KEY_C,
    SEG_KEY_D,
    SEG_KEY_E,
    SEG_KEY_F,
    SEG_KEY_G,
    SEG_KEY_H,
    SEG_KEY_I,
    SEG_KEY_J,
    SEG_KEY_K,
    SEG_KEY_L,
    SEG_KEY_M,
    SEG_KEY_N,
    SEG_KEY_O,
    SEG_KEY_P,
    SEG_KEY_Q,
    SEG_KEY_R,
    SEG_KEY_S,
    SEG_KEY_T,
    SEG_KEY_U,
    SEG_KEY_V,
    SEG_KEY_W,
    SEG_KEY_X,
    SEG_KEY_Y,
    SEG_KEY_Z,
    SEG_KEY_APOSTROPHE,
    SEG_KEY_BACKSLASH,
    SEG_KEY_COLON,
    SEG_KEY_COMMA,
    SEG_KEY_FUNCTION_1,
    SEG_KEY_FUNCTION_2,
    SEG_KEY_FUNCTION_3,
    SEG_KEY_FUNCTION_4,
    SEG_KEY_FUNCTION_5,
    SEG_KEY_FUNCTION_6,
    SEG_KEY_FUNCTION_7,
    SEG_KEY_FUNCTION_8,
    SEG_KEY_FUNCTION_9,
    SEG_KEY_FUNCTION_10,
    SEG_KEY_FUNCTION_11,
    SEG_KEY_FUNCTION_12,
    SEG_KEY_FUNCTION_13,
    SEG_KEY_FUNCTION_14,
    SEG_KEY_FUNCTION_15,
    SEG_KEY_FUNCTION_16,
    SEG_KEY_FUNCTION_17,
    SEG_KEY_FUNCTION_18,
    SEG_KEY_FUNCTION_19,
    SEG_KEY_FUNCTION_20,
    SEG_KEY_FUNCTION_21,
    SEG_KEY_FUNCTION_22,
    SEG_KEY_FUNCTION_23,
    SEG_KEY_FUNCTION_24,
    SEG_KEY_FUNCTION_25,
    SEG_KEY_FUNCTION_26,
    SEG_KEY_NUMPAD_0,
    SEG_KEY_NUMPAD_1,
    SEG_KEY_NUMPAD_2,
    SEG_KEY_NUMPAD_3,
    SEG_KEY_NUMPAD_4,
    SEG_KEY_NUMPAD_5,
    SEG_KEY_NUMPAD_6,
    SEG_KEY_NUMPAD_7,
    SEG_KEY_NUMPAD_8,
    SEG_KEY_NUMPAD_9,
    SEG_KEY_BACKSPACE,
    SEG_KEY_ESCAPE,
    SEG_KEY_ENTER,
    SEG_KEY_TAB,
    SEG_KEY_SHIFT,
    SEG_KEY_CONTROL,
    SEG_KEY_CAPS_LOCK,
    SEG_KEY_ALT,
    SEG_KEY_SPACEBAR,
    SEG_KEY_PAGE_UP,
    SEG_KEY_PAGE_DOWN,
    SEG_KEY_END,
    SEG_KEY_HOME,
    SEG_KEY_UP,
    SEG_KEY_DOWN,
    SEG_KEY_RIGHT,
    SEG_KEY_LEFT,
    SEG_KEY_INSERT,
    SEG_KEY_DELETE,
    SEG_KEY_ADD,
    SEG_KEY_SUBTRACT,
    SEG_KEY_DECIMAL,
    SEG_KEY_DIVIDE,
    SEG_KEY_MINUS,
    SEG_KEY_PLUS,
    SEG_KEY_PERIOD,
    SEG_KEY_LEFT_BRACKET,
    SEG_KEY_RIGHT_BRACKET,
    SEG_KEY_LEFT_PARENTHESIS,
    SEG_KEY_RIGHT_PARENTHESIS,
    SEG_KEY_SEMICOLON,
    SEG_KEY_FORWARD_SLASH,
    SEG_KEY_ACCENT,
    SEG_KEY_MULTIPLY,
    SEG_KEY_NUMBER_LOCK,
    SEG_KEY_LEFT_SHIFT,
    SEG_KEY_RIGHT_SHIFT,
    SEG_KEY_LEFT_CONTROL,
    SEG_KEY_RIGHT_CONTROL,
    SEG_KEY_LEFT_ALT,
    SEG_KEY_RIGHT_ALT,
    SEG_KEY_QUOTE
};
enum seg_mouse_input{
    SEG_MOUSE_UNKNOWN,
    SEG_MOUSE_LEFT_BUTTON,
    SEG_MOUSE_MIDDLE_BUTTON,
    SEG_MOUSE_RIGHT_BUTTON,
    SEG_MOUSE_EXTRA_BUTTON_0,
    SEG_MOUSE_EXTRA_BUTTON_1,
};
// First argument is the struct seg_raw_instance ptr
struct seg_instance_callbacks{
    void(*keys)(void*,uint64_t,char);
    void(*mouse)(void*,uint64_t,uint64_t,char,char);
    void(*size)(void*,uint64_t,uint64_t,uint64_t);
    void(*close)(void*);
};
struct seg_raw_instance_prototype{
    uint64_t height;
    uint64_t width;
    struct seg_instance_callbacks callbacks;
};
struct seg_raw_instance{
    void* internals;
    uint64_t height;
    uint64_t width;
    enum seg_window_display_mode display_mode;
    struct seg_instance_callbacks callbacks;
};
void seg_update_instance_handler(void);
struct seg_raw_instance* seg_construct_raw_instance(struct seg_raw_instance_prototype,char*);
struct seg_raw_instance* seg_build_raw_instance(uint64_t,uint64_t,struct seg_instance_callbacks,char*);
struct seg_raw_instance* seg_create_raw_instance(uint64_t,uint64_t,void(*)(struct seg_raw_instance*,uint64_t,char),void(*)(struct seg_raw_instance*,uint64_t,uint64_t,char,char),void(*)(struct seg_raw_instance*,uint64_t,uint64_t,uint64_t),void(*)(struct seg_raw_instance*),char*);
void seg_display_raw_instance(struct seg_raw_instance*);
void seg_destroy_raw_instance(struct seg_raw_instance*);
enum seg_action_type{
    SEG_ACTION_NONE,
    SEG_ACTION_KEY_DOWN,
    SEG_ACTION_KEY_UP,
    SEG_ACTION_MOUSE_BUTTON_DOWN,
    SEG_ACTION_MOUSE_BUTTON_UP
};
struct seg_action{
    uint64_t code;
    char type;
};
struct seg_actions{
    uint64_t size;
    uint64_t capacity;
    struct seg_action* ptr;
};
struct seg_actions seg_create_actions(void);
struct seg_action seg_pop_action(struct seg_actions*);
void seg_push_action(struct seg_actions*,struct seg_action);
void seg_destroy_actions(struct seg_actions*);
struct seg_instance{
    struct seg_raw_instance internals;
    struct seg_actions acts;
    struct seg_string nomen;
};
struct seg_instance* seg_construct_instance(struct seg_raw_instance_prototype,struct seg_string);
struct seg_instance* seg_build_instance(uint64_t,uint64_t,struct seg_instance_callbacks,struct seg_string);
#endif