'''
/*=============================================================================
| Assignment: pa02 - Calculating an 8, 16, or 32 bit
| checksum on an ASCII input file
|
| Author: Trisha Esther Ruiz
| Language: Python
|
| To Compile:
| python pa02.py //Caution - expecting input parameters
|
| To Execute:
| python-> python pa02.py inputFile.txt 8

| where inputFile.txt is an ASCII input file
| and the number 8 could also be 16 or 32
| which are the valid checksum sizes, all
| other values are rejected with an error message
| and program termination
|
| Note: All input files are simple 8 bit ASCII input
|
| Class: CIS3360 - Security in Computing - Fall 2022
| Instructor: McAlpin
| Due Date: p11/27/2022
+=============================================================================*/
'''
import sys
out = sys.stdout
err = sys.stderr

def numToPad(hexa, size):
	hexa = 	hexa.replace('58','')
	bitSize = len(hexa) * 4
	numPads = bitSize % size
	if(numPads == 0):
		return int(numPads)
	numPads = size - numPads
	numPads = numPads /8
	return int(numPads)

def pad(hexa, numX):
	for i in range(numX):
		hexa += '58'
	return hexa
	
def asciiToHex(ascii, size):
	ans = ''
	temp = ''
	for char in ascii:
		temp = str(hex(ord(char)))
		if(temp == '0xa'):
			ans += '0A'
		else:
			temp = temp[temp.index('x')+1:]
			ans += temp
	
	ans = pad(ans, numToPad(ans, size))
	return ans
	
def hexLookUp(hexa):
	hexa = hexa.upper()
	if(hexa == '1'):
		return '0001'
	if(hexa == '2'):
		return '0010'
	if(hexa == '3'):
		return '0011'
	if(hexa == '4'):
		return '0100'
	if(hexa == '5'):
		return '0101'
	if(hexa == '6'):
		return '0110'
	if(hexa == '7'):
		return '0111'
	if(hexa == '8'):
		return '1000'
	if(hexa == '9'):
		return '1001'
	if(hexa == 'A'):
		return '1010'
	if(hexa == 'B'):
		return '1011'
	if(hexa == 'C'):
		return '1100'
	if(hexa == 'D'):
		return '1101'
	if(hexa == 'E'):
		return '1110'
	if(hexa == 'F'):
		return '1111'
	return '0000'
	
def hexToBinary(hexa):
	ans = ''
	for char in hexa:
		ans += hexLookUp(char)
	return ans
def asciiToBinary(ascii, size):
	ans = asciiToHex(ascii, size)
	ans = hexToBinary(ans)
	return ans
def checksumCalc(input, size):
	binary = asciiToBinary(input, size)
	
	i = 0
	temp = ''
	ans = 0
	
	for char in binary:
		temp += char
		i += 1

		#ADD MOD
		if (i%size == 0):
			ans += int(temp, 2)
			temp = ''
	
	ans = ans % (2**size)
	
	temp = hex(ans)
	temp = temp[temp.index('x')+1:]
	
	return temp
			



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

def printX(numX):
	for i in range(numX):
		out.write('X')
def main():

	#DEFINING VARIABLES
	inputFileName = ""
	size = -1
	checksum = ''

	#CREATING FILE
	inputFileName = str(sys.argv[1])	
	size = int(sys.argv[2])

	#READ INPUT FILE
	inputFile = open(inputFileName, 'r')
	inputString = inputFile.read()


	#CHECK FOR INVALID CHECKSUM
	if(size != 8 and size != 16 and size != 32):
		err.write("Valid checksum sizes are 8, 16, or 32\n")
		
	else:
		#ECHO INPUT FILE
		out.write("\n")
		out.write(echo(inputString))

		#SHOW X PADS
		numX = numToPad(asciiToHex(inputString, size), size)
		printX(numX)

		#PRINTCHECKSUM
		checksum = checksumCalc(inputString,  size)
		characterCnt = len(inputString) + numX
		out.write("\n{:>2} bit checksum is {:>8} for all {:>4} chars\n".format(size, checksum, characterCnt))
		#printf("%2d bit checksum is %8lx for all %4d chars\n", size, checksum, characterCnt)


	
main()

'''
/*=============================================================================
| I Trisha Esther Ruiz (tr799219) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
CIS3360-McAlpin PA 2 4
| that any violation of the above terms will be treated as academic dishonesty.
+============================================================================*/
'''
