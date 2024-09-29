#include "setup.h"

int main(){
		GPIO_setup('A',5);																							//Pass the port and pin to use
		while(1){
			Timer_setup(1);																								//Pass the delay required in seconds
			GPIO_toggle(5);																								//Pass the pin number same as above
		}
}
