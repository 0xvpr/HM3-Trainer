segment .text
global _Flash

_Flash:
  fstp  dword [ecx+0x24]
  fld   dword [speed]
  fstp  dword [ecx+0x24]
  ret   4
  jmp   [return]
speed:
    dd 0x40A00000
return:
    dd 0x0062BB11
