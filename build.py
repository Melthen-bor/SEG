import os
import sys
exec_name='Seg'
use_opengl=False
use_libs=False
lang='c'
os_macro=''
match sys.platform:
    case 'win32':
        os_macro='WINDOWS'
    case 'cygwin':
        os_macro='WINDOWS'
macros=[os_macro]
def is_in(lst,thing):
    count=0
    while count<len(lst):
        if lst[count]==thing:
            return True
        count+=1
    return False
def get_file_types(files,ext):
    count=0
    out=[]
    while count<len(files):
        parts=files[count].split('.')
        if is_in(ext,parts[len(parts)-1]):
            out+=[files[count]]
        count+=1
    return out
def get_file_arguments(files,direct):
    count=0
    out=''
    while count<len(files):
        out+=direct
        out+=files[count]
        out+=' '
        count+=1
    return out
def remove_extensions(files):
    count=0
    out=[]
    while count<len(files):
        out+=['.'.join(files[count].split('.')[:-1])]
        count+=1
    return out
def remove_first_three_letters(files):
    count=0
    out=[]
    while count<len(files):
        out+=[files[count][3:]]
        count+=1
    return out
raw_sources=os.listdir(os.getcwd()+'\\src')
match lang:
    case 'c++':
        sources=get_file_types(raw_sources,['cpp'])
    case 'c':
        sources=get_file_types(raw_sources,['c'])
    case 'fort':
        sources=get_file_types(raw_sources,['f'])
    case 'asm':
        sources=get_file_types(raw_sources,['asm'])
if use_libs:
    raw_libraries=os.listdir(os.getcwd()+'\\lib')
    libraries=get_file_types(raw_libraries,['a','lib','so','dll'])
    lib_arg=get_file_arguments(remove_extensions(libraraies),'-l')
    if use_opengl:
        lib_arg+='-lkernel32 -lopengl32'
    base=' -o '+exec_name+' -L '+os.getcwd()+'\\lib -I '+os.getcwd()+'\\include '+get_file_arguments(sources,'src\\')+lib_arg+get_file_arguments(macros,'-D')
    match lang:
        case 'c++':
            os.system('g++'+base)
        case 'c':
            os.system('gcc'+base)
        case 'fort':
            os.system('gfortran'+base)
else:
    base=' -o '+exec_name+' -I '+os.getcwd()+'\\include '+get_file_arguments(sources,'src\\')+get_file_arguments(macros,'-D')
    match lang:
        case 'c++':
            os.system('g++'+base)
        case 'c':
            os.system('gcc'+base)
        case 'fort':
            os.system('gfortran'+base)
if is_in(os.listdir(os.getcwd()),exec_name+'.exe'):
    os.system(exec_name)
else:
    print('No build found')