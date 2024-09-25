/*
 * Kevin Nguyen
 * A00955925
 */

#ifndef PROCESS_H
#define PROCESS_H

char process(char cr, char (*filter_func)(char));
char upper_filter(char c);
char lower_filter(char c);
char null_filter(char c);

#endif    // PROCESS_H
