
#ifndef ENCODER_H
#define ENCODER_H


class Encoder
{

    Encoder();
    void begin();

    void pollSpeed();

    float getLeftSpeed();
    float getRightSpeed();

    // ISR_getLeftEncoderTime();
    // ISR_getRightEncoderTime();

}

#endif //ENCODER_H