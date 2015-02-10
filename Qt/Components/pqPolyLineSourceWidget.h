/*=========================================================================

   Program: ParaView
   Module:    pqPolyLineSourceWidget.h

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
#ifndef __pqPolyLineSourceWidget_h
#define __pqPolyLineSourceWidget_h

#include "pqHandleWidget.h"
#include "pqComponentsModule.h"

class pqServer;

/// GUI for PolyLineWidgetRepresentation. Enables 3D placement of points.
class PQCOMPONENTS_EXPORT pqPolyLineSourceWidget : public pqHandleWidget
{
  typedef pqHandleWidget Superclass;

  Q_OBJECT

public:
  pqPolyLineSourceWidget(vtkSMProxy* o, vtkSMProxy* pxy, QWidget* p = 0);
  virtual ~pqPolyLineSourceWidget();

protected slots:
  void addPoint();
  void removePoints();

protected:
  void createWidget(pqServer*);

  /// Snap currently selected point to surface.
  virtual void pick(double x, double y, double z);

private:
  pqPolyLineSourceWidget(const pqPolyLineSourceWidget&); // Not implemented.
  void operator=(const pqPolyLineSourceWidget&); // Not implemented.

  class pqImplementation;
  pqImplementation* const Implementation;

};

#endif
