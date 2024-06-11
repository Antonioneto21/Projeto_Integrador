#include <Wire.h>

// Endereço em hexadecimal do sensor MPU 9250
const int ENDERECO_SENSOR = 0x68;

// Definindo os pinos I2C
const int SDA_PIN = 4; // GPIO4 (D2)
const int SCL_PIN = 5; // GPIO5 (D1)

int girX, girY, girZ, acelX, acelY, acelZ, temperatura;

void setup() {
  Serial.begin(115200); // Aumentei a taxa de baud para uma melhor performance

  // Inicializa a biblioteca Wire com os pinos definidos
  Wire.begin(4, 5);

  // Inicializa o sensor MPU-9250
  Wire.beginTransmission(ENDERECO_SENSOR);
  Wire.write(0x6B); // Registrador de energia (PWR_MGMT_1)
  Wire.write(0); // Inicializa o sensor
  Wire.endTransmission(true);

  // Adicione um pequeno delay para garantir que o sensor tenha tempo de iniciar
  delay(100);
}

void loop() {
  // Começa uma transmissão com o sensor
  Wire.beginTransmission(ENDERECO_SENSOR);
  Wire.write(0x3B); // Iniciando com o registrador 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);

  // Solicita os dados do sensor
  Wire.requestFrom(ENDERECO_SENSOR, 14, true);

  // Verifica se os 14 bytes foram recebidos
  if (Wire.available() == 14) {
    // Armazena o valor dos sensores nas variáveis correspondentes
    acelX = Wire.read() << 8 | Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
    acelY = Wire.read() << 8 | Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    acelZ = Wire.read() << 8 | Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
    temperatura = Wire.read() << 8 | Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
    girX = Wire.read() << 8 | Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
    girY = Wire.read() << 8 | Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
    girZ = Wire.read() << 8 | Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

    // Printa o valor X do acelerômetro na serial
    Serial.print("Acelerômetro X = ");
    Serial.print(acelX);

    // Printa o valor Y do acelerômetro na serial
    Serial.print(" \tY = ");
    Serial.print(acelY);

    // Printa o valor Z do acelerômetro na serial
    Serial.print(" \tZ = ");
    Serial.println(acelZ);

    // Printa o valor X do giroscópio na serial
    Serial.print("Giroscópio X = ");
    Serial.print(girX);

    // Printa o valor Y do giroscópio na serial
    Serial.print(" \tY = ");
    Serial.print(girY);

    // Printa o valor Z do giroscópio na serial
    Serial.print(" \tZ = ");
    Serial.println(girZ);

    // Printa o valor da temperatura na serial, calculando em graus celsius
    Serial.print("Temperatura = ");
    Serial.println(temperatura / 340.00 + 36.53);
  } else {
    // Se os 14 bytes não foram recebidos, printa uma mensagem de erro
    Serial.println("Erro ao ler os dados do sensor");
  }

  delay(200);
}
