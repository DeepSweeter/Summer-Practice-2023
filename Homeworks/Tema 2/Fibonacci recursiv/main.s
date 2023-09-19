.data
    text1: .asciiz "Citeste n: "
    text2: .asciiz "Sirul lui Fibonacci pana la n-lea termen: "
    text3: .asciiz " "

.text

fibonacci:
    addi $sp, $sp, -12  #Respectare calling convention
    sw $ra, 0($sp)      #Salvare pe stiva adresa return
    sw $s0, 4($sp)      #Salvare registrii protejati
    sw $s1, 8($sp)

    move $s0, $a0       #Stocam parametrul a0 in s0

    addi $t0, $zero, 1  #Folosim pentru verificare (setat pe 1)

    bne $a0, $t0, continue      #Verificam daca a0 este diferit de 1
         addi $v0, $zero, 1     #Daca este 1 returnam valoarea 1
         jal return_label

    continue:
        add $t0, $zero, $zero   #Folosim pentru verificare(setat pe 0)
        bne $a0, $t0, continue2 #Verificam daca e diferit de 0
            addi $v0, $zero, 1  #Daca este 0 returnam 1
            jal return_label

    continue2:
        addi $a0, $s0, -1       #Aplicam formula return fibonacci(n-1) + fibonacci(n-2)
        jal fibonacci           #Apel pentru n-1
        addi $sp, $sp, -4       #Salvam pe stiva valoarea returnata
        sw $v0, 0($sp)

        addi $a0, $s0, -2       #Apel pentru n-2
        jal fibonacci
        lw $s1, 0($sp)          #Luam de pe stiva valoare returnata de n-1
        add $v0, $v0, $s1       #Facem suma
        addi $sp, $sp, 4        #Refacem stiva
        

        return_label:           #Respectare calling convention
            lw $ra, 0($sp)      #Refacere adresa de return
            lw $s0, 4($sp)      #Refacere registrii protejati
            lw $s1, 8($sp)
            addi $sp, $sp, 12   #Refacere stiva
            jr $ra              #Jump la adresa de return

.end fibonacci      

main:
    li $v0, 4      #Afisare text1
    la $a0, text1
    syscall

    li $v0, 5       #Citire n
    syscall
    move $s0, $v0   #Salvam valoare citita intr-un registru protejat
    
    li $v0, 4       #Afisare text2
    la $a0, text2
    syscall
    
    add $s1, $zero, $zero   #Setare registru s1 pe zero
    loop:                   #do{
        move $a0, $s1       
        jal fibonacci       #apel fibonacci(s1)

        move $a0, $v0       #Afisare valoarea returnata
        addi $v0, $zero, 1
        syscall

        addi $v0, $zero, 4  #Afisare spatiu intre valori
        la $a0, text3
        syscall

        addi $s1, $s1, 1    #s1++

        bne $s1, $s0, loop  # }while(s1 != s0);

    addi $v0, $zero, 10     #End program
    syscall


.end main
