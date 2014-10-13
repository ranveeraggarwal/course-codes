import commands

inputfiles = ['cc1.din', 'spice.din', 'tex.din']
missrates = []
blocksize = [1,2,4,8,16,32,64,128,256]
for fil in inputfiles:
	tempmissrates = []
	outputs = []
	for p in blocksize:
		tmp = commands.getstatusoutput('./d4-7/dineroIV -l1-usize 8k -l1-ubsize ' + str(4*p) + ' -l1-uassoc 2 -l1-uwalloc a -l1-uwback a -informat d -l1-uccc < id4-traces/' + str(fil))
		outputs.append(tmp)
	for i in xrange(0,9):
		temp = outputs[i][1].split("\n")[35].split("\t")[1].strip()
		tempmissrates.append(temp)
	missrates.append(tempmissrates)

it = 0
for i in missrates:
	print inputfiles[it]
	it = it + 1
	block_size = 1
	for j in i:
		#print str(block_size) + ", " + j
		print j
		block_size = block_size * 2
	print "\n"