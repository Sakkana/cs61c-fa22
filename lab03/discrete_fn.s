.globl f # this allows other files to find the function f

.data
arr: .word 6, 61, 17, -38, 19, 42, 5

# f takes in two arguments:
# a0 is the value we want to evaluate f at
# a1 is the address of the "output" array (defined above).
# The return value should be stored in a0

.text
f:
    # a0 下标索引
    # a1 数组地址
    addi a0, a0, 3
    slli t0, a0, 4
    add  t1, a1, t0
    lw   a0, 0(t1)

    # This is how you return from a function. You'll learn more about this later.
    # This should be the last line in your program.
    jr ra