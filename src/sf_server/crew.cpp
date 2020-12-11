#include "crew.hpp"

#include <cstdlib>

std::string Crew::genCrewCode() {
  const char chars[] = "abcdefghijklmnopqrstuvwxyz";
  std::string code(6, ' ');
  
  for(int i=0; i < 6; i++) {
    code[i] = chars[rand()%26];
  }
  return code;
}
