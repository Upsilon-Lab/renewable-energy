from traceback import print_tb
import numpy as np
import pandas as pd
import solarpy as sp
import matplotlib.pyplot as plt


# Calculate Solar Irradiance
# --------------------------

# Direction normal to the plane in North,East,Down coords
direction_labels = ['North','East','South','West','Up','Tracking']
vnorm_arr = np.array([[1,0,-1],[0,1,-1],[-1,0,-1],[0,-1,-1],[0,0,-1]])

# Height relative to sea level = 0
h = 114

# latitude of UCLA
lat = 34

# initialize day
today = pd.to_datetime('today').date()
day = pd.date_range(today,periods=24*60,freq='min')

# Get irradiance for each minute, m in day for 5 fixed directions
G = pd.DataFrame({direction:[sp.irradiance_on_plane(v, h, m, lat) for m in day] for v,direction in zip(vnorm_arr,direction_labels)},index=day)
# Get beam irradiance as a proxy for tracked
G[direction_labels[-1]]=[sp.beam_irradiance(h,m,lat)for m in day]
G = G[G.mean(axis=1)!=0]

# Calculate power output from solar panel
# ---------------------------------------

# Surface area converted to m^2
s = 13.23 * 8.07 * .0254**2
# Efficiency of 20%
eff = 10/(G.values.max()*s)
print('Efficiency needed to reach max 10W for tracking: {:.2f}%'.format(eff*100))
P = G*s*eff

# Calculate the power gain from tracking w.r.t. the other directions


P_diff = [P['Tracking'] - P[label] for label in P.keys()[0:-1]]
P_diff = pd.concat(P_diff,axis=1,keys=P.keys()[0:-1])
print('Average gain in power from tracking:')
print(P_diff.mean())

# plotting
# --------
fig_dir = 'figures/'

# Plot solar irradiance and power output of the solar panel
fig,axs = plt.subplots(1,2,figsize=(10,4))
G.plot(ax=axs[0]).legend(loc='upper right')
axs[0].set_title('Daily Solar Irradiance')
axs[0].set_xlabel('$t\ [minutes]$')
axs[0].set_ylabel('$G\ [W/m^2]$')
P.plot(ax=axs[1]).legend(loc='upper right')
axs[1].set_title('Solar Panel {:.2f}% Efficiency'.format(eff*100))
axs[1].set_xlabel('$t\ [minutes]$')
axs[1].set_ylabel('$P\ [W]$')

plt.savefig(fig_dir+'solar_irradience_power_{:.2f}eff.png'.format(eff*100))

fig,ax = plt.subplots(figsize=(6,4))
P_diff.plot(ax=ax).legend(loc='upper right')
ax.set_title('Power Gain From Tracking {:.2f}% Efficiency'.format(eff*100))
ax.set_xlabel('$t\ [minutes]$')
ax.set_ylabel('$\Delta P\ [W]$')

plt.savefig(fig_dir+'power_gain_{:.2f}eff.png'.format(eff*100))
