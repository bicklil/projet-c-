//MOTEUR Gauche
#define ENA 5 //Connecté à Arduino pin 5(sortie pwm)
#define IN1 4 //Connecté à Arduino pin 4
#define IN2 7 //Connecté à Arduino pin 7

//MOTEUR Droite
#define ENB 6 //Connecté à Arduino pin 6(Sortie pwm)
#define IN3 8 //Connecté à Arduino pin 8
#define IN4 9 //Connecté à Arduino pin 9


// fonctionde recuperation du clavier 

int moteur()
{
 String tableau[4];
 int i;
 for(i=0;i<4;i++){
   tableau[i]=Serial.readStringUntil(',');
 }
 ControleMoteur (tableau[1].toInt(),tableau[2].toInt(),tableau[3].toInt); 
 return 1;
}

// fonction moteur 1 et 2

void ControleMoteur ( long num, long sens, long vitesse )
  {
    if (num == 1)
    {
     switch(sens)
     {
       case 0:
             digitalWrite(IN1,LOW); 
             digitalWrite(IN2,LOW);
             analogWrite(ENA,vitesse);
             break;
       case 1:
             digitalWrite(IN1,LOW); 
             digitalWrite(IN2,HIGH);
             analogWrite(ENA,vitesse);
             break;
       case 2:
             digitalWrite(IN1,HIGH); 
             digitalWrite(IN2,LOW);
             analogWrite(ENA,vitesse);
             break;
     }}
     if (num == 2)
    {
     switch(sens)
     {
       case 0:
             digitalWrite(IN1,LOW); 
             digitalWrite(IN2,LOW);
             analogWrite(ENA,vitesse);
             break;
       case 1:
             digitalWrite(IN1,LOW); 
             digitalWrite(IN2,HIGH);
             analogWrite(ENA,vitesse);
             break;
       case 2:
             digitalWrite(IN1,HIGH); 
             digitalWrite(IN2,LOW);
             analogWrite(ENA,vitesse);
             break;
     }}}


void setup() {
 pinMode(ENA,OUTPUT);//Configurer les broches comme sortie
 pinMode(ENB,OUTPUT);
 pinMode(IN1,OUTPUT);
 pinMode(IN2,OUTPUT);
 pinMode(IN3,OUTPUT);
 pinMode(IN4,OUTPUT);
 digitalWrite(ENA,LOW);// Moteur 1 - Ne pas tourner (désactivation moteur)
 digitalWrite(ENB,LOW);// Moteur 2 - Ne pas tourner (désactivation moteur)
}
void loop() 
{
   moteur();
      //////////
      //
      //faire appel fonction moteur 1 et 2
      //
      //////////
    
}
