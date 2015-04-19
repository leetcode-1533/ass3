/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkVis15HaloDataReader.cxx

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkVis15HaloDataReader.h"

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
#include "vtkIntArray.h"

#include "vtkIdTypeArray.h"

#include <vector>
#include <string>

// most probably no needed but at least one is. 
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <cstdlib>

vtkStandardNewMacro(vtkVis15HaloDataReader);

#ifdef read
#undef read
#endif


//----------------------------------------------------------------------------
vtkVis15HaloDataReader::vtkVis15HaloDataReader()
{
  vtkUnstructuredGrid *output = vtkUnstructuredGrid::New();
  this->GetExecutive()->SetOutputData(0, output);
  // Releasing data for pipeline parallism.
  // Filters will know it is empty.
  output->ReleaseData();
  output->Delete();
}


//----------------------------------------------------------------------------
vtkVis15HaloDataReader::~vtkVis15HaloDataReader()
{
}

vtkUnstructuredGrid *vtkVis15HaloDataReader::GetOutput()
{
  return vtkUnstructuredGrid::SafeDownCast(this->GetExecutive()->GetOutputData(0));
}

//----------------------------------------------------------------------------

int vtkVis15HaloDataReader::RequestInformation (
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
int vtkVis15HaloDataReader::RequestData(
  vtkInformation *,
  vtkInformationVector **,
  vtkInformationVector *outputVector)
{
  vtkInformation *outInfo = outputVector->GetInformationObject(0);
  vtkUnstructuredGrid *output = vtkUnstructuredGrid::SafeDownCast(
    outInfo->Get(vtkDataObject::DATA_OBJECT()));



  vtkSmartPointer<vtkIdTypeArray> id = vtkSmartPointer<vtkIdTypeArray>::New();
 //vtkSmartPointer<vtkFloatArray> descids = vtkSmartPointer<vtkIntArray>::New();
  
  vtkSmartPointer<vtkFloatArray> vel = vtkSmartPointer<vtkFloatArray>::New();
  vtkSmartPointer<vtkFloatArray> jval = vtkSmartPointer<vtkFloatArray>::New();
  vtkSmartPointer<vtkFloatArray> acc = vtkSmartPointer<vtkFloatArray>::New();
  
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
  /*
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
*/

  union 
    {
    char buffer[275];
    struct 
        {
        vtkIdType ident;            // unique identifier 
        int DescID; //Descendent of identifier
        float Mvir,Vmax,Vrms,Rvir,Rs; // some things
        float Np; // debugging thing?
        float X,Y,Z;              // position of body 
        float VX,VY,VZ;           // velocity of body 
        float JX,JY,JZ; // J of body.  angular momentum maybe?
        float Spin,rs_klypin,Mvir_all,M200b,M200c,M500c,M2500c,Xoff,Voff,spin_bullock,b_to_a,c_to_a;
        float AX,AY,AZ; // Acceleration (hopefully)
        float b_to_a500c,c_to_a500c; //other unknowns
        float Ax500c,Ay500c,Az500c;
        float TU,M_pe_Behroozi,M_pe_Diemer; // other values
        } fields;
    } inp;
    
// ID,DescID,Mvir,Vmax,Vrms,Rvir,Rs,Np,X,Y,Z,VX,VY,VZ,JX,JY,JZ,Spin,rs_klypin,Mvir_all,M200b,M200c,M500c,M2500c,Xoff,Voff,spin_bullock,b_to_a,c_to_a,A[x],A[y],A[z],b_to_a(500c),c_to_a(500c),A[x](500c),A[y](500c),A[z](500c),T/|U|,M_pe_Behroozi,M_pe_Diemer





  // Skip header.
  do {
    this->IS->getline(inp.buffer, 275, '\n');
  } while (inp.buffer[0] != '#' || strncmp(inp.buffer, "# SDF-EOH", 9));
int length = this->IS->tellg();
int numLines=0;
char unused[100000];

while ( !(this->IS->eof()) )
{
this->IS->getline(unused, 100000);
   ++numLines;
}
this->IS->seekg(length);
numLines-=1;
  // Skip sha-1 chunks
  this->IS->seekg(16*24, std::ios_base::cur);

  vel->SetName("velocity");
  vel->SetNumberOfComponents(3);
  vel->SetNumberOfValues(numLines);

  jval->SetName("jval");
  jval->SetNumberOfComponents(3);
  jval->SetNumberOfValues(numLines);

  acc->SetName("acceleration");
  acc->SetNumberOfComponents(3);
  acc->SetNumberOfValues(numLines);


  id->SetName("ident");
  id->SetNumberOfValues(numLines);

  points->SetNumberOfPoints(numLines);

// NICE BUG ....!  for (vtkIdType pnr = 0; !this-IS->eof(); pnr++)
 for (vtkIdType pnr = 0; !(this->IS->eof()); pnr++)
    {
    this->IS->read(inp.buffer, 48);
    points->InsertPoint(pnr, inp.fields.X, inp.fields.Y, inp.fields.Z);
    vel->InsertTuple3(pnr, inp.fields.VX, inp.fields.VY, inp.fields.VZ);
    jval->InsertTuple3(pnr, inp.fields.JX, inp.fields.JY, inp.fields.JZ);
    acc->InsertTuple3(pnr, inp.fields.AX, inp.fields.AY, inp.fields.AZ);
 id->InsertValue(pnr, inp.fields.ident);
    }

  output->SetPoints(points);
  output->GetPointData()->AddArray(vel); 
  output->GetPointData()->AddArray(acc); 
  output->GetPointData()->AddArray(jval); 
  output->GetPointData()->AddArray(id); 

  this->CloseVTKFile ();
  return 1;
}

//----------------------------------------------------------------------------
int vtkVis15HaloDataReader::FillOutputPortInformation(
  int,
  vtkInformation* info)
{
  info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkUnstructuredGrid");
  return 1;
}

//----------------------------------------------------------------------------
void vtkVis15HaloDataReader::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}

