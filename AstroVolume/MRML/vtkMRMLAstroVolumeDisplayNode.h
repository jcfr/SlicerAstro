#ifndef __vtkMRMLAstroVolumeDisplayNode_h
#define __vtkMRMLAstroVolumeDisplayNode_h

// MRML includes
#include "vtkMRMLScalarVolumeDisplayNode.h"

#include <vtkSlicerAstroVolumeModuleMRMLExport.h>

// VTK includes
#include "vtkStringArray.h"

class vtkAlgorithmOutput;
class vtkImageData;
class vtkMRMLUnitNode;

class VTK_MRML_ASTRO_EXPORT vtkMRMLAstroVolumeDisplayNode : public vtkMRMLScalarVolumeDisplayNode
{
  public:
  static vtkMRMLAstroVolumeDisplayNode *New();
  vtkTypeMacro(vtkMRMLAstroVolumeDisplayNode,vtkMRMLScalarVolumeDisplayNode);
  void PrintSelf(ostream& os, vtkIndent indent);

  virtual vtkMRMLNode* CreateNodeInstance();

  /// 
  /// Set node attributes
  virtual void ReadXMLAttributes( const char** atts);

  /// 
  /// Write this node's information to a MRML file in XML format.
  virtual void WriteXML(ostream& of, int indent);

  /// 
  /// Copy the node's attributes to this object
  virtual void Copy(vtkMRMLNode *node);

  /// 
  /// Get node XML tag name (like Volume, Model)
  virtual const char* GetNodeTagName() {return "AstroVolumeDisplay";};

  ///
  /// Set/Get the CoordinateSystem.
  /// Default is "WCS".
  /// \sa SetSpace(), GetSpace()
  vtkGetStringMacro(Space);
  vtkSetStringMacro(Space);

  ///
  /// Set/Get the SpaceQuantities.
  /// The default is 3 and the values are "length; length; velocity".
  /// \sa SetSpaceQuantities(), GetSpaceQuantities()
  vtkGetObjectMacro(SpaceQuantities, vtkStringArray);
  vtkSetObjectMacro(SpaceQuantities, vtkStringArray);

  ///
  /// Set the i-th SpaceQunatity name
  int SetSpaceQuantity(int ind, const char *name);

  ///
  /// Given a volume node, create a human readable string describing the contents
  virtual std::string GetPixelString(double *ijk);

  ///
  /// Given a coordinate of the volume and unit node, create a string if special formatting is required
  virtual const char* GetDisplayStringFromValue(const double world, vtkMRMLUnitNode *node);

  ///
  /// \brief GetDisplayStringFromValueAxes
  /// \param world
  /// \return Given a coordinate of the volume, create a string if special formatting is required
  ///
  virtual const char *GetDisplayStringFromValueX(const double world);
  virtual const char *GetDisplayStringFromValueY(const double world);
  virtual const char *GetDisplayStringFromValueZ(const double world);

protected:

  char* Space;
  vtkStringArray* SpaceQuantities;

  vtkMRMLAstroVolumeDisplayNode();
  ~vtkMRMLAstroVolumeDisplayNode();
  vtkMRMLAstroVolumeDisplayNode(const vtkMRMLAstroVolumeDisplayNode&);
  void operator=(const vtkMRMLAstroVolumeDisplayNode&);


};

#endif

