/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkInformation.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkInformation - Store vtkAlgorithm input/output information.
// .SECTION Description
// vtkInformation represents information and/or data for one input or
// one output of a vtkAlgorithm.  It maps from keys to values of
// several data types.  Instances of this class are collected in
// vtkInformationVector instances and passed to
// vtkAlgorithm::ProcessRequest calls.  The information and
// data referenced by the instance on a particular input or output
// define the request made to the vtkAlgorithm instance.

#ifndef __vtkInformation_h
#define __vtkInformation_h

#include "vtkObject.h"

class vtkDataObject;
class vtkExecutive;
class vtkInformationDataObjectKey;
class vtkInformationDoubleKey;
class vtkInformationDoubleVectorKey;
class vtkInformationExecutivePortKey;
class vtkInformationExecutivePortVectorKey;
class vtkInformationIdTypeKey;
class vtkInformationInformationKey;
class vtkInformationInformationVectorKey;
class vtkInformationIntegerKey;
class vtkInformationIntegerPointerKey;
class vtkInformationIntegerVectorKey;
class vtkInformationInternals;
class vtkInformationKey;
class vtkInformationKeyToInformationFriendship;
class vtkInformationKeyVectorKey;
class vtkInformationObjectBaseKey;
class vtkInformationRequestKey;
class vtkInformationStringKey;
class vtkInformationUnsignedLongKey;
class vtkInformationVector;

class vtkInformation : public vtkObject
{
public:
  VTK_COMMON_EXPORT static vtkInformation *New();
  vtkExportedTypeRevisionMacro(vtkInformation,vtkObject,VTK_COMMON_EXPORT);
  VTK_COMMON_EXPORT void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Clear all information entries.
  VTK_COMMON_EXPORT void Clear();

  // Description:
  // Copy all information entries from the given vtkInformation
  // instance.  Any previously existing entries are removed.  If 
  // deep==1, a deep copy of the information structure is performed (new 
  // instances of any contained vtkInformation and vtkInformationVector 
  // objects are created).
  VTK_COMMON_EXPORT void Copy(vtkInformation* from, int deep=0);

  // Description:
  // Copy the key/value pair associated with the given key in the
  // given information object.  If deep=1, a deep copy of the information
  // structure is performed (new instances of any contained vtkInformation and 
  // vtkInformationVector objects are created).
  VTK_COMMON_EXPORT void CopyEntry(vtkInformation* from, vtkInformationKey* key, int deep=0);
  VTK_COMMON_EXPORT void CopyEntry(vtkInformation* from, vtkInformationDataObjectKey* key, int deep=0);
  VTK_COMMON_EXPORT void CopyEntry(vtkInformation* from, vtkInformationDoubleVectorKey* key, int deep=0);
  VTK_COMMON_EXPORT void CopyEntry(vtkInformation* from, vtkInformationInformationKey* key, int deep=0);
  VTK_COMMON_EXPORT void CopyEntry(vtkInformation* from, vtkInformationInformationVectorKey* key, int deep=0);
  VTK_COMMON_EXPORT void CopyEntry(vtkInformation* from, vtkInformationIntegerKey* key, int deep=0);
  VTK_COMMON_EXPORT void CopyEntry(vtkInformation* from, vtkInformationIntegerVectorKey* key, int deep=0);
  VTK_COMMON_EXPORT void CopyEntry(vtkInformation* from, vtkInformationRequestKey* key, int deep=0);
  VTK_COMMON_EXPORT void CopyEntry(vtkInformation* from, vtkInformationStringKey* key, int deep=0);
  VTK_COMMON_EXPORT void CopyEntry(vtkInformation* from, vtkInformationUnsignedLongKey* key, int deep=0);
  //BTX
  VTK_FILTERING_EXPORT void CopyEntry(vtkInformation* from, vtkInformationExecutivePortKey* key, int deep=0);
  //ETX

  // Description:
  // Use the given key to lookup a list of other keys in the given
  // information object.  The key/value pairs associated with these
  // other keys will be copied.  If deep==1, a deep copy of the
  // information structure is performed.
  VTK_COMMON_EXPORT void CopyEntries(vtkInformation* from, vtkInformationKeyVectorKey* key, int deep=0);

  // Description:
  // Get/Set a request-valued entry.
  VTK_COMMON_EXPORT void Set(vtkInformationRequestKey* key);
  VTK_COMMON_EXPORT void Remove(vtkInformationRequestKey* key);
  VTK_COMMON_EXPORT int Has(vtkInformationRequestKey* key);

  // Description:
  // Get/Set an integer-valued entry.
  VTK_COMMON_EXPORT void Set(vtkInformationIntegerKey* key, int value);
  VTK_COMMON_EXPORT int Get(vtkInformationIntegerKey* key);
  VTK_COMMON_EXPORT void Remove(vtkInformationIntegerKey* key);
  VTK_COMMON_EXPORT int Has(vtkInformationIntegerKey* key);

  // Description:
  // Get/Set a vtkIdType-valued entry.
  VTK_COMMON_EXPORT void Set(vtkInformationIdTypeKey* key, vtkIdType value);
  VTK_COMMON_EXPORT vtkIdType Get(vtkInformationIdTypeKey* key);
  VTK_COMMON_EXPORT void Remove(vtkInformationIdTypeKey* key);
  VTK_COMMON_EXPORT int Has(vtkInformationIdTypeKey* key);

  // Description:
  // Get/Set an double-valued entry.
  VTK_COMMON_EXPORT void Set(vtkInformationDoubleKey* key, double value);
  VTK_COMMON_EXPORT double Get(vtkInformationDoubleKey* key);
  VTK_COMMON_EXPORT void Remove(vtkInformationDoubleKey* key);
  VTK_COMMON_EXPORT int Has(vtkInformationDoubleKey* key);

  // Description:
  // Get/Set an integer-vector-valued entry.
  VTK_COMMON_EXPORT void Append(vtkInformationIntegerVectorKey* key, int value);
  VTK_COMMON_EXPORT void Set(vtkInformationIntegerVectorKey* key, int* value, int length);
  VTK_COMMON_EXPORT void Set(vtkInformationIntegerVectorKey* key, int value1, 
           int value2, int value3);
  VTK_COMMON_EXPORT void Set(vtkInformationIntegerVectorKey* key, 
           int value1, int value2, int value3,
           int value4, int value5, int value6);
  VTK_COMMON_EXPORT int* Get(vtkInformationIntegerVectorKey* key);
  VTK_COMMON_EXPORT int  Get(vtkInformationIntegerVectorKey* key, int idx);
  VTK_COMMON_EXPORT void Get(vtkInformationIntegerVectorKey* key, int* value);
  VTK_COMMON_EXPORT int Length(vtkInformationIntegerVectorKey* key);
  VTK_COMMON_EXPORT void Remove(vtkInformationIntegerVectorKey* key);
  VTK_COMMON_EXPORT int Has(vtkInformationIntegerVectorKey* key);

  // Description:
  // Get/Set an integer-pointer-valued entry.
  VTK_COMMON_EXPORT void Set(vtkInformationIntegerPointerKey* key, int* value, int length);
  VTK_COMMON_EXPORT int* Get(vtkInformationIntegerPointerKey* key);
  VTK_COMMON_EXPORT void Get(vtkInformationIntegerPointerKey* key, int* value);
  VTK_COMMON_EXPORT int Length(vtkInformationIntegerPointerKey* key);
  VTK_COMMON_EXPORT void Remove(vtkInformationIntegerPointerKey* key);
  VTK_COMMON_EXPORT int Has(vtkInformationIntegerPointerKey* key);

  // Description:
  // Get/Set an unsigned-long-valued entry.
  VTK_COMMON_EXPORT void Set(vtkInformationUnsignedLongKey* key, unsigned long value);
  VTK_COMMON_EXPORT unsigned long Get(vtkInformationUnsignedLongKey* key);
  VTK_COMMON_EXPORT void Remove(vtkInformationUnsignedLongKey* key);
  VTK_COMMON_EXPORT int Has(vtkInformationUnsignedLongKey* key);

  // Description:
  // Get/Set an double-vector-valued entry.
  VTK_COMMON_EXPORT void Append(vtkInformationDoubleVectorKey* key, double value);
  VTK_COMMON_EXPORT void Set(vtkInformationDoubleVectorKey* key, double* value, int length);
  VTK_COMMON_EXPORT void Set(vtkInformationDoubleVectorKey* key, double value1, 
           double value2, double value3);
  VTK_COMMON_EXPORT void Set(vtkInformationDoubleVectorKey* key, 
           double value1, double value2, double value3,
           double value4, double value5, double value6);
  VTK_COMMON_EXPORT double* Get(vtkInformationDoubleVectorKey* key);
  VTK_COMMON_EXPORT double  Get(vtkInformationDoubleVectorKey* key, int idx);
  VTK_COMMON_EXPORT void Get(vtkInformationDoubleVectorKey* key, double* value);
  VTK_COMMON_EXPORT int Length(vtkInformationDoubleVectorKey* key);
  VTK_COMMON_EXPORT void Remove(vtkInformationDoubleVectorKey* key);
  VTK_COMMON_EXPORT int Has(vtkInformationDoubleVectorKey* key);

  // Description:
  // Get/Set an InformationKey-vector-valued entry.
  VTK_COMMON_EXPORT void Append(vtkInformationKeyVectorKey* key, vtkInformationKey* value);
  VTK_COMMON_EXPORT void AppendUnique(vtkInformationKeyVectorKey* key, vtkInformationKey* value);
  VTK_COMMON_EXPORT void Set(vtkInformationKeyVectorKey* key, vtkInformationKey** value, int length);
  VTK_COMMON_EXPORT void Remove(vtkInformationKeyVectorKey* key, vtkInformationKey* value);
  VTK_COMMON_EXPORT vtkInformationKey** Get(vtkInformationKeyVectorKey* key);
  VTK_COMMON_EXPORT vtkInformationKey*  Get(vtkInformationKeyVectorKey* key, int idx);
  VTK_COMMON_EXPORT void Get(vtkInformationKeyVectorKey* key, vtkInformationKey** value);
  VTK_COMMON_EXPORT int Length(vtkInformationKeyVectorKey* key);
  VTK_COMMON_EXPORT void Remove(vtkInformationKeyVectorKey* key);
  VTK_COMMON_EXPORT int Has(vtkInformationKeyVectorKey* key);

  // Provide extra overloads of this method to avoid requiring user
  // code to include the headers for these key types.  Avoid wrapping
  // them because the original method can be called from the wrappers
  // anyway and this causes a python help string to be too long.
  //BTX
  VTK_COMMON_EXPORT void Append(vtkInformationKeyVectorKey* key,
              vtkInformationDataObjectKey* value);
  VTK_COMMON_EXPORT void Append(vtkInformationKeyVectorKey* key, vtkInformationDoubleKey* value);
  VTK_COMMON_EXPORT void Append(vtkInformationKeyVectorKey* key,
              vtkInformationDoubleVectorKey* value);
  VTK_FILTERING_EXPORT void Append(vtkInformationKeyVectorKey* key,
              vtkInformationExecutivePortKey* value);
  VTK_COMMON_EXPORT void Append(vtkInformationKeyVectorKey* key,
              vtkInformationInformationKey* value);
  VTK_COMMON_EXPORT void Append(vtkInformationKeyVectorKey* key,
              vtkInformationInformationVectorKey* value);
  VTK_COMMON_EXPORT void Append(vtkInformationKeyVectorKey* key,
              vtkInformationIntegerKey* value);
  VTK_COMMON_EXPORT void Append(vtkInformationKeyVectorKey* key,
              vtkInformationIntegerVectorKey* value);
  VTK_COMMON_EXPORT void Append(vtkInformationKeyVectorKey* key, vtkInformationStringKey* value);
  VTK_COMMON_EXPORT void Append(vtkInformationKeyVectorKey* key,
              vtkInformationObjectBaseKey* value);
  VTK_COMMON_EXPORT void Append(vtkInformationKeyVectorKey* key,
              vtkInformationUnsignedLongKey* value);

  VTK_COMMON_EXPORT void AppendUnique(vtkInformationKeyVectorKey* key,
                    vtkInformationDataObjectKey* value);
  VTK_COMMON_EXPORT void AppendUnique(vtkInformationKeyVectorKey* key, 
                    vtkInformationDoubleKey* value);
  VTK_COMMON_EXPORT void AppendUnique(vtkInformationKeyVectorKey* key,
                    vtkInformationDoubleVectorKey* value);
  VTK_FILTERING_EXPORT void AppendUnique(vtkInformationKeyVectorKey* key,
                    vtkInformationExecutivePortKey* value);
  VTK_COMMON_EXPORT void AppendUnique(vtkInformationKeyVectorKey* key,
                    vtkInformationInformationKey* value);
  VTK_COMMON_EXPORT void AppendUnique(vtkInformationKeyVectorKey* key,
                    vtkInformationInformationVectorKey* value);
  VTK_COMMON_EXPORT void AppendUnique(vtkInformationKeyVectorKey* key,
                    vtkInformationIntegerKey* value);
  VTK_COMMON_EXPORT void AppendUnique(vtkInformationKeyVectorKey* key,
                    vtkInformationIntegerVectorKey* value);
  VTK_COMMON_EXPORT void AppendUnique(vtkInformationKeyVectorKey* key, 
                    vtkInformationStringKey* value);
  VTK_COMMON_EXPORT void AppendUnique(vtkInformationKeyVectorKey* key,
                    vtkInformationObjectBaseKey* value);
  VTK_COMMON_EXPORT void AppendUnique(vtkInformationKeyVectorKey* key,
                    vtkInformationUnsignedLongKey* value);
  //ETX

  // Description:
  // Get/Set a string-valued entry.
  VTK_COMMON_EXPORT void Set(vtkInformationStringKey* key, const char*);
  VTK_COMMON_EXPORT const char* Get(vtkInformationStringKey* key);
  VTK_COMMON_EXPORT void Remove(vtkInformationStringKey* key);
  VTK_COMMON_EXPORT int Has(vtkInformationStringKey* key);

  // Description:
  // Get/Set an entry storing another vtkInformation instance.
  VTK_COMMON_EXPORT void Set(vtkInformationInformationKey* key, vtkInformation*);
  VTK_COMMON_EXPORT vtkInformation* Get(vtkInformationInformationKey* key);
  VTK_COMMON_EXPORT void Remove(vtkInformationInformationKey* key);
  VTK_COMMON_EXPORT int Has(vtkInformationInformationKey* key);

  // Description:
  // Get/Set an entry storing a vtkInformationVector instance.
  VTK_COMMON_EXPORT void Set(vtkInformationInformationVectorKey* key, vtkInformationVector*);
  VTK_COMMON_EXPORT vtkInformationVector* Get(vtkInformationInformationVectorKey* key);
  VTK_COMMON_EXPORT void Remove(vtkInformationInformationVectorKey* key);
  VTK_COMMON_EXPORT int Has(vtkInformationInformationVectorKey* key);

  // Description:
  // Get/Set an entry storing a vtkObjectBase instance.
  VTK_COMMON_EXPORT void Set(vtkInformationObjectBaseKey* key, vtkObjectBase*);
  VTK_COMMON_EXPORT vtkObjectBase* Get(vtkInformationObjectBaseKey* key);
  VTK_COMMON_EXPORT void Remove(vtkInformationObjectBaseKey* key);
  VTK_COMMON_EXPORT int Has(vtkInformationObjectBaseKey* key);

  // Description:
  // Get/Set an entry storing a vtkDataObject instance.
  VTK_COMMON_EXPORT void Set(vtkInformationDataObjectKey* key, vtkDataObject*);
  VTK_COMMON_EXPORT vtkDataObject* Get(vtkInformationDataObjectKey* key);
  VTK_COMMON_EXPORT void Remove(vtkInformationDataObjectKey* key);
  VTK_COMMON_EXPORT int Has(vtkInformationDataObjectKey* key);

  //BTX
  // Description:
  // Get/Set an entry storing a vtkExecutive/port number pair.
  VTK_FILTERING_EXPORT void Set(vtkInformationExecutivePortKey* key, vtkExecutive*, int);
  VTK_FILTERING_EXPORT vtkExecutive* GetExecutive(vtkInformationExecutivePortKey* key);
  VTK_FILTERING_EXPORT int GetPort(vtkInformationExecutivePortKey* key);
  VTK_FILTERING_EXPORT void Get(vtkInformationExecutivePortKey* key, vtkExecutive*& executive, int &port);
  VTK_FILTERING_EXPORT void Remove(vtkInformationExecutivePortKey* key);
  VTK_FILTERING_EXPORT int Has(vtkInformationExecutivePortKey* key);

  // Description:
  // Get/Set an entry storing a vector of vtkExecutive/port number pairs.
  VTK_FILTERING_EXPORT void Append(vtkInformationExecutivePortVectorKey* key,
              vtkExecutive* executive, int port);
  VTK_FILTERING_EXPORT void Remove(vtkInformationExecutivePortVectorKey* key,
              vtkExecutive* executive, int port);
  VTK_FILTERING_EXPORT void Set(vtkInformationExecutivePortVectorKey* key,
           vtkExecutive** executives, int* ports, int length);
  VTK_FILTERING_EXPORT vtkExecutive** GetExecutives(vtkInformationExecutivePortVectorKey* key);
  VTK_FILTERING_EXPORT int* GetPorts(vtkInformationExecutivePortVectorKey* key);
  VTK_FILTERING_EXPORT void Get(vtkInformationExecutivePortVectorKey* key,
           vtkExecutive** executives, int* ports);
  VTK_FILTERING_EXPORT int Length(vtkInformationExecutivePortVectorKey* key);
  VTK_FILTERING_EXPORT void Remove(vtkInformationExecutivePortVectorKey* key);
  VTK_FILTERING_EXPORT int Has(vtkInformationExecutivePortVectorKey* key);
  //ETX

  // Description:
  // Upcast the given key instance.
  VTK_COMMON_EXPORT static vtkInformationKey* GetKey(vtkInformationDataObjectKey* key);
  VTK_COMMON_EXPORT static vtkInformationKey* GetKey(vtkInformationDoubleKey* key);
  VTK_COMMON_EXPORT static vtkInformationKey* GetKey(vtkInformationDoubleVectorKey* key);
  VTK_COMMON_EXPORT static vtkInformationKey* GetKey(vtkInformationInformationKey* key);
  VTK_COMMON_EXPORT static vtkInformationKey* GetKey(vtkInformationInformationVectorKey* key);
  VTK_COMMON_EXPORT static vtkInformationKey* GetKey(vtkInformationIntegerKey* key);
  VTK_COMMON_EXPORT static vtkInformationKey* GetKey(vtkInformationIntegerVectorKey* key);
  VTK_COMMON_EXPORT static vtkInformationKey* GetKey(vtkInformationRequestKey* key);
  VTK_COMMON_EXPORT static vtkInformationKey* GetKey(vtkInformationStringKey* key);
  VTK_COMMON_EXPORT static vtkInformationKey* GetKey(vtkInformationKey* key);
  VTK_COMMON_EXPORT static vtkInformationKey* GetKey(vtkInformationUnsignedLongKey* key);
  //BTX
  VTK_FILTERING_EXPORT static vtkInformationKey* GetKey(vtkInformationExecutivePortKey* key);
  //ETX

  // Description:
  // Initiate garbage collection when a reference is removed.
  VTK_COMMON_EXPORT virtual void Register(vtkObjectBase* o);
  VTK_COMMON_EXPORT virtual void UnRegister(vtkObjectBase* o);

  // Description:
  // Get/Set the Request ivar
  VTK_COMMON_EXPORT void SetRequest(vtkInformationRequestKey *request) { this->Request = request; }
  VTK_COMMON_EXPORT vtkInformationRequestKey *GetRequest() { return this->Request; }
      
protected:
  VTK_COMMON_EXPORT vtkInformation();
  VTK_COMMON_EXPORT ~vtkInformation();

  // Get/Set a map entry directly through the vtkObjectBase instance
  // representing the value.  Used internally to manage the map.
  VTK_COMMON_EXPORT void SetAsObjectBase(vtkInformationKey* key, vtkObjectBase* value);
  VTK_COMMON_EXPORT vtkObjectBase* GetAsObjectBase(vtkInformationKey* key);

  // Expand the table to a larger size
  VTK_COMMON_EXPORT void ExpandTable();
  
  // Internal implementation details.
  vtkInformationInternals* Internal;

  // Garbage collection support.
  VTK_COMMON_EXPORT virtual void ReportReferences(vtkGarbageCollector*);

  // Report the object associated with the given key to the collector.
  VTK_COMMON_EXPORT void ReportAsObjectBase(vtkInformationKey* key,
                          vtkGarbageCollector* collector);

private:
  //BTX
  friend class vtkInformationKeyToInformationFriendship;
  friend class vtkInformationIterator;
  //ETX
private:
  VTK_COMMON_EXPORT vtkInformation(const vtkInformation&);  // Not implemented.
  VTK_COMMON_EXPORT void operator=(const vtkInformation&);  // Not implemented.
  vtkInformationRequestKey *Request;
};

#endif
