BITS 64

global _simdCrc32

section .text
_simdCrc32:
        push    rbp
        mov     rbp, rsp
        and     rsp, -32

        vmovdqa YWORD [rsp-64], ymm0    ; store __m256i to memory

        mov     eax, DWORD [rsp - 64]   ; 1st block (4 bytes)
                                        ; next 4 bytes
        crc32   eax, DWORD [rsp - 60]   ; using crc32
        crc32   eax, DWORD [rsp - 56]   ; and so on for 7 times  
        crc32   eax, DWORD [rsp - 52]  
        crc32   eax, DWORD [rsp - 48] 
        crc32   eax, DWORD [rsp - 44]    
        crc32   eax, DWORD [rsp - 40]
        crc32   eax, DWORD [rsp - 36]   
        
        mov rsp, rbp
        pop rbp
        ret

;         push    rbp
;         mov     rbp, rsp
;         and     rsp, -32
;         vmovdqa YWORD [rsp-96], ymm0
;         mov     DWORD [rsp-4], 0
;         vmovdqa ymm0, YWORD [rsp-96]
;         vmovdqa YWORD [rsp-64], ymm0
;         mov     QWORD [rsp-16], 0
;         jmp     .L2
; .L4:
;         mov     rax, QWORD [rsp-16]
;         mov     eax, DWORD [rsp-64+rax*4]
;         mov     edx, DWORD [rsp-4]
;         mov     DWORD [rsp-20], edx
;         mov     DWORD [rsp-24], eax
;         mov     eax, DWORD [rsp-20]
;         mov     edx, DWORD [rsp-24]
;         crc32   eax, edx
;         nop
;         mov     DWORD [rsp-4], eax
;         add     QWORD [rsp-16], 1
; .L2:
;         cmp     QWORD [rsp-16], 7
;         jbe     .L4
;         mov     eax, DWORD [rsp-4]
;         leave
;         ret