import numpy as np
import pandas as pd
import solarpy
import datetime
import matplotlib.pyplot as plt

# Direction normal to the plane in North,East,Down coords
vnorm = np.array([0, 0, -1])

# Height relative to sea level = 0
h = 114

# latitude of UCLA
lat = 34

# initialize day
today = pd.to_datetime('today').date()
day = pd.date_range(today,periods=24*60,freq='min')

# Get irradiance for each minute, m in day
G = pd.DataFrame({'G':[solarpy.irradiance_on_plane(vnorm, h, m, lat) for m in day]},index=day)

# plotting
G.plot()
plt.show()
