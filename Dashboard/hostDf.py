import os
import pandas as pd



hostFirst,hostLast,hostEmail,hostNumber,hostNationality,hostGender,hostAge=([] for i in range(7))

hostFilesPath="../Data/host"


host_dir=os.listdir(hostFilesPath)
print(host_dir)
for hostname in host_dir:
    f=os.path.join(hostFilesPath,hostname)
    if os.path.isfile(f):
        hostFile = open(hostFilesPath+"/"+hostname, "r")
        lines = hostFile.readlines()
        lines = [line.rstrip() for line in lines]
        hostFirst.append(lines[1])
        hostLast.append(lines[2])
        hostEmail.append(lines[3])
        hostNumber.append(lines[4])
        hostNationality.append(lines[5])
        hostGender.append(lines[6])
        hostAge.append(lines[7])
        #iterate over a file, put every line in its respectable list


pd.set_option("display.max_columns", 100)
HostDf=pd.DataFrame(
    {
      'fname': hostFirst,
      'lname': hostLast,
      'email': hostEmail,
      'number': hostNumber,
      'nationality': hostNationality,
      'gender': hostGender,
      'age': hostAge 
      }
    )













