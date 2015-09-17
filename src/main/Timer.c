#include "klib/klib.h"

/**
 * Allocation et initialisation d'un nouveau pointeur de type Timer.
 * @return 
 */
Timer* libexp TimerNew(void)
{
    Timer *this = malloc(sizeof(Timer));
    TimerInit(this);
    
    return this;
}

/**
 * Initialisation d'une structure de type Timer.
 * @param this
 */
void libexp TimerInit(Timer *this)
{
	if(this != NULL)
	{
		this->start = TimerStart;
		this->stop = TimerStop;
		this->time = TimerTime;
		this->cpu = TimerCPU;
		this->cpuTime = TimerCPUTime;

		this->free = TimerFree;
	}
}

/**
 * Libération de la mémoire allouée pour un Timer.
 * @param this
 */
void libexp TimerFree(Timer *this)
{
    free(this);
}

/**
 * Démarrage du Timer.
 * Les valeurs à TIMER_START et TIMER_STOP sont initialisées.
 * @param this
 */
boolean libexp TimerStart(Timer *this)
{
	if(this == NULL)
		return false;
	
    this->_cpu[TIMER_START] = clock();
    this->_cpu[TIMER_STOP] = this->_cpu[TIMER_STOP];
    gettimeofday(&this->_time[TIMER_START], NULL);
    this->_time[TIMER_STOP] = this->_time[TIMER_START];
	
	return true;
}

/**
 * Arrêt du Timer.
 * Les valeurs à TIMER_STOP sont modifiées.
 * @param this
 */
boolean libexp TimerStop(Timer *this)
{
	if(this == NULL)
		return false;
	
    gettimeofday(&this->_time[TIMER_STOP], NULL);
    this->_cpu[TIMER_STOP] = clock();
	
	return true;
}

/**
 * Renvoie le temps écoulé en secondes entre le démarrage et l'arrêt du Timer.
 * @param this
 * @return 
 */
double libexp TimerTime(Timer *this)
{
    return (this != NULL) ? (double)(this->_time[TIMER_STOP].tv_sec + this->_time[TIMER_STOP].tv_usec*0.000001) - (double)(this->_time[TIMER_START].tv_sec + this->_time[TIMER_START].tv_usec*0.000001) : -1.;
}

/**
 * Renvoie le nombre de clocks processeurs entre le démarrage et l'arrêt du Timer.
 * @param this
 * @return 
 */
int libexp TimerCPU(Timer *this)
{
	return (this != NULL) ? (size_t)(this->_cpu[TIMER_STOP] - this->_cpu[TIMER_START]) : -1;
}

/**
 * Renvoie le nombre de secondes d'utilisation processeur entre le démarrage et l'arrêt du Timer.
 * @param this
 * @return 
 */
double libexp TimerCPUTime(Timer *this)
{
    return (this != NULL) ? (double)(this->_cpu[TIMER_STOP] - this->_cpu[TIMER_START])/CLOCKS_PER_SEC : -1.;
}

#ifdef WIN32

/**
 * gettimeofday.c
 *    Win32 gettimeofday() replacement
 *
 * src/port/gettimeofday.c
 *
 * Copyright (c) 2003 SRA, Inc.
 * Copyright (c) 2003 SKC, Inc.
 *
 * Permission to use, copy, modify, and distribute this software and
 * its documentation for any purpose, without fee, and without a
 * written agreement is hereby granted, provided that the above
 * copyright notice and this paragraph and the following two
 * paragraphs appear in all copies.
 *
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE TO ANY PARTY FOR DIRECT,
 * INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING
 * LOST PROFITS, ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS
 * DOCUMENTATION, EVEN IF THE UNIVERSITY OF CALIFORNIA HAS BEEN ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE AUTHOR SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN "AS
 * IS" BASIS, AND THE AUTHOR HAS NO OBLIGATIONS TO PROVIDE MAINTENANCE,
 * SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 * 
 * @param tp
 * @param tzp
 * @return 
 */
int gettimeofday(struct timeval *tp, struct timeval *tzp)
{
    FILETIME    file_time;
    SYSTEMTIME  system_time;
    ULARGE_INTEGER ularge;

    GetSystemTime(&system_time);
    SystemTimeToFileTime(&system_time, &file_time);
    ularge.LowPart = file_time.dwLowDateTime;
    ularge.HighPart = file_time.dwHighDateTime;

    tp->tv_sec = (long) ((ularge.QuadPart - EPOCH) / 10000000L);
    tp->tv_usec = (long) (system_time.wMilliseconds * 1000);

    return 0;
}

#endif