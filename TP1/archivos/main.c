#include <stm32f103x6.h>

/*  variables del programa */

int seg; //variable de tiempo
extern unsigned char tecla = 0xFF; // guarda la tecla presionada. Default=0xFF=NO DATA   
typedef enum {acceso, bloqueo, ingresando, inicio}estado; // estados de la MEF
extern estado state ; // estado actual

extern unsigned char fin_tiempo_bloqueo; // flag de tiempo de bloqueo por contraseña incorrecta
extern unsigned char ingresando_secuencia; // flag para determinar si se está ingresando la secuencia de números

int nroDigito; // variable para saber cuántos dígitos del total fueron ingresados 
extern unsigned char cumple; // flag para saber si la secuencia se está ingresando de forma correcta
int password  [4] = {2,5,8,0}; // contraseña de la cerradura


 


int main (void) { 
   
   while (1) {

      if (( tecla != 0xFF ) || ( fin_tiempo_bloqueo )  || ( ingresando_secuencia ))  // si se presionó una tecla, finalizó el tiempo del estado actual o se estaba ingresando la secuencia
	    ex_state();
      else
	    mostar_pantalla();
      MEF_update();    //actualizo el estado de la MEF

    }

      return 0;
 }   

 
 void ex_state(void){ // verifica estado de la MEF y realiza tarea (correspondiente al estado actual)
    
    
    switch (state){
       case acceso:  //si la cerradura está abierta
	  controlar_tiempo_ingreso();	 
       break;
	  
       case bloqueo: //si la cerradura está cerrada
	    controlar_tiempo_bloqueo();
       break;
       
       case ingresando:  //si se está ingresando una contraseña
	     controlar_secuencia();
       break;
       
       case inicio:
	     mostrar_pantalla();
       break;
       
   } 
} 
    
   private void controlar_tiempo_ingreso (){
      if (seg<5){   //si no se terminó el tiempo del estado
	   delay(1000); //cuento un segundo (ESTA FUNCIÖN SE PUEDE CAMBIAR)
	   seg= seg +1;
	 }
      else { //si el tiempofinalizó  TAL VEZ LO TIENE QUE HACER EL MEF_UPDATE
	 fin_tiempo_bloqueo= 0; //reinicio el flag de tiempo
	 seg= 0; //reinicio el contador de tiempo
      }
   }
      
    private void controlar_tiempo_bloqueo (){
      if (seg<2){   //si no se terminó el tiempo del estado
	   delay(1000); //cuento un segundo (ESTA FUNCIÖN SE PUEDE CAMBIAR)
	   seg= seg +1;
	 }
      else { //si el tiempofinalizó  TAL VEZ LO TIENE QUE HACER EL MEF_UPDATE
	 fin_tiempo_bloqueo= 0; //reinicio el flag de tiempo
	 seg= 0; //reinicio el contador de tiempo
       }
    }

    private void controlar_secuencia (){
		if (tecla != 255){  //si hay una tecla presionada
	   keypad_scan(&tecla); //se recibe la tecla
	   if ((nroDigito<4) && (cumple)){   //si no se completó la secuencia y no se presionó una tecla incorrecta
	      cumple = ( (password [ nroDigito ]) == tecla); //si el dígito actual coincide con el de la secuencia
	      nroDigito=nroDigito + 1; //se cuenta la tecla presionada
	    }	    
	  }
     }

	
/*	switch(state){
	
		case principal: // muestra pantalla "introducir clave" 
			ShowMessages(); // Muestro los mensajes en el lcd

			break;
		
		case enterPassword: //Intento de apertura
			if(prev_state == entering){ //si se está ingresando la clave correctamente
				keypad_scan(&tecla); //se recibe un nuevo dígito
				 flagTecla=0; //borro el flag
			        update_secuence(tecla,&entering); //se controla si la tecla presionada corresponde a la secuencia
			}
			else{
			      if(end_entered) { //si la secuencia se ingresó correctamente
				open_lock(); //se abre la cerradura
			        ShowMessages(); //muestro en el display el aviso de apertura
			      }
			      else {
				 entering= 0; //bajó el intento de ingreso de clave
				 resset_stats(); //reinicio el estado de la MEF a estado de "reposo"
				 ShowMessages(); //muestro en el display el aviso de error
				 lock_keypad(); //bloqueo temporalmente el teclado 
			      }
			}
			break;
		case temp_unlock: //tiempo de apertura de la cerradura
		   
			if(prev_state == alarm){
				modificar_min_alarma(); 
			}else{
				modificar_min_reloj();
			}
			prev_state = config_min;
			break;
		case config_sec:
			if(prev_state == alarm){
				modificar_seg_alarma();
			}else{
				modificar_seg_reloj();
			}
			prev_state = config_sec;
			break;
		case alarm: // visualizacion de la alarma (Activada - Desactivada)
			LCD_pos_xy(0,1); // me posiciono en el renglon de abajo
		*/							
			/*if(alarm_state == 0)
				LCD_write_string("Desactivada");
			else LCD_write_string("Activada   ");*/
		/*	
			ShowTimeAlarm(); // Muestro la hora de la alarma					
			break;
		case alarm_sound: // visualizacion de alarma sonando en pantalla principal.
			ShowTime(); // reloj 
			
			LCD_pos_xy(0,1);// me posiciono en el renglon de abajo
			if(titilo==0){
				LCD_cursor_blink_on(); 
				LCD_write_string("ALARMA          ");
				titilo = 1;
			}else{
				LCD_write_string("                ");
				LCD_cursor_blink_off(); 
				titilo = 0;
			} */			
			/*if(tecla == '#'){ // si la quiere desactivar
				alarm_state = 0;
				state = principal;
			}*/ // LO HAGO EN LA MEF
		/*	break;
		*/
		//	}
