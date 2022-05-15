segment .text
global _NoRecoilTramp

_NoRecoilTramp:
    fstp    dword [ecx + 0xF8]
    mov     dword [ecx + 0xF8], 3267887104
    jmp     dword [return]
return:
    dd      0x00649BD2
