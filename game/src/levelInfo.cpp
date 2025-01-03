#include "../inc/levelInfo.h"

#include <iostream>

#include "../inc/customQueue.h"

//-----------------------------------
//     Constructor and destructor
//-----------------------------------

LevelInfo::LevelInfo(int level) {
    this->logger = Logger::getInstance();
    this->level = level;
    this->loadLevel();
}

LevelInfo::~LevelInfo() {
    if (this->mapFile.is_open()) {
        this->mapFile.close();
    }
}

//-----------------------------------
//          Private methods
//-----------------------------------

void LevelInfo::loadLevel() {
    std::string filePath = "levels/level_" + std::to_string(this->level) + ".map";
    this->mapFile.open(filePath);

    if (this->mapFile.is_open()) {
        this->loadPathPoints();
        this->loadEnemies();
        this->loadMap();
        this->loadCoordinates();
    }
    else {
        this->logger->log(LogLevel::CRITICAL, "Failed to load level " + std::to_string(this->level) + " file (\"./" + filePath + "\")", "LevelInfo::loadLevel()", __LINE__);
        throw std::runtime_error("Failed to load level " + std::to_string(this->level));
    }
    this->mapFile.close();

    this->loadTexture();

    this->logger->log(LogLevel::DEBUG, "Loaded level " + std::to_string(this->level) + " info", "LevelInfo::loadLevel()", __LINE__);
}

void LevelInfo::loadPathPoints() {
    std::string line;
    std::getline(this->mapFile, line);

    while (!line.empty()) {
        float x = std::stof(line.substr(0, line.find(',')));
        float y = std::stof(line.substr(line.find(',') + 1));
        this->path.push_back(sf::Vector2f(x, y));
        this->pathLength++;
        std::getline(this->mapFile, line);
    }
}

void LevelInfo::loadEnemies() {
    std::string line;
    std::getline(this->mapFile, line);
    this->roundsCount = std::stoi(line);

    for (int round = 0; round < this->roundsCount; round++) {
        std::getline(this->mapFile, line);
        this->rounds[round] = Queue<char>();
        while (!line.empty()) {
            std::string enemyType = line.substr(0, line.find(','));
            int num = std::stoi(line.substr(line.find(',') + 1));
            for (int i = 0; i < num; i++) {
                this->rounds[round].push(enemyType[0]);
            }
            std::getline(this->mapFile, line);
        }
    }
}

void LevelInfo::loadMap() {
    std::string line;
    std::getline(this->mapFile, line);

    unsigned int width = std::stoul(line.substr(0, line.find(',')));
    unsigned int height = std::stoul(line.substr(line.find(',') + 1));
    this->mapSize = std::make_pair(width, height);

    for (unsigned int i = 0; i < height; i++) {
        std::getline(this->mapFile, line);
        std::vector<bool> row;
        for (size_t j = 0; j < width; j++) {
            if (line[j] == 'O') {
                row.push_back(false);
            }
            else {
                row.push_back(true);
            }
        }
        this->map.push_back(row);
    }
    std::getline(this->mapFile, line);
}

void LevelInfo::loadCoordinates() {
    std::string line;
    std::getline(this->mapFile, line);

    int width = std::stoi(line.substr(0, line.find(',')));
    int height = std::stoi(line.substr(line.find(',') + 1));
    this->mapTileSize = sf::Vector2f(width, height);

    for (int i = 0; i < 4; i++) {
        std::getline(this->mapFile, line);
        float x = std::stof(line.substr(0, line.find(',')));
        float y = std::stof(line.substr(line.find(',') + 1));
        this->mapCorners[i] = sf::Vector2f(x, y);
    }
}

void LevelInfo::loadTexture() {
    std::string path = "textures/level_" + std::to_string(this->level) + ".png";
    if (!this->levelBackground.loadFromFile(path)) {
        this->logger->log(LogLevel::CRITICAL, "Failed to load level " + std::to_string(this->level) + " background (\"./" + path + "\")", "LevelInfo::loadTexture()", __LINE__);
        throw std::runtime_error("Failed to load level " + std::to_string(this->level) + " background");
    }
}

//-----------------------------------
//             Accessors
//-----------------------------------

sf::Texture LevelInfo::getBackgroundTexture() const { return this->levelBackground; }

const sf::Vector2f* LevelInfo::getMapCorners() const { return this->mapCorners; }

int LevelInfo::getMapHeight() const { return this->mapSize.second; }

int LevelInfo::getMapWidth() const { return this->mapSize.first; }

sf::Vector2f LevelInfo::getMapTileSize() const { return this->mapTileSize; }

char LevelInfo::getNextEnemy(int round) { return this->rounds[round].pop(); }

std::vector<sf::Vector2f> LevelInfo::getPath() const { return this->path; }

sf::Vector2f LevelInfo::getLastPathPoint() const { return this->path.back(); }

int LevelInfo::getPathLength() const { return this->pathLength; }

int LevelInfo::getRoundsCount() const { return this->roundsCount; }

//-----------------------------------
//          Public methods
//-----------------------------------

bool LevelInfo::isTileBlocked(std::pair<unsigned int, unsigned int> tile) const {
    return this->map[tile.second][tile.first];
}

void LevelInfo::blockTile(std::pair<unsigned int, unsigned int> tile) {
    this->map[tile.second][tile.first] = true;
}

void LevelInfo::unblockTile(std::pair<unsigned int, unsigned int> tile) {
    this->map[tile.second][tile.first] = false;
}

bool LevelInfo::hasNextEnemy(int round) const {
    if (round >= this->roundsCount) {
        this->logger->log(LogLevel::WARNING, "Round " + std::to_string(round) + " does not exist", "LevelInfo::hasNextEnemy()", __LINE__);
        return false;
    }
    return !this->rounds.at(round).empty();
}