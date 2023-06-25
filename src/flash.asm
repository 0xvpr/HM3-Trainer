segment .text
global _Flash

_Flash:
  fstp  dword [ecx+0x24]
  fld   dword [rel speed]
  fstp  dword [ecx+0x24]
  ret   4
  jmp   [rel return]
speed:
    dd 5.
return:
    dd 0x62BB11
