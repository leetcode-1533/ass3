/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkVis15DatasetReader.cxx

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkVis15DatasetReader.h"

#include "vtkByteSwap.h"
#include "vtkCellArray.h"
#include "vtkFieldData.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkObjectFactory.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkDataSetAttributes.h"
#include "vtkPointData.h"
#include "vtkUnstructuredGrid.h"
#include "vtkSmartPointer.h"
#include "vtkFloatArray.h"
#include "vtkIdTypeArray.h"

#include <vector>

vtkStandardNewMacro(vtkVis15DatasetReader);

#ifdef read
#undef read
#endif


//----------------------------------------------------------------------------
vtkVis15DatasetReader::vtkVis15DatasetReader()
{
  vtkUnstructuredGrid *output = vtkUnstructuredGrid::New();
  this->GetExecutive()->SetOutputData(0, output);
  // Releasing data for pipeline parallism.
  // Filters will know it is empty.
  output->ReleaseData();
  output->Delete();
}


//----------------------------------------------------------------------------
vtkVis15DatasetReader::~vtkVis15DatasetReader()
{
}

vtkUnstructuredGrid *vtkVis15DatasetReader::GetOutput()
{
  return vtkUnstructuredGrid::SafeDownCast(this->GetExecutive()->GetOutputData(0));
}

//----------------------------------------------------------------------------

int vtkVis15DatasetReader::RequestInformation (
  vtkInformation * vtkNotUsed(request),
  vtkInformationVector ** vtkNotUsed( inputVector ),
  vtkInformationVector *outputVector)
{
  // get the info objects
  vtkInformation* outInfo = outputVector->GetInformationObject(0);


  // fill in the pertinent stuff from the header
//  outInfo->Set(vtkDataObject::ORIGIN(),origin,3);
//  outInfo->Set(vtkDataObject::SPACING(),spacing,3);

  // whole dataset must be read
//  outInfo->Set(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(),extent,6);

  return 1;
}


//----------------------------------------------------------------------------
int vtkVis15DatasetReader::RequestData(
  vtkInformation *,
  vtkInformationVector **,
  vtkInformationVector *outputVector)
{
  vtkInformation *outInfo = outputVector->GetInformationObject(0);
  vtkUnstructuredGrid *output = vtkUnstructuredGrid::SafeDownCast(
    outInfo->Get(vtkDataObject::DATA_OBJECT()));

  vtkSmartPointer<vtkFloatArray> vel = vtkSmartPointer<vtkFloatArray>::New();
  vtkSmartPointer<vtkFloatArray> acc = vtkSmartPointer<vtkFloatArray>::New();
  vtkSmartPointer<vtkFloatArray> phi = vtkSmartPointer<vtkFloatArray>::New();
  vtkSmartPointer<vtkIdTypeArray> id = vtkSmartPointer<vtkIdTypeArray>::New();

  vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

  // All of the data in the first piece.
  if (outInfo->Get(vtkStreamingDemandDrivenPipeline::UPDATE_PIECE_NUMBER()) > 0)
    {
    return 1;
    }

  if (!this->OpenVTKFile())
    {
    return 1;
    }

  union
    {
    char buffer[100];
    struct
        {
        float x, y, z;              // position of body
        float vx, vy, vz;           // velocity of body
        float ax, ay, az;           // acceleration
        float phi;                  // potential
        vtkIdType ident;            // unique identifier
        } fields;
    } inp;

  // Skip header.
  do {
    this->IS->getline(inp.buffer, 100, '\n');
  } while (inp.buffer[0] != '#' || strncmp(inp.buffer, "# SDF-EOH", 9));

  // Skip sha-1 chunks
  this->IS->seekg(16*24, std::ios_base::cur);

  vel->SetName("velocity");
  vel->SetNumberOfComponents(3);
  vel->SetNumberOfValues(2097152);

  acc->SetName("acceleration");
  acc->SetNumberOfComponents(3);
  acc->SetNumberOfValues(2097152);

  phi->SetName("phi");
  phi->SetNumberOfValues(2097152);

  id->SetName("ident");
  id->SetNumberOfValues(2097152);

  points->SetNumberOfPoints(2097152);

// NICE BUG ....!  for (vtkIdType pnr = 0; !this-IS->eof(); pnr++)
 for (vtkIdType pnr = 0; !(this->IS->eof()); pnr++)
    {
    this->IS->read(inp.buffer, 48);
    points->InsertPoint(pnr, inp.fields.x, inp.fields.y, inp.fields.z);
    vel->InsertTuple3(pnr, inp.fields.vx, inp.fields.vy, inp.fields.vz);
    acc->InsertTuple3(pnr, inp.fields.ax, inp.fields.ay, inp.fields.az);
    phi->InsertValue(pnr, inp.fields.phi);
    id->InsertValue(pnr, inp.fields.ident);
    }

  output->SetPoints(points);
  output->GetPointData()->AddArray(vel);
  output->GetPointData()->AddArray(acc);
  output->GetPointData()->AddArray(phi);
  output->GetPointData()->AddArray(id);

  this->CloseVTKFile ();
  return 1;
}

//----------------------------------------------------------------------------
int vtkVis15DatasetReader::FillOutputPortInformation(
  int,
  vtkInformation* info)
{
  info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkUnstructuredGrid");
  return 1;
}

//----------------------------------------------------------------------------
void vtkVis15DatasetReader::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}
