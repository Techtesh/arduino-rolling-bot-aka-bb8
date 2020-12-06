//delays optimised for LEDs need to change for MOTORs

//BB8 Mitthoogiri Mark_3 (State version)

//Library for Servo
#include<Servo.h>
Servo myservo;

//Pins
const int MD1_PWM_Pin = 11;
const int MD2_PWM_Pin = 10;

const int MD1_Dir_Pin = 12;
//const int MD1_DirR_Pin = 13;
const int MD2_Dir_Pin = 7;
//const int MD2_DirR_Pin = 8;

const int MD1_Brk_Pin = 8;
const int MD2_Brk_Pin = 4;


//Value Variables
int MD1_PWMV = 0;
int MD2_PWMV = 0;
boolean MD1_Dir = HIGH ;
boolean MD2_Dir = HIGH;
//boolean MD1_DirR = LOW;
//boolean MD2_DirR = LOW;

boolean MD1_Brk = LOW;
boolean MD2_Brk = LOW;

boolean state_M1 = LOW;
boolean state_M2 = LOW;

int spd = 500;
int servo_pos = 180; //assuming spd=500 maps to 180 degrees in 0 to 360 degree range.
int temp_MP3 = 0; //I don't want our bot to keep buzzing all the time u know!

void setup() {
  // put your setup code here, to run once:

  myservo.attach(9);

  Serial.begin(9600);

  pinMode(MD1_PWM_Pin, OUTPUT);
  pinMode(MD2_PWM_Pin, OUTPUT);

  pinMode(MD1_Dir_Pin, OUTPUT);
  //pinMode(MD1_DirR_Pin, OUTPUT);
  pinMode(MD2_Dir_Pin, OUTPUT);
  //pinMode(MD2_DirR_Pin, OUTPUT);

  //pinModes set now Mitthoogir shuru karenge shuru kar!
}

void loop() {
  // put your main code here, to run repeatedly: for no reason at all... aisa samaz ke galti mat karna.

  if (Serial.available() > 0)
  {
    char data = Serial.read();

    switch (data)
    {
      case '0' : spd = 0; break;
      case '1' : spd = 25; break;
      case '2' : spd = 50; break;
      case '3' : spd = 75; break;
      case '4' : spd = 100; break;
      case '5' : spd = 125; break;
      case '6' : spd = 150; break;
      case '7' : spd = 175; break;
      case '8' : spd = 200; break;
      case '9' : spd = 225; break;
      case 'q' : spd = 250; break;

      case 'F' : //Forward
        MD1_Dir = LOW; /*MD1_DirR = LOW;*/ MD2_Dir = LOW; /*MD2_DirR = LOW;*/
        MD1_PWMV = spd; MD2_PWMV = spd;

        digitalWrite(MD1_Brk_Pin, LOW);
        digitalWrite(MD2_Brk_Pin, LOW);

        if (state_M1 == LOW) //if M1 F
        {
          digitalWrite(MD1_Dir_Pin, MD1_Dir);  //Keep it F
          analogWrite(MD1_PWM_Pin, MD1_PWMV);
        }
        if (state_M2 == LOW) //if M2 F
        {
          digitalWrite(MD2_Dir_Pin, MD2_Dir);  // keep it F
          analogWrite(MD2_PWM_Pin, MD2_PWMV);
        }
        else if (state_M1 == HIGH || state_M2 == HIGH) //if either of M is R, introduce delay then change dir
        {
          analogWrite(MD1_Dir_Pin, 0);
          analogWrite(MD1_Dir_Pin, 0);
          delay(2);
          digitalWrite(MD1_Dir_Pin, MD1_Dir);
          digitalWrite(MD2_Dir_Pin, MD2_Dir);
          analogWrite(MD1_PWM_Pin, MD1_PWMV);
          analogWrite(MD2_PWM_Pin, MD2_PWMV);
        }
        //clubbed both the M for this case to simultaneously change the dir.

        state_M1 = LOW;
        state_M2 = LOW;

        break;

      case 'B' : //Backward
        MD1_Dir = HIGH; /*MD1_DirR = HIGH;*/ MD2_Dir = HIGH; /*MD2_DirR = HIGH;*/
        MD1_PWMV = spd; MD2_PWMV = spd;

        digitalWrite(MD1_Brk_Pin, LOW);
        digitalWrite(MD2_Brk_Pin, LOW);

        if (state_M1 == HIGH) //if M1 R
        {
          digitalWrite(MD1_Dir_Pin, MD1_Dir);  //Keep it R
          analogWrite(MD1_PWM_Pin, MD1_PWMV);
        }
        if (state_M2 == HIGH) //if M2 R
        {
          digitalWrite(MD2_Dir_Pin, MD2_Dir);  // keep it R
          analogWrite(MD2_PWM_Pin, MD2_PWMV);
        }
        else if (state_M1 == LOW || state_M2 == LOW) //if either of M is F introduce delay then change dir
        {
          analogWrite(MD1_Dir_Pin, 0);
          analogWrite(MD1_Dir_Pin, 0);
          delay(2);
          digitalWrite(MD1_Dir_Pin, MD1_Dir);
          digitalWrite(MD2_Dir_Pin, MD2_Dir);
          analogWrite(MD1_PWM_Pin, MD1_PWMV);
          analogWrite(MD2_PWM_Pin, MD2_PWMV);
        }
        //clubbed both the M for this case to simultaneously change the dir.

        state_M1 = HIGH;
        state_M2 = HIGH;

        break;

      case 'L' : //Left
        MD1_Dir = HIGH; /*MD1_DirR = HIGH;*/ MD2_Dir = LOW; /*MD2_DirR = LOW;*/
        MD1_PWMV = spd; MD2_PWMV = spd;

        digitalWrite(MD1_Brk_Pin, LOW);
        digitalWrite(MD2_Brk_Pin, LOW);

        if (state_M1 == HIGH) //if M1 R
        {
          digitalWrite(MD1_Dir_Pin, MD1_Dir);  //Keep it R
          analogWrite(MD1_PWM_Pin, MD1_PWMV);
        }
        if (state_M2 == LOW) //if M2 F
        {
          digitalWrite(MD2_Dir_Pin, MD2_Dir);  // keep it F
          analogWrite(MD2_PWM_Pin, MD2_PWMV);
        }
        else if (state_M1 == LOW || state_M2 == HIGH) //if either of M is Opp. introduce delay then change dir
        {
          analogWrite(MD1_Dir_Pin, 0);
          analogWrite(MD1_Dir_Pin, 0);
          delay(2);
          digitalWrite(MD1_Dir_Pin, MD1_Dir);
          digitalWrite(MD2_Dir_Pin, MD2_Dir);
          analogWrite(MD1_PWM_Pin, MD1_PWMV);
          analogWrite(MD2_PWM_Pin, MD2_PWMV);
        }
        //clubbed both the M for this case to simultaneously change the dir.

        state_M1 = HIGH;
        state_M2 = LOW;

        break;

      case 'R' : //Right
        MD1_Dir = LOW; /*MD1_DirR = LOW;*/ MD2_Dir = HIGH; /*MD2_DirR = HIGH;*/
        MD1_PWMV = spd; MD2_PWMV = spd;

        digitalWrite(MD1_Brk_Pin, LOW);
        digitalWrite(MD2_Brk_Pin, LOW);

        if (state_M1 == LOW) //if M1 F
        {
          digitalWrite(MD1_Dir_Pin, MD1_Dir);  //Keep it F
          analogWrite(MD1_PWM_Pin, MD1_PWMV);
        }
        if (state_M2 == HIGH) //if M2 R
        {
          digitalWrite(MD2_Dir_Pin, MD2_Dir);  // keep it R
          analogWrite(MD2_PWM_Pin, MD2_PWMV);
        }
        else if (state_M1 == HIGH || state_M2 == LOW) //if either of M is Opp. introduce delay then change dir
        {
          analogWrite(MD1_Dir_Pin, 0);
          analogWrite(MD1_Dir_Pin, 0);
          delay(2);
          digitalWrite(MD1_Dir_Pin, MD1_Dir);
          digitalWrite(MD2_Dir_Pin, MD2_Dir);
          analogWrite(MD1_PWM_Pin, MD1_PWMV);
          analogWrite(MD2_PWM_Pin, MD2_PWMV);
        }
        //clubbed both the M for this case to simultaneously change the dir.

        state_M1 = LOW;
        state_M2 = HIGH;

        break;

      case 'G' : //Forward Left
        MD1_Dir = LOW; /*MD1_DirR = LOW;*/ MD2_Dir = LOW; /*MD2_DirR = LOW;*/
        MD1_PWMV = spd/2; MD2_PWMV = spd;

        digitalWrite(MD1_Brk_Pin, LOW);
        digitalWrite(MD2_Brk_Pin, LOW);

        if (state_M1 == LOW) //if M1 F
        {
          digitalWrite(MD1_Dir_Pin, MD1_Dir);  //Keep it F
          analogWrite(MD1_PWM_Pin, MD1_PWMV);
        }
        if (state_M2 == LOW) //if M2 F
        {
          digitalWrite(MD2_Dir_Pin, MD2_Dir);  // keep it F
          analogWrite(MD2_PWM_Pin, MD2_PWMV);
        }
        else if (state_M1 == HIGH || state_M2 == HIGH) //if either of M is Opp. introduce delay then change dir
        {
          analogWrite(MD1_Dir_Pin, 0);
          analogWrite(MD1_Dir_Pin, 0);
          delay(2);
          digitalWrite(MD1_Dir_Pin, MD1_Dir);
          digitalWrite(MD2_Dir_Pin, MD2_Dir);
          analogWrite(MD1_PWM_Pin, MD1_PWMV);
          analogWrite(MD2_PWM_Pin, MD2_PWMV);
        }
        //clubbed both the M for this case to simultaneously change the dir.

        state_M1 = LOW;
        state_M2 = LOW;

        break;

      case 'I' : //Forward Right
        MD1_Dir = LOW; /*MD1_DirR = LOW;*/ MD2_Dir = LOW; /*MD2_DirR = LOW;*/
        MD1_PWMV = spd; MD2_PWMV = spd/2;

        digitalWrite(MD1_Brk_Pin, LOW);
        digitalWrite(MD2_Brk_Pin, LOW);

        if (state_M1 == LOW) //if M1 F
        {
          digitalWrite(MD1_Dir_Pin, MD1_Dir);  //Keep it F
          analogWrite(MD1_PWM_Pin, MD1_PWMV);
        }
        if (state_M2 == LOW) //if M2 F
        {
          digitalWrite(MD2_Dir_Pin, MD2_Dir);  // keep it F
          analogWrite(MD2_PWM_Pin, MD2_PWMV);
        }
        else if (state_M1 == HIGH || state_M2 == HIGH) //if either of M is Opp. introduce delay then change dir
        {
          analogWrite(MD1_Dir_Pin, 0);
          analogWrite(MD1_Dir_Pin, 0);
          delay(2);
          digitalWrite(MD1_Dir_Pin, MD1_Dir);
          digitalWrite(MD2_Dir_Pin, MD2_Dir);
          analogWrite(MD1_PWM_Pin, MD1_PWMV);
          analogWrite(MD2_PWM_Pin, MD2_PWMV);
        }
        //clubbed both the M for this case to simultaneously change the dir.

        state_M1 = LOW;
        state_M2 = LOW;

        break;

      case 'H' : //Backward Left
        MD1_Dir = HIGH; /*MD1_DirR = HIGH;*/ MD2_Dir = HIGH; /*MD2_DirR = HIGH;*/
        MD1_PWMV = spd/2; MD2_PWMV = spd;

        digitalWrite(MD1_Brk_Pin, LOW);
        digitalWrite(MD2_Brk_Pin, LOW);

        if (state_M1 == HIGH) //if M1 R
        {
          digitalWrite(MD1_Dir_Pin, MD1_Dir);  //Keep it R
          analogWrite(MD1_PWM_Pin, MD1_PWMV);
        }
        if (state_M2 == HIGH) //if M2 R
        {
          digitalWrite(MD2_Dir_Pin, MD2_Dir);  // keep it R
          analogWrite(MD2_PWM_Pin, MD2_PWMV);
        }
        else if (state_M1 == LOW || state_M2 == LOW) //if either of M is Opp. introduce delay then change dir
        {
          analogWrite(MD1_PWM_Pin, 0);
          analogWrite(MD2_PWM_Pin, 0);
          delay(2);
          digitalWrite(MD1_Dir_Pin, MD1_Dir);
          digitalWrite(MD2_Dir_Pin, MD2_Dir);
          analogWrite(MD1_PWM_Pin, MD1_PWMV);
          analogWrite(MD2_PWM_Pin, MD2_PWMV);
        }
        //clubbed both the M for this case to simultaneously change the dir.

        state_M1 = HIGH;
        state_M2 = HIGH;

        break;

      case 'J' : //Backward Right
        MD1_Dir = HIGH; /*MD1_DirR = HIGH;*/ MD2_Dir = HIGH; /*MD2_DirR = HIGH;*/
        MD1_PWMV = spd; MD2_PWMV = spd/2;
        
        digitalWrite(MD1_Brk_Pin, LOW);
        digitalWrite(MD2_Brk_Pin, LOW);

        if (state_M1 == HIGH) //if M1 R
        {
          digitalWrite(MD1_Dir_Pin, MD1_Dir);  //Keep it R
          analogWrite(MD1_PWM_Pin, MD1_PWMV);
        }
        if (state_M2 == HIGH) //if M2 F
        {
          digitalWrite(MD2_Dir_Pin, MD2_Dir);  // keep it F
          analogWrite(MD2_PWM_Pin, MD2_PWMV);
        }
        else if (state_M1 == LOW || state_M2 == LOW) //if either of M is Opp. introduce delay then change dir
        {
          analogWrite(MD1_PWM_Pin, 0);
          analogWrite(MD2_PWM_Pin, 0);
          delay(2);
          digitalWrite(MD1_Dir_Pin, MD1_Dir);
          digitalWrite(MD2_Dir_Pin, MD2_Dir);
          analogWrite(MD1_PWM_Pin, MD1_PWMV);
          analogWrite(MD2_PWM_Pin, MD2_PWMV);
        }
        //clubbed both the M for this case to simultaneously change the dir.

        state_M1 = HIGH;
        state_M2 = HIGH;

        break;

      case 'S' :  //Stop (Motion I guess, don't have hw to try mann!)
        // MD1_Dir = LOW; /*MD1_DirR = LOW;*/ MD2_Dir = LOW; /*MD2_DirR = LOW;*/
        MD1_PWMV = 0; MD2_PWMV = 0;

        

        analogWrite(MD1_Dir_Pin, MD1_PWMV);
        analogWrite(MD2_Dir_Pin, MD2_PWMV);
        //delay(2);
        break;

      /* case 'V' : //Play MP3
                 temp_MP3=spd;//Spd value used to determine which MP3 file to play.......I know this is brilliant!
                 break;

        case 'v' : //Stop MP3
                 temp_MP3=0; //Baja band kar be!
                 break;

        case 'X' : //Map spd to Servo
                 servo_pos=map(spd, 0, 1023, 0, 360); //Again using the spd slider but this one will cause increase in motor speed and change in servo at atime if X is given. Use with caution or have fun!
                 myservo.write(servo_pos);
                 delay(15); //'Cause u know, they recommend mann...
                 break;

        case 'x' : //Stop mapping spd to Servo and leave it as it is
                 myservo.write(servo_pos);
                 delay(15); //'Cause u know, they recommend mann...
                 break;
      */


      case 'D' : //All stop, back to positions, Ah-Hu! And wait for 1 sec for no reason at all.
        MD1_Dir = LOW; /*MD1_DirR = LOW;*/ MD2_Dir = LOW; /*MD2_DirR = LOW;*/
        MD1_PWMV = 0; MD2_PWMV = 0;

        analogWrite(MD1_PWM_Pin, MD1_PWMV);
        analogWrite(MD2_PWM_Pin, MD2_PWMV);

        delay(2);

        digitalWrite(MD1_Brk_Pin, HIGH);
        digitalWrite(MD2_Brk_Pin, HIGH);
        
        /*temp_MP3=0;

          myservo.write(180);
          delay(15);*/

        delay(2); //Yse, even if there's alredy 15 ms delay above, still... 1 complete second!

        break;


      default : break;


    }

  }

}

//After compiling, says 11% of program storage is used. So, we can add many things eh! Ya, the mp3 module code is yet to be added...

