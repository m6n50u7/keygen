# keygen
make one pseudo-random long key using multiple small memorable keys.<br />
instead of saving a large enctypted key file that you may lose once you lose your device, why don't you just remeber few passwords and use them every time you need to restore your key?<br />
using this key generator you can for example use three passwords with size of 5 byte, 8 byte and 9 bytes to get a key with the size of 5 * 8 * 9 = 360 bytes.<br />
how to compile for linux:
>gcc keygen.c -o keygen<br />

how to use the tool:<br/>
to generate a key and print it:<br/>
>keygen Opt Key1 Key2 ...etc<br />
to generate a key file:<br />
>keygen Opt Key1 Key2 ...etc > key.bin<br />
# Currently available options:
r: replace any null byte in the code with other bytes (0x01, 0x02 ... etc).<br />
l: let the null bytes be inside the key.<br />
i: ignore the null bytes. this would shrink the result key.<br />
# Notes:
you have to chose subkeys that their sizes are even to get the longest possible pseudo-random keys.<br />
