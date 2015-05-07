# -*- coding: utf-8 -*-
"""
Created on Sun Apr 19 17:11:28 2015

@author: y1275963
"""

from thingking import loadtxt 
import matplotlib.pyplot as plt

treename = '/Users/y1275963/ass3/data' + 'tree_0_0_0.dat'

if __name__ == "__main__":
    treename = '/Users/y1275963/ass3/data/tree_0_0_0.dat'
    test = loadtxt(treename,unpack = True)