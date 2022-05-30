import os
import numpy as np
import pandas as pd
import hostDf as hdf
import travelerDf as tdf



pd.set_option("display.max_columns", 100)
frames=[hdf.HostDf,tdf.TravelerDf]
UserDf=pd.concat(frames)

I=pd.Index(["Hosts","Travelers"])

travelerAgee=tdf.TravelerDf['age'].mean()
travelerNationalityy=tdf.TravelerDf['nationality'].value_counts().idxmax()
hostAgee=hdf.HostDf['age'].mean()
hostNationalityy=hdf.HostDf['nationality'].value_counts().idxmax()


usersStatistics = pd.DataFrame(data=[["Traveler",travelerAgee,travelerNationalityy],["Host",hostAgee,hostNationalityy]], columns=[' ','Mean age','Most nationality'])

print(usersStatistics)

# combinedStatistics=pd.DataFrame({
# ('Actual class', 'Cat'): {('Predicted class', 'Cat'): 5, ('Predicted class', 'Dog'): 2, ('Predicted class', 'Rabbit'): 0},
# ('Actual class', 'Dog'): {('Predicted class', 'Cat'): 3, ('Predicted class', 'Dog'): 3, ('Predicted class', 'Rabbit'): 2},
# ('Actual class', 'Rabbit'): {('Predicted class', 'Cat'): 0, ('Predicted class', 'Dog'): 1, ('Predicted class', 'Rabbit'): 11},
#     })
# print(combinedStatistics)











