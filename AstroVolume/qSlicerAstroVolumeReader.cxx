/*==============================================================================

  Program: 3D Slicer

  Copyright (c) Kitware Inc.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Davide Punzo, Kapteyn Astronomical Institute.
==============================================================================*/

// Qt includes
#include <QFileInfo>

// SlicerQt includes
#include "qSlicerAstroVolumeIOOptionsWidget.h"
#include "qSlicerAstroVolumeReader.h"

// Slicer includes
#include <vtkSlicerVolumesLogic.h>

// Logic includes
#include <vtkSlicerApplicationLogic.h>
#include "vtkSlicerAstroVolumeLogic.h"

// MRML includes
#include <vtkMRMLLabelMapVolumeNode.h>
#include <vtkMRMLScalarVolumeNode.h>
#include <vtkMRMLSelectionNode.h>

// VTK includes
#include <vtkSmartPointer.h>
#include <vtkStringArray.h>

//-----------------------------------------------------------------------------
class qSlicerAstroVolumeReaderPrivate
{
  public:
  vtkSmartPointer<vtkSlicerVolumesLogic> Logic;
};

//-----------------------------------------------------------------------------
qSlicerAstroVolumeReader::qSlicerAstroVolumeReader(QObject* _parent)
  : Superclass(_parent)
  , d_ptr(new qSlicerAstroVolumeReaderPrivate)
{
}

//-----------------------------------------------------------------------------
qSlicerAstroVolumeReader::qSlicerAstroVolumeReader(vtkSlicerVolumesLogic* logic, QObject* _parent)
  : Superclass(_parent)
  , d_ptr(new qSlicerAstroVolumeReaderPrivate)
{
  this->setLogic(logic);
}

//-----------------------------------------------------------------------------
qSlicerAstroVolumeReader::~qSlicerAstroVolumeReader()
{
}

//-----------------------------------------------------------------------------
void qSlicerAstroVolumeReader::setLogic(vtkSlicerVolumesLogic* logic)
{
  Q_D(qSlicerAstroVolumeReader);
  d->Logic = logic;
}

//-----------------------------------------------------------------------------
vtkSlicerVolumesLogic* qSlicerAstroVolumeReader::logic()const
{
  Q_D(const qSlicerAstroVolumeReader);
  return d->Logic.GetPointer();
}

//-----------------------------------------------------------------------------
QString qSlicerAstroVolumeReader::description()const
{
  return "AstroVolume";
}

//-----------------------------------------------------------------------------
qSlicerIO::IOFileType qSlicerAstroVolumeReader::fileType()const
{
  return QString("VolumeFile");
}

//-----------------------------------------------------------------------------
QStringList qSlicerAstroVolumeReader::extensions()const
{
  return QStringList()
    << "Volume (*.fits)"
    << "Image (*.fits)"
    << "All Files (*)";
}

//-----------------------------------------------------------------------------
qSlicerIOOptions* qSlicerAstroVolumeReader::options()const
{
  return new qSlicerAstroVolumeIOOptionsWidget;
}

//-----------------------------------------------------------------------------
bool qSlicerAstroVolumeReader::load(const IOProperties& properties)
{
  Q_D(qSlicerAstroVolumeReader);
  Q_ASSERT(properties.contains("fileName"));
  QString fileName = properties["fileName"].toString();

  QString name = QFileInfo(fileName).baseName();

  if (properties.contains("name"))
    {
    name = properties["name"].toString();
    }
  int options = 0;
  if (properties.contains("labelmap"))
    {
    options |= properties["labelmap"].toBool() ? 0x1 : 0x0;
    }
  if (properties.contains("center"))
    {
    options |= properties["center"].toBool() ? 0x2 : 0x0;
    }
  if (properties.contains("singleFile"))
    {
    options |= properties["singleFile"].toBool() ? 0x4 : 0x0;
    }
  if (properties.contains("autoWindowLevel"))
    {
    options |= properties["autoWindowLevel"].toBool() ? 0x8: 0x0;
    }
  if (properties.contains("discardOrientation"))
    {
    options |= properties["discardOrientation"].toBool() ? 0x10 : 0x0;
    }
  vtkSmartPointer<vtkStringArray> fileList;
  if (properties.contains("fileNames"))
    {
    fileList = vtkSmartPointer<vtkStringArray>::New();
    foreach(QString file, properties["fileNames"].toStringList())
      {
      fileList->InsertNextValue(file.toLatin1());
      }
    }


  Q_ASSERT(d->Logic);

  vtkMRMLVolumeNode* node = d->Logic->AddArchetypeVolume(
    fileName.toLatin1(),
    name.toLatin1(),
    options,
    fileList.GetPointer());

  if (node)
    {
    vtkSlicerApplicationLogic* appLogic =
      d->Logic->GetApplicationLogic();
    vtkMRMLSelectionNode* selectionNode =
      appLogic ? appLogic->GetSelectionNode() : 0;
    if (selectionNode)
      {
      if (vtkMRMLLabelMapVolumeNode::SafeDownCast(node))
        {
        selectionNode->SetReferenceActiveLabelVolumeID(node->GetID());
        }
      else
        {
        selectionNode->SetReferenceActiveVolumeID(node->GetID());
        }
      if (appLogic)
        {
        appLogic->PropagateVolumeSelection(); // includes FitSliceToAll by default
        }
      }
    this->setLoadedNodes(QStringList(QString(node->GetID())));
    }
  else
    {
    this->setLoadedNodes(QStringList());
    }

  return node != 0;
}
