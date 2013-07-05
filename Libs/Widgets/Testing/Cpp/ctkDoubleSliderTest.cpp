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

// CTK includes
#include "ctkDoubleSlider.h"
#include "ctkTest.h"

#include <iostream>

// ----------------------------------------------------------------------------
class ctkDoubleSliderTester: public QObject
{
  Q_OBJECT

public:
private slots:
  void testWheelEvents();
};

// ----------------------------------------------------------------------------
void ctkDoubleSliderTester::testWheelEvents()
{
  ctkDoubleSlider* slider;
  slider = new ctkDoubleSlider();

  slider->setMinimum(0.0);
  slider->setMaximum(10.0);
  slider->setValue(5.0);
  slider->setSingleStep(0.1);
  slider->setPageStep(1.0);
//  slider->setInvertedControls(true);
/*
  QPoint middleOfSlider(slider->width() / 2, slider->height() / 2);
  QPoint cursorPosition = slider->mapToGlobal(middleOfSlider);
  QWheelEvent* scrollingUp = new QWheelEvent(middleOfSlider,
    cursorPosition,
    1,
    Qt::NoButton,
    Qt::NoModifier);
  std::cout << "Test Single Step Add with Inverted Controls" << std::endl;
  QApplication::instance()->sendEvent(slider, scrollingUp);
*/
  QTest::keyClick(slider, Qt::Key_Up, Qt::NoModifier, 1000);
  QCoreApplication::processEvents();

  if (!qFuzzyCompare(slider->value(), 5.1))
    {
    std::cerr << "ctkDoubleSlider:: Single Step Add failed" << slider->value() << std::endl;
    std::exit(EXIT_FAILURE);
    }
}

// ----------------------------------------------------------------------------
CTK_TEST_MAIN(ctkDoubleSliderTest)

#include "moc_ctkDoubleSliderTest.cpp"
