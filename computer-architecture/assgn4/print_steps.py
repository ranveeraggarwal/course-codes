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

print(len(res))
