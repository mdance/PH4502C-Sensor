#include <Arduino.h>
#include "ph4502c_sensor.h"

void PH4502C_Sensor::init() {
    pinMode(this->_ph_level_pin, INPUT);
    if (this->_temp_pin != PH4502C_TEMPERATURE_DISABLED) {
      pinMode(this->_temp_pin, INPUT);
    }
}

void PH4502C_Sensor::recalibrate(float calibration) {
    this->_calibration = calibration;
}

float PH4502C_Sensor::read_ph_level() {
    float total = 0.0f;

    for (int i = 0; i < this->_reading_count; i++) {
        total += analogRead(this->_ph_level_pin);
        delay(this->_reading_interval);
    }

    float avg_adc = total / this->_reading_count;
    float voltage = (avg_adc / this->_adc_resolution) * PH4502C_VOLTAGE;
    
    float ph = this->_calibration + (PH4502C_MID_VOLTAGE - voltage) / PH4502C_PH_VOLTAGE_PER_PH;

    return ph;
}

float PH4502C_Sensor::read_ph_level_single() {
    float adc = analogRead(this->_ph_level_pin);
    float voltage = (adc / this->_adc_resolution) * PH4502C_VOLTAGE;

    return this->_calibration + (PH4502C_MID_VOLTAGE - voltage) / PH4502C_PH_VOLTAGE_PER_PH;
}

int PH4502C_Sensor::read_temp() {
    if (this->_temp_pin == PH4502C_TEMPERATURE_DISABLED) {
        return 0;
    }

    return analogRead(this->_temp_pin);
}

