import os
import pandas as pd



placeCountry,placeCity,placeStreet,placeView,placePayment,placeRoom,placePrice,placeNoOfRooms,placeDiscount,placeID,placeOwner,placeStartDate,placeEndDate,placeEndDay,placeEndMonth,placeDuration=([] for i in range(16))

rootdir = '../Data/place'
currentPlace=""
hostEm,hostPlaces,noOfPlaces=[],[],[]

places=[]
for subdir, dirs, files in os.walk(rootdir):
    hostEm.append(subdir)
    hostPlaces.append(files)
    for file in files:
        places.append(os.path.join(subdir, file))
        # print(file)
        
hostPlaces.pop(0)

for hostPlace in hostPlaces:
    noOfPlaces.append(len(hostPlace))

hostEm.pop(0)
hostEm = [x.replace(' ', '').replace('../Data/place\\', '') for x in hostEm]

hostPlacesDf=pd.DataFrame(
        {
      'host':hostEm,
      'noOfPlaces':noOfPlaces
        }
    )


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
    placePrice.append(int(lines[6])) #bar
    placeNoOfRooms.append(int(lines[7]))  
    placeDiscount.append(int(lines[8])) 
    placeID.append(int(lines[9]))
    placeOwner.append(lines[10])
    startDate='2022'+'-'+lines[12]+'-'+lines[11]
    placeStartDate.append(startDate) 
    endDate='2022'+'-'+lines[14]+'-'+lines[13]
    placeEndDate.append(endDate) 
    placeDuration.append(int(lines[15]))
    
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
      'id':placeID,
      'owner': placeOwner,
      'startDate': placeStartDate,
      'endDate': placeEndDate,
      'duration': placeDuration,
      }
    )

count = (PlaceDf['discount'] != 0).sum()
newDf=PlaceDf[PlaceDf['discount']!=0] 
mean=newDf['discount'].mean()
placeStatistics = pd.DataFrame(data=[[count,mean]], columns=['Discounts','Avg Discount'])
print(placeStatistics)
print(count)
# print(PlaceDf)