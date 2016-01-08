#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <cstdint>
#include <stdexcept>

void error_message(const char *msg);
void error_message(const std::string &msg);
void verbose_message(const std::string &msg);
void verbose_message(const char *msg);
void set_verbose_mode(const bool verbose);
bool verbose_mode();
char *flat_decode(char *compressed, int size, int &deflated);
char *compress(const char *raw, size_t size, uint32_t &writed) throw(std::exception);
std::string utf16be_to_utf8(std::string &str);
std::string charset_to_utf8(std::string &str);

#endif
