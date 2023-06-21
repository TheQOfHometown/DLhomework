//智能垃圾桶：超声波感应开盖
#include <Servo.h>//之间要有空格，否则编译时会报错。
Servo myservo;//定义舵机
volatile float dist;
int D1 = 2; //超声波接口T
int D2 = 3; //超声波接口E
int S1 = 4; //舵机接口

unsigned char jiao;//角度
float checkdistance(int a1, int a2) { //超声波感应，测量距离v
  digitalWrite(a1, LOW);
  delayMicroseconds(2);
  digitalWrite(a1, HIGH);
  delayMicroseconds(10);
  digitalWrite(a1, LOW);
  float distance = pulseIn(a2, HIGH) / 58.00;
  delay(50);
  return distance;
}



void setup()
{
  dist = 0;//定义距离变量
  Serial.begin(9600);
  pinMode(D1, OUTPUT);//定义超声波输出引脚
  pinMode(D2, INPUT);//定义超声波输入引脚
  myservo.attach(S1);//定义舵机接口
  myservo.write(90);//设置舵机初始角度
}
void loop()
{
  dist = checkdistance(D1, D2);//通过超声波获取距离
  if ((dist > 1) && (dist < 10) )  //当距离大于1并且小于10cm时
  {
    //打开盖
    for (jiao = 90; jiao > 0; jiao = jiao - 1)
    {
      myservo.write(jiao);//设置舵机打开转向角度
      delay(5);
    }

    //停顿2秒
    delay(2000);

    //合上盖
    for (jiao = 0; jiao < 90; jiao = jiao + 1)
    {
      myservo.write(jiao);//设置舵机关闭转向角度
      delay(5);
    }
  }
  //Serial.println(dist);
}
