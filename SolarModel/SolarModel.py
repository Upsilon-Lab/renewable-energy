import numpy as np
import pandas as pd
import solarpy
import datetime
import matplotlib.pyplot as plt

vnorm = np.array([0, 0, -1])
# North, East, Down
h = 114
# altitude 0 = sea level
lat = 34
# latitude of UCLA

# initialize day
today = pd.to_datetime('today').date()
day = pd.date_range(today,periods=24*60,freq='min')

# Get irradiance for each minute, m in day
G = pd.DataFrame({'G':[solarpy.irradiance_on_plane(vnorm, h, m, lat) for m in day]},index=day)

# plotting
G.plot()
plt.show()
