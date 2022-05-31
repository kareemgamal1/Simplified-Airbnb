import os
import pandas as pd



travelerFirst,travelerLast,travelerEmail,travelerNumber,travelerNationality,travelerGender,travelerAge=([] for i in range(7))

travelerFilesPath="../Data/traveller"


traveler_dir=os.listdir(travelerFilesPath)
print(traveler_dir)
for travelername in traveler_dir:
    f=os.path.join(travelerFilesPath,travelername)
    if os.path.isfile(f):
        travelerFile = open(travelerFilesPath+"/"+travelername, "r")
        lines = travelerFile.readlines()
        lines = [line.rstrip() for line in lines]
        travelerFirst.append(lines[1])
        travelerLast.append(lines[2])
        travelerEmail.append(lines[3])
        travelerNumber.append(lines[4])
        travelerNationality.append(lines[5])
        travelerGender.append(lines[6])
        travelerAge.append(int(lines[7]))
        #iterate over a file, put every line in its respectable list


pd.set_option("display.max_columns", 100)
TravelerDf=pd.DataFrame(
    {
      'fname': travelerFirst,
      'lname': travelerLast,
      'email': travelerEmail,
      'number': travelerNumber,
      'nationality': travelerNationality,
      'gender': travelerGender,
      'age': travelerAge 
      }
    )
TravelerDf['age_group'] = pd.cut(TravelerDf['age'],bins=[0,17,59,120], labels=["0-17","18-59","60+"])
print(TravelerDf.head())












