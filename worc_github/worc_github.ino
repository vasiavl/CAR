

int But1=0; //меняем код 1-ый раз
int But2=0;  //меняем код 2-ой раз 
int But3=0;
int forwardR,forwardL,flag,flagP, flagForwardL, flagForwardR =0;//состояние реверса двигателей и флаги  переключения состояний

void setup() {
    pinMode(Button_1, INPUT_PULLUP); //меняем код 1-ый раз
    pinMode(Button_2, INPUT_PULLUP);//меняем код 2-ой раз 
    pinMode(Button_3, INPUT_PULLUP);
    pinMode(forward_agoPinR, OUTPUT);
    pinMode(forward_agoPinL, OUTPUT);
    pinMode(LRPin, OUTPUT);
  Serial.begin(9600); 
}

void loop() {                               
  Yaw = analogRead(analogInYawPin);  //меняем код 1-ый раз
  Roll = analogRead(analogInRollPin); //меняем код 2-ой раз 
  Pitch = analogRead(analogInPitchPin);
  forwardR=  digitalRead(forward_agoPinR);
  forwardL=  digitalRead(forward_agoPinL); 
  tvistFlag= digitalRead( LRPin);
  
   
  outputPitch = map(Pitch, 540, 1023, 0, 255);  //меняем код 1-ый раз
  outputPitchD = map(Pitch, 480, 0, 0, 255); //меняем код 2-ой раз 
  outputRoll =  map(Roll, 480, 0, 0, 255);
  outputRollR =  map(Roll, 540, 1023, 0, 255);
  outputYawL = map(Yaw, 540, 1023, 0, 255); 
  outputYawR = map(Yaw, 480, 0, 0, 255);
                                                                                        
                                                                                                                                                              
   if (460>Pitch) //меняем код 1-ый раз
   {       outputPitch= 0;//меняем код 2-ой раз 
           if (HIGH==forwardR|| HIGH==forwardL)
              { flagForwardL =flagForwardR=flag= LOW;}
           if (480>Roll){ R= outputPitchD;  outputRollR= 0;//left
             if (outputPitchD>outputRoll)   L= (outputPitchD-outputRoll/1.5);
             if (outputPitchD<outputRoll)   L= 0; }
           if ((540>Roll)&& (Roll>480))  {  R=L=outputPitchD;     }                                                  
           if  (Roll>540)   { L= outputPitchD;  outputRoll= 0;
              if (outputPitchD>outputRollR)   R= (outputPitchD-outputRollR/1.5);
              if (outputPitchD<outputRollR)   R= 0;}
   }  
 if (Pitch > 560) //меняем код 1-ый раз
  {             outputPitchD= 0;//меняем код 2-ой раз 
          if (LOW==forwardR|| LOW==forwardL)
          { flagForwardR =flagForwardL=flag= HIGH ; }
                                                                      
          if  (480>Roll) { R= outputPitch;  //outputRollR= 0;
             if (outputPitch>outputRoll)   L= (outputPitch-outputRoll/1.5);
             if (outputPitch<outputRoll)   L= 0; }          
           if  ((540>Roll)&& (Roll>480)) {outputRoll= outputRollR =0; R=L= outputPitch;  } 
          if  (Roll>540) {     L= outputPitch;   outputRoll= 0;
             if (outputPitch>outputRollR)   R= (outputPitch-outputRollR/1.5);
             if (outputPitch<outputRollR)   R= 0; }
    }    
    if ((560>Pitch)&& (Pitch >460)) //меняем код 1-ый раз
    {       Rdriv=Ldriv=0;//меняем код 2-ой раз 
            outputRoll =outputRollR =  0;  //R=L=outputPitchD =outputPitch =0;  
         if (   Yaw>540)//left
         { 
              if (HIGH==forwardL|| LOW==forwardR)
              { flagForwardL= LOW; flagForwardR= HIGH; flagY= LOW; }  
                  L = 0;  R= outputYawL;
               if (Yaw>820) {  R= L= outputYawL; }                                        
         }           
         if (480>Yaw)//rait
          { 
              if (LOW==forwardL|| HIGH==forwardR)
               {  flagForwardL= HIGH ; flagForwardR= LOW; flagY= HIGH;}
                   R= 0;   L= outputYawR;
              if  (200>Yaw){  R=L= outputYawR; }  
          }                                                      
         if ((540>Yaw)&& (Yaw >480)) {  R=L =0;}
    }  
  
  if  (460>Roll)// left  Ydiff
  {    
    if  (HIGH== tvistFlag){tvistFlag= LOW; timeY=0 ; }
    if(timeY>2)tvist=0 ;
    if(timeY<2)tvist=25 ;
      timeY=timeY+1 ;        
   }      
  if  (560>Roll&& Roll>460) {tvist=timeY=0 ; }                                          
  if  (Roll>560)//right
   {   if  (LOW==tvistFlag) {tvistFlag= HIGH; timeY=0 ;}
        if(timeY>2)tvist=0 ;
       if(timeY<2)tvist=25 ;
         timeY=timeY+1 ; 
   }


    
 if (flag !=flagP  ){Rdriv=Ldriv=R=L=0; flagP=flag; }
 if (flagY !=flagYF){Rdriv=Ldriv=0; flagYF=flagY; }
   if  (Rdriv-R >20)  { Rdriv=Rdriv-25;} 
   else {if (R-Rdriv>20)Rdriv=Rdriv+25;
        else Rdriv=R;  }
    if (L-Ldriv>20) { Ldriv=Ldriv+25; }
    else {
      if (Ldriv-L >20) Ldriv=Ldriv-25;
          else Ldriv=L; }
     digitalWrite( LRPin, tvistFlag);
     digitalWrite( forward_agoPinL,flagForwardL );
     digitalWrite( forward_agoPinR,flagForwardR );     
     analogWrite(analogWriteRPin, tvist); 
     analogWrite(analogWritePRYPinR, Rdriv);
     analogWrite(analogWritePRYPinL, Ldriv); 
   But1=    digitalRead(Button_1);
    But2= digitalRead(Button_2);       
    But3=  digitalRead(Button_3);                                                                                                                           
                                                         
 
 
  Serial.print(" Yaw = " );  //меняем код 1-ый раз                      
  Serial.print(Yaw);  //меняем код 2-ой раз     
  Serial.print("\t outputYawR = ");      
  Serial.print(outputYawR); 
  Serial.print("\t outputYawL = ");      
  Serial.print(outputYawL);  
  Serial.print("\n Roll = " );                       
  Serial.print(Roll);      
  Serial.print("\t outputRoll = ");      
  Serial.print(outputRoll); 
   Serial.print("\t outputRollR = ");      
  Serial.print(outputRollR); 
  Serial.print("\n Pitch = " );                       
  Serial.print(Pitch);      
  Serial.print("\t outputPitch = ");      
  Serial.print(outputPitch); 
  Serial.print("  R = " );                       
  Serial.print(R); 
  Serial.print("\t Rdriv = " );                       
  Serial.print(Rdriv);
  Serial.print("\n                outputPitchD = ");      
  Serial.print(outputPitchD); 
  Serial.print("  L = ");      
  Serial.print(L);
  Serial.print("\t Ldriv = ");      
  Serial.print(Ldriv); 
  Serial.print("\n forwardR = ");            
  Serial.print(  forwardR); 
  Serial.print("\t forwardL = ");            
  Serial.print(  forwardL);  
 Serial.print("\t flag=") ;            
  Serial.print(  flag); 
 Serial.print("\t flagP=") ;            
  Serial.println(  flagP); 
Serial.print("\t flagY=") ;            
  Serial.print(  flagY); 
 Serial.print("\t flagYF=") ;            
  Serial.println(  flagYF); 
Serial.print("\t tvistFlag=") ;            
  Serial.print(  tvistFlag); 
 Serial.print("\t tvist=") ;            
  Serial.print(  tvist); 
 Serial.print("\t timeY=") ;            
  Serial.print(  timeY);  
  
  delay(2550);   
