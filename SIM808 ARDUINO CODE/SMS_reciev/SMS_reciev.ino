//arduino pin 0 is connected to GSM TX pin
//arduino pin 1 is connected to GSM TX pin
//arduino pin 4 is connected to Pushbutton
//arduino GND pin is connected to GSM GND pin
// وظيفة البرنامج:
// عندما تستقبل الاردوينو رسالة بها كلمة (*on*) 
// تعطي اشارة  HIGH للـ Pin13
// عندما تستقبل الاردوينو رسالة بها كلمة (*off*) 
// تعطي اشارةLOW للـ Pin13
char x;
String y;
void setup() {
  pinMode(13, OUTPUT); // تهيئة الpin13 كـOUTPUT
  Serial.begin(9600); // لتهيئة اتصال سيريال مع الGSM
  Serial.write("AT");
  Serial.write(13);
  Serial.write(10);
  delay(1000);
  digitalWrite(13, LOW); // للتاكد من ان الحالة الابتدائية للـ PIN  هي  LOW
    while (Serial.available() < 0) {

  }
  Serial.println(Serial.read());
  Serial.write("AT+CMGA=DEL ALL"); // لمسح جميع الرسائل من الذاكرة
  Serial.write(13);
  Serial.write(10);
  Serial.write("AT+CNMI=3,2,2,1,1"); // لتعرض المسج حال وصوله تلقائيا
  Serial.write(13);
  Serial.write(10);
  Serial.write("AT+CMGF=1"); // لتحويل وضعية استقبال الرسائل كـ Text
  Serial.write(13);
  Serial.write(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) { //اذا وصل بيانات على منفذ السيريال يقوم بمحو محتويات المتغير y
    y = "";
    while (Serial.available()) { // طالما يوجد معلومات على منفذ السيريال يظل يحفظ البيانات 
      x = Serial.read();
      y = y + x;
      delay(5); // تاخير زمني بسيط حتى يكون هناك وقت كافي لوصول الاحرف
    }
  }
  if (y.indexOf("*on*") >= 0) { // هذا الامر يفحص وجود الكملة ما بين الفواصل في الـString 
    Serial.print("on");
    digitalWrite(13, HIGH);
     y=""; // يمسح محتوى Y
  }
   if (y.indexOf("*OFF*") >= 0) {
    Serial.print("OFF");
    digitalWrite(13, LOW);
   }
}
