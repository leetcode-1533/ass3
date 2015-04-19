
import vtk, sys,os
from vtkMETAPython import vtkVis15DatasetReader
from vtkMETAPython import vtkVis15HaloDataReader

filename="/home/csunix/scsdjd/Public/ds14_scivis_0128_e4_dt04_0.0600.txt"
if (len(sys.argv) > 1):
  filename=os.path.realpath(sys.argv[1])
print "filename =", filename

if (len(sys.argv) > 1):
  haloname=os.path.realpath(sys.argv[2])
print "haloname =", haloname

print "Running vtkVis15DatasetReader."
rd = vtkVis15DatasetReader()
#rd.SetFileName("ds14_scivis_0128_e4_dt04_0.2000.txt")
rd.SetFileName(filename)
#rd.SetFileName("ds14_scivis_0128_e4_dt04_0.0200.txt")
rd.Update()
bnds = rd.GetOutput().GetPoints().GetBounds()

print "Running vtkVis15HaloDataReader."
hr = vtkVis15HaloDataReader()
#rd.SetFileName("ds14_scivis_0128_e4_dt04_0.2000.txt")
hr.SetFileName(haloname)
#rd.SetFileName("ds14_scivis_0128_e4_dt04_0.0200.txt")
hr.Update()


print "Running vtkPolyData."
poly=vtk.vtkPolyData()
poly=hr.GetOutput().GetPoints()
numHalos = poly.GetNumberOfPoints()
print "Num points =", numHalos
point = [0,0,0]
poly.GetPoint(0,point);


print "point at: ", point[0], ",",point[1], "," ,point[2]


spheresourcelist = list()
spheremaplist = list()
sphereactorlist =list()
pointlist = list()
haloRadius = 75.0
haloColor=[0,1,0]


for i in range(numHalos):
  spheresourcelist.append(vtk.vtkSphereSource())
  spheremaplist.append(vtk.vtkPolyDataMapper())
  sphereactorlist.append(vtk.vtkActor())
  pointlist.append([0,0,0])
  
for i in range(numHalos):
  poly.GetPoint(i,pointlist[i])
  spheresourcelist[i].SetCenter(pointlist[i][0],pointlist[i][1],pointlist[i][2])
  spheremaplist[i].SetInputConnection(spheresourcelist[i].GetOutputPort())
  sphereactorlist[i].SetMapper(spheremaplist[i])
  sphereactorlist[i].GetProperty().SetColor(haloColor[0],haloColor[1],haloColor[2])


ren = vtk.vtkRenderer()
renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren)
renWin.SetWindowName("Phi field")
iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)

for i in range(numHalos):
  ren.AddActor(sphereactorlist[i])


#==============================================================================

assv = vtk.vtkAssignAttribute()
assv.SetInputConnection(hr.GetOutputPort())
assv.Assign("velocity", "VECTORS", "POINT_DATA")

print "running hogs"


hogs = vtk.vtkHedgeHog()
hogs.SetInputConnection(assv.GetOutputPort())
hogs.SetVectorModeToUseVector()
hogs.SetScaleFactor(10)

lut1 = vtk.vtkLookupTable()
lut1.SetNumberOfColors(64)
lut1.SetHueRange(0.66,0)
lut1.SetValueRange(1,1)
lut1.SetSaturationRange(1,1)
lut1.Build()

map1 = vtk.vtkPolyDataMapper()
map1.SetInputConnection(hogs.GetOutputPort())
map1.SetScalarRange(hogs.GetOutputDataObject(0).GetScalarRange())
map1.SetLookupTable(lut1)
map1.SetColorModeToMapScalars()


actor1 = vtk.vtkActor()
actor1.SetMapper(map1)
actor1.GetProperty().SetColor(1,0,0)
print "hogs done!"

#==============================================================================

'''
arrCalc=vtk.vtkArrayCalculator()
arrCalc.SetInputConnection(rd.GetOutputPort())
arrCalc.AddVectorArrayName("velocity")
arrCalc.SetResultArrayName("velocityMagnitude")
arrCalc.SetFunction('mag(velocity)')

arrCalc.Update()
'''

'''
ass = vtk.vtkAssignAttribute()
ass.SetInputConnection(rd.GetOutputPort())
ass.Assign("phi", "SCALARS", "POINT_DATA")

print "Running Shepard."

shep = vtk.vtkShepardMethod()
shep.SetInputConnection(ass.GetOutputPort())
shep.SetSampleDimensions(100,100,100)
shep.SetMaximumDistance(0.1)
shep.SetModelBounds(bnds)



shep.Update()
print "Shep completed."
so = shep.GetOutput()
print so
sd = so.GetPointData()
for i in range(0,sd.GetNumberOfArrays()):
  ar = sd.GetArray(i)
  print i, "\t", ar.GetName(), "\t", ar.GetRange()

sca = sd.GetScalars()
(lo,hi) = sca.GetRange()
hist = []
for i in range(0,101):
  hist += [0]
for i in range(0,sca.GetNumberOfTuples()):
  v = sca.GetComponent(i, 0)
  t = (v - lo) / (hi - lo)
  b = int(t*100)
  hist[b] += 1
for i in range(0,100):
  print i, "\t", hist[i]



iso = vtk.vtkContourFilter()
iso.SetInputConnection(shep.GetOutputPort())
iso.ComputeNormalsOn()
#iso.SetNumberOfContours(3)
#iso.SetValue(0, (lo+hi)*0.53)
#iso.SetValue(1, (lo+hi)*0.5)
#iso.SetValue(2, (lo+hi)*0.65)
iso.SetNumberOfContours(8)
iso.SetValue(0, (lo+hi)*0.53)
iso.SetValue(1, (lo+hi)*0.5)
iso.SetValue(2, (lo+hi)*0.65)
iso.SetValue(3, (lo+hi)*0.25)
iso.SetValue(4, (lo+hi)*0.15)
iso.SetValue(5, (lo+hi)*0.75)
iso.SetValue(6, (lo+hi)*0.47)
iso.SetValue(7, (lo+hi)*0.32)

lut = vtk.vtkLookupTable()
lut.SetNumberOfColors(64)
lut.SetHueRange(0.66,1)
lut.SetValueRange(1,1)
lut.SetSaturationRange(1,1)
lut.Build()

map = vtk.vtkPolyDataMapper()
map.SetInputConnection(iso.GetOutputPort())
map.SetLookupTable(lut)
map.SetScalarRange(lo,hi)
map.SetColorModeToMapScalars()

actor = vtk.vtkActor()
actor.SetMapper(map)
actor.GetProperty().SetOpacity(0.5)

ren.AddActor(actor)
'''

ren.AddActor(actor1)

ren.SetBackground(1, 1, 1)
renWin.SetSize(500, 500)
renWin.Render()

cam1 = ren.GetActiveCamera()
#cam1.Zoom(1.5)

iren.Initialize()
renWin.Render()
iren.Start()




