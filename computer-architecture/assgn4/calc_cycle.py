import sys
import re
fil = sys.argv[1]
f = open(fil, 'r')
red = f.read()
red = red.split('\n')
res = []
start = 0
for i in red:
    if "jal main" in i:
        start = 1
    if start == 1:
        if re.findall (r'\[0x[0-9a-fA-F]+\]', i):
            res.append(i)

#for line in res:
#    print(line)

#Single Cycle
sci_cycles = len(res)*5
print "The number of cycles in Single Cycle Implementation is: ", sci_cycles

#Multi Cycle
mci_cycles = 0
for line in res:
    line = line.split(" ")
    if "lw" in line:
        mci_cycles = mci_cycles + 5
    elif "sw" in line:
        mci_cycles = mci_cycles + 4
    elif ("beq" in line) or ("j" in line) or ("jal" in line) or ("jr" in line) or ("bne" in line) or ("bgez" in line):
        mci_cycles = mci_cycles + 3
    else:
        mci_cycles = mci_cycles + 4
print "The number of cycles in Multi Cycle Implementation is: ", mci_cycles
print "Their ratio is: ", sci_cycles*1.0/mci_cycles*1.0

    
