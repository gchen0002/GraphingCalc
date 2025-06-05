#include "sidebar.h"
#include "constants.h" // For SCREEN_HEIGHT
#include <iostream>   // Included via sidebar.h but good practice

Sidebar::Sidebar()
    : font(), sb_text(font), _left(0.f), _width(0.f) // initialize sb_text, provide defaults for _left, _width
{
    // this constructor is minimal. if it's actually used,
    // it would likely need to load the font and set up 'rect' as well.
    // for now, this makes it compile by initializing sb_text.
    std::cout << "Sidebar Default CTOR: Minimal initialization." << std::endl;
    items.reserve(50);

    for (int i = 0; i < 30; i++)
    {
        items.push_back("");
    }
}

Sidebar::Sidebar(float left, float width)
    : font(), sb_text(font), _left(left), _width(width) // Initialize sb_text with font
{
    cout << "Sidebar CTOR: TOP" << endl;
    items.reserve(50);

    // set up the sidebar rectangle:
    rect.setFillColor(sf::Color(105, 105, 105)); //(192,192,192)); //silver
    rect.setPosition(sf::Vector2f(left, 0));
    rect.setSize(sf::Vector2f(width, SCREEN_HEIGHT));
    cout << "Sidebar CTOR: about to load font." << endl;
    
    ////- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // the font file must be in the "working directory"
    //  check projects->run->working directory
    //       [Make sure it's not pointing to the app file]

    if (!font.openFromFile("Roboto-Thin.ttf")) // SFML 3: openFromFile
    {
        cout << "Sidebar() CTOR: Font failed to load" << endl;
        cin.get();
        exit(-1);
    }
    ////- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    cout << "Sidebar CTOR: loaded font." << endl;

    //. . . . . text / font problems: . . . . . . . .
    // sb_text is already constructed with 'font'. Now set its properties.
    // sb_text.setFont(font); // This is redundant as it was constructed with font.
    sb_text.setCharacterSize(20);
    sb_text.setStyle(sf::Text::Style::Bold); // SFML 3: sf::Text::Style::Bold
    sb_text.setFillColor(sf::Color::Yellow);

    ////this is how you would position text on screen:
    // sb_text.setPosition(sf::Vector2f(10, SCREEN_HEIGHT-sb_text.getLocalBounds().height-5));

    items.push_back("sidebar sample text");
    // Fill the items vector with empty strings so that we can use [] to read them:
    for (int i = 0; i < 30; i++)
    {
        items.push_back("");
    }
    cout << "Sidebar: CTOR: Exit." << endl;
}

void Sidebar::draw(sf::RenderWindow &window)
{
    const float VERTICAL_LINE_SPACING = 5.0;
    const float LEFT_MARGIN = 10.0;

    window.draw(rect);
    float height = 10.f; 
    texts.clear(); // Clear the vector of bounding boxes

    for (int i = 0; i < items.size(); i++) 
    {
        sb_text.setString(items[i].c_str());
        sb_text.setPosition(sf::Vector2f(_left + LEFT_MARGIN, height));
        
        // Store the bounding box 
        texts.push_back(sb_text.getGlobalBounds());

        height += sb_text.getLocalBounds().size.y + VERTICAL_LINE_SPACING;
        window.draw(sb_text);
    }
}

string &Sidebar::operator[](int index)
{
    return items[index];
}


int Sidebar::ButtonClicked(sf::Vector2f mouse_pos)
{
    for (int i = 0; i < texts.size(); i++)
    {
        // Check if the item string is not empty and if the mouse click is within its bounds
        if (!items[i].empty() && texts[i].contains(mouse_pos))
        {
            return i; // Return the index of the clicked item
        }
    }
    return -1; // No button was clicked
}