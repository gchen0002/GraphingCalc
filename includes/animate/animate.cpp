#include "animate.h"
#include "constants.h"
#include <iostream>
#include "system.h"

animate::animate()
    : font(), myTextLabel(font), sidebar(WORK_PANEL, SIDE_BAR), graph_info(new Graph_Info())
{
    cout << "animate CTOR: TOP" << endl;
    system = System(graph_info);
    // SFML 3: VideoMode constructor takes sf::Vector2u or {unsigned int, unsigned int}
    window.create(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "SFML window!");
    // VideoMode class has functions to detect screen size etc.
    // RenderWindow constructor has a third argumnet to set style
    // of the window: resize, fullscreen etc.

    // System will be implemented to manage a vector of objects to be animated.
    //   at that point, the constructor of the System class will take a vector
    //   of objects created by the animate object.
    //   animate will
    // system = System(); // system is already default-constructed as a member
    window.setFramerateLimit(60);

    mouseIn = true;

    mousePoint = sf::CircleShape(); // default constructed, then set properties
    mousePoint.setRadius(5.0f);     // use f for float literal
    mousePoint.setFillColor(sf::Color::Red);

    cout << "Game CTOR. preparing to load the font." << endl; // Typo: Geme -> Game
    //--- FONT ----------
    // font file must be in the "working directory:
    //      debug folder
    // Make sure working directory is where it should be and not
    //  inside the app file:
    //  Project->RUN->Working Folder
    //
    // font must be a member of the class.
    //  Will not work with a local declaration
    if (!font.openFromFile("Roboto-Thin.ttf")) // SFML 3: openFromFile
    {
        cout << "animate() CTOR: Font failed to load" << endl;
        cin.get();
        exit(-1);
    }

    // myTextLabel is already constructed with font. now set its properties.
    // myTextLabel = sf::Text("Initial String for myTextLabel", font); // This was assignment + wrong constructor
    myTextLabel.setString("Initial String for myTextLabel");
    // myTextLabel.setFont(font); // Redundant, already constructed with font
    myTextLabel.setCharacterSize(20);
    myTextLabel.setStyle(sf::Text::Style::Bold); // SFML 3: sf::Text::Style::Bold
    myTextLabel.setFillColor(sf::Color::Green);
    // assuming .height is correct for SFML 3. Use .f for float literals.
    myTextLabel.setPosition(sf::Vector2f(10.f, SCREEN_HEIGHT - myTextLabel.getLocalBounds().size.y - 5.f));
    cout << "animate instantiated successfully." << endl;
}

void animate::Draw()
{
    system.Draw(window);
    if (mouseIn)
    {
        window.draw(mousePoint);
    }

    sidebar.draw(window);

    //- - - - - - - - - - - - - - - - - - -
    // getPosition() gives you screen coords, getPosition(window) gives you window coords
    // cout<<"mosue pos: "<<sf::Mouse::getPosition(window).x<<", "<<sf::Mouse::getPosition(window).y<<endl;
    //- - - - - - - - - - - - - - - - - - -

    // drawing Test: . . . . . . . . . . . .
    // This is how you draw text:)
    window.draw(myTextLabel);
    //. . . . . . . . . . . . . . . . . . .
}

void animate::update()
{
    // cause changes to the data for the next frame
    system.Step(command);
    command = 0;
    if (mouseIn)
    {
        // mousePoint red dot:
        // sf::Mouse::getPosition returns sf::Vector2i. setPosition prefers sf::Vector2f or float, float.
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        mousePoint.setPosition({static_cast<float>(mousePos.x - 5),
                               static_cast<float>(mousePos.y - 5)});

        // mouse location text for sidebar:
        sidebar[SB_MOUSE_POSITION] = mouse_pos_string(window);
    }
}
void animate::render()
{
    window.clear();
    Draw();
    window.display();
}

void animate::processEvents()
{
    // sf::Event event;
    float mouseX, mouseY;
    // SFML 3: pollEvent returns std::optional<sf::Event>
    while (auto optEvent = window.pollEvent())
    {
        sf::Event event = *optEvent; // get the event from the optional

        // check the type of the event...
        if (event.is<sf::Event::Closed>())
        {
            window.close();
        }
        else if (const sf::Event::KeyPressed* keyPressed = event.getIf<sf::Event::KeyPressed>())
        {
            switch (keyPressed->code)
            {
            case sf::Keyboard::Key::Left: // SFML 3: sf::Keyboard::Key::Left
                sidebar[SB_KEY_PRESSED] = "LEFT ARROW";
                command = 4;
                break;
            case sf::Keyboard::Key::Right: // SFML 3: sf::Keyboard::Key::Right
                sidebar[SB_KEY_PRESSED] = "RIGHT ARROW";
                command = 6;
                break;
            case sf::Keyboard::Key::Escape: // SFML 3: sf::Keyboard::Key::Escape
                sidebar[SB_KEY_PRESSED] = "ESC: EXIT";
                window.close();
                break;
            default:
                break;
            }
        }
        else if (event.is<sf::Event::MouseEntered>())
        {
            mouseIn = true;
        }
        else if (event.is<sf::Event::MouseLeft>())
        {
            mouseIn = false;
        }
        else if (const sf::Event::MouseMoved* mouseMoved = event.getIf<sf::Event::MouseMoved>())
        {
            mouseX = static_cast<float>(mouseMoved->position.x); // position is sf::Vector2i
            mouseY = static_cast<float>(mouseMoved->position.y);
            // do something with it if you need to...
        }
        else if (const sf::Event::MouseButtonReleased* mouseButton = event.getIf<sf::Event::MouseButtonReleased>())
        {
            if (mouseButton->button == sf::Mouse::Button::Right) // SFML 3: sf::Mouse::Button::Right
            {
                sidebar[SB_MOUSE_CLICKED] = "RIGHT CLICK " +
                                            mouse_pos_string(window);
            }
            else // assuming other clicks are left, or check sf::Mouse::Button::Left
            {
                sidebar[SB_MOUSE_CLICKED] = "LEFT CLICK " +
                                            mouse_pos_string(window);
            }
        }

    }
}
void animate::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render(); // clear/draw/display
    }
    cout << endl
         << "-------ANIMATE MAIN LOOP EXITING ------------" << endl;
}


std::string mouse_pos_string(sf::RenderWindow &window)
{
    return "(" +
           std::to_string(sf::Mouse::getPosition(window).x) +
           ", " +
           std::to_string(sf::Mouse::getPosition(window).y) +
           ")";
}