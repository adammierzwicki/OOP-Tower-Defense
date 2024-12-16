#include <iostream>
#include "levelInfo.h"

//-----------------------------------
//     Constructor and destructor
//-----------------------------------

LevelInfo::LevelInfo(int level)
{
    this->level = level;
    this->mapFilePath = "levels/level_" + std::to_string(level) + ".map";
    this->loadLevel();
}

LevelInfo::~LevelInfo()
{
    if (this->mapFile.is_open())
    {
        this->mapFile.close();
    }
}

//-----------------------------------
//          Private methods
//-----------------------------------

void LevelInfo::loadCoordinates()
{
    std::string line;
    std::getline(this->mapFile, line);
    int x = std::stoi(line.substr(0, line.find(',')));
    int y = std::stoi(line.substr(line.find(',') + 1));
    this->mapTileSize = sf::Vector2f(x, y);

    for (int i = 0; i < 4; i++)
    {
        std::getline(this->mapFile, line);
        float x = std::stof(line.substr(0, line.find(',')));
        float y = std::stof(line.substr(line.find(',') + 1));
        this->mapCorners[i] = sf::Vector2f(x, y);
    }
}

void LevelInfo::loadEnemies()
{
    std::string line;
    std::getline(this->mapFile, line);
    while (!line.empty())
    {
        std::string enemyType = line.substr(0, line.find(','));
        int num = std::stoi(line.substr(line.find(',') + 1));
        enemies[enemyType] = num;
        std::getline(this->mapFile, line);
    }
}

void LevelInfo::loadLevel()
{
    this->mapFile.open(this->mapFilePath);
    if (this->mapFile.is_open())
    {
        this->loadPathPoints();
        this->loadEnemies();
        this->loadMap();
        this->loadCoordinates();
    }
    else
    {
        std::cerr << "Error: Could not load level " << this->level << std::endl;
    }
    this->mapFile.close();

    this->loadTexture();
}

void LevelInfo::loadMap()
{
    std::string line;
    std::getline(this->mapFile, line);
    int width = std::stoi(line.substr(0, line.find(',')));
    int height = std::stoi(line.substr(line.find(',') + 1));
    this->mapSize = std::make_pair(width, height);
    for (int i = 0; i < height; i++)
    {
        std::getline(this->mapFile, line);
        std::vector<bool> row;
        for (int j = 0; j < width; j++)
        {
            if (line[j] == 'O')
            {
                row.push_back(false);
            }
            else
            {
                row.push_back(true);
            }
        }
        this->map.push_back(row);
    }
    std::getline(this->mapFile, line);
}

void LevelInfo::loadPathPoints()
{
    std::string line;
    std::getline(this->mapFile, line);
    while (!line.empty())
    {
        float x = std::stof(line.substr(0, line.find(',')));
        float y = std::stof(line.substr(line.find(',') + 1));
        this->path.push_back(sf::Vector2f(x, y));
        this->pathLength++;
        std::getline(this->mapFile, line);
    }
}

void LevelInfo::loadTexture()
{
    std::string path = "textures/level_" + std::to_string(this->level) + ".png";
    if (!this->levelBackground.loadFromFile(path))
    {
        std::cerr << "Error: Could not load level " << this->level << " background" << std::endl;
    }
}

//-----------------------------------
//             Accessors
//-----------------------------------

sf::Texture LevelInfo::getBackgroundTexture()
{
    return this->levelBackground;
}

std::map<std::string, int> LevelInfo::getEnemies()
{
    return this->enemies;
}

sf::Vector2f LevelInfo::getLastPathPoint()
{
    return this->path.back();
}

sf::Vector2f *LevelInfo::getMapCorners()
{
    return this->mapCorners;
}

int LevelInfo::getMapWidth()
{
    return this->mapSize.first;
}

int LevelInfo::getMapHeight()
{
    return this->mapSize.second;
}

sf::Vector2f LevelInfo::getMapTileSize()
{
    return this->mapTileSize;
}

std::vector<sf::Vector2f> LevelInfo::getPath()
{
    return this->path;
}

int LevelInfo::getPathLength()
{
    return this->pathLength;
}

//-----------------------------------
//          Public methods
//-----------------------------------

bool LevelInfo::isTileBlocked(int x, int y)
{
    return this->map[y][x];
}

void LevelInfo::blockTile(int x, int y)
{
    this->map[y][x] = true;
}

void LevelInfo::printInfo()
{
    std::cout << "Level " << this->level << " info:" << std::endl;
    std::cout << "Path points:" << std::endl;
    for (auto point : this->path)
    {
        std::cout << point.x << " " << point.y << std::endl;
    }
    std::cout << "Enemies:" << std::endl;
    for (auto enemy : this->enemies)
    {
        std::cout << enemy.first << " " << enemy.second << std::endl;
    }
}

void LevelInfo::unblockTile(int x, int y)
{
    this->map[y][x] = false;
}
