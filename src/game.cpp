#include "game.hpp"

Game::Game() : s("Omega", 100, &game_objects), os(&s) {
  // add player ship
  this->s.setPos(Vec2(-1, 0.1));
  this->s.addModule(new module::Generator("Generator MK I", 1, 1));
  this->s.addModule(new module::Lifesupport("LifeSupport", 1, 3));
  this->s.addModule(new module::Dockingport("Docking port", 1));
  this->s.addModule(new module::Sensor("SR Sensor 2.7", 1));
  this->s.addModule(new module::Cargo("Cargo hold", 1, 1000));
  this->s.addModule(
      new module::ShieldGenerator("Shield Generator MK I", 1, 0.5, 1));
  this->s.addModule(new module::Engine("Engine MK I", 1, 1, 2));
  this->s.addModule(new module::Weapon("S Projectile", 2, 0.1, 0.1, 10));
  this->s.addModule(new module::Capacitor("Capacitor MK I", 1, 100, 1, 10));

  // add planets
  this->game_objects.push_back(new go::Planet("Rix", 1, 1));
  this->game_objects.push_back(new go::Planet("Lira", 2, -1));
  this->game_objects.push_back(new go::Planet("Omecron", -3, 0));
  this->game_objects.push_back(new go::Planet("Deca", -4, -2));
  this->game_objects.push_back(new go::Planet("Zyppr", 5, 2));

  // add star
  this->game_objects.push_back(new go::Star("Mycra", 0, 0));

  // add Station
  this->game_objects.push_back(new go::Station("Mycra Outpost", -1, 0));

  // add some other ships
  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution(-8.0, 8.0);
  for (int i = 0; i < 5; i++) {
    Ship *friendly_ship = new Ship("Camera", 100, &game_objects);
    friendly_ship->setPos(
        Vec2(distribution(generator), distribution(generator)));
    friendly_ship->addModule(new module::Generator("Generator MK I", 1, 1));
    friendly_ship->addModule(new module::ShipAi("Ship AI", 1));
    friendly_ship->addModule(new module::Lifesupport("LifeSupport", 1, 3));
    friendly_ship->addModule(new module::Dockingport("Docking port", 1));
    friendly_ship->addModule(new module::Sensor("SR Sensor 2.7", 1));
    friendly_ship->addModule(new module::Cargo("Cargo hold", 1, 1000));
    friendly_ship->addModule(
        new module::ShieldGenerator("Shield Generator MK I", 1, 0.5, 1));
    friendly_ship->addModule(new module::Engine("Engine MK I", 1, 1, 2));
    friendly_ship->addModule(
        new module::Capacitor("Capacitor MK I", 1, 100, 1, 10));
    this->game_objects.push_back(friendly_ship);
  }

  Log::info("game module loaded");
}

/**
 * free all game objects
 */
Game::~Game() {
  for (const auto &gobject : this->game_objects) {
    delete gobject;
  }
  this->game_objects.clear();
}

void Game::start() {
  this->os.boot();
  Log::info("game start");
}

void Game::render(ConsoleKey key) {
  double sim_time = this->calcSimTime();
  this->s.simulate(sim_time);
  for (const auto &gobject : this->game_objects) {
    gobject->simulate(sim_time);
  }

  this->os.render(key);
}

void Game::renderWin(ConsoleKey key) { this->os.renderWin(key); }

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
