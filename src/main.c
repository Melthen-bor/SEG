#include <files.h>
#include <strings.h>
#include <vars.h>
#include <stdlib.h>
void shell(void){
    struct seg_string_list strs=seg_create_string_list();
    seg_add_string_no_copy(&strs,seg_build_string("Command not recognized"));
    seg_add_string_no_copy(&strs,seg_build_string("\033[0m"));
    seg_add_c_str(&strs,"Not enough arguments");
    seg_add_c_str(&strs,"Type mismatch");
    seg_add_c_str(&strs,"Variable does not exist");
    seg_add_c_str(&strs,"Data corrupted");
    struct seg_string_list opts=seg_create_string_list();
    seg_add_string_no_copy(&opts,seg_build_string("exit"));
    seg_add_string_no_copy(&opts,seg_build_string("clr"));
    seg_add_string_no_copy(&opts,seg_build_string("run"));
    seg_add_string_no_copy(&opts,seg_build_string("hist"));
    seg_add_c_str(&opts,"str");
    seg_add_c_str(&opts,"echo");
    struct seg_var_list vars=seg_create_var_list();
    struct seg_string_list string_vars=seg_create_string_list();
    struct seg_string_list history=seg_create_string_list();
    struct seg_string str;
    struct seg_string_list cmd;
    struct seg_file out={{0,0,0},0,stdout};
    struct seg_file in={{0,0,0},0,stdin};
    char* c_str;
    uint64_t count;
    int status=0;
    while(1){
        str=seg_read_line(in);
        seg_add_string(&history,str);
        cmd=seg_split_string(str,' ');
        switch(seg_match_string(seg_string_at(cmd,0),opts)){
        case 0:
            goto end;
        case 1:
            system("cls");
            break;
        case 2:
            seg_destroy_string(&str);
            str=seg_join_strings_range(cmd,' ',1,cmd.length-1);
            c_str=seg_c_str(str);
            status=system(c_str);
            free(c_str);
            break;
        case 3:
            switch(seg_string_list_size(cmd)){
            case 1:
                count=0;
                while(count<seg_string_list_size(history)) seg_write_line(out,seg_string_at(history,count++));
                break;
            case 2:
                seg_write_line(out,seg_string_at(history,seg_uint_from_string(seg_string_at(cmd,1))));
                break;
            case 3:
                count=seg_uint_from_string(seg_string_at(cmd,1));
                while(count<(seg_uint_from_string(seg_string_at(cmd,2))+1)) seg_write_line(out,seg_string_at(history,count++));
                break;
            }
            break;
        case 4:
            if(seg_string_list_size(cmd)<3) seg_write_line(out,seg_string_at(strs,2));
            else if(seg_doth_var_exist(vars,seg_string_at(cmd,1))){
                if(!(seg_var_at(vars,seg_find_var(vars,seg_string_at(cmd,1))).type==0)) seg_write_line(out,seg_string_at(strs,3));
                else seg_copy_string_into_index(&string_vars,seg_var_at(vars,seg_find_var(vars,seg_string_at(cmd,1))).index,seg_string_at(cmd,2));
            } else{
                seg_add_var(&vars,seg_build_variable(seg_string_at(cmd,1),0,seg_string_list_size(string_vars)));
                seg_add_string(&string_vars,seg_string_at(cmd,2));
            }
            break;
        case 5:
            switch(seg_string_list_size(cmd)){
            case 1:
                
                break;
            case 2:
                if(!seg_doth_var_exist(vars,seg_string_at(cmd,1))) seg_write_line(out,seg_string_at(strs,4));
                else{
                    switch(seg_var_at(vars,seg_find_var(vars,seg_string_at(cmd,1))).type){
                    case 0:
                        seg_write_line(out,seg_string_at(string_vars,seg_var_at(vars,seg_find_var(vars,seg_string_at(cmd,1))).index));
                        break;
                    default:
                        seg_write_line(out,seg_string_at(strs,5));
                    }
                }
                break;
            }
            break;
        default:
            seg_write(out,seg_string_at(strs,0));
            seg_put_char(out,':');
            seg_write_line(out,seg_string_at(cmd,0));
        }
        seg_destroy_string(&str);
        seg_destroy_string_list(&cmd);
    }
end:
    seg_write(out,seg_string_at(strs,1));
    seg_destroy_string(&str);
    seg_destroy_string_list(&cmd);
    seg_destroy_string_list(&strs);
    seg_destroy_string_list(&opts);
    seg_destroy_string_list(&history);
}