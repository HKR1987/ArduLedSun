# ArduLedSun start
Po włączeniu podajemy na UART aktualną godzinę w formacie GGMMSS np. 143020

Na porcie UART zwracana jest aktualna godzina

Na chwilę obecną są dostępne 4 funkcje:

wlaczWszystkie(GGMMSS);

wylaczWszystkie(GGMMSS);

rozjasniaj(GGMMSS, GGMMSS);

przyciemniaj(GGMMSS, GGMMSS);

Rozjasniaj i przyciemniaj posiada dwa parametry: pierwszy 'od', drugi 'do' - oznacza ile czasu będzie trwało rozjaśnianie/przyciemnianie
