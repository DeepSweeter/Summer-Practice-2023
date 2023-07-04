#! python
import sys, os, time
import subprocess


# Necesita ca terminalul in care va aflati sa fie in acelasi folder cu fisierele de design si test
# Ex rularw: python3 IcarusCompiler.py design.sv testbench.sv (Scriptul si restul fisierelor ar trebuii sa fie in acelasi folder)
# Ar trebuii sa ruleze cu oricate argumente, desi nu e testat cu mai mult de 2.
# Totodata nu am verificat daca merge si cu fisiere care au fost adaugate cu directiva include. 
# A nu se rula intr-un folder cu mai multe fisiere .vcd

if __name__ == '__main__':
    currentFolder = os.getcwd()
    arguments = ""
    for i in range(1, len(sys.argv)):
        arguments += f"{sys.argv[i]} "
    try:
        subprocess.Popen(f"iverilog -o {sys.argv[1].split('.')[0]} {arguments} ",  stderr=subprocess.STDOUT).wait()
        subprocess.Popen(f"vvp -N {sys.argv[1].split('.')[0]}", stderr=subprocess.STDOUT).wait()
    except subprocess.CalledProcessError as e:
        print("Eroare la compilare icarus: " + e)
    for file in os.listdir(currentFolder):
        if file.endswith(".vcd"):
            try:
                subprocess.Popen(f"gtkwave {file}", stderr=subprocess.STDOUT).wait()
            except subprocess.CalledProcessError as e:
                print("Eroare la gtkwave: " + e)
            break