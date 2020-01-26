coordinates = []
x = [int(i) for i in input("X:").split(",")]
y = [int(i) for i in input("Y:").split(",")]
for i in range(1,len(x)):
    coordinates += [[x[i],y[i]]]
coordinatesData = str(coordinates)


processedData = "";
#cost[1][2] = 3;
data = input()
while data != "":
    command = data.split("]")
    index1 = str(int(command[0][5:])-1)
    index2 = str(int(command[1][1:])-1)

    output1=command[0][:5]+index1+"]"+command[1][0]+index2+"]"+command[2]
    output2=command[0][:5]+index2+"]"+command[1][0]+index1+"]"+command[2]

    processedData+=output1+"\n"
    processedData+=output2+"\n"

    data = input()

print("\n\n\n")
print(coordinatesData.replace("[","{").replace("]","}"))
print(processedData)
with open("./NodesProcessed.txt","w+") as outfile:
     outfile.write(processedData)
