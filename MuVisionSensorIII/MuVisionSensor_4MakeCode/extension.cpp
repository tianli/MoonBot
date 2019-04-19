#include "pxt.h"
#include "MuVisionSensor.h"
using namespace pxt;
//% color="#ff6600" weight=20 icon="\uf085"
namespace muvs {
    MuVisionSensor *Mu0;
    MuVisionSensor *Mu1;
    MuVisionSensor *Mu2;
    MuVisionSensor *Mu3;
    MuVisionSensor* MU[4]={Mu0,Mu1,Mu2,Mu3};
    MicroBitSerial *serial=nullptr;
    MicroBitI2C *i2c=nullptr; 

    //% 
    void begin(int id, int port){
        MU[id] = new MuVisionSensor(0x60+id);
        MuVisionSensor *mu = MU[id];
        if(port==0){
            serial=new MicroBitSerial(MICROBIT_PIN_P13,MICROBIT_PIN_P16);
            mu->begin(serial,kSerialMode);
        }
        else if(port==1)
        {
            i2c=new MicroBitI2C(I2C_SDA0, I2C_SCL0);
            mu->begin(i2c,kI2CMode);
        }
    }
    //% 
    void VisionBegin(int id, int status, int type){
        MuVisionSensor *mu = MU[id];
        type=1<<(type-1);
        if(status)
            while(mu->VisionBegin(type)!=MU_OK);
        else
            mu->VisionSetStatus(type,false);
    }
    //% 
    void reset(int id){
        MuVisionSensor *mu = MU[id];
        while(mu->SensorSetDefault()!=MU_OK);
    }
    //%
    void set_led(int id,int led, int detected_color, int undetected_color) {
        MuVisionSensor *mu = MU[id];
        while(mu->LedSetColor(MuVsLed(led), MuVsLedColor(detected_color), MuVsLedColor(undetected_color), 1) != MU_OK);
    }
    //%
    void set_level(int id, int type,int level){
        MuVisionSensor *mu = MU[id];
        type=1<<(type-1);
        while(mu->VisionSetLevel(type, MuVsVisionLevel(level)) != MU_OK);
    }
    //%
    void set_zoom(int id, int level){
        MuVisionSensor *mu = MU[id];
        while(mu->CameraSetZoom(MuVsCameraZoom(level)) != MU_OK);
    }
    //%
    void set_baudrate(int id, int baud){
        MuVisionSensor *mu = MU[id];
        while(mu->UartSetBaudrate(MuVsBaudrate(baud)) != MU_OK);
    }
    //%
    void set_WB(int id, int wb){
        MuVisionSensor *mu = MU[id];
        while(mu->CameraSetAwb(MuVsCameraWhiteBalance(wb)) != MU_OK);
    }
    //%
    void onOff(int id,int on){
        MuVisionSensor *mu = MU[id];
        while(mu->CameraSetFPS(MuVsCameraFPS(on)) != MU_OK);
    }
    //%
    int detected(int id, int type){
        MuVisionSensor *mu = MU[id];
        type=1<<(type-1);
        int ret = mu->GetValue(type,kStatus);
        return ret;
    }
    //%
    int MuVs2GetColorRCGLabel(int id, int x ,int y){
        MuVisionSensor *mu = MU[id];
        static int x_last = -1;
        static int y_last = -1;
        x = x>100 ? 100:(x<0 ? 0:x);
        y = y>100 ? 100:(y<0 ? 0:y);
        if (x != x_last) {
            x_last = x;
            mu->write(VISION_COLOR_RECOGNITION, kXValue, x);
        }
        if (y != y_last) {
            y_last = y;
            mu->write(VISION_COLOR_RECOGNITION, kYValue, y);
        }
        return mu->GetValue(VISION_COLOR_RECOGNITION, kStatus);
    }
    //%
    int MuVs2GetColorDetectLabel(int id, int label) {
        MuVisionSensor *mu = MU[id];
        static int label_last = -1;
        if (label_last != label) {
            label_last = label;
            mu->write(VISION_COLOR_DETECT, kLabel, label);
        }
        return mu->GetValue(VISION_COLOR_DETECT, kStatus);
    }
    //%
    int get_value(int id, int type, int item){
        MuVisionSensor *mu = MU[id];
        type=1<<(type-1);
        return mu->GetValue(type,MuVsObjectInf(item));    
    }
    //%
    int get_color_value(int id, int item){
        MuVisionSensor *mu = MU[id];
        return mu->GetValue(VISION_COLOR_RECOGNITION,MuVsObjectInf(item));    
    }
    //%
    int get_shape_card_type(int id, int label){
        MuVisionSensor *mu = MU[id];
        return mu->GetValue(VISION_SHAPE_CARD_DETECT, kLabel) == label;
    }
    //%
    int get_traffic_card_type(int id, int label){
        MuVisionSensor *mu = MU[id];
        return mu->GetValue(VISION_TRAFFIC_CARD_DETECT, kLabel) == label;
    }
    //%
    int get_number_card_type(int id, int label){
        MuVisionSensor *mu = MU[id];
        return mu->GetValue(VISION_NUM_CARD_DETECT, kLabel) == label;
    }
    //%
    int get_color_recognize(int id, int label){
        MuVisionSensor *mu = MU[id];
        return mu->GetValue(VISION_COLOR_RECOGNITION, kLabel) == label;
    }

}
