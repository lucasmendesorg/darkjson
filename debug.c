#include <stdio.h>
#include <stdarg.h>
#include <darkjson.h>

#ifdef DEBUG
int debugf(const char *who, const char *fmt, ...) {
	va_list args;
	char buffer[4096];
	va_start(args, fmt);
	vsnprintf(buffer, sizeof(buffer), fmt, args);
	va_end(args);
	if(!who) who = "";
	return fprintf(stderr, "%24s - %s\n", who, buffer);
}
#endif
int tracef(const char *who, const char *fmt, ...) {
	va_list args;
	char buffer[4096];
	va_start(args, fmt);
	vsnprintf(buffer, sizeof(buffer), fmt, args);
	va_end(args);
	if(!who) who = "";
	return fprintf(stderr, "%24s - %s\n", who, buffer);
}
