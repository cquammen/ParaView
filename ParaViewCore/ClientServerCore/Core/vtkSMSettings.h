/*=========================================================================

  Program:   ParaView

  Copyright (c) Kitware, Inc.
  All rights reserved.
  See Copyright.txt or http://www.paraview.org/HTML/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkSMSettings
// .SECTION Description
// vtkSMSettings provides the underlying mechanism for setting default property
// values in ParaView
#ifndef __vtkSMSettings_h
#define __vtkSMSettings_h

#include "vtkPVClientServerCoreCoreModule.h" //needed for exports
#include "vtkObject.h"
#include "vtkStdString.h"

#include <vector>

class VTKPVCLIENTSERVERCORECORE_EXPORT vtkSMSettings : public vtkObject
{
public:
  static vtkSMSettings* New();
  vtkTypeMacro(vtkSMSettings, vtkObject);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Get singleton instance.
  static vtkSMSettings* GetInstance();

  // Description:
  // Set user-specific settings. These are stored in a home directory.
  virtual void SetUserSettingsString(const char* settings);
  virtual char* GetUserSettingsString();

  // Description:
  // Set site-specific settings. These are stored in a location TBD.
  virtual void SetSiteSettingsString(const char* settings);
  virtual char* GetSiteSettingsString();

  // Description:
  // Distribute settings across nodes.
  virtual void BroadcastSettings();

  // Description:
  // Check whether a setting is defined for the requested name
  bool Has(const char* settingName);

  // Description:
  // Get setting as a vector of various types. Returns true on success, false on failure.
  bool GetVectorSetting(const char* settingName, std::vector<int> & values);
  bool GetVectorSetting(const char* settingName, std::vector<long long int> & values);
  bool GetVectorSetting(const char* settingName, std::vector<double> & values);
  bool GetVectorSetting(const char* settingName, std::vector<vtkStdString> & values);

protected:
  vtkSMSettings();
  virtual ~vtkSMSettings();

private:
  vtkSMSettings(const vtkSMSettings&); // Purposely not implemented
  void operator=(const vtkSMSettings&); // Purposely not implemented

  // User-specified settings
  char * UserSettingsString;

  // Site-specific settings
  char * SiteSettingsString;

  class vtkSMSettingsInternal;
  vtkSMSettingsInternal * Internal;
};

#endif
