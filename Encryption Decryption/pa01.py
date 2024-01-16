'''
/*=============================================================================
| Assignment: pa01 - Encrypting a plaintext file using the Vigenere cipher
|
| Author: Trisha Esther Ruiz
| Language: c, c++, Java, go, python
|
| To Compile: javac pa01.java
| gcc -o pa01 pa01.c
| g++ -o pa01 pa01.cpp
| go build pa01.go
| python pa01.py
|
| To Execute: java -> java pa01 kX.txt pX.txt
| or c++ -> ./pa01 kX.txt pX.txt
| or c -> ./pa01 kX.txt pX.txt
| or go -> ./pa01 kX.txt pX.txt
| or python -> python pa01.py kX.txt pX.txt
| where kX.txt is the keytext file
| and pX.txt is plaintext file
|
| Note: All input files are simple 8 bit ASCII input
|
| Class: CIS3360 - Security in Computing - Fall 2022
| Instructor: McAlpin
| Due Date: 10/16/2022
|
+=============================================================================*/
'''

import sys
out = sys.stdout

def strip(message):
	lowerLetters = "abcdefghijklmnopqrstuvwxyz"
	onlyLetters = ""

	for letter in message:
		if letter in lowerLetters:
			onlyLetters += letter
	return onlyLetters

def pad(message, arr, key):
	i = 0
	j = 0

	#taking only letters in message
	while(i < len(arr) and i < len(message)):
		arr[i] = message[i]
		i += 1
	if (key == True):
		#padding rest of key
		while(i < len(arr)):
			if (j == len(message)):
				j = 0
			arr[i] = message[j]
			i += 1
			j+= 1
	else:
		#padding x
		while(i < len(arr)):
			arr[i] = "x"
			i += 1

def encrypt(plain, key, cipher):
	i = 0
	for letter in plain:
		cipher[i] = chr((((ord(plain[i])-97)+(ord(key[i])-97) )% 26)+97)
		i += 1

def echo(arr):
	str = ""
	i = 0
	
	for letter in arr:
		if i == 80:
			str += "\n"
			i = 0
		str += letter
		i += 1
	return str
		
	
def main():

	#DEFINING VARIABLES
	keyFileName = ""
	
	key = ["" for i in range(512)]
	plain = ["" for i in range(512)]
	ciphertext = ["" for i in range(512)]
	
	plainString = ""
	keyString = ""

	#CREATING FILE
	keyFileName = str(sys.argv[1])
	keyFile = open(keyFileName, 'r')
	
	plainTextFileName = str(sys.argv[2])
	plainTextFile = open(plainTextFileName, 'r')

	#LOWER CASE
	plainString = plainTextFile.read().lower()
	keyString = keyFile.read().lower()

	#ONLY LETTERS
	plainString = strip(plainString)
	keyString = strip(keyString)

	#pad key into a array
	pad(keyString, key, True)
	pad(plainString, plain, False)

	#encrypt
	encrypt(plain, key, ciphertext)

	#output

	out.write("\n\nVigenere Key:\n\n"+echo(keyString)+"\n")
	out.write("\n\nPlaintxt:\n\n"+echo(plain)+"\n")
	out.write("\n\nCiphertext:\n\n"+echo(ciphertext)+"\n")

	plainTextFile.close()
	keyFile.close()

main()