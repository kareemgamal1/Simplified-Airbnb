import os
import pandas as pd



placeCountry,placeCity,placeStreet,placeView,placePayment,placeRoom,placePrice,placeNoOfRooms,placeDiscount,placeOwner,placeStartDate,placeEndDate,placeEndDay,placeEndMonth,placeDuration=([] for i in range(15))

rootdir = '../Data/place'

places=[]
for subdir, dirs, files in os.walk(rootdir):
    for file in files:
        places.append(os.path.join(subdir, file))
# print(places)        

for place in places:
    placeFile = open(place, "r")
    lines = placeFile.readlines()
    lines = [line.rstrip() for line in lines]
    placeCountry.append(lines[0])    
    placeCity.append(lines[1])  
    placeStreet.append(lines[2])  
    placeView.append(lines[3])  
    placePayment.append(lines[4])  
    placeRoom.append("Room" if (lines[5]=='1') else "Apartment")  
    placePrice.append(lines[6]) #bar
    placeNoOfRooms.append(lines[7])  
    placeDiscount.append(lines[8]) 
    placeOwner.append(lines[10])
    startDate='2022'+'-'+lines[12]+'-'+lines[11]
    placeStartDate.append(startDate) 
    endDate='2022'+'-'+lines[14]+'-'+lines[13]
    placeEndDate.append  (endDate) 
    placeDuration.append(lines[15])
    
# print(placeStartDate)
pd.set_option("display.max_columns", 100)
PlaceDf=pd.DataFrame(
    {
      'country': placeCountry,
      'city': placeCity,
      'street': placeStreet,
      'view': placeView,
      'method': placePayment,
      'room': placeRoom,
      'price': placePrice,
      'rooms': placeNoOfRooms,
      'discount': placeDiscount,
      'owner': placeOwner,
      'startDate': placeStartDate,
      'endDate': placeEndDate,
      'duration': placeDuration,
      }
    )
print(PlaceDf)