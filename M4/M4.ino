#define CLK 3
#define F_CLK 250000.0
#define T_CLK_HALF ((unsigned int) (1000000.0 / (2.0 * F_CLK)))

void setup() {
    pinMode(CLK, OUTPUT);
}

void loop() {
    digitalWrite(CLK, HIGH);
    delayMicroseconds(T_CLK_HALF);
    digitalWrite(CLK, LOW);
    delayMicroseconds(T_CLK_HALF);
}