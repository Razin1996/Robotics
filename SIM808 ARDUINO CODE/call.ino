//arduino pin 0 is connected to GSM TX pin
//arduino pin 1 is connected to GSM TX pin
//arduino pin 4 is connected to Pushbutton
//arduino GND pin is connected to GSM GND pin

// وظيفة البرنامج:
//عند الضغط على Pushbutton موصول على Pin 4 فان الGSM ستتصل على الرقم الموجود بالكود

void setup() {
  pinMode(4, INPUT_PULLUP); //اقراء عن تعليمة INPUT_PULLUP :)
  Serial.begin(9600); // لتهيئة اتصال سيريال مع الGSM
  Serial.write("AT"); // نرسل AT حتى نتاكد من ان القطعة تعمل
  Serial.write(13); //ارسال الرقمين 13و10 على على الترتيب وبدون تاخير زمني تعبر عن Enter
  Serial.write(10);
  delay(1000); // ننتظر فترة قصيرة حتى ترد القطعة
  while(Serial.available()<0){
    
  }
  Serial.print(Serial.read()); //لعرض رد القطعة حال وصول رد منها
}

void loop() {
  if (digitalRead(4) == LOW) {
    Serial.write("ATD0797297111;");   //اذا وصلت اشارة LOW لل Pin4 فان الاردوينو سترسل امر الاتصال للGSM
    Serial.write(13);  //ارسال الرقمين 13و10 على على الترتيب وبدون تاخير زمني تعبر عن Enter
    Serial.write(10);
    delay(2000); //ننتظر ثانيتين حتى نتيح وقت كافي للGSM  لاجراء  المكالمة 
  }
}
