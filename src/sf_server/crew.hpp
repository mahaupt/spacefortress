#pragma once

#include <memory>
#include <string>
#include <vector>

#include "serverclient.hpp"

class Crew {
 public:
  std::string crew_code;

  std::vector<std::weak_ptr<ServerClient>> crew_members;

  Crew(const std::string &crew_code) : crew_code(crew_code) {}
  Crew(const std::string &crew_code,
       const std::shared_ptr<ServerClient> &client);

  void addCrewMember(const std::shared_ptr<ServerClient> &client);

  // info
  static std::string genCrewCode();
};
