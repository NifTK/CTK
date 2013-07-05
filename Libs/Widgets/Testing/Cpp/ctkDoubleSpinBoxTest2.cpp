/*=========================================================================

  Library:   CTK

  Copyright (c) University College London (UCL). All rights reserved.

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

// Qt includes
#include <QApplication>
#include <QDebug>
#include <QSignalSpy>
#include <QTimer>

// CTK includes
#include "ctkDoubleSpinBox.h"

// STD includes
#include <cstdlib>
#include <iostream>

//-----------------------------------------------------------------------------
int ctkDoubleSpinBoxTest2(int argc, char * argv [] )
{
  QApplication app(argc, argv);

  ctkDoubleSpinBox spinBox;

  // ----------------------------------------
  // Inverted controls property
  // ----------------------------------------

  spinBox.setMinimum(1.0);
  spinBox.setMaximum(15.0);
  spinBox.setValue(8.69);
  spinBox.setInvertedControls(true);
  if (spinBox.invertedControls() != true)
    {
    qDebug()<<"inverted controls could not be enabled.";
    return EXIT_FAILURE;
    }

  qDebug()<<"Inverted controls enabled.";

  qDebug()<<"SingleStep:";
  spinBox.setSingleStep(0.01);
  if (spinBox.singleStep() != 0.01)
    {
    qDebug()<<"singleStep does not correspond. Got: "<<spinBox.singleStep();
    return EXIT_FAILURE;
    }
  spinBox.stepUp();
  if (spinBox.value() != 8.68)
    {
    qDebug()<<"Value does not correspond. Got: "<<spinBox.value();
    return EXIT_FAILURE;
    }
  spinBox.setSingleStep(1.0);
  spinBox.stepDown();
  if (spinBox.displayedValue() != 9.68)
    {
    qDebug()<<"Value does not correspond. Got: "<<spinBox.value();
    return EXIT_FAILURE;
    }

  spinBox.setValue(spinBox.minimum());
  spinBox.stepUp();
  if (spinBox.value() != spinBox.minimum())
    {
    qDebug()<<"Stepping up from minimum value should not change the current value if the controls are inverted.";
    return EXIT_FAILURE;
    }
  spinBox.stepDown();
  if (spinBox.value() == spinBox.minimum())
    {
    qDebug()<<"Stepping down from minimum value should change the current value if the controls are inverted.";
    return EXIT_FAILURE;
    }
  spinBox.setValue(spinBox.maximum());
  spinBox.stepDown();
  if (spinBox.value() != spinBox.maximum())
    {
    qDebug()<<"Stepping down from maximum value should not change the current value if the controls are inverted.";
    return EXIT_FAILURE;
    }
  spinBox.stepUp();
  if (spinBox.value() == spinBox.maximum())
    {
    qDebug()<<"Stepping up from maximum value should change the current value if the controls are inverted.";
    return EXIT_FAILURE;
    }

  spinBox.setInvertedControls(false);
  if (spinBox.invertedControls() != false)
    {
    qDebug()<<"inverted controls could not be disabled.";
    return EXIT_FAILURE;
    }
  qDebug()<<"Inverted controls disabled.";

  spinBox.setValue(spinBox.minimum());
  spinBox.stepDown();
  if (spinBox.value() != spinBox.minimum())
    {
    qDebug()<<"Stepping down from minimum value should not change the current value if the controls are not inverted.";
    return EXIT_FAILURE;
    }
  spinBox.stepUp();
  if (spinBox.value() == spinBox.minimum())
    {
    qDebug()<<"Stepping up from minimum value should change the current value if the controls are not inverted.";
    return EXIT_FAILURE;
    }
  spinBox.setValue(spinBox.maximum());
  spinBox.stepUp();
  if (spinBox.value() != spinBox.maximum())
    {
    qDebug()<<"Stepping up from maximum value should not change the current value if the controls are not inverted.";
    return EXIT_FAILURE;
    }
  spinBox.stepDown();
  if (spinBox.value() == spinBox.maximum())
    {
    qDebug()<<"Stepping down from maximum value should change the current value if the controls are not inverted.";
    return EXIT_FAILURE;
    }

//-----------------------------------------------------------------------------
  spinBox.show();

  if (argc < 2 || QString(argv[1]) != "-I" )
    {
    QTimer::singleShot(100, &app, SLOT(quit()));
    }

  return app.exec();
}
