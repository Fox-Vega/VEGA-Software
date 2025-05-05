#include <OtherOutputs.h>


void MyPIXEL::MyPIXEL_Setup() {
        pixels.begin();
        pixels.setBrightness(PIXEL_Brightness);
}

void MyPIXEL::MyPIXEL_Uni(int PIXELNum, int Red, int Green, int Blue) {
    if (USEPIXELS == true) {
        pixels.setPixelColor(PIXELNum, pixels.Color(Red, Green, Blue));
        pixels.show();
    }
}

void MyPIXEL::MyPIXEL_Multi(int PIXELNumStart, int PIXELNumEnd, int Red, int Green, int Blue) {
    if (USEPIXELS == true) {
        for (int i = PIXELNumStart; i <= PIXELNumEnd; i++) {
            pixels.setPixelColor(i, pixels.Color(Red, Green, Blue));
        }
        pixels.show();
    }
}

void MyPIXEL::MyPIXEL_Closest(int Azimuth, int Red, int Green, int Blue) {
    if (USEPIXELS == true) {
        int ClosestPIXEL = NUMPIXELS + (Azimuth / 360.0 * NUMPIXELS);
        if (ClosestPIXEL >= 16) {
            ClosestPIXEL = 0;
        }
        pixels.setPixelColor(ClosestPIXEL, pixels.Color(Red, Green, Blue));
        pixels.show();
    }
}

void MyPIXEL::MyPIXEL_Clear() {
    for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Set all pixels to off
    }
    pixels.show();
}

void MyBUZZER::MyBUZZER_Start(int BUZZERNote, int BUZZERDuration) {
    int NoteDuration = 1000 / BUZZERDuration;
    tone(BUZZER_PIN, BUZZERNote, NoteDuration); // Play the note for the specified duration
    delay(BUZZERDuration * 1.4);
    noTone(BUZZER_PIN); // Stop the tone after the duration
    delay(100);
}

void MyBUZZER::MyBUZZER_Preset(int BUZZERPresetNum) {
    switch (BUZZERPresetNum) {
            case '1':
                short Melody_Preset1[] = {260, 260, 260, 255, 0, 300, 250, 330};
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
            case '2':
                short Melody_Preset2[] = {330, 330, 330, 0, 0, 300, 250, 330};
                int NoteDurs2[] = {7, 7, 7, 7, 14, 4, 5, 3};
                int Size_Melody_Preset2 = sizeof(Melody_Preset2)/sizeof(Melody_Preset2[0]);
                for (int playing_Note = 0; playing_Note < Size_Melody_Preset2; playing_Note++) {
                        int noteDur = 1000 / NoteDurs2[playing_Note];
                        tone(BUZZER_PIN, Melody_Preset2[playing_Note], noteDur);
                        int PBTWNotes = noteDur * 1.4;
                        delay(PBTWNotes);
                        noTone(BUZZER_PIN);
                }
                delay(100);
                break;
                
    }
}