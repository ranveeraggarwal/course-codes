f = open("output3.txt", 'r')
f = f.read()

objects = f.split("l1-ucache")

index = 1

for obj in objects[1:]:
	if (int(obj.split("\n")[9].split("\t")[1].strip()) > 0) or (int(obj.split("\n")[10].split("\t")[1].strip()) > 0):
		print index
		break
	index = index + 1