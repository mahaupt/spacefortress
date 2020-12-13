#pragma once

#include <string>
#include <vector>
#include <memory>

#include "serverclient.hpp"

class Crew {
public:
  std::string crew_code;
  
  std::vector<std::weak_ptr<ServerClient>> crew_members;
  
  std::string genCrewCode();
};
