# -*- coding: utf-8 -*-
"""
Created on Tue Apr 28 16:35:29 2015

@author: y1275963
"""

from sdfpy import load_sdf
from thingking import loadtxt

path = '/Users/y1275963/Desktop/data/'
filename = path + 'ds14_scivis_0128_e4_dt04_1.0000'
particles = load_sdf(filename)

rx =  particles.parameters['Rx']
ry =  particles.parameters['Ry']