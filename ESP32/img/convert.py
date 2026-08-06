
dir = 'C:/Users/FR22048/DEV/epan/img/'

def convert(file_in, file_out, table):
    fin = open( dir  + '/'  + file_in, 'rb')
    fout = open( dir  + '/' + file_out, 'w')
    print(file_out)

    fout.write("const  uint8_t  " + table + "[] = {\n")

    data = fin.read(1)
    nb=0
    size = 0
    while data:
        nb = nb + 1
        size += 1
        if (nb==1):
            fout.write("  ")
        # i = int(data)
        ss = "0x{0:02x}, ".format( data[0] )
        fout.write( ss )
        if (nb==16):
            nb = 0
            fout.write("\n")
        data = fin.read(1)
    fout.write("};")
    fout.write("\n\n\n")        
    fout.write( "size_t " + table + "Len = " + str(size) + ";"  )


    fin.close()
    fout.close()



convert('IMGmetronome.png','IMGmetronome.h','IMGmetronome')

