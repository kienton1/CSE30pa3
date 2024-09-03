// CSE30 assignment template
// 
// id: 
//
////////////////////////////////////////
#include "Version.h"

#ifndef MYINSTNODE_S
    .section .note.GNU-stack,"",%progbits
    .end
#else

    // version 1.0 08/22/2024
    .arch   armv6
    .arm
    .fpu    vfp
    .syntax unified

    #include "node.h"    
    
    .extern malloc
    .extern free
    .extern strcpy
    .extern strncpy
    .extern strlen
    .extern strdup
    .text

    .type   insert_node, %function
    .global insert_node
    // determine how many registers to save and set FP_OFF
    //.equ    FP_OFF, ??

    // preserved register use table fill this in to help you
    //
    // r4
    // r5
    // r6
    // r7
    // r8
    // r9

insert_node:
    psuh     {r4-r7, fp, lr}
    add     fp, sp, #16
    mov     r0, #sizeof(node)
    bl      malloc
    cmp     r0, #0
    beq     allocation_failed
    mov     r4, r0
    mov     r0, r1              
    bl      strdup 
    cmp     r0, #0 
    beq     id_dup_failed
    str     r0, [r4, #offset_id] 
    str     r2, [r4, #offset_xcoord] 
    str     r3, [r4, #offset_ycoord]
    ldr     r0, [fp, #offset_old_head]
    str     r0, [r4, #offset_next]    
    mov     r0, r4              
    b       end_function
id_dup_failed:
    mov     r0, r4
    bl      free
    mov     r0, #0

allocation_failed:
    mov     r0, #0

end_function:
    sub     sp, fp, #16
    pop     {r4-r7, fp, lr}
    bx      lr
    .size   insert_node, (. - insert_node)
    .section .note.GNU-stack,"",%progbits
.end
#endif
