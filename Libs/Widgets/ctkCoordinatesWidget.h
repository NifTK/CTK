/*=========================================================================

  Library:   CTK

  Copyright (c) Kitware Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0.txt

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=========================================================================*/

#ifndef __ctkCoordinatesWidget_h
#define __ctkCoordinatesWidget_h

// Qt includes
#include <QWidget>
#include <QWeakPointer>

// CTK includes
#include "ctkDoubleSpinBox.h"
#include "ctkWidgetsExport.h"

/// \ingroup Widgets
///
/// ctkCoordinatesWidget is a simple container of dimension coordinates.
/// For each coordinate a double spinbox is associated, everytime a value is
/// modified, the signal valueChanged is fired.
/// TODO: use pimpl
class CTK_WIDGETS_EXPORT ctkCoordinatesWidget : public QWidget
{
  Q_OBJECT

  Q_PROPERTY(int dimension READ dimension WRITE setDimension)
  /// This property controls whether the coordinates must be normalized.
  /// If true, the norm of the coordinates is enforced to be 1.
  /// False by default.
  Q_PROPERTY(bool normalized READ isNormalized WRITE setNormalized)

  /// This property controls how many decimals should be displayed by the
  /// spinboxes. This number might not be used depending on decimalsOption.
  /// In general, the coordinatesWidget tries to use the same number of
  /// decimals for all the spinboxes except if numbers require more decimals.
  Q_PROPERTY(int decimals READ decimals WRITE setDecimals)
  /// This property provides more controls over the decimals.
  /// \sa ctkDoubleSpinBox::DecimalsOptions, decimals
  Q_PROPERTY(ctkDoubleSpinBox::DecimalsOptions decimalsOption READ decimalsOption WRITE setDecimalsOption)

  Q_PROPERTY(double singleStep  READ singleStep WRITE setSingleStep STORED false)
  /// This property controls the minimum value of the spinboxes.
  /// No limit (-max double) by default.
  /// \sa minimum(), setMinimum(), maximum, sizeHintPolicy
  Q_PROPERTY(double minimum READ minimum WRITE setMinimum)
  /// This property the maximum value of the spinboxes.
  /// No limit (max double) by default.
  /// \sa maximum(), setMaximum(), minimum, sizeHintPolicy
  Q_PROPERTY(double maximum READ maximum WRITE setMaximum)

  Q_PROPERTY(QString coordinates READ coordinatesAsString WRITE setCoordinatesAsString)

  /// This property controls the size hint of the spinboxes.
  /// ctkDoubleSpinBox::SizeHintByValue by default
  /// \sa ctkDoubleSpinBox::SizeHintPolicy
  Q_PROPERTY(ctkDoubleSpinBox::SizeHintPolicy sizeHintPolicy READ sizeHintPolicy WRITE setSizeHintPolicy)

public:
  explicit ctkCoordinatesWidget(QWidget* parent = 0);
  virtual ~ctkCoordinatesWidget();

  /// Set/Get the dimension of the point
  /// The default dimension is 3
  void setDimension(int dim);
  int dimension() const;

  /// Get the number of decimals of each coordinate spin box
  /// The default number of decimals is 3.
  int decimals() const;

  /// Return the decimalsOption property value
  /// \sa decimalsOption
  ctkDoubleSpinBox::DecimalsOptions decimalsOption()const;
  /// Set the decimalsOption property value.
  /// \sa decimalsOption
  void setDecimalsOption(ctkDoubleSpinBox::DecimalsOptions option);

  /// Set/Get the single step of each coordinate spin box
  /// The default single step is 1.
  void setSingleStep(double step);
  double singleStep() const;

  /// Set/Get the minimum value of each coordinate spin box
  /// The default minimum is -100000.
  void setMinimum(double minimum);
  double minimum() const;

  /// Set/Get the maximum value of each coordinate spin box
  /// The default maximum is 100000.
  void setMaximum(double minimum);
  double maximum() const;

  /// Set the minimum and maximum of each coordinate spinbox at once.
  /// \sa minimum, maximum
  void setRange(double minimum, double maximum);

  /// Change the normalized property. If \a normalize is true, it normalizes
  /// the current coordinates, the range of possible values is reset to [-1, 1].
  /// \sa isNormalized
  void setNormalized(bool normalize);
  bool isNormalized()const;

  /// Return the norm of the coordinates.
  double norm()const;
  /// Return the squared norm of the coordinates.
  double squaredNorm()const;

  /// Set/Get the coordinates. Use commas to separate elements, spaces are
  /// allowed: e.g. "0,0.0, 0."
  void setCoordinatesAsString(QString pos);
  QString coordinatesAsString()const;

  /// Set/Get the coordinates
  /// The default values are 0.
  void setCoordinates(double* pos);
  double const * coordinates()const;

  /// Convenient function that sets up to 4 elements of the coordinates.
  void setCoordinates(double x, double y = 0., double z = 0., double w = 0.);

  /// Set the sizeHintPolicy property value.
  /// \sa sizeHintPolicy
  void setSizeHintPolicy(ctkDoubleSpinBox::SizeHintPolicy newSizeHintPolicy);
  /// Return the sizeHintPolicy property value.
  /// \sa sizeHintPolicy
  ctkDoubleSpinBox::SizeHintPolicy sizeHintPolicy()const;

  /// Set/Get the value proxy of the spinboxes used to display the coordinates.
  /// \sa setValueProxy(), valueProxy()
  void setValueProxy(ctkValueProxy* proxy);
  ctkValueProxy* valueProxy() const;

  /// Return the spinbox identitfied by id
  ctkDoubleSpinBox* spinBox(int id);
public Q_SLOTS:
  void normalize();

  /// Set the number of decimals of each coordinate spin box.
  void setDecimals(int decimals);

Q_SIGNALS:
  ///
  /// valueChanged is fired anytime a coordinate is modified, the returned
  /// value is the point coordinates
  /// TODO: Don't fire the signal if the new values are not changed 
  void coordinatesChanged(double* pos);

protected Q_SLOTS:
  void updateCoordinate(double);
  void updateCoordinates();
  void updateDecimals();
  void updateOtherDecimals(int);
  void setTemporaryDecimals(int);
  void onValueProxyAboutToBeModified();
  void onValueProxyModified();

protected:
  void addSpinBox();

  /// Normalize coordinates vector and return the previous norm.
  static double normalize(double* coordinates, int dimension);

  /// Compute the norm of a coordinates \a dimension vector
  static double norm(double* coordinates, int dimension);
  static double squaredNorm(double* coordinates, int dimension);

  /// Return the ideal number of decimals based on the spinBox value or
  /// 16 if there is no "good" number of decimals.
  /// \sa ctk::significantDecimals()
  static int spinBoxSignificantDecimals(ctkDoubleSpinBox* spinBox);

  int     Decimals;
  ctkDoubleSpinBox::DecimalsOptions DecimalsOption;
  double  SingleStep;
  double  Minimum;
  double  Maximum;
  bool    Normalized;
  int     Dimension;
  ctkDoubleSpinBox::SizeHintPolicy SizeHintPolicy;

  double* Coordinates;
  QList<int> LastUserEditedCoordinates;
  bool    ChangingDecimals;
  QWeakPointer<ctkValueProxy> Proxy;
};

#endif
