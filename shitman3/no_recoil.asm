segment     .text
global      _no_recoil

_no_recoil:
    push    dword [rel multiplier]
    fstp    dword [ecx + 0xF8]
    pop     dword [ecx + 0xF8]
    jmp     dword [rel return]
return:
    dd      0x649BD2
multiplier:
    dd      -100.
