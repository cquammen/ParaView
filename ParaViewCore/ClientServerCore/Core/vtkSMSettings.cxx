/*=========================================================================

  Program:   ParaView

  Copyright (c) Kitware, Inc.
  All rights reserved.
  See Copyright.txt or http://www.paraview.org/HTML/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkSMSettings.h"

#include "vtkObjectFactory.h"
#include "vtkSmartPointer.h"

#include "vtk_jsoncpp.h"

//----------------------------------------------------------------------------
class vtkSMSettings::vtkSMSettingsInternal {
public:
  Json::Value UserSettingsJSONRoot;
  Json::Value SiteSettingsJSONRoot;

  // Description:
  // See if given setting is defined
  bool Has(const char* settingName)
  {
    Json::Value value = this->GetValue(settingName);
    return !value.isNull();
  }

  // Description:
  // Get a Json::Value type given a string
  //
  // String format is:
  // "." => root node
  // ".[n]" => elements at index 'n' of root node (an array value)
  // ".name" => member named 'name' of root node (an object value)
  // ".name1.name2.name3"
  // ".[0][1][2].name1[3]"
  Json::Value GetValue(const char* settingName)
  {
    // Convert setting string to path
    const std::string settingString(settingName);
    Json::Path path(settingString);
    
    // Try user-specific settings first
    Json::Value setting = path.make(this->UserSettingsJSONRoot);
    if (!setting)
      {
      setting = path.make(this->SiteSettingsJSONRoot);
      }

    if (!setting)
      {
      return Json::Value::null;
      }

    return setting;
  }

  template< typename T >
  bool GetVectorSetting(const char* settingName, std::vector<T> & values)
  {
    values.clear();

    Json::Value setting = this->GetValue(settingName);
    if (!setting)
      {
      return false;
      }

    // \TODO - need more error checking
    if (setting.isArray())
      {
      for (Json::Value::ArrayIndex i = 0; i < setting.size(); ++i)
        {
        T value;
        this->As(setting[i], value);
        values.push_back(value);
        }
      }
    else
      {
      T value;
      this->As(setting, value);
      values.push_back(value);
      }

    return true;
  }

  template< typename T >
  bool As(const Json::Value & jsonValue, T & value);

};

//----------------------------------------------------------------------------
template<>
bool vtkSMSettings::vtkSMSettingsInternal::As(const Json::Value & jsonValue, int & value)
{
  bool success = jsonValue.isNumeric();
  if (success)
    {
    value = jsonValue.asInt();
    }
  
  return success;
}

//----------------------------------------------------------------------------
template<>
bool vtkSMSettings::vtkSMSettingsInternal::As(const Json::Value & jsonValue, long long int & value)
{
  bool success = jsonValue.isNumeric();
  if (success)
    {
    value = jsonValue.asLargestInt();
    }
  
  return success;
}

//----------------------------------------------------------------------------
template<>
bool vtkSMSettings::vtkSMSettingsInternal::As(const Json::Value & jsonValue, double & value)
{
  bool success = jsonValue.isNumeric();
  if (success)
    {
    try
      {
      value = jsonValue.asDouble();
      }
    catch (...)
      {
      std::cout << "Could not convert \n" << jsonValue.toStyledString() << "\n";
      }
    }
  
  return success;
}

//----------------------------------------------------------------------------
template<>
bool vtkSMSettings::vtkSMSettingsInternal::As(const Json::Value & jsonValue, vtkStdString & value)
{
  bool success = jsonValue.isString();
  if (success)
    {
    try
      {
      value = jsonValue.asString();
      }
    catch (...)
      {
      std::cout << "Could not convert \n" << jsonValue.toStyledString() << "\n";
      }
    }
  
  return success;
}

//----------------------------------------------------------------------------
vtkStandardNewMacro(vtkSMSettings);

//----------------------------------------------------------------------------
vtkSMSettings::vtkSMSettings()
{
  this->UserSettingsString = NULL;
  this->SiteSettingsString = NULL;
  this->Internal = new vtkSMSettingsInternal();
}

//----------------------------------------------------------------------------
vtkSMSettings::~vtkSMSettings()
{
  delete this->Internal;
}

//----------------------------------------------------------------------------
vtkSMSettings* vtkSMSettings::GetInstance()
{
  static vtkSmartPointer<vtkSMSettings> Instance;
  if (Instance.GetPointer() == NULL)
    {
    vtkSMSettings* settings = vtkSMSettings::New();
    Instance = settings;
    settings->FastDelete();
    }

  return Instance;
}

//----------------------------------------------------------------------------
void vtkSMSettings::SetUserSettingsString(const char* settings)
{
  vtkDebugMacro(<< this->GetClassName() << " (" << this << "): setting UserSettingsString to "
                << (settings ? settings :"(null)") );
  if ( this->UserSettingsString == NULL && settings == NULL) { return;}
  if ( this->UserSettingsString && settings && (!strcmp(this->UserSettingsString,settings))) { return;}
  delete [] this->UserSettingsString;

  if (settings)
    {
    size_t n = strlen(settings) + 1;
    char *cp1 =  new char[n];
    const char *cp2 = settings;
    this->UserSettingsString = cp1;
    do { *cp1++ = *cp2++; } while ( --n );
    }
   else
    {
    this->UserSettingsString = NULL;
    }
  this->Modified();

  if (!this->UserSettingsString)
    {
    return;
    }

  // Parse the user settings
  Json::Reader reader;
  bool success = reader.parse(std::string( settings ), this->Internal->UserSettingsJSONRoot, false);
  if (!success)
    {
    vtkErrorMacro(<< "Could not parse user settings JSON");
    this->Internal->UserSettingsJSONRoot = Json::Value::null;
    }
}

//----------------------------------------------------------------------------
char* vtkSMSettings::GetUserSettingsString()
{
  return this->UserSettingsString;
}

//----------------------------------------------------------------------------
void vtkSMSettings::SetSiteSettingsString(const char* settings)
{
  vtkDebugMacro(<< this->GetClassName() << " (" << this << "): setting SiteSettingsString to "
                << (settings ? settings :"(null)") );
  if ( this->SiteSettingsString == NULL && settings == NULL) { return;}
  if ( this->SiteSettingsString && settings && (!strcmp(this->SiteSettingsString,settings))) { return;}
  delete [] this->SiteSettingsString;

  if (settings)
    {
    size_t n = strlen(settings) + 1;
    char *cp1 =  new char[n];
    const char *cp2 = settings;
    this->SiteSettingsString = cp1;
    do { *cp1++ = *cp2++; } while ( --n );
    }
   else
    {
    this->SiteSettingsString = NULL;
    }
  this->Modified();

  if ( !this->SiteSettingsString )
    {
    return;
    }

}

//----------------------------------------------------------------------------
char* vtkSMSettings::GetSiteSettingsString()
{
  return this->SiteSettingsString;
}

//----------------------------------------------------------------------------
void vtkSMSettings::BroadcastSettings()
{
  // TODO - implement
}

//----------------------------------------------------------------------------
bool vtkSMSettings::Has(const char* settingName)
{
  return this->Internal->Has(settingName);
}

//----------------------------------------------------------------------------
bool vtkSMSettings::GetVectorSetting(const char* settingName, std::vector<int> & values)
{
  this->Internal->GetVectorSetting(settingName, values);
}

//----------------------------------------------------------------------------
bool vtkSMSettings::GetVectorSetting(const char* settingName, std::vector<long long int> & values)
{
  this->Internal->GetVectorSetting(settingName, values);
}

//----------------------------------------------------------------------------
bool vtkSMSettings::GetVectorSetting(const char* settingName, std::vector<double> & values)
{
  this->Internal->GetVectorSetting(settingName, values);
}

//----------------------------------------------------------------------------
bool vtkSMSettings::GetVectorSetting(const char* settingName, std::vector<vtkStdString> & values)
{
  this->Internal->GetVectorSetting(settingName, values);
}

//----------------------------------------------------------------------------
void vtkSMSettings::PrintSelf(ostream& os, vtkIndent indent)
{
  os << indent << "UserSettingsString: ";
  if ( this->UserSettingsString )
    {
    os << "\n" << this->UserSettingsString << "\n";
    }
  else
    {
    os << "(null)";
    }

  os << indent << "SiteSettingsString: ";
  if ( this->SiteSettingsString )
    {
    os << "\n" << this->SiteSettingsString << "\n";
    }
  else
    {
    os << "(null)";
    }
}
