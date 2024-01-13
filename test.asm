section .data
array dd 5, 3, 1, 4, 2
n dd 5

section .text
global _start

_start:
 mov ecx, [array]
 mov edx, [n]
 mov eax, 1
 xor edi, edi
 lea esi, [array]
 lea ebx, [array+edx*4]
 sub ebx, esi
 jg _done
 
 ; 对子数组进行插入排序
 mov eax, 1
 xor edi, edi
 mov ecx, ebx
 dec ecx
 jg _done
 
 _loop:
     mov edx, eax
     shl edx, 2
     imul eax, edx, 4
     add eax, ecx
     mov [esi+eax*4], edx
     mov edx, eax
     shr edx, 1
     imul edx, edx, 4
     add edx, ecx
     mov [esi+edx*4], edx
     
     ; 计算下一个子数组的大小
     mov edx, ebx
     shr edx, 1
     imul edx, edx, 4
     add edx, ecx
     
     ; 合并排序后的子数组
     mov eax, ebx
     shr eax, 1
     imul eax, eax, 4
     add eax, ecx
     mov [esi+eax*4], eax
     mov eax, ebx
     shr eax, 1
     imul eax, eax, 4
     add eax, ecx
     mov [esi+eax*4], eax
     
     ; 更新子数组的大小
     mov eax, 1
     xor edi, edi
     mov ecx, ebx
     dec ecx
     jg _loop
 
 _done:
 mov eax, 1
 xor edi, edi
 syscall
 
 ; 返回
 jmp _start
