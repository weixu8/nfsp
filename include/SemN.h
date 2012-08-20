/**
 *
 * \file    $RCSfile: SemN.h,v $
 * \author  $Author: deniel $ 
 * \date    $Date: 2005/08/03 07:05:46 $
 * \brief   Portable system tools.
 *
 * Defines system utilities (like semaphores)
 * so that they are POSIX and work on
 * most plateforms.
 *
 *
 */

#ifndef TOOLS_H
#define TOOLS_H

#include <pthread.h>
#include <semaphore.h>

/*
 *  Synchronization features
 */

typedef struct semaphore
{
  sem_t semaphore;
} semaphore_t;

/** Initializes a semaphore. */
int semaphore_init(semaphore_t * sem, unsigned int value);
/** Destroys a semaphore. */
int semaphore_destroy(semaphore_t * sem);

/** Takes a token. */
void semaphore_P(semaphore_t * sem);
/** Give back a token. */
void semaphore_V(semaphore_t * sem);

#endif
