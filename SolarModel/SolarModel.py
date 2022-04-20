import numpy as np
import pandas as pd
import solarpy as sp
import matplotlib.pyplot as plt
from datetime import datetime

# Calculate Solar Irradiance
# --------------------------

# Direction normal to the plane in North,East,Down coords
direction_labels = ['North','East','South','West','Up','Tracking']
vnorm_arr = np.array([[1,0,-1],[0,1,-1],[-1,0,-1],[0,-1,-1],[0,0,-1]])

# Height relative to sea level = 0
h = 114

# latitude of UCLA
lat = 34

# start date, stop date (stops at T00:00 on the stop date)
spring = [np.datetime64('2022-03-01'),np.datetime64('2022-06-01')]
# Get time index for spring months MAM by minute
time_MAM = pd.date_range(spring[0],spring[1],freq='min')

# Get irradiance for each minute, m in day for 5 fixed directions
G = pd.DataFrame({direction:[sp.irradiance_on_plane(v, h, m, lat) for m in time_MAM] for v,direction in zip(vnorm_arr,direction_labels)},index=time_MAM)
# Get beam irradiance as a proxy for tracked
G[direction_labels[-1]]=[sp.beam_irradiance(h,m,lat)for m in time_MAM]
G = G[G.mean(axis=1)>0]
# Average for a daily solar irradiance
G = G.groupby(G.index.time).mean()
# Format index as time in HH:MM
idx = G.index.to_numpy()
for i in range(len(idx)):
    idx[i] = idx[i].strftime('%H:%M')
G.set_index(idx,inplace=True)

# Calculate power output from solar panel
# ---------------------------------------

# Surface area converted to m^2
s = 13.23 * 8.07 * .0254**2
# Efficiency needed to reach 10W
eff = 10/(G.max()*s)

print('Efficiency needed to reach max 10W:')
print(eff*100)

P = G*s*eff['Tracking']

# Calculate the power gain from tracking w.r.t. the other directions
P_diff = [P['Tracking'] - P[label] for label in P.keys()[0:-1]]
P_diff = pd.concat(P_diff,axis=1,keys=P.keys()[0:-1])
print('Average gain in power from tracking:')
print(P_diff.mean())

# plotting
# --------
fig_dir = 'figures/'

fig,axs = plt.subplots(1,2,figsize=(10,4))
# Plot solar irradiance
G.plot(ax=axs[0]).legend(loc='upper right')

axs[0].set_title('Average Daily Solar Irradiance for Spring(MAM)')
axs[0].set_xlabel('')
axs[0].set_ylabel('$G\ [W/m^2]$')
axs[0].set_xlim(0,len(idx))
axs[0].set_ylim(0,1000)

y_ax_right = axs[0].twinx()
y_ax_right.set_ylabel('$P$ at ${:.2f}\%$ Efficiency $[W]$'.format(eff['Tracking']*100),rotation=-90)
y_ax_right.set_ylim(0,axs[0].get_ylim()[1]*s*eff['Tracking'])

# # Plot power output from solar panel
# P.plot(ax=axs[1]).legend(loc='upper right')
# axs[1].set_title('Solar Panel With {:.2f}% Efficiency'.format(eff['Tracking']*100))
# axs[1].set_xlabel('$t\ [minutes]$')
# axs[1].set_ylabel('$P\ [W]$')
# axs[1].set_xlim(idx.min(),idx.max())

# plt.savefig(fig_dir+'solar_irradience_power_{:.2f}eff.png'.format(eff['Tracking']*100))

# fig,ax = plt.subplots(figsize=(6,4))
# Plot power gained from tracking
P_diff.plot(ax=axs[1]).legend(loc='upper right')

axs[1].set_title('Power Gain From Tracking {:.2f}% Efficiency'.format(eff['Tracking']*100))
axs[1].set_xlabel('')
axs[1].set_ylabel('$\Delta P\ [W]$')
axs[1].set_xlim(0,len(idx))
axs[1].set_ylim(0)

fig.supxlabel('$t\ [minutes]$')
fig.tight_layout()

plt.savefig(fig_dir+'solar_power_{:.2f}eff.png'.format(eff['Tracking']*100))
