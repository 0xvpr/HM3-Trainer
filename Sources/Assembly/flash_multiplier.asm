segment .text
global _Multiplier

_Multiplier:
    push    dword [speed]
    pop     dword [esi + 0x14]
    jmp     dword [return]
    int3
speed:
    dd      0x40A00000
return:
    dd      0x0062CFA1
