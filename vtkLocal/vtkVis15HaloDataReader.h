/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkVis15HaloDataReader.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkVis15HaloDataReader - read vtk unstructured grid data file
// .SECTION Description
// .SECTION Caveats
// Binary files written on one system may not be readable on other systems.
// .SECTION See Also
// vtkUnstructuredGrid vtkDataReader

#ifndef __vtkVis15HaloDataReader_h
#define __vtkVis15HaloDataReader_h


#include "vtkDataReader.h"
#include "vtkUnstructuredGrid.h"
#include "vtkMETAModule.h"

class vtkImageData;

class VTK_META_EXPORT vtkVis15HaloDataReader : public vtkDataReader
{
public:
  static vtkVis15HaloDataReader *New();
  vtkTypeMacro(vtkVis15HaloDataReader,vtkDataReader);
  void PrintSelf(ostream& os, vtkIndent indent);

  vtkUnstructuredGrid *GetOutput();

protected:
  vtkVis15HaloDataReader();
  ~vtkVis15HaloDataReader();

  virtual int RequestData(vtkInformation *, vtkInformationVector **,
                          vtkInformationVector *);

  // Since the Outputs[0] has the same UpdateExtent format
  // as the generic DataObject we can copy the UpdateExtent
  // as a default behavior.

  virtual int RequestInformation(vtkInformation *, vtkInformationVector **, vtkInformationVector *);
  virtual int FillOutputPortInformation(int, vtkInformation*);
  
private:
  vtkVis15HaloDataReader(const vtkVis15HaloDataReader&);  // Not implemented.
  void operator=(const vtkVis15HaloDataReader&);  // Not implemented.
};

#endif


