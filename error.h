// error.h
// Řešení IJC-DU1, příklad b), 17.3.2021
// Autor: Vitkor Kubec, FIT
// Přeloženo: gcc 9.3.0

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#pragma once
void warning_msg(const char *fmt, ...);
void error_exit(const char *fmt, ...);
