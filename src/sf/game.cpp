#include "game.hpp"

#include "main.hpp"

Game::Game() : running(false) { Log::info("game module loaded"); }

/**
 * game objects are auto freed
 */
Game::~Game() {}

/**
 * main loading function
 */
void Game::createGameWorld() {
  this->running = true;

  // add playership
  auto playership = std::make_shared<Ship>("Omega", 100, &game_objects);
  playership->setPos(Vec2(-1, 0.1));
  playership->addStandardModules();
  this->pshipos = std::make_shared<ShipOs>(playership.get());
  this->pship = playership;
  this->game_objects.push_back(playership);

  // add planets
  this->game_objects.push_back(std::make_shared<go::Planet>("Rix", 1, 1));
  this->game_objects.push_back(std::make_shared<go::Planet>("Lira", 2, -1));
  this->game_objects.push_back(std::make_shared<go::Planet>("Omecron", -3, 0));
  this->game_objects.push_back(std::make_shared<go::Planet>("Deca", -4, -2));
  this->game_objects.push_back(std::make_shared<go::Planet>("Zyppr", 5, 2));

  // add star
  this->game_objects.push_back(std::make_shared<go::Star>("Mycra", 0, 0));

  // add Station
  this->game_objects.push_back(
      std::make_shared<go::Station>("Mycra Outpost", -1, 0));

  // add some other ships
  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution(-8.0, 8.0);
  for (int i = 0; i < 5; i++) {
    auto friendly_ship = std::make_shared<Ship>("Camera", 100, &game_objects);
    friendly_ship->setPos(
        Vec2(distribution(generator), distribution(generator)));
    friendly_ship->addStandardModules();
    friendly_ship->addModule(new module::ShipAi("Ship AI", 1));
    this->game_objects.push_back(friendly_ship);
  }

  Log::info("game objects created");
}

/**
 * creating game objects, player ship and startup shipos
 */
void Game::start() {
  this->createGameWorld();
  this->pshipos->boot();
  (void)this->calcSimTime(); //call once to init timer
  Log::info("game start");
}

/**
 * cleanup game memory
 */
void Game::stop() {
  this->running = false;
  this->pshipos.reset();
  this->game_objects.clear();
  Log::info("game stop");
}

/**
 * main simulation and render loop
 * GameObjects will be simulated (todo: check if async simulation is benificial)
 * ShipOs renders the main display
 * execution of all main OS functions
 */
void Game::render(ConsoleKey key) {
  // simulate
  double sim_time = this->calcSimTime();
  for (size_t i = 0; i < this->game_objects.size(); i++) {
    this->game_objects[i]->simulate(sim_time);
  }

  // render
  this->pshipos->render(key);
}

/**
 * render loop of shipos windows and popups
 * This is called after the main window is refreshed
 */
void Game::renderWin(ConsoleKey key) {
  this->pshipos->renderWin(key);

  // garbage collector
  this->garbageCollector();
}

/**
 * calculates the time period since the last time this function was called, or 0
 * on the first call. used to call once for simulation times, do not call twice
 * per game loop!
 */
double Game::calcSimTime() {
  static auto last_start_time = std::chrono::steady_clock::now();
  auto start_time = std::chrono::steady_clock::now();
  double sim_time = std::chrono::duration_cast<std::chrono::milliseconds>(
                        start_time - last_start_time)
                        .count() /
                    1000.0;
  last_start_time = start_time;

  return sim_time;
}

/**
 * Searches for dead game objects and removes them from game
 */
void Game::garbageCollector() {
  auto it = this->game_objects.begin();
  while (it != this->game_objects.end()) {
    // is dead object?
    if (!(*it)->isAlive()) {
      it = this->game_objects.erase(it);
    } else {
      it++;
    }
  }
}
