Library Name：MuVisionSensor
Device Name：MU Vision Sensor
Model Name：MUVS-AB2
Website：www.morpx.com
Support：support@morpx.com

Morpx Inc 2019

======
Directory structure:

src/  -- library source code
examples/  -- Arduino examples
  getTargetPositions/ -- default example for detection using library calls.
  direct_i2c_examples/ -- examples for detection using direct i2c communication.


======
Get Started:

To use the MuVisionSensor library in Arduino, follow these 4 steps:

1. Add MuVisionSensor library in Arduino
2. add MuVisionSensor.h and Wire.h in your Arduino code
  #include <Wire.h>
  #include "MuVisionSensor.h"

3. In your setup() function, add
  Wire.begin();
  Mu.begin(&Wire, kI2CMode);

  and set the vision type
  Mu.VisionBegin(VISION_BALL_DETECT);

4. In your loop() function, read the status variable of your detection.
  int x = Mu.GetValue(VISION_BALL_DETECT, kXValue);
  int y = Mu.GetValue(VISION_TYPE, kYValue);
  int width = Mu.GetValue(VISION_TYPE, kWidthValue);
  int height = Mu.GetValue(VISION_TYPE, kHeightValue);

For more usage examples or detection other supported objects, please check 
the "getTargetPositions" example code.


======
Chang Log:

V1.1.4 20190117
1.Fix failed lock causing the sensor to hang
2.Modified the LED library.
3.Modified some of the enum names.
