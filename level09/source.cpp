// ffs c++ syntax, N isnt a namespace but a class ?
// since there is methods and constructor it most likely is
class N {
  public:
    int operator+(N& obj2); // vtable[0]
    int operator-(N& obj2); // vtable[4]
    void setAnnotation(void *data, char *av_1);
    N(int data); // c++ constructor syntax, no return
  private:
    int prop_0x68; // Not sure about it being private, but it make sens for now
};

// c++filt _ZN1NC2Ei
//	push  ebp
//	mov		ebp,esp
//	mov		eax,DWORD PTR [ebp+0x8]
//	mov		DWORD PTR [eax],0x8048848
//	mov		eax,DWORD PTR [ebp+0x8]
//	mov		edx,DWORD PTR [ebp+0xc]
//	mov		DWORD PTR [eax+0x68],edx
//	pop		ebp
//	ret
//	Call vtable so its either a constructor or a setter ?
//	I think in c++ constructor have the same name as the class, and asm only had 1 call, so its a constructor
N::N(int data) {
  prop_0x68 = data; // Whats being set is at table offset 0x68, so im considering it a prop
}

// push ebp
// mov ebp, esp
// sub esp, 0x18
// mov eax, dword [ebp + 0xc]
// mov dword [esp], eax
// call sym.imp.strlen
// mov edx, dword [ebp + 8]
// add edx, 4
// mov dword [esp + 8], eax
// mov eax, dword [ebp + 0xc]
// mov dword [esp + 4], eax
// mov dword [esp], edx
// call sym.imp.memcpy
// leave
// ret
// This is most likely the vuln
void N::setAnnotation(void *data, char *av_1) {
  memcpy(data + 4, av_1, strlen(av_1));
  return ;
}

// c++filt _ZN1NplERS_ operator+(N&)
int operator+(N& obj2) {
  return prop_0x68 + obj2.prop_0x68;
}

// c++filt _ZN1NplERS_ operator-(N&)
int operator-(N& obj2) {
  return prop_0x68 - obj2.prop_0x68;
}

void main(int ac, char **av) {
  // push ebp
  // mov ebp, esp
  // push ebx
  // and esp, 0xfffffff0
  // sub esp, 0x20
  // cmp dword [argv], 1
  // jg 0x8048610
  if (ac <= 1) {
    // mov dword [esp], 1 ; int status
    // call sym.imp._exit ; void _exit(int status)
    exit(1);
  }

  // mov dword [esp], 0x6c
  // call sym operator new(unsigned int)
  // mov ebx, eax
  N obj = new(0x6c); // I think the arg is the size of obj ? Since the property seems to be allocated at 0x68

  // mov dword [esp+0x4], 5
  // mov dword [esp], ebx
  // call method N::N(int)
  N::N(obj, 5); // set some field inside obj to 5

  // mov dword [esp+0x1c], ebx
  // mov dword [esp], 0x6c
  // call sym operator new(unsigned int)
  N new_ob = new(0x6c);

  // mov ebx, eax
  // mov dword [esp+0x4], 6      ;  int32_t arg_ch
  // mov dword [esp], ebx        ;  int32_t arg_8h
  // call method N::N(int)       ;  N::N(int)
  N::N(new_ob, 6); // set some field inside new_ob to 6

  // mov dword [esp+0x18], ebx    ; esp+0x18 = new_ob

  // mov eax, dword [esp+0x1c]
  // mov dword [esp+0x14], eax    ; esp+0x14 = (esp+0x1c) obj

  // mov eax, dword [esp+0x18]
  // mov dword [esp+0x10], eax    ; esp+0x10 = new_ob

  // mov eax, dword [ebp+0xc]
  // add eax, 4
  // mov eax, dword [eax]
  // mov dword [esp+0x4], eax     ; esp+0x4 = av[1]

  // mov eax, dword [esp+0x14]
  // mov dword [esp], eax         ; esp = obj
  // call method N::setAnnotation(char*)
  N::setAnnotation(obj, av[1]); // memcpy whats inside av[1] in obj + 4

  // mov eax, dword [esp+0x10]    ; eax = new_ob
  // mov eax, dword [eax]         ;                 Edit! this is where i segv
  // mov edx, dword [eax]         ; ? wtf
  // This is probably some sort of virtual call, where the first load the obj virtual table
  // and the second load the first function, since there is no offset. I think..
  // edx = new_obj->operator+; // first vtable func is operator+
  // mov eax, dword [esp+0x14]
  // mov dword [esp+0x4], eax
  // mov eax, dword [esp+0x10]
  // mov dword [esp], eax
  // call edx
  new_obj.operator+(obj); // at least without memory corruption

  // mov ebx, dword [ebp-0x4]     ; obj; esp+0x1c; sub esp, 0x20, but why store it here ?
  // leave
  // ret
  return ;
}
