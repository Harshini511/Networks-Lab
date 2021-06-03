file = open("out1.tr","r")
count = 0
for line in file:
	col = []
	col = line.split()
	if(col[0] == "d"):
		#print("Packet number : ",col[11])
		count = count + 1
print("The number of dropped packets is : ", count)
