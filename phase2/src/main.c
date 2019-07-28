#include "asl.h"
#include "const.h"
#include "const_rikaya.h"
#include "main.h"
#include "pcb.h"
#include "scheduler.h"
#include "utils.h"

struct list_head ready_queue; /* Coda dei processi in stato ready */
pcb_t* current_process; /* Puntatore al processo attualmente in esecuzione */
int process_counter;	/* Contatore dei processi */
int clock_semaphore; /* Semaforo del clock (SYS6) */
int clock_semaphore_counter; /* Contatore dei processi bloccati sul semaforo del clock */

int main() {
  initNewAreas(); /* Iniziliazzazione delle new area */
  initPcbs(); /* Inizializzazione lista PCB liberi */
  initAsl(); /* Inizializzazione lista SEMD liberi */
  mkEmptyProcQ(&ready_queue); /* Inizializzazione lista processi in stato ready */

  process_counter = 0;
  current_process = NULL;

  /* Inizializzazione semaforo del clock */
  clock_semaphore = 0;
  clock_semaphore_counter = 0;

  // Per ora settiamo priorità 1
  pcb_t* pcb = initPCB(test, 1); /* Inizializza processo */

  insertProcQ(&ready_queue, pcb); /* Inserimento di pcb nella coda dei processi in stato ready */

  setIT(SYSTEM_CLOCK); /* System Clock Timer */

  scheduler(); /* Passaggio del controllo allo scheduler */
  return 0;
}
