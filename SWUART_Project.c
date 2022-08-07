/* DIO_Interface */
#define IN 0
#define OUT 1
#define LOW 0
#define HIGH 1

/* STD_TYPES */
typedef unsigned char         uint8_t   ;
typedef unsigned short int    uint16_t  ;
typedef unsigned long int     uint32_t  ;

typedef signed char           sint8_t   ;
typedef signed short int      sint16_t  ;
typedef signed long int       sint32_t  ;

typedef float                 f32  ;
typedef double                f64  ;
typedef long double           f80  ;

/* Registers */
#define UCSRA		*((uint8_t*)0x2B)
#define UCSRB		*((uint8_t*)0x2A)
#define UCSRC		*((uint8_t*)0x40)
#define UBRRL		*((uint8_t*)0x29)
#define UDR			*((uint8_t*)0x2C)
#define UBRRH		UCSRC

/*UART_Driver*/
void SWUART_init(uint32_t baudrate)
{
    UCSRA = 0x00;
    UCSRB = 0x18;
    UCSRC = 0xAE;

    f32 BaudPreScale = (((F_CPU / (baudrate * 16UL))) - 1);

    UBRRL = BaudPreScale;
	UBRRH = (BaudPreScale >> 8);


}

void SWUART_send(uint8_t data)
{
    while ( ! ((UCSRA >> 5)&1));
	UDR = data;
}

void SWUART_recieve*uint8_t *data)
{
    while ( ((UCSRA >> 7)&1) ==0);
	*data = UDR;
}


void
_delay_ms(double __ms)
{
	uint16_t __ticks;
	double __tmp = ((F_CPU) / 4e3) * __ms;
	if (__tmp < 1.0)
		__ticks = 1;
	else if (__tmp > 65535)
	{
		//	__ticks = requested delay in 1/10 ms
		__ticks = (uint16_t) (__ms * 10.0);
		while(__ticks)
		{
			// wait 1/10 ms
			_delay_loop_2(((F_CPU) / 4e3) / 10);
			__ticks --;
		}
		return;
	}
	else
		__ticks = (uint16_t)__tmp;
	_delay_loop_2(__ticks);
}

/* Main code */
int main(void){
    /* Drivers Initializations */
    DIO_Init(0,'A',OUT);
    DIO_Init(1,'A',IN);
    SWUART_init(9600);
    /* Variables initializations */
    uint8_t Data=0;
    /*
        This Code will Send from 0 to 255 then it will overflow and start over again.
        Sending will be 100 ms between the two send actions.
    */
    for(;;)
    {
        SWUART_send(Data);
        _dela_ms(100);
        Data++;
    }
    return 0;
}













