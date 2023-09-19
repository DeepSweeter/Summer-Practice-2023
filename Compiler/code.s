addi $t0, $t0, 1
addi $t1, $t1, 8
addi $t2, $t2, 10
sw $t2, 4($t1)
lw $t3, 4($t1)
FOR:
add $t1, $t1, $t0
beq $t1, $t2, END
j FOR
END:
sub $t4, $t0, $t1
and $t5, $t0, $t1
or $t6, $t0, $t2
slt $t5, $t0, $t2
addi $zero, $zero, 1