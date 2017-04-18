file_name = raw_input("File to cypher? ")
with open(file_name, 'r') as text_file:
    text = text_file.read()
key = raw_input("Key? ")
cypher = ""
char = ''
j = 0
for i in range(0, len(text)):
    char = text[i]
    if char == '\n' or char == ' ':
        cypher += char
    elif j >= len(key):
        j = 0
        val = (ord(text[i])+ord(key[j])) % 255
        cypher += chr(val)
    else:
        val = (ord(text[i])+ord(key[j])) % 255
        cypher += chr(val)

text_file.close()
write = input ("Overwrite " + file_name +"? ")
if write:
    cypher_file = open(file_name, 'w')
else:
    cypher_file = open("cyphered.txt", 'w+')
cypher_file.write(cypher)
print "Done"
