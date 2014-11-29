#include <IRremote.h>

const int RECEBE_PINO = 2;    
const int SAIDA_PINO = 9;

IRrecv ir_recebe(RECEBE_PINO);   
decode_results codigo_recebido;     

boolean ligado = false;
int velocidade = 120;

void setup()    
{    
	pinMode(SAIDA_PINO, OUTPUT);
	Serial.begin(9600);  
	ir_recebe.enableIRIn();    
}    
void loop() {    

	
	if (ir_recebe.decode(&codigo_recebido)) {  

		if (codigo_recebido.value != 0 ){   
			Serial.println(codigo_recebido.value, HEX);    
		}   

		// liga e desliga
		if (codigo_recebido.value == 0xBD807F){
			if(ligado){
				ligado = false;
				analogWrite(SAIDA_PINO, 0);    
			}else{
				ligado = true;
				analogWrite(SAIDA_PINO, velocidade);
			}
		}    

		if(ligado){

			// Aumenta Velocidade
			if(codigo_recebido.value == 0xBD30CF){
				if(velocidade < 150){
					velocidade += 5;
					analogWrite(SAIDA_PINO, velocidade);
				}
			}
			// Diminui velocidade
			if(codigo_recebido.value == 0xBD08F7){
				if(velocidade > 100){
					velocidade -= 5;
					analogWrite(SAIDA_PINO, velocidade);
				}		
			}
		}	
				
		ir_recebe.resume(); 
	}    
}