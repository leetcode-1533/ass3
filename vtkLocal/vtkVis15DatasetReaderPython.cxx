// python wrapper for vtkVis15DatasetReader
//
#define VTK_WRAPPING_CXX
#define VTK_STREAMS_FWD_ONLY
#include "vtkPythonArgs.h"
#include "vtkPythonOverload.h"
#include <vtksys/ios/sstream>
#include "vtkVis15DatasetReader.h"

extern "C" { VTK_ABI_EXPORT void PyVTKAddFile_vtkVis15DatasetReader(PyObject *, const char *); }
extern "C" { VTK_ABI_EXPORT PyObject *PyVTKClass_vtkVis15DatasetReaderNew(const char *); }

#ifndef DECLARED_PyVTKClass_vtkDataReaderNew
extern "C" { PyObject *PyVTKClass_vtkDataReaderNew(const char *); }
#define DECLARED_PyVTKClass_vtkDataReaderNew
#endif

static const char **PyvtkVis15DatasetReader_Doc();


static PyObject *
PyvtkVis15DatasetReader_GetClassName(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "GetClassName");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkVis15DatasetReader *op = static_cast<vtkVis15DatasetReader *>(vp);

  PyObject *result = NULL;

  if (op && ap.CheckArgCount(0))
    {
    const char *tempr = (ap.IsBound() ?
      op->GetClassName() :
      op->vtkVis15DatasetReader::GetClassName());

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildValue(tempr);
      }
    }

  return result;
}


static PyObject *
PyvtkVis15DatasetReader_IsA(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "IsA");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkVis15DatasetReader *op = static_cast<vtkVis15DatasetReader *>(vp);

  char *temp0 = NULL;
  PyObject *result = NULL;

  if (op && ap.CheckArgCount(1) &&
      ap.GetValue(temp0))
    {
    int tempr = (ap.IsBound() ?
      op->IsA(temp0) :
      op->vtkVis15DatasetReader::IsA(temp0));

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildValue(tempr);
      }
    }

  return result;
}


static PyObject *
PyvtkVis15DatasetReader_NewInstance(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "NewInstance");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkVis15DatasetReader *op = static_cast<vtkVis15DatasetReader *>(vp);

  PyObject *result = NULL;

  if (op && ap.CheckArgCount(0))
    {
    vtkVis15DatasetReader *tempr = (ap.IsBound() ?
      op->NewInstance() :
      op->vtkVis15DatasetReader::NewInstance());

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildVTKObject(tempr);
      if (result && PyVTKObject_Check(result))
        {
        PyVTKObject_GetObject(result)->UnRegister(0);
        PyVTKObject_SetFlag(result, VTK_PYTHON_IGNORE_UNREGISTER, 1);
        }
      }
    }

  return result;
}


static PyObject *
PyvtkVis15DatasetReader_SafeDownCast(PyObject *, PyObject *args)
{
  vtkPythonArgs ap(args, "SafeDownCast");

  vtkObject *temp0 = NULL;
  PyObject *result = NULL;

  if (ap.CheckArgCount(1) &&
      ap.GetVTKObject(temp0, "vtkObject"))
    {
    vtkVis15DatasetReader *tempr = vtkVis15DatasetReader::SafeDownCast(temp0);

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildVTKObject(tempr);
      }
    }

  return result;
}


static PyObject *
PyvtkVis15DatasetReader_GetOutput(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "GetOutput");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkVis15DatasetReader *op = static_cast<vtkVis15DatasetReader *>(vp);

  PyObject *result = NULL;

  if (op && ap.CheckArgCount(0))
    {
    vtkUnstructuredGrid *tempr = (ap.IsBound() ?
      op->GetOutput() :
      op->vtkVis15DatasetReader::GetOutput());

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildVTKObject(tempr);
      }
    }

  return result;
}

static PyMethodDef PyvtkVis15DatasetReader_Methods[] = {
  {(char*)"GetClassName", PyvtkVis15DatasetReader_GetClassName, METH_VARARGS,
   (char*)"V.GetClassName() -> string\nC++: const char *GetClassName()\n\n"},
  {(char*)"IsA", PyvtkVis15DatasetReader_IsA, METH_VARARGS,
   (char*)"V.IsA(string) -> int\nC++: int IsA(const char *name)\n\n"},
  {(char*)"NewInstance", PyvtkVis15DatasetReader_NewInstance, METH_VARARGS,
   (char*)"V.NewInstance() -> vtkVis15DatasetReader\nC++: vtkVis15DatasetReader *NewInstance()\n\n"},
  {(char*)"SafeDownCast", PyvtkVis15DatasetReader_SafeDownCast, METH_VARARGS | METH_STATIC,
   (char*)"V.SafeDownCast(vtkObject) -> vtkVis15DatasetReader\nC++: vtkVis15DatasetReader *SafeDownCast(vtkObject* o)\n\n"},
  {(char*)"GetOutput", PyvtkVis15DatasetReader_GetOutput, METH_VARARGS,
   (char*)"V.GetOutput() -> vtkUnstructuredGrid\nC++: vtkUnstructuredGrid *GetOutput()\n\n"},
  {NULL, NULL, 0, NULL}
};

static vtkObjectBase *PyvtkVis15DatasetReader_StaticNew()
{
  return vtkVis15DatasetReader::New();
}

PyObject *PyVTKClass_vtkVis15DatasetReaderNew(const char *modulename)
{
  PyObject *cls = PyVTKClass_New(&PyvtkVis15DatasetReader_StaticNew,
    PyvtkVis15DatasetReader_Methods,
    "vtkVis15DatasetReader", modulename,
    NULL, NULL,
    PyvtkVis15DatasetReader_Doc(),
    PyVTKClass_vtkDataReaderNew(modulename));
  return cls;
}

const char **PyvtkVis15DatasetReader_Doc()
{
  static const char *docstring[] = {
    "vtkVis15DatasetReader - read vtk unstructured grid data file\n\n",
    "Superclass: vtkDataReader\n\n",
    "Caveats:\n\nBinary files written on one system may not be readable on other\nsystems.\n\nSee Also:\n\nvtkUnstructuredGrid vtkDataReader\n\n",
    NULL
  };

  return docstring;
}

void PyVTKAddFile_vtkVis15DatasetReader(
  PyObject *dict, const char *modulename)
{
  PyObject *o;
  o = PyVTKClass_vtkVis15DatasetReaderNew(modulename);

  if (o && PyDict_SetItemString(dict, (char *)"vtkVis15DatasetReader", o) != 0)
    {
    Py_DECREF(o);
    }

}

