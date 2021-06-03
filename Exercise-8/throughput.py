throughput = 0
total_throughput = 0
size = total_size = 0
file = open("out1.tr","r")
time = 0
col = []
for line in file:
	a = line.split(" ")
	a.pop(6)
	col.append(a)

for x in col:
	if((x[0] == "r") and (x[2] == "1") and (x[3] == "2")):
		size = size + int(x[5])
		if(time == 0.0):
			time = float(x[1])
	if(x[0] == "r"):
		total_size = total_size + int(x[5])
throughput = float(size * 8) / (float(col[-1][1]) - time)
throughput = throughput / 1000000
print("Between 1 and 2...")
print("Total size is : ",size)
print("Total time is : ",float(col[-1][1]) - time)
print("Throughput is : ", throughput)
print("________________")
total_throughput = (float(total_size) * 8) / (float(col[-1][1]))
total_throughput = total_throughput / 1000000
print("Total throughput is : ", total_throughput)