import commands

inputfiles = ['cc1.din', 'spice.din', 'tex.din']
missrates = []
for fil in inputfiles:
	tempmissrates = []
	outputs = []
	cachesize = 2
	for i in xrange(1,9):
		cachesize = cachesize*2
		tmp = commands.getstatusoutput('./d4-7/dineroIV -l1-usize '+ str(cachesize) +'k -l1-ubsize 16 -l1-uassoc 2 -l1-uwalloc a -l1-uwback a -informat d -l1-uccc < id4-traces/' + str(fil))
		outputs.append(tmp)
	for i in xrange(0,8):
		temp = outputs[i][1].split("\n")[35].split("\t")[1].strip()
		tempmissrates.append(temp)
	missrates.append(tempmissrates)

it = 0
for i in missrates:
	print inputfiles[it]
	it = it + 1
	cache_size = 4
	for j in i:
		print str(cache_size) + ", " + j
		cache_size = cache_size * 2
	print "\n"