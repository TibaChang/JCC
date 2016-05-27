.file   "./demo/demo_code.s"


    .globl   x
    .data
    .align   4
    .type    x, @object
    .size    x, 4
x:
    .long    1000

.comm   a,4,4

.comm   b,4,4

    .globl   c
    .data
    .align   4
    .type    c, @object
    .size    c, 4
c:
    .long    100

    .globl   aa
    .data
    .align   4
    .type    aa, @object
    .size    aa, 4
aa:
    .long    5

    .globl   cc
    .data
    .align   4
    .type    cc, @object
    .size    cc, 4
cc:
    .long    100000

    .globl   ch_a
    .data
    .align   1
    .type    ch_a, @object
    .size    ch_a, 1
ch_a:
    .byte    90

    .globl   ch_z
    .data
    .align   1
    .type    ch_z, @object
    .size    ch_z, 1
ch_z:
    .byte    97

