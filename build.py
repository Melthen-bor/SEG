import os
import sys
lang='c lib'
use_libs=False
name='seg'
macros=['SEG_NOT_AS_LIB']
use_sml=False
if use_sml:
    import processor as sml
def join_add(lst: list[str],jon: str) -> str:
    if lst==None:
        return ''
    if len(lst)==0:
        return ''
    out=jon
    out+=jon.join(lst)
    return out
def replace_ext(lst: list[str],ext: str) -> list[str]:
    out=[]
    while len(lst)>0:
        out+=['.'.join(lst.pop(0).split('.')[:-1]+[ext])]
def prefix(lst: list[str],pref: str) -> list[str]:
    out=[]
    while len(lst)>0:
        out+=[pref+lst.pop(0)]
    return out
def process_list(lst: list[str|int|list|dict],replace: list[str|list]):
    if len(lst)==0:
        return ''
    out=[]
    test=False
    while len(lst)>0:
        temp=lst.pop(0)
        match temp:
            case 'int':
                test=True
                out+=[replace[temp]]
            case 'str':
                out+=[temp]
            case 'list':
                out+=[''.join(process_list(temp,replace))]
            case 'dict':
                out+=[temp["join"].join(process_list(temp["list"],replace))]
    if test:
        return process_list(out,replace)
    return out
def get_files(ext,dir):
    srcs=os.listdir(os.getcwd()+'\\'+dir)
    out=[]
    while len(srcs)>0:
        if len(srcs[0].split('.'))==1:
            out+=prefix(get_files(ext,dir+'\\'+srcs[0]),'\\'+srcs[0])
        elif srcs[0].split('.')[-1]==ext:
            out+=[srcs[0]]
        srcs.pop(0)
    return out
def get_files_exts(exts,dir):
    out=[]
    while len(exts)>0:
        out+=get_files(exts.pop(0),dir)
    return out
class compiler:
    def __init__(self,nomen,sic_libs,sic_includes,sic_nomen,out_ext,sic_mark_os,compile_only,sic_vnvs,sic_vnvs_opts,opts):
        self.name=nomen
        self.usel=sic_libs
        self.usei=sic_includes
        self.usen=sic_nomen
        self.processed=out_ext
        self.others=opts
        self.mark_os=sic_mark_os
        self.onlyComp=compile_only
        self.at_once=sic_vnvs
        self.once_opts=sic_vnvs_opts
    # srcs-0
    # nomen-1
    # libs-2
    # processed-3
    def compile(self,srcs,nomen,libs):
        global use_libs
        global macros
        if self.at_once:
            if self.onlyComp:
                if self.usel and use_libs:
                    if self.usei:
                        if self.usen:
                            if len(macros)>0:
                                os.system(self.name+' -o'+nomen+join_add(libs,' -l')+' -I'+os.getcwd()+'\\include'+join_add(prefix(srcs,'src\\'),' ')+' -c'+join_add(macros,' -d'))
                            else:
                                os.system(self.name+' -o'+nomen+join_add(libs,' -l')+' -I'+os.getcwd()+'\\include'+join_add(prefix(srcs,'src\\'),' ')+' -c')
                        else:
                            if len(macros)>0:
                                os.system(self.name+join_add(libs,' -l')+' -I'+os.getcwd()+'\\include'+join_add(prefix(srcs,'src\\'),' ')+' -c'+join_add(macros,' -d'))
                            else:
                                os.system(self.name+join_add(libs,' -l')+' -I'+os.getcwd()+'\\include'+join_add(prefix(srcs,'src\\'),' ')+' -c')
                    else:
                        if self.usen:
                            if len(macros)>0:
                                os.system(self.name+' -o'+nomen+join_add(libs,' -l')+join_add(prefix(srcs,'src\\'),' ')+' -c'+join_add(macros,' -d'))
                            else:
                                os.system(self.name+' -o'+nomen+join_add(libs,' -l')+join_add(prefix(srcs,'src\\'),' ')+' -c')
                        else:
                            if len(macros)>0:
                                os.system(self.name+join_add(libs,' -l')+join_add(prefix(srcs,'src\\'),' ')+' -c'+join_add(macros,' -d'))
                            else:
                                os.system(self.name+join_add(libs,' -l')+join_add(prefix(srcs,'src\\'),' ')+' -c')
                else:
                    if self.usei:
                        if self.usen:
                            if len(macros)>0:
                                os.system(self.name+' -o '+nomen+' -I'+os.getcwd()+'\\include'+join_add(prefix(srcs,'src\\'),' ')+' -c'+join_add(macros,' -d'))
                            else:
                                os.system(self.name+' -o '+nomen+' -I'+os.getcwd()+'\\include'+join_add(prefix(srcs,'src\\'),' ')+' -c')
                        else:
                            if len(macros)>0:
                                os.system(self.name+' -I'+os.getcwd()+'\\include'+join_add(prefix(srcs,'src\\'),' ')+' -c'+join_add(macros,' -d'))
                            else:
                                os.system(self.name+' -I'+os.getcwd()+'\\include'+join_add(prefix(srcs,'src\\'),' ')+' -c')
                    else:
                        if self.usen:
                            if len(macros)>0:
                                os.system(self.name+ '-o'+nomen+join_add(prefix(srcs,'src\\'),' ')+' -c'+join_add(macros,' -d'))
                            else:
                                os.system(self.name+ '-o'+nomen+join_add(prefix(srcs,'src\\'),' ')+' -c')
                        else:
                            if len(macros)>0:
                                os.system(self.name+join_add(prefix(srcs,'src\\'),' ')+' -c'+join_add(macros,' -d'))
                            else:
                                os.system(self.name+join_add(prefix(srcs,'src\\'),' ')+' -c')
            else:
                if self.usel and use_libs:
                    if self.usei:
                        if self.usen:
                            if len(macros)>0:
                                os.system(self.name+' -o'+nomen+join_add(libs,' -l')+' -I'+os.getcwd()+'\\include'+join_add(prefix(srcs,'src\\'),' ')+join_add(macros,' -d'))
                            else:
                                os.system(self.name+' -o'+nomen+join_add(libs,' -l')+' -I'+os.getcwd()+'\\include'+join_add(prefix(srcs,'src\\'),' '))
                        else:
                            if len(macros)>0:
                                os.system(self.name+join_add(libs,' -l')+' -I'+os.getcwd()+'\\include'+join_add(prefix(srcs,'src\\'),' ')+join_add(macros,' -d'))
                            else:
                                os.system(self.name+join_add(libs,' -l')+' -I'+os.getcwd()+'\\include'+join_add(prefix(srcs,'src\\'),' '))
                    else:
                        if self.usen:
                            if len(macros)>0:
                                os.system(self.name+' -o'+nomen+join_add(libs,' -l')+join_add(prefix(srcs,'src\\'),' ')+join_add(macros,' -d'))
                            else:
                                os.system(self.name+' -o'+nomen+join_add(libs,' -l')+join_add(prefix(srcs,'src\\'),' '))
                        else:
                            if len(macros)>0:
                                os.system(self.name+join_add(libs,' -l')+join_add(prefix(srcs,'src\\'),' ')+join_add(macros,' -d'))
                            else:
                                os.system(self.name+join_add(libs,' -l')+join_add(prefix(srcs,'src\\'),' '))
                else:
                    if self.usei:
                        if self.usen:
                            if len(macros)>0:
                                os.system(self.name+' -o '+nomen+' -I'+os.getcwd()+'\\include'+join_add(prefix(srcs,'src\\'),' ')+join_add(macros,' -d'))
                            else:
                                os.system(self.name+' -o '+nomen+' -I'+os.getcwd()+'\\include'+join_add(prefix(srcs,'src\\'),' '))
                        else:
                            if len(macros)>0:
                                os.system(self.name+' -I'+os.getcwd()+'\\include'+join_add(prefix(srcs,'src\\'),' ')+join_add(macros,' -d'))
                            else:
                                os.system(self.name+' -I'+os.getcwd()+'\\include'+join_add(prefix(srcs,'src\\'),' '))
                    else:
                        if self.usen:
                            if len(macros)>0:
                                os.system(self.name+ '-o'+nomen+join_add(prefix(srcs,'src\\'),' ')+join_add(macros,' -d'))
                            else:
                                os.system(self.name+ '-o'+nomen+join_add(prefix(srcs,'src\\'),' '))
                        else:
                            if len(macros)>0:
                                os.system(self.name+join_add(prefix(srcs,'src\\'),' ')+join_add(macros,' -d'))
                            else:
                                os.system(self.name+join_add(prefix(srcs,'src\\'),' '))
        else:
            temp=prefix(srcs,'src\\')
            index=0
            while index<len(temp):
                if self.onlyComp:
                    if self.usel and use_libs:
                        if self.usei:
                            if self.usen:
                                if len(macros)>0:
                                    os.system(self.name+' -o'+nomen+join_add(libs,' -l')+' -I'+os.getcwd()+'\\include '+temp[index]+' -c'+join_add(macros,' -d'))
                                else:
                                    os.system(self.name+' -o'+nomen+join_add(libs,' -l')+' -I'+os.getcwd()+'\\include '+temp[index]+' -c')
                            else:
                                if len(macros)>0:
                                    os.system(self.name+join_add(libs,' -l')+' -I'+os.getcwd()+'\\include '+temp[index]+' -c'+join_add(macros,' -d'))
                                else:
                                    os.system(self.name+join_add(libs,' -l')+' -I'+os.getcwd()+'\\include '+temp[index]+' -c')
                        else:
                            if self.usen:
                                if len(macros)>0:
                                    os.system(self.name+' -o'+nomen+join_add(libs,' -l')+' '+temp[index]+' -c'+join_add(macros,' -d'))
                                else:
                                    os.system(self.name+' -o'+nomen+join_add(libs,' -l')+' '+temp[index]+' -c')
                            else:
                                if len(macros)>0:
                                    os.system(self.name+join_add(libs,' -l')+' '+temp[index]+' -c'+join_add(macros,' -d'))
                                else:
                                    os.system(self.name+join_add(libs,' -l')+' '+temp[index]+' -c')
                    else:
                        if self.usei:
                            if self.usen:
                                if len(macros)>0:
                                    os.system(self.name+' -o '+nomen+' -I'+os.getcwd()+'\\include '+temp[index]+' -c'+join_add(macros,' -d'))
                                else:
                                    os.system(self.name+' -o '+nomen+' -I'+os.getcwd()+'\\include '+temp[index]+' -c')
                            else:
                                if len(macros)>0:
                                    os.system(self.name+' -I'+os.getcwd()+'\\include '+temp[index]+' -c'+join_add(macros,' -d'))
                                else:
                                    os.system(self.name+' -I'+os.getcwd()+'\\include '+temp[index]+' -c')
                        else:
                            if self.usen:
                                if len(macros)>0:
                                    os.system(self.name+ '-o'+nomen+' '+temp[index]+' -c'+join_add(macros,' -d'))
                                else:
                                    os.system(self.name+ '-o'+nomen+' '+temp[index]+' -c')
                            else:
                                if len(macros)>0:
                                    os.system(self.name+' '+temp[index]+' -c'+join_add(macros,' -d'))
                                else:
                                    os.system(self.name+' '+temp[index]+' -c')
                else:
                    if self.usel and use_libs:
                        if self.usei:
                            if self.usen:
                                if len(macros)>0:
                                    os.system(self.name+' -o'+nomen+join_add(libs,' -l')+' -I'+os.getcwd()+'\\include '+temp[index]+join_add(macros,' -d'))
                                else:
                                    os.system(self.name+' -o'+nomen+join_add(libs,' -l')+' -I'+os.getcwd()+'\\include '+temp[index])
                            else:
                                if len(macros)>0:
                                    os.system(self.name+join_add(libs,' -l')+' -I'+os.getcwd()+'\\include '+temp[index]+join_add(macros,' -d'))
                                else:
                                    os.system(self.name+join_add(libs,' -l')+' -I'+os.getcwd()+'\\include '+temp[index])
                        else:
                            if self.usen:
                                if len(macros)>0:
                                    os.system(self.name+' -o'+nomen+join_add(libs,' -l')+' '+temp[index]+join_add(macros,' -d'))
                                else:
                                    os.system(self.name+' -o'+nomen+join_add(libs,' -l')+' '+temp[index])
                            else:
                                if len(macros)>0:
                                    os.system(self.name+join_add(libs,' -l')+' '+temp[index]+join_add(macros,' -d'))
                                else:
                                    os.system(self.name+join_add(libs,' -l')+' '+temp[index])
                    else:
                        if self.usei:
                            if self.usen:
                                if len(macros)>0:
                                    os.system(self.name+' -o '+nomen+' -I'+os.getcwd()+'\\include '+temp[index]+join_add(macros,' -d'))
                                else:
                                    os.system(self.name+' -o '+nomen+' -I'+os.getcwd()+'\\include '+temp[index])
                            else:
                                if len(macros)>0:
                                    os.system(self.name+' -I'+os.getcwd()+'\\include '+temp[index]+join_add(macros,' -d'))
                                else:
                                    os.system(self.name+' -I'+os.getcwd()+'\\include '+temp[index])
                        else:
                            if self.usen:
                                if len(macros)>0:
                                    os.system(self.name+ '-o'+nomen+' '+temp[index]+join_add(macros,' -d'))
                                else:
                                    os.system(self.name+ '-o'+nomen+' '+temp[index])
                            else:
                                if len(macros)>0:
                                    os.system(self.name+' '+temp[index]+join_add(macros,' -d'))
                                else:
                                    os.system(self.name+' '+temp[index])
                index+=1
        if self.once_opts:
            os.system(' '.join(process_list(self.others,[prefix(srcs,'src\\'),nomen,libs,replace_ext(prefix(srcs,'src\\'),self.processed)])))
        else:
            for file in srcs:
                os.system(' '.join(process_list(self.others,['src\\'+file,nomen,libs,'.'.join([file.split('.')[:-1],self.processed])])))
class language:
    def __init__(self,nomen,ext,end,opts,complr):
        self.name=nomen
        self.ext=ext
        self.compiler=complr
        self.options=opts
        self.end=end
    # nomen-0
    # args-1
    # ext-2
    # out-3
    def compile(self,project,args):
        global use_sml
        file=open('libs.data')
        libs=file.read().split(' ')
        file.close()
        if use_sml:
            sml.process_files(prefix(get_files(self.ext,'code'),'code\\'),prefix(get_files(self.ext,'code'),'src\\'))
            sml.process_files(prefix(get_files_exts(['hpp','h'],'headers\\'),'headers\\'),prefix(get_files_exts(['hpp','h'],'headers'),'include\\'))
        self.compiler.compile(get_files(self.ext,'src'),project,libs)
        os.system(process_list(self.options,[project,args,self.ext,project+'.'+self.end]))
langs=[]
def get_language(nomen):
    global langs
    count=0
    while count<len(langs):
        if langs[count].name==nomen:
            return langs[count]
        count+=1
    return language(None,None,None)
def add_language(nomen,ext,end,opts,complr):
    global langs
    langs+=[language(nomen,ext,end,opts,complr)]
def get_remove_file():
    match sys.platform:
        case 'win32':
            return 'del'
        case 'cygwin':
            return 'del'
        case _:
            return 'rm'
add_language('c','c','exe',[0,1],compiler('gcc ',True,True,True,'exe',True,False,True,True,[]))
add_language('c++','cpp','exe',[0,1],compiler('g++',True,True,True,'exe',True,False,True,True,[]))
add_language('java','java','jar',['java','-jar',3,1],compiler('javac',False,False,False,'class',False,False,True,True,['jar','-cfe',[1,'.jar'],1,3]))
add_language('v','v','exe',[0,1],compiler('v build',False,False,False,'exe',False,False,True,True,[]))
add_language('c++ small','cpp','exe',[0,1],compiler('gcc',True,True,True,'exe',True,False,True,True,[]))
add_language('rust','rs','exe',[0,1],compiler('rustc',True,False,True,'exe',False,False,True,True,[]))
add_language('c lib','c','a',[],compiler('gcc',True,True,False,'o',True,True,False,False,['ar','rcs',['lib',1,'.a'],3]))
add_language('c++ lib','cpp','a',[],compiler('g++',True,True,False,'o',True,True,False,False,['ar','rcs',['lib',1,'.a'],3]))
add_language('c++ small lib','cpp','a',[ ],compiler('gcc',True,True,False,'o',True,True,False,False,['ar','rcs',['lib',1,'.a'],3]))
add_language('fortran','f','exe',[0,1],compiler('gfortran',True,True,True,'exe',True,False,True,True,[]))
add_language('nasm win64','asm','exe',[0,1],compiler('nasm -f win64 ',False,False,False,'o',False,False,False,True,['gcc -o',[1,'.exe'],3]))
get_language(lang).compile(name,[])