import yt

prefix = "http://darksky.slac.stanford.edu/scivis2015/data/ds14_scivis_0128/"
ds = yt.load(prefix+"ds14_scivis_0128_e4_dt04_1.0000")
ad = ds.all_data()
p = yt.ProjectionPlot(ds, 'z', ('deposit','all_cic'))
p.save()
