from random import randint

alfabeto = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"]

string = ""
for k in range(10000):
    for i in range(0, len(alfabeto)):
        for j in range(0, len(alfabeto)):
            string += alfabeto[randint(0, len(alfabeto) - 1)] + alfabeto[randint(0, len(alfabeto) - 1)] + " "
            string += alfabeto[i] + alfabeto[j] + " "

file = open("testFiles/file_prova_perm.txt", "w")
file.write(string)
file.close()
