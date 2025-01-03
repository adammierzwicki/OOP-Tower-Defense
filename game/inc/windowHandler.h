#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

#include "drawableObject.h"
#include "ui.h"

class UI;

/**
 * @brief Class for handling window and system events
 *
 * Contains methods for initializing window, polling
 * events and rendering objects on screen
 */
class WindowHandler {
private:
    //-----------------------------------
    //             Attributes
    //-----------------------------------

    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event windowEvent;
    std::vector<sf::Event> events;

    //-----------------------------------
    //          Private methods
    //-----------------------------------

    /**
     * @brief Initialize window
     *
     * Sets window size, title and framerate limit, opens new window
     */
    void initWindow();
    /**
     * @brief Poll events
     *
     * Polls events from window and handles them
     */
    void pollEvents();

public:

    //-----------------------------------
    //     Constructor and destructor
    //-----------------------------------

    /**
     * @brief Construct a new Window Handler object
     *
     * Initializes new window by calling `initWindow` function
     */
    WindowHandler();

    /**
     * @brief Destroy the Window Handler object
     *
     * Deletes window object and frees memory
     */
    ~WindowHandler();

    //-----------------------------------
    //             Accessors
    //-----------------------------------

    /**
     * @brief Get window
     * @return Pointer to window object
     */
    sf::RenderWindow* getWindow() const;

    /**
     * @brief Get events list
     * @return Vector of events
     */
    const std::vector<sf::Event>& getEvents() const;

    //-----------------------------------
    //          Public methods
    //-----------------------------------

    /**
     * @brief Check if left mouse button is clicked
     *
     * @return True if left mouse button is clicked, false otherwise
     */
    bool mouseLeftClicked();

    /**
     * @brief Render window
     *
     * @param background Background sprite
     * @param screenContent Vector of objects to render
     *
     * Renders background and all objects from `screenContent` vector in order on window
     */
    void render(sf::Sprite background, std::vector<DrawableObject*> screenContent, UI* ui);

    /**
     * @brief Check if window is open
     *
     * @return True if window is open, false otherwise
     */
    bool running() const;

    /**
     * @brief Update window
     *
     * Calls `pollEvents` function
     */
    void update();
};