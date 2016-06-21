›addi $sp, $zero, 3
addi $29, $0, 3   # $sp = $29 and $zero = $0 two forms are both OK
addi $1, $2, 0x500 #comments, 0x500 is hex
addi $1, $2, 500 #comments, 500 is decimal
halt ## everything after '#' is ignored
