# do{
#     t2 = *t0
#     s0+=t2;
#     t1--;
#     t0 = *(t0 + 1)
# }while(t1 != 0)


#zona de date
.data
    len = 6
    a: .word 2, 23, 14, 7, 9, 10


#zona de cod
.text

main:
    la $t0, a                   #pune adresa de inceput a lui a in registrul t0
    li $t1, len                 #pune in registrul t1 valoare 6
    add $s0, $zero, $zero       #ne asiguram ca valoare registrului s0 este 0


    start_loop:
        lw $t2, 0($t0)          #luam primi 4 octeti stocati la adresa t0, cu alte cuvinte prima valoare din vector
        add $s0, $s0, $t2       #adunam la s0 valoarea respectiva
        addi $t1, $t1, -1       #scadem din t1 
        addi $t0, $t0, 4        #adunam la adresa 4 octeti pentru a ajunge la urmatorul element din vector
        bne $t1, $zero, start_loop #sarim inapoi la startloop daca t1 e diferit de 0
    la $t0, a                   #punem inapoi in t0 adresa lui a... poate sa lipseasca in cazul acesta

    li $v0, 1                   #punem in v0 o valoare imediata. Corespunde comenzii de afisare intreg
    move $a0, $s0               #mutam din s0 in a0 suma finala. valoare din a0 va fi afisata la consola
    syscall                     #apelam functie system cu parametrii respectivi

    li $v0, 10                  #valoarea 10 corespunde cu end program
    syscall                     #apelam syscall din nou pentru a incheia programul

.end main
