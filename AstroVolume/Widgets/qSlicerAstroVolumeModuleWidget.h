#ifndef __qSlicerAstroVolumeModuleWidget_h
#define __qSlicerAstroVolumeModuleWidget_h

// CTK includes
#include <ctkVTKObject.h>

// SlicerQt includes
#include "qSlicerAbstractModuleWidget.h"

// Volumes includes
#include "qSlicerAstroVolumeModuleWidgetsExport.h"

class qSlicerAstroVolumeModuleWidgetPrivate;
class vtkMRMLNode;
class vtkMRMLAstroVolumeNode;
class vtkMRMLAstroLabelMapVolumeNode;
class qSlicerVolumeRenderingModuleWidget;
class vtkMRMLVolumeRenderingDisplayNode;
class qMRMLAstroVolumeInfoWidget;
class qSlicerAstroVolumeDisplayWidget;

/// \ingroup Slicer_QtModules_AstroVolume
class Q_SLICER_QTMODULES_ASTROVOLUME_WIDGETS_EXPORT qSlicerAstroVolumeModuleWidget :
  public qSlicerAbstractModuleWidget
{
  Q_OBJECT
  QVTK_OBJECT
public:

  typedef qSlicerAbstractModuleWidget Superclass;
  qSlicerAstroVolumeModuleWidget(QWidget *parent=0);
  virtual ~qSlicerAstroVolumeModuleWidget();

  /// Get volumeRenderingWidget
  Q_INVOKABLE qSlicerVolumeRenderingModuleWidget* volumeRenderingWidget()const;

  /// Get columeRenderingDisplay
  Q_INVOKABLE vtkMRMLVolumeRenderingDisplayNode* volumeRenderingDisplay()const;

  /// Get AstroVolumeInfoWidget
  Q_INVOKABLE qMRMLAstroVolumeInfoWidget* astroVolumeInfoWidget()const;

  /// Get AstroVolumeInfoWidget
  Q_INVOKABLE qSlicerAstroVolumeDisplayWidget* astroVolumeDisplayWidget()const;

public slots:
  void onVisibilityChanged(bool visibility);
  void setComparative3DViews(const char* volumeNodeOneID,
                             const char* volumeNodeTwoID);
  void stopRockView();
  /// Set the MRML node of interest
  void setMRMLVolumeNode(vtkMRMLNode* node);
  void setMRMLVolumeNode(vtkMRMLAstroVolumeNode* volumeNode);
  void setMRMLVolumeNode(vtkMRMLAstroLabelMapVolumeNode* volumeNode);

protected slots:
  void resetOffset(vtkMRMLNode* node);
  void SetPresets(vtkMRMLNode* node);
  void onROICropDisplayCheckBoxToggled(bool toggle);
  void onMRMLVolumeRenderingDisplayNodeModified(vtkObject*);
  void onMRMLDisplayROINodeModified(vtkObject*);
  void onCurrentQualityControlChanged(int);
  void setDisplayROIEnabled(bool);
  void onCropToggled(bool);
  void onInputVolumeChanged(vtkMRMLNode *node);
  void onMRMLSelectionNodeModified(vtkObject* sender);
  void setDisplayConnection(vtkMRMLNode* node);
  void clearPresets();

protected:
  virtual void setup();
  virtual void setMRMLScene(vtkMRMLScene*);
  QScopedPointer<qSlicerAstroVolumeModuleWidgetPrivate> d_ptr;

private:
  Q_DECLARE_PRIVATE(qSlicerAstroVolumeModuleWidget);
  Q_DISABLE_COPY(qSlicerAstroVolumeModuleWidget);
};

#endif
