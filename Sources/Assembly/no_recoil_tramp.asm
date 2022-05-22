segment .text
global _NoRecoilTramp

_NoRecoilTramp:
    push    eax
    mov     eax, dword [rel mul]
    fstp    dword [ecx + 0xF8]
    mov     dword [ecx + 0xF8], eax
    pop     eax
    jmp     dword [rel return]
return:
    dd      0x649BD2
mul:
    dd      -100.
