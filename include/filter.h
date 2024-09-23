#ifndef FILTER_H
#define FILTER_H

char filter(char c, char (*filter_func)(char));
char upper(char c);
char lower(char c);
char null(char c);

#endif // FILTER_H
