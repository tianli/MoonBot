/*
 * mu_vision_sensor_uart_hw_interface.cpp
 *
 *  Created on: 2018年8月8日
 *      Author: ysq
 */

#include "mu_vision_sensor_i2c_hw_interface.h"

MuVisionSensorI2C::MuVisionSensorI2C(MuVsI2C* i2c_port, uint32_t address)
    : MuVsI2CMethod(address),
      i2c_port_(i2c_port){
}

MuVisionSensorI2C::~MuVisionSensorI2C() {}

uint32_t MuVisionSensorI2C::I2CRead(uint8_t reg_address, uint8_t* temp) {
  int result;
  result = i2c_port_->write((uint8_t)mu_address_<<1, (const char *)&reg_address, 1);
  if (result !=0)
      return 1;
  result = i2c_port_->read((uint8_t)mu_address_<<1, (char *)temp, 1);
  if (result !=0)
      return 1;
  return MU_OK;
}

uint32_t MuVisionSensorI2C::I2CWrite(uint8_t reg_address, uint8_t value) {
  int ret = MU_OK;
  ret = i2c_port_->writeRegister((uint8_t)mu_address_<<1,reg_address,value);
  return ret;
}


