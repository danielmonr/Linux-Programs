import os
file_name = raw_input("File to decypher? ")
try:
    cypher_file = open(file_name, 'r')
except IOError:
    print("Creating File...")
    cypher_file = open(file_name, 'w+')
    cypher_file.close()
    cypher_file = open(file_name, 'r')
cypher = cypher_file.read()
key = raw_input("Key? ")
text = ""
char = ''
j = 0
val = 0
for i in range(0, len(cypher)):
    char = cypher[i]
    if char == '\n' or char == ' ':
        text += char
    elif j >= len(key):
        j = 0
        val = ord(cypher[i])-ord(key[j])
        if val < 0:
            val = 255+val
        text += chr(val)
    else:
        val = ord(cypher[i])-ord(key[j])
        if val < 0:
            val = 255+val
        text += chr(val)

cypher_file.close()
write = input ("Overwrite " + file_name +"? ")
if write:
    text_file = open(file_name, 'w')
else:
    text_file = open("uncyphered.txt", 'w+')
text_file.write(text)
print "Done"
