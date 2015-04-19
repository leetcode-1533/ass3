# -*- coding: utf-8 -*-
"""
Created on Sun Apr 19 15:35:00 2015

@author: y1275963
"""
from thingking import loadtxt 
import matplotlib.pyplot as plt
#from mpl_toolkits.mplot3d import Axes3D

prefix = "http://darksky.slac.stanford.edu/scivis2015/data/ds14_scivis_0128/"


def signal_time(filename):
    halo = prefix + "rockstar/hlists/" +filename +".list"

    test = loadtxt(halo,unpack = True)
    
    x = test[17]
    y = test[18]
    z = test[19]
    
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.scatter(x,y,z)
    fig.savefig(filename+'.png')
def filelist():
    template = "hlist_0.13000"
    for index in range(12,101):
        new_field = '{0:.2f}'.format(index/100.0)
        test = template.replace('0.13',new_field)
        yield test
if __name__ == "__main__":
    for entry in filelist():
        signal_time(entry)
    