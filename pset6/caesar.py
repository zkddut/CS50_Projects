#!/usr/bin/python -tt

import sys

def convert_to_cipher(key, plaintext):
	cipher = ""
	for c in plaintext:
		cipher += chr(ord(c) + int(key))
	return cipher
###

# This basic command line argument parsing code is provided and
# calls the print_words() and print_top() functions which you must define.
def main():
	if len(sys.argv) != 3:
		print ('usage: ./caesar.py plaintext key')
		sys.exit(1)

	key = sys.argv[1]
	plaintext = sys.argv[2]
	print (convert_to_cipher(key, plaintext))

if __name__ == '__main__':
  main()