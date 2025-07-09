import sys
import os
prefix='©'
current_str=''
def find(a0,a1):
  index=0
  while index<len(a0):
    if a0[index]==a1:
      return index
    index+=1
  return None
def find_and_replace(a0,a1,a2):
  index=0
  out=a0
  while index<len(a0):
    if a0[index]=='__VA_ARGS__':
      if len(a1)<len(a2):
        out[index]=','.join(a2[len(a1)-1:len(a2)-1])
    loc=find(a1,a0[index])
    if not loc==None:
      if not len(a2)<len(a1):
        out[index]=a2[loc]
      else:
        out[index]=''
    index+=1
  return out
def join_as_macro(a0):
  index=0
  out=''
  while index<len(a0):
    if a0[index]==prefix+'_':
      index+=1
      if index<len(a0):
        if a0[index]==' ':
          index+=1
          if index<len(a0):
            out+=a0[index]
    else:
      out+=a0[index]
      if index+1<len(a0):
        if a0[index+1]==' ':
          if index+2<len(a0):
            if a0[index+2]==prefix+'_':
              index+=1
    index+=1
  return out
class macro:
  def __init__(a0,a1,a2,a3):
    a0.nomen=a1
    a0.tkns=a2
    a0.args=a3
  def expand(a0,a1):
    return join_as_macro(find_and_replace(a0.tkns,a0.args,a1))
def find_macro(a0,a1):
  index=0
  while index<len(a0):
    if a0[index].nomen==a1:
      return index
    index+=1
  return None
def process_cycle(a0:str,a1:list[macro],a2):
  global prefix
  global current_str
  def internal_defined(ia0):
    i_index=0
    while i_index<len(a1):
      if a1[i_index].nomen==ia0:
        return True
      i_index+=1
    return False
  index=0
  while index<len(a0):
    if a0[index]==prefix:
      start_index=index
      index+=1
      name=''
      while index<len(a0):
        if a0[index].isalpha() or a0[index]=='_':
          name+=a0[index]
        else:
          break
        index+=1
      match name:
        case 'if':
          if index<len(a0):
            if a0[index]=='(':
              depth=1
              temp=''
              index+=1
              while index<len(a0) and depth>0:
                if a0[index]==')':
                  if not depth==1:
                    temp+=')'
                  depth-=1
                elif a0[index]=='(':
                  depth+=1
                  temp+='('
                else:
                  temp+=a0[index]
                index+=1
              end_cond_index=index
              test=eval(temp,{"internal_defined_macros":a1},{"defined":internal_defined})
              depth=1
              has_else=False
              while index<len(a0) and depth>0:
                temp=''
                if a0[index]==prefix:
                  start_end_if_index=index
                  index+=1
                  while index<len(a0):
                    if a0[index].isalpha() or a0[index]=='_':
                      temp+=a0[index]
                    else:
                      break
                    index+=1
                  if temp=='if':
                    depth+=1
                  elif temp=='else':
                    start_end_index=start_end_if_index
                    end_else_index=index
                    has_else=True
                  elif temp=='endif':
                    depth-=1
                else:
                  index+=1
              if test:
                if has_else:
                  current_str=a0[0:start_index]+a0[end_cond_index:start_end_index]+a0[index:]
                  return [True,a1,True,a2]
                else:
                  current_str=a0[0:start_index]+a0[end_cond_index:start_end_if_index]+a0[index:]
                  return [True,a1,True,a2]
              else:
                if has_else:
                  current_str=a0[0:start_index]+a0[end_else_index:start_end_if_index]+a0[index:]
                  return [True,a1,True,a2]
                else:
                  current_str=a0[0:start_index]+a0[index:]
                  return [True,a1,True,a2]
        case 'define':
          tkns=[]
          temp_list=[]
          name=''
          if index<len(a0):
            if a0[index]==' ':
              index+=1
              if index<len(a0):
                while index<len(a0):
                  if a0[index].isalpha() or a0[index]=='_':
                    name+=a0[index]
                  else:
                    break
                  index+=1
                if index<len(a0):
                  if a0[index]=='(':
                    index+=1
                    temp=''
                    while index<len(a0):
                      if a0[index].isalpha() or a0[index]=='_':
                        temp+=a0[index]
                      elif a0[index]==',':
                        temp_list+=[temp]
                        temp=''
                      elif a0[index]==')':
                        temp_list+=[temp]
                        break
                      index+=1
                depth=1
                temp=''
                if index<len(a0):
                  while index<len(a0) and depth>0:
                    if a0[index]==prefix:
                      if not temp=='':
                        tkns+=[temp]
                        temp=''
                      index+=1
                      if index<len(a0):
                        while index<len(a0):
                          if a0[index].isalpha() or a0[index]=='_':
                            temp+=a0[index]
                          else:
                            break
                          index+=1
                        if temp=="define":
                          tkns+=[prefix+temp]
                          depth+=1
                        elif temp=="enddef":
                          if not depth==1:
                            tkns+=[prefix+temp]
                          depth-=1
                        else:
                          tkns+=[prefix+temp]
                        temp=''
                    elif a0[index].isalpha() or a0[index]=='_':
                      temp+=a0[index]
                      index+=1
                    else:
                      if not temp=='':
                        tkns+=[temp]
                        temp=''
                      tkns+=[a0[index]]
                      index+=1
                current_str=a0[0:start_index]+a0[index:]
                return [True,a1+[macro(name,tkns,temp_list)],True,a2]
          current_str=a0[0:start_index-1]+a0[index:]
          return [True,a1,True,a2]
        case 'push':
          temp=''
          depth=1
          if index<len(a0):
            if a0[index]=='(':
              index+=1
              if index<len(a0):
                while index<len(a0) and depth>0:
                  if a0[index]=='(':
                    temp+=a0[index]
                    depth+=1
                  elif a0[index]==')':
                    if not depth==1:
                      temp+=a0[index]
                    depth-=1
                  else:
                    temp+=a0[index]
          current_str=a0[0:start_index]+a0[index:]
          return [True,a1,True,[a2[0]+[temp]]+a2[1:]]
        case 'undef':
          temp=''
          if index<len(a0):
            if a0[index]==' ':
              index+=1
              if index<len(a0):
                while index<len(a0):
                  if a0[index].isalpha() or a0[index]=='_':
                    temp+=a0[index]
                  else:
                    break
                  index+=1
                current_str=a0[0:start_index]+a0[index:0]
                return [True,a1[0:find_macro(a1,temp)-1]+a1[find_macro(a1,temp)+1:],True,a2]
        case 'pop':
          current_str=a0[0:start_index]+a2[0][-1]+a0[index:]
          return [True,a1,True,[a2[0][:-1]]+a2[1:]]
        case 'include':
          temp=''
          if index<len(a0):
            if a0[index]==' ':
              index+=1
              if index<len(a0):
                while index<len(a0):
                  if a0[index].isalpha() or a0[index]=='.' or a0[index]=='_':
                    print('Include handling:'+a0[index])
                    temp+=a0[index]
                  else:
                    break
                  index+=1
                file=open(os.getcwd()+'\\headers\\'+temp,encoding='utf-8-sig')
                temp=file.read()
                file.close()
                current_str=a0[0:start_index]+temp+a0[index:]
                return [True,a1,True,a2]
        case 'file':
          current_str=a0[0:start_index]+a2[1]+a0[index:]
          return [True,a1,True,a2]
        case _:
          if not find_macro(a1,name)==None:
            if index<len(a0):
              if a0[index]=='(':
                index+=1
                temp=''
                temp_list=[]
                depth=1
                while index<len(a0) and depth>0:
                  if a0[index]==',' and depth==1:
                    temp_list+=[temp]
                    temp=''
                  elif a0[index]==')':
                    if depth==1:
                      temp_list+=[temp]
                      temp=''
                    depth-=1
                  else:
                    if a0[index]=='(':
                      depth+=1
                    temp+=a0[index]
                  index+=1
                current_str=a0[0:start_index]+a1[find_macro(a1,name).expand(temp_list)+a0[index:]]
                return [True,a1,True,a2]
          current_str=a0[0:start_index-1]+a0[index:]
          return [True,a1,True,a2]
    elif a0[index]=='"':
      index+=1
      if index<len(a0):
        while index<len(a0):
          if a0[index]=='"':
            break
          index+=1
    elif a0[index]=='\'':
      index+=1
      if index<len(a0):
        while index<len(a0):
          if a0[index]=='\'':
            break
          index+=1
    else:
      index+=1
  current_str=a0
  return [False,a1,False,a2]
def process(a0,a1):
  global prefix
  global current_str
  state=[a0,[],True,[[],a1]]
  current_str=a0
  cycle=0
  while state[2]:
    print('Starting cycle:'+str(cycle))
    print(current_str)
    state=process_cycle(current_str,state[1],state[3])
    cycle+=1
  return current_str
def process_file(a0,a1):
  global prefix
  file=open(a0,encoding='utf-8-sig')
  out_file=open(a1,'w+',encoding='utf-8-sig')
  out_file.write(process(file.read(),a0))
  file.close()
  out_file.close()
def process_files(a0,a1):
  if len(a0)==len(a1):
    index=0
    while(index<len(a0)):
      process_file(a0[index],a1[index])
      index+=1