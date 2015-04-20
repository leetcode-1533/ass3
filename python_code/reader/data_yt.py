import yt

prefix = "/Users/y1275963/ass3/data/"
ds = yt.load(prefix+"ds14_scivis_0128_e4_dt04_0.0600")
ad = ds.all_data()
p = yt.ProjectionPlot(ds, 'z', ('deposit','all_cic'))
p.save()
