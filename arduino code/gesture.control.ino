const int trigger1 = 5; 
const int echo1 = 6;    
const int trigger2 = 9; 
const int echo2 = 10;   

long time_taken;
int dist, distL, distR;

long duration; 
float r;
unsigned long temp = 0;
int temp1 = 0;
int l = 0;

void find_distance(void);
void calculate_distance(int trigger, int echo);

void find_distance(void) { 
    digitalWrite(trigger1, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger1, LOW);
    duration = pulseIn(echo1, HIGH, 5000);
    r = 3.4 * duration / 2;                 
    distL = r / 100.00;

    digitalWrite(trigger2, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger2, LOW);
    duration = pulseIn(echo2, HIGH, 5000);
    r = 3.4 * duration / 2;     
    distR = r / 100.00;
    delay(100);
}

void setup() {
    Serial.begin(9600); 
    pinMode(trigger1, OUTPUT); 
    pinMode(echo1, INPUT); 
    pinMode(trigger2, OUTPUT); 
    pinMode(echo2, INPUT); 
}

void calculate_distance(int trigger, int echo) {
    digitalWrite(trigger, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger, LOW);
    time_taken = pulseIn(echo, HIGH);
    dist = time_taken * 0.034 / 2;
    if (dist > 50)
        dist = 50;
}

void loop() { 
    calculate_distance(trigger1, echo1);
    distL = dist; 
    calculate_distance(trigger2, echo2);
    distR = dist; 

    Serial.print("L=");
    Serial.println(distL);
    Serial.print("R=");
    Serial.println(distR);


    if ((distL > 25 && distR > 25) && (distL < 50 && distR < 50)) { 
        delay(500);
    }

    calculate_distance(trigger1, echo1);
    distL = dist;

    calculate_distance(trigger2, echo2);
    distR = dist;



    
    if (distL >= 10 && distL <= 20) {
        delay(50); 
        calculate_distance(trigger1, echo1);
        distL = dist;
        if (distL >= 10 && distL <= 20) {
            Serial.println("Left Locked");
            while (distL <= 40) {
                calculate_distance(trigger1, echo1);
                distL = dist;
                if (distL < 15) { 
                    Serial.println("Vup");
                    delay(300);
                }
                if (distL > 20) { 
                    Serial.println("Vdown");
                    delay(300);
                }
            }
        }
    }

    
    if (distR >= 10 && distR <= 20) {
        delay(50); 
        calculate_distance(trigger2, echo2);
        distR = dist;
        if (distR >= 10 && distR <= 20) {
            Serial.println("Right Locked");
            while (distR <= 40) {
                calculate_distance(trigger2, echo2);
                distR = dist;
                if (distR < 15) { 
                    Serial.println("Rewind");
                    delay(300);
                }
                if (distR > 20) { 
                    Serial.println("Forward");
                    delay(300);
                }
            }
        }
    }

    
    if (distR <= 8 && distR >= 0) { 
        temp = millis();
        while (millis() <= (temp + 300))
            find_distance();

        Serial.println("next");
    }

    delay(200);
}
