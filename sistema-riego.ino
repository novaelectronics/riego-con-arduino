//El sistema realiza el riego los dias domingos, miercoles y viernes a las 10 de la mañana. 
//El riego dura 7 minutos. el rele debe ir conectado a una bomba de agua o a una valvula electronica. 

#include <DS3231.h>
// Inicializando el modulo DS3231 , SDA conectado al pin A4 y SCL al pin A5 del Arduino UNO
DS3231  rtc(SDA, SCL);

void setup()
{
  pinMode(13,OUTPUT); //pin led para  de un led de prueba
  pinMode(8,OUTPUT); //IN1 del modulo rele de 2 canales
  digitalWrite(8,HIGH);
  
  // Inicializando conexion serial
  Serial.begin(9600);
  
  // Iniciando modulo rtc
  rtc.begin();
  
  // Las siguientes lineas se pueden descomentar para ajustar la hora, fecha y dia de a semana del rtc, es importante volver a comentar las lineas luego de ajustar.
  //rtc.setDOW(WEDNESDAY);     // Set Day-of-Week to SUNDAY
  //rtc.setTime(12, 0, 0);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(1, 1, 2014);   // Set the date to January 1st, 2014
}

void loop()
{
  checkAlarms();
  //Enviar  Day-of-Week (dia de la semana) por serial
  Serial.print(rtc.getDOWStr());
  Serial.print(" ");
  
  //Enviar Date (fecha) por serial
  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");

  // Enviar Time (hora) por serial
  Serial.println(rtc.getTimeStr());
  
  // Esperar 1 segundo para repetir
  delay (1000);
}

void checkAlarms(){
// pointer to a time string
  char *strTime;
  // Obtener hora 
  strTime = rtc.getTimeStr(FORMAT_LONG);

  // Comparar con una determinada hora en este caso 10:00:00 y dia Lunes, Miercoles, Viernes
  if((strcmp(strTime, "10:00:00") == 0) && ((rtc.getDOWStr()== "Monday")|| (rtc.getDOWStr()== "Wednesday") || (rtc.getDOWStr()== "Friday"))){
  Serial.println("***LED ON***");
  Serial.print("La hora es: ");
  Serial.println(strTime);
 
  accion(); //llamada a la funcion que activa el rele
    }
}

void accion(){
  Serial.println("Regando..."); 
  digitalWrite(8,LOW); // Activa el Rele  ON
  digitalWrite(13,HIGH); //prender led
  delay(420000); // esperar 7 minutos
  digitalWrite(8,HIGH); // Desactiva Rele OFF
  digitalWrite(13,LOW); //apaga led
  
}
