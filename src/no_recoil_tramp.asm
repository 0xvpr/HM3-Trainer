segment .text
global _NoRecoilTramp

_NoRecoilTramp:
    push    dword [rel mul]
    fstp    dword [ecx + 0xF8]
    pop     dword [ecx + 0xF8]
    jmp     dword [rel return]
return:
    dd      0x649BD2
mul:
    dd      -100.
