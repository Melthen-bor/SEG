#include <instance_handler.h>
#include <bits.h>
#if defined(_WIN32)||defined(_WIN64)||defined(WINDOWS)
#include <windows.h>
LRESULT CALLBACK seg_internal_window_procedure(HWND,UINT,WPARAM,LPARAM);
struct {
    char flags;
    WNDCLASSEXA window_class;
    uint64_t instance_amount;
    ATOM window_class_atom;
    int* window_display_modes;
    HWND*** handles;
    enum seg_key_types* key_map;
    char* key_flags;
} seg_internal_instance_handler_environment={
    0,
    (WNDCLASSEXA){
        sizeof(WNDCLASSEXA),
        0x0023,
        seg_internal_window_procedure,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        "Class Name\0",
        0
    },
    0,
    0,
    (int*)(int[]){
        SW_SHOWMINIMIZED,
        SW_SHOWMAXIMIZED,
        SW_SHOWNORMAL
    },
    0,
    (enum seg_key_types*)(enum seg_key_types[]){
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_BACKSPACE,
        SEG_KEY_TAB,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_ENTER,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_SHIFT,
        SEG_KEY_CONTROL,
        SEG_KEY_ALT,
        SEG_KEY_CAPS_LOCK,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_ESCAPE,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_SPACEBAR,
        SEG_KEY_PAGE_UP,
        SEG_KEY_PAGE_DOWN,
        SEG_KEY_END,
        SEG_KEY_HOME,
        SEG_KEY_LEFT,
        SEG_KEY_UP,
        SEG_KEY_RIGHT,
        SEG_KEY_DOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_INSERT,
        SEG_KEY_DELETE,
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
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
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
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
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
        SEG_KEY_MULTIPLY,
        SEG_KEY_ADD,
        SEG_KEY_UNKNOWN,
        SEG_KEY_SUBTRACT,
        SEG_KEY_DECIMAL,
        SEG_KEY_DIVIDE,
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
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_NUMBER_LOCK,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_LEFT_SHIFT,
        SEG_KEY_RIGHT_SHIFT,
        SEG_KEY_LEFT_CONTROL,
        SEG_KEY_RIGHT_CONTROL,
        SEG_KEY_LEFT_ALT,
        SEG_KEY_RIGHT_ALT,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_SEMICOLON,
        SEG_KEY_PLUS,
        SEG_KEY_COMMA,
        SEG_KEY_MINUS,
        SEG_KEY_PERIOD,
        SEG_KEY_FORWARD_SLASH,
        SEG_KEY_ACCENT,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_LEFT_BRACKET,
        SEG_KEY_BACKSLASH,
        SEG_KEY_RIGHT_BRACKET,
        SEG_KEY_QUOTE,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN,
        SEG_KEY_UNKNOWN
    },
    (char*)(char[]){
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0
    }
};
void seg_update_instance_handler(void){
    MSG msg;
    GetMessage(&msg,0,0,0);
    DispatchMessage(&msg);
}
uint64_t seg_internal_get_window_handle(HWND hwnd){
    uint64_t out=0;
    while(out<seg_internal_instance_handler_environment.instance_amount) if(*(*(seg_internal_instance_handler_environment.handles[out++]))==hwnd) return out-1;
    return out;
}
char seg_internal_check_instance_callbacks(struct seg_instance_callbacks calls){
    return calls.keys?calls.mouse?calls.size?1:0:0:0;
}
LRESULT CALLBACK seg_internal_window_procedure(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam){
    struct seg_raw_instance* temp_ptr=(struct seg_raw_instance*)(seg_internal_get_window_handle(hwnd)[seg_internal_instance_handler_environment.handles]);
    if(!seg_internal_check_instance_callbacks(temp_ptr->callbacks)) return 0;
    switch(msg){
    case WM_SIZE:
        temp_ptr->callbacks.size(temp_ptr,(uint64_t)wparam,(uint64_t)seg_get_high_word(lparam),(uint64_t)seg_get_low_word(lparam));
        break;
    case WM_KEYDOWN:
        if(seg_get_bit(((wparam/8)[seg_internal_instance_handler_environment.key_flags]),wparam)) return 0;
        seg_set_bit(((wparam/8)+seg_internal_instance_handler_environment.key_flags),wparam,1);
        temp_ptr->callbacks.keys(temp_ptr,(uint64_t)(wparam[seg_internal_instance_handler_environment.key_map]),(char)1);
        break;
    case WM_SIZING:
        return 1;
    case WM_KEYUP:
        if(!seg_get_bit(((wparam/8)[seg_internal_instance_handler_environment.key_flags]),wparam)) return 0;
        seg_set_bit(((wparam/8)+seg_internal_instance_handler_environment.key_flags),wparam,0);
        temp_ptr->callbacks.keys(temp_ptr,(uint64_t)(wparam[seg_internal_instance_handler_environment.key_map]),(char)0);
        break;
    case WM_LBUTTONDOWN:
        temp_ptr->callbacks.mouse(temp_ptr,(uint64_t)seg_get_low_word(lparam),(uint64_t)seg_get_high_word(lparam),(char)SEG_MOUSE_LEFT_BUTTON,(char)1);
        break;
    case WM_LBUTTONUP:
        temp_ptr->callbacks.mouse(temp_ptr,(uint64_t)seg_get_low_word(lparam),(uint64_t)seg_get_high_word(lparam),(char)SEG_MOUSE_LEFT_BUTTON,(char)0);
        break;
    case WM_RBUTTONDOWN:
        temp_ptr->callbacks.mouse(temp_ptr,(uint64_t)seg_get_low_word(lparam),(uint64_t)seg_get_high_word(lparam),(char)SEG_MOUSE_RIGHT_BUTTON,(char)1);
        break;
    case WM_RBUTTONUP:
        temp_ptr->callbacks.mouse(temp_ptr,(uint64_t)seg_get_low_word(lparam),(uint64_t)seg_get_high_word(lparam),(char)SEG_MOUSE_RIGHT_BUTTON,(char)0);
        break;
    case WM_MBUTTONDOWN:
        temp_ptr->callbacks.mouse(temp_ptr,(uint64_t)seg_get_low_word(lparam),(uint64_t)seg_get_high_word(lparam),(char)SEG_MOUSE_MIDDLE_BUTTON,(char)1);
        break;
    case WM_MBUTTONUP:
        temp_ptr->callbacks.mouse(temp_ptr,(uint64_t)seg_get_low_word(lparam),(uint64_t)seg_get_high_word(lparam),(char)SEG_MOUSE_MIDDLE_BUTTON,(char)0);
        break;
    case WM_XBUTTONDOWN:
        temp_ptr->callbacks.mouse(temp_ptr,(uint64_t)seg_get_low_word(lparam),(uint64_t)seg_get_high_word(lparam),(char)(3+seg_get_high_word(wparam)),(char)1);
        return 1;
    case WM_XBUTTONUP:
        temp_ptr->callbacks.mouse(temp_ptr,(uint64_t)seg_get_low_word(lparam),(uint64_t)seg_get_high_word(lparam),(char)(3+seg_get_high_word(wparam)),(char)0);
        return 1;
    }
    return 0;
}
struct seg_raw_instance* seg_build_raw_instance(uint64_t height,uint64_t width,struct seg_instance_callbacks calls,char* name){
    if(!(seg_get_bit(seg_internal_instance_handler_environment.flags,0))){
        seg_set_bit((char*)(&seg_internal_instance_handler_environment),0,1);
        seg_internal_instance_handler_environment.window_class_atom=RegisterClassExA(&seg_internal_instance_handler_environment.window_class);
        seg_internal_instance_handler_environment.handles=malloc(sizeof(HWND));
    } else seg_internal_instance_handler_environment.handles=realloc(seg_internal_instance_handler_environment.handles,sizeof(HWND)*(seg_internal_instance_handler_environment.instance_amount+1));
    struct seg_raw_instance* out=malloc(sizeof(struct seg_raw_instance));
    *out=(struct seg_raw_instance){malloc(sizeof(HWND)),height,width,SEG_NORMAL,calls};
    *(HWND*)(out->internals)=CreateWindowEx(0,seg_internal_instance_handler_environment.window_class.lpszClassName,name,WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,width,height,0,0,0,0);
    seg_internal_instance_handler_environment.handles[seg_internal_instance_handler_environment.instance_amount++]=(HWND**)out;
    return out;
}
struct seg_raw_instance* seg_construct_raw_instance(struct seg_raw_instance_prototype proto,char* name){
    return seg_build_raw_instance(proto.height,proto.width,proto.callbacks,name);
}
struct seg_raw_instance* seg_create_raw_instance(uint64_t height,uint64_t width,void(*keys)(struct seg_raw_instance*,uint64_t,char),void(*mouse)(struct seg_raw_instance*,uint64_t,uint64_t,char,char),void(*size)(struct seg_raw_instance*,uint64_t,uint64_t,uint64_t),void(*close)(struct seg_raw_instance*),char* name){
    return seg_build_raw_instance(height,width,(struct seg_instance_callbacks){(void(*)(void*,uint64_t,char))keys,(void(*)(void*,uint64_t,uint64_t,char,char))mouse,(void(*)(void*,uint64_t,uint64_t,uint64_t))size,(void(*)(void*))close},name);
}
void seg_display_raw_instance(struct seg_raw_instance* raw_instance){
    ShowWindow(*(HWND*)(raw_instance->internals),seg_internal_instance_handler_environment.window_display_modes[raw_instance->display_mode]);
}
void seg_destroy_raw_instance(struct seg_raw_instance* this){
    if(this==0) return;
    seg_internal_instance_handler_environment.handles[seg_internal_get_window_handle(*(HWND*)(this->internals))]=seg_internal_instance_handler_environment.handles[seg_internal_instance_handler_environment.instance_amount--];
    DestroyWindow(*(HWND*)(this->internals));
    free(this->internals);
    if(!(seg_internal_instance_handler_environment.instance_amount)){
        seg_internal_instance_handler_environment.flags=0;
        UnregisterClassW((LPCWSTR)(uint64_t)seg_internal_instance_handler_environment.window_class_atom,0);
        free(seg_internal_instance_handler_environment.handles);
    } else seg_internal_instance_handler_environment.handles=realloc(seg_internal_instance_handler_environment.handles,sizeof(HWND)*seg_internal_instance_handler_environment.instance_amount);
}
struct seg_actions seg_create_actions(void){
    return (struct seg_actions){0,0,0};
}
void seg_push_action(struct seg_actions* this,struct seg_action item){
    if(!(this->capacity)){
        this->capacity=1;
        this->ptr=malloc(sizeof(struct seg_action));
    } else if(!(this->size<this->capacity)) this->ptr=realloc(this->ptr,sizeof(struct seg_action)*(++this->capacity));
    this->size++[this->ptr]=item;
}
struct seg_action seg_pop_action(struct seg_actions* this){
    uint64_t count=0;
    this->size--;
    struct seg_action out=*this->ptr;
    while(count<(this->size-1)) *(this->ptr+count)=*(this->ptr+(++count));
    return out;
}
void seg_destroy_actions(struct seg_actions* this){
    free(this->ptr);
    this->size=0;
    this->capacity=0;
}
struct seg_instance* seg_construct_instance(struct seg_raw_instance_prototype proto,struct seg_string nomen){
    if(!(seg_get_bit(seg_internal_instance_handler_environment.flags,0))){
        seg_set_bit((char*)(&seg_internal_instance_handler_environment),0,1);
        seg_internal_instance_handler_environment.window_class_atom=RegisterClassExA(&seg_internal_instance_handler_environment.window_class);
        seg_internal_instance_handler_environment.handles=malloc(sizeof(HWND));
    } else seg_internal_instance_handler_environment.handles=realloc(seg_internal_instance_handler_environment.handles,sizeof(HWND)*(seg_internal_instance_handler_environment.instance_amount+1));
    char* name=seg_c_str(nomen);
    struct seg_instance* out=malloc(sizeof(struct seg_instance));
    return out;
}
#endif