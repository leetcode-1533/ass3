
import vtk, sys,os
from vtkMETAPython import vtkVis15DatasetReader

filename="/home/csunix/scsdjd/Public/ds14_scivis_0128_e4_dt04_0.0600.txt"
if (len(sys.argv) > 1):
  filename=os.path.realpath(sys.argv[1])
print "filename =", filename


rd = vtkVis15DatasetReader()
#rd.SetFileName("ds14_scivis_0128_e4_dt04_0.2000.txt")
rd.SetFileName(filename)
#rd.SetFileName("ds14_scivis_0128_e4_dt04_0.0200.txt")
rd.Update()
bnds = rd.GetOutput().GetPoints().GetBounds()


arrCalc=vtk.vtkArrayCalculator()
arrCalc.SetInputConnection(rd.GetOutputPort())
arrCalc.AddVectorArrayName("acceleration")
arrCalc.SetResultArrayName("accelerationMagnitude")
arrCalc.SetFunction('mag(acceleration)')

arrCalc.Update()
ass = vtk.vtkAssignAttribute()
ass.SetInputConnection(arrCalc.GetOutputPort())
ass.Assign("accelerationMagnitude", "SCALARS", "POINT_DATA")

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
'''
iso.SetValue(0, (lo+hi)*0.53)
iso.SetValue(1, (lo+hi)*0.5)
iso.SetValue(2, (lo+hi)*0.65)
iso.SetValue(3, (lo+hi)*0.25)
iso.SetValue(4, (lo+hi)*0.15)
iso.SetValue(5, (lo+hi)*0.75)
iso.SetValue(6, (lo+hi)*0.47)
iso.SetValue(7, (lo+hi)*0.32)
'''

iso.SetValue(0, (lo+hi)*0.01)
iso.SetValue(1, (lo+hi)*0.03)
iso.SetValue(2, (lo+hi)*0.05)
iso.SetValue(3, (lo+hi)*0.08)
iso.SetValue(4, (lo+hi)*0.10)
iso.SetValue(5, (lo+hi)*0.15)
iso.SetValue(6, (lo+hi)*0.18)
iso.SetValue(7, (lo+hi)*0.22)


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

ren = vtk.vtkRenderer()
renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren)
renWin.SetWindowName("Acceleration Magnitude")
iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)

ren.AddActor(actor)
ren.SetBackground(1, 1, 1)
renWin.SetSize(500, 500)
renWin.Render()

cam1 = ren.GetActiveCamera()
cam1.Zoom(1.5)

iren.Initialize()
renWin.Render()
iren.Start()




