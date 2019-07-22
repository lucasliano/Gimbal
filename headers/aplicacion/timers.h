/* Timers*/
#define TIMER_DEC 1   //100ms
#define TIMER_SEG 2   //1000ms
#define TIMER_MIN 3   //60000ms

/*Nombre de timers transparentes*/
#define TIMER_CONTROL 1


/*Funciones asociadas a timers*/
void Init_Timers();
void ActualizarDec();
void ActualizarSeg();
void ActualizarMin();
void SetTimer(uint16_t timer);
