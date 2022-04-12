import numpy as np
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
date = datetime.datetime(2020, 4, 11, 0, 0)

# adding minutes
dateArray = np.array([date + datetime.timedelta(minutes=i) for i in range(1440)])

G = np.array([solarpy.irradiance_on_plane(vnorm, h, dateArray[i], lat) for i in range(1440)])
# vnorm, h, date, lat

# plotting
t = np.array([i for i in range(1440)])
plt.plot(t, G)
plt.show()
