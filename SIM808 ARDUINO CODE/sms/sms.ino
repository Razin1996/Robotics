//arduino pin 0 is connected to GSM TX pin
//arduino pin 1 is connected to GSM TX pin
//arduino pin 4 is connected to MICROPHONE MODULE
//arduino GND pin is connected to GSM GND pin
//عند الضغط على Pushbutton موصول على Pin 4 فان الGSM سترسل رسالة للرقم الموجود بالكود
void setup() {
  // put your setup code here, to run once:
  pinMode(4, INPUT);  //اقراء عن تعليمة INPUT_PULLUP :)
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
  // put your main code here, to run repeatedly:
  if (digitalRead(4) == HIGH) {
    Serial.write("AT+CMGF=1"); // يحددوضيعة استقبال الرسالة كـ Text
    Serial.write(13);
    Serial.write(10);
    Serial.write("AT+CMGS="); // AT+CMGS="07********" // الامر الخاص بارسال الرسالة
    Serial.write(34);  //34 يمثل كود الـ ASCII  لـ (")
    Serial.write("+8801927719271");
    Serial.write(34); //34 يمثل كود الـ ASCII  لـ (")
    Serial.write(13);  //ارسال الرقمين 13و10 على على الترتيب وبدون تاخير زمني تعبر عن Enter
    Serial.write(10);
    delay(1000); //ننتظر حتى تتهيئ ال GSM  لاستقبال نص الرسالة
    Serial.write("System Ready"); // ما بداخل الفواصل هو نص الرسالة
    Serial.write(26); // يمثل الـ ASCII  كود لـ SEND 
  }
}
