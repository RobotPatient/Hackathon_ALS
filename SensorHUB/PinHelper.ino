void pinModeTest( uint32_t ulPin, uint32_t ulMode )
{
  // Reports Port/Pin for digital pin


  if ( g_APinDescription[ulPin].ulPinType == PIO_NOT_A_PIN )
  {

    return ;
  }

  EPortType port = g_APinDescription[ulPin].ulPort;
  uint32_t pin = g_APinDescription[ulPin].ulPin;
  uint32_t pinMask = (1ul << pin);
 

  char portLetter = 'A';
  portLetter += port;

}
