#include <Arduino.h>
#include "src/types.h"
#include "src/storage.h"
#include "src/screen.h"
#include "src/matchrun.h"
//25 worked, 19 worked, 18 worked, 5 worked
#define BLUEDETECTOR 5 
#define REDDETECTOR 18

Screen * s;
MatchRun * mrun;
Storage * st;

void setup()
{
    Serial.begin(115200);
    s = new Screen();
    newmatch();
    pinMode(BLUEDETECTOR, INPUT_PULLUP);
    pinMode(REDDETECTOR, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(BLUEDETECTOR), bluescored, FALLING);
    attachInterrupt(digitalPinToInterrupt(REDDETECTOR), redscored, FALLING);
};

void loop()
{
    if (mrun -> is_finished())
    {
        delete mrun;
        mrun = NULL;
        newmatch();
    };
    delay(1000);
};

void newmatch() 
{
    mrun = new MatchRun(s);
}

void bluescored()
{
    if (mrun != NULL && !mrun -> is_finished())
    {
        mrun->blue_score_handle();
    };
}

void redscored()
{
    if (mrun != NULL && !mrun -> is_finished())
    {
        mrun->red_score_handle();
    };
}