# -*- coding: utf-8 -*-
"""
Created on Tue Apr 28 20:10:13 2015

@author: y1275963
"""

import csv
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np

filepath = '/Users/y1275963/consistent-trees/read_tree/'
fig = plt.figure()
ax = plt.axes(projection='3d')

u = np.linspace(0, np.pi, 30)
v = np.linspace(0, 2 * np.pi, 30)

with open(filepath+'test.csv') as csvfile:
    test = csv.reader(csvfile,delimiter=',')
    for row in test:
        x_base = float(row[2])
        y_base = float(row[3])
        z_base = float(row[4])
        
#        rad = float(row[1])
        

        x = x_base + np.outer(np.sin(u), np.sin(v))*rad
        y = y_base + np.outer(np.sin(u), np.sin(v))*rad
        z = z_base + np.outer(np.cos(u), np.ones_like(v))*rad
        
        ax.plot_wireframe(x, y, z)
#        x.append(float(row[2]))
#        y.append(float(row[3]))
#        z.append(float(row[4]))
        


