#include "crew.hpp"

#include <cstdlib>

Crew::Crew(const std::string &crew_code,
           const std::shared_ptr<ServerClient> &client)
    : Crew(crew_code) {
  this->addCrewMember(client);
}

std::string Crew::genCrewCode() {
  const char chars[] = "abcdefghijklmnopqrstuvwxyz";
  std::string code(6, ' ');

  for (int i = 0; i < 6; i++) {
    code[i] = chars[rand() % 26];
  }
  return code;
}

void Crew::addCrewMember(const std::shared_ptr<ServerClient> &client) {
  this->crew_members.push_back(client);
  client->setCrewmenber(true);
}
