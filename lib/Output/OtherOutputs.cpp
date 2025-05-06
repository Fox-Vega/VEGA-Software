#include <OtherOutputs.h>
#include <Output.h>


void MyPIXEL::setup() {
        pixels.begin();
        pixels.setBrightness(PIXEL_Brightness);
}

void MyPIXEL::uni(int PIXELNum, int Red, int Green, int Blue) {
    if (USEPIXELS == true) {
        pixels.setPixelColor(PIXELNum, pixels.Color(Red, Green, Blue));
        pixels.show();
    }
}

void MyPIXEL::multi(int PIXELNumStart, int PIXELNumEnd, int Red, int Green, int Blue) {
    if (USEPIXELS == true) {
        for (int i = PIXELNumStart; i <= PIXELNumEnd; i++) {
            mypixel.uni(i, Red, Green, Blue);
        }
    }
}

void MyPIXEL::closest(int Azimuth, int Red, int Green, int Blue) {
    if (USEPIXELS == true) {
        int ClosestPIXEL = NUMPIXELS + (Azimuth / 360.0 * NUMPIXELS);
        if (ClosestPIXEL >= 16) {
            ClosestPIXEL = 0;
        }
        mypixel.uni(ClosestPIXEL, Red, Green, Blue);
    }
}

void MyPIXEL::clear() {
    for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    }
    pixels.show();
}


void MyBUZZER::start(int BUZZERNote, int BUZZERDuration) {
    int NoteDuration = 1000 / BUZZERDuration;
    tone(BUZZER_PIN, BUZZERNote, NoteDuration);
    delay(BUZZERDuration * 1.4);
    noTone(BUZZER_PIN);
    delay(100);
}

void MyBUZZER::preset(int BUZZERPresetNum) {
    switch (BUZZERPresetNum) {
        case '1':
            int Melody_Preset1[] = {260, 260, 260, 255, 0, 300, 250, 330};
            int NoteDurs[] = {7, 7, 7, 7, 14, 4, 5, 3};
            int Size_Melody_Preset1 = sizeof(Melody_Preset1)/sizeof(Melody_Preset1[0]);
            for (int playing_Note = 0; playing_Note < Size_Melody_Preset1; playing_Note++) {
                    int noteDur = 1000 / NoteDurs[playing_Note];
                    tone(BUZZER_PIN, Melody_Preset1[playing_Note], noteDur);
                    int PBTWNotes = noteDur * 1.4;
                    delay(PBTWNotes);
                    noTone(BUZZER_PIN);
            }
            delay(100);
            break;       
    }
}