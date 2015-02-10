/*=========================================================================

   Program: ParaView
   Module:    pqPolyLineSourceWidget.cxx

   Copyright (c) 2005,2006 Sandia Corporation, Kitware Inc.
   All rights reserved.

   ParaView is a free software; you can redistribute it and/or modify it
   under the terms of the ParaView license version 1.2.

   See License_v1.2.txt for the full ParaView license.
   A copy of this license can be obtained by contacting
   Kitware Inc.
   28 Corporate Drive
   Clifton Park, NY 12065
   USA

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

========================================================================*/
#include "pqPolyLineSourceWidget.h"
#include "ui_pqPolyLineSourceControls.h"

#include "pq3DWidgetFactory.h"
#include "pqPropertyLinks.h"
#include "pqSignalAdaptorTreeWidget.h"

#include "vtkSMNewWidgetRepresentationProxy.h"

class pqPolyLineSourceWidget::pqImplementation
{
public:
  pqImplementation()
  {
    this->PointsAdaptor = NULL;
  }

  ~pqImplementation()
  {
    delete this->PointsAdaptor;
  }

  /// Stores the Qt widgets
  QWidget ControlsContainer;
  Ui::pqPolyLineSourceControls Controls;

  pqPropertyLinks Links;
  pqSignalAdaptorTreeWidget* PointsAdaptor;
};


//-----------------------------------------------------------------------------
pqPolyLineSourceWidget::pqPolyLineSourceWidget(
  vtkSMProxy* _smproxy, vtkSMProxy* pxy, QWidget* p) :
  Superclass(_smproxy, pxy, p),
  Implementation(new pqImplementation())
{
  this->Implementation->Controls.setupUi(
    &this->Implementation->ControlsContainer);
  this->Implementation->PointsAdaptor = new pqSignalAdaptorTreeWidget(
    this->Implementation->Controls.HandlePositions, true);

  QObject::connect(&this->Implementation->Links,
    SIGNAL(qtWidgetChanged()),
    this, SLOT(setModified()));

  QObject::connect(&this->Implementation->Links,
    SIGNAL(qtWidgetChanged()),
    this, SLOT(render()));

  QObject::connect(this->Implementation->Controls.AddPoint, SIGNAL(clicked()),
    this, SLOT(addPoint()));
  QObject::connect(this->Implementation->Controls.Delete, SIGNAL(clicked()),
    this, SLOT(removePoints()));

  this->layout()->addWidget(&this->Implementation->ControlsContainer);

  this->Implementation->Links.addPropertyLink(
    this->Implementation->PointsAdaptor, "values",
    SIGNAL(valuesChanged()),
    pxy, pxy->GetProperty("Points"));
}

//-----------------------------------------------------------------------------
pqPolyLineSourceWidget::~pqPolyLineSourceWidget()
{
  delete this->Implementation;
}

//-----------------------------------------------------------------------------
void pqPolyLineSourceWidget::addPoint()
{
  std::cout << "Adding point\n";
  QTreeWidgetItem* newItem = this->Implementation->PointsAdaptor->growTable();
  QTreeWidget* tree = this->Implementation->Controls.HandlePositions;
  tree->setCurrentItem(newItem);
  // edit the first column.
  tree->editItem(newItem, 0);
}

//-----------------------------------------------------------------------------
void pqPolyLineSourceWidget::removePoints()
{
  std::cout << "removing point\n";
  QList<QTreeWidgetItem*> items =
    this->Implementation->Controls.HandlePositions->selectedItems();
  foreach (QTreeWidgetItem* item, items)
    {
    if (this->Implementation->Controls.HandlePositions->topLevelItemCount() <= 1)
      {
      qDebug() <<
        "At least one point location is required. Deletion request ignored.";
      // don't allow deletion of the last point.
      break;
      }
    delete item;
    }
}

//-----------------------------------------------------------------------------
void pqPolyLineSourceWidget::createWidget(pqServer* server)
{

}

//-----------------------------------------------------------------------------
void pqPolyLineSourceWidget::pick(double x, double y, double z)
{
  vtkSMProxy* widget = this->getWidgetProxy();

  QList<QTreeWidgetItem*> items =
    this->Implementation->Controls.HandlePositions->selectedItems();
  if (items.size() > 0)
    {
    QTreeWidgetItem* item = items.front();
    item->setText(0, QString("%1").arg(x));
    item->setText(1, QString("%1").arg(y));
    item->setText(2, QString("%1").arg(z));
    }

  widget->UpdateVTKObjects();
  this->setModified();
  this->render();
}
