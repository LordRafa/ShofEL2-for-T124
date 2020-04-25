/*****************************************************************************/
/*                                                                           */
/* Very simple Arduino code to reset the Jetson TK1 in RCM and normal modes: */
/* When a d is received on the serial the TK1 will restart in RCM mode.      */
/* When a r is received on the serial the TK1 will restart in normal mode.   */
/* Serial Conf: 9600 8N1                                                     */
/*                                                                           */
/*****************************************************************************/

#define RST_PIN 10
#define DBG_PIN 9

void setup() {

  pinMode( RST_PIN, OUTPUT );
  pinMode( DBG_PIN, OUTPUT );
  digitalWrite( RST_PIN, LOW );
  digitalWrite( DBG_PIN, LOW );

  Serial.begin( 9600 );

}

void do_reset() {

  digitalWrite( RST_PIN, HIGH );
  delay(100);
  digitalWrite( RST_PIN, LOW );

}

void do_debug() {

  digitalWrite( DBG_PIN, HIGH );
  do_reset();
  delay( 100 );
  digitalWrite( DBG_PIN, LOW );

}

void loop() {

  delay( 1000 );

  while ( 1 ) {

    String cmd = Serial.readString();
    Serial.print( cmd );
    if ( cmd[0] == 'r' ) {      
      do_reset();
    } else if ( cmd[0] == 'd' ) {
      do_debug();
    }

  }

}
