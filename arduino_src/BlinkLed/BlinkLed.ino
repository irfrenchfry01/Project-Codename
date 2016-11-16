
const int LedPin = 13;

void LedInit(void)
{
  PORTC_PCR5 = PORT_PCR_MUX(0x1);
  GPIOC_PDDR = (1<<5);
  GPIOC_PSOR = (1<<5);
}

void ToggleLed(void)
{
  uint32_t PortC = GPIOC_PSOR;
  PortC = PortC | (1<<5);
  GPIOC_PTOR = PortC;
  delay(100);
  //PortC = PortC | (1<<5);
  //GPIOC_PCOR = PortC;
  //delay(100);
}

void setup() {
  // put your setup code here, to run once:
  LedInit();
}

void loop() {
  // put your main code here, to run repeatedly:
  ToggleLed();
}
