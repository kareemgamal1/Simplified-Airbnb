import os
import pandas as pd
import hostDf as hdf
import travelerDf as tdf



pd.set_option("display.max_columns", 100)
frames=[hdf.HostDf,tdf.TravelerDf]
UserDf=pd.concat(frames)
print(UserDf)











