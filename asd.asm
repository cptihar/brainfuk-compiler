section .data
   tape_size equ 30
   pointer dq 0

section .bss
   tape resb tape_size

section .text
   global _start

_start:
   cld
   mov edi, tape
   mov [pointer], edi
   ; End of assembly setup
   ; Start of brainfuck code


   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   inc byte [edi]
   mov eax, 4
   mov ebx, 1
   mov ecx, [pointer]
   mov edx, 1
   int 0x80



   ; End of brainfuck code
   ; Close program

   mov eax, 1
   xor ebx, ebx
   int 0x80
