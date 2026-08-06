#import numpy as np
#import pickle

#import struct

dir = 'C:/Users/FR22048/DEV/epan/wav/'

def convert(bank,file_in, file_out, table):
    fin = open( dir + bank + '/'  + file_in, 'rb')
    fout = open( dir + bank + '/' + file_out, 'w')
    print(file_out)

    fout.write("const int16_t " + table + "[] = {\n")

    data = fin.read(44)  # skip WAV header
    data = fin.read(2)
    nb=0
    while data:
        nb = nb + 1
        if (nb==1):
            fout.write("  ")
        i = int.from_bytes( data , byteorder='little', signed=True)
#        str = "0x{0:x}, ".format(i)
        str = "{0}, ".format(i)
        fout.write( str )
        if (nb==10):
            nb = 0
            fout.write("\n")
        data = fin.read(2)


    fout.write("};")

    fin.close()
    fout.close()


def convert_sound(bank,sound):
    convert (bank, sound + '.wav', sound + '.h', sound + "_wav")


bank = "bank2"
convert_sound(bank,'s00')
convert_sound(bank,'s01')
convert_sound(bank,'s02')
convert_sound(bank,'s03')
convert_sound(bank,'s04')
convert_sound(bank,'s05')
convert_sound(bank,'s06')
convert_sound(bank,'s07')
convert_sound(bank,'s08')
convert_sound(bank,'s09')
convert_sound(bank,'s10')
convert_sound(bank,'s11')
convert_sound(bank,'s12')
convert_sound(bank,'s13')

# bank = "."
# convert_sound(bank,'clic1')
# convert_sound(bank,'clic2')
# convert_sound(bank,'error')
