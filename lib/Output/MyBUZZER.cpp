#include <MyBUZZER.h>

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
                int Melody_Preset1[] = {260, 260, 260, 255, 0, 300, 250, 330};
                int NoteDurs[] = {7, 7, 7, 7, 14, 4, 5, 3};
                int Size_Melody_Preset1 = sizeof(Melody_Preset1)/sizeof(Melody_Preset1[0]);
                for (int playing_Note = 0; playing_Note < Size_Melody_Preset1; playing_Note++) {
                    int noteDur = 1000 / NoteDurs[playing_Note];
                    tone(45, Melody_Preset1[playing_Note], noteDur);
                    int PBTWNotes = noteDur * 1.4;
                    delay(PBTWNotes);
                    noTone(45);
                    break;
                }
        }
}