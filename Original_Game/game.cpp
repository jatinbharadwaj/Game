#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>
#include <vector>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Game");
    
    sf::CircleShape bullet(5.f);
    bullet.setFillColor(sf::Color(255, 255, 255));
    bullet.setPosition(50.f, 700.f);
    sf::Vector2f bvelocity;
    bvelocity.x = 0;
    bvelocity.y = -.1;
    
    //circle one
    sf::CircleShape circle(50.f);
    circle.setFillColor(sf::Color(150, 50, 250));
    circle.setPosition(0.f, -200.f);
    
    //circle two
    sf::CircleShape circle2(50.f);
    circle2.setFillColor(sf::Color(50, 50, 250));
    circle2.setPosition(100.f, -200.f);
    
    //circle three
    sf::CircleShape circle3(50.f);
    circle3.setFillColor(sf::Color(150, 50, 50));
    circle3.setPosition(200.f, -200.f);
    
    //circle four
    sf::CircleShape circle4(50.f);
    circle4.setFillColor(sf::Color(150, 50, 50));
    circle4.setPosition(300.f, -200.f);
    
    //circle five
    sf::CircleShape circle5(50.f);
    circle5.setFillColor(sf::Color(150, 50, 50));
    circle5.setPosition(400.f, -200.f);
    
    //circle six
    sf::CircleShape circle6(50.f);
    circle6.setFillColor(sf::Color(150, 50, 50));
    circle6.setPosition(500.f, -200.f);
    
    //circle seven
    sf::CircleShape circle7(50.f);
    circle7.setFillColor(sf::Color(255, 0, 255));
    circle7.setPosition(600.f, -2000.f);
    
    
    
    
    //velocity vetor 1
    sf::Vector2f velocity;
    velocity.x = 0;
    velocity.y = .01;
    
    //velocity vector 2
    sf::Vector2f velocity2;
    velocity2.x = 0;
    velocity2.y = .02;
    
    //velocity vector 3
    sf::Vector2f velocity3;
    velocity3.x = .0;
    velocity3.y = .005;
    
    //velocity vector 4
    sf::Vector2f velocity4;
    velocity4.x = .0;
    velocity4.y = .03;
    
    int s = rand() % 3, s1 = rand() % 3, s2 = rand() % 3, s3 = rand() % 3;
    std::vector<sf::Vector2f> velocities = {velocity, velocity2, velocity3, velocity4};
    
    
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        //move circle 1
        sf::Vector2f position = circle.getPosition();
        position += velocity;
        circle.setPosition(position);
        
        //move circle 2
        sf::Vector2f position2 = circle2.getPosition();
        position2 += velocity2;
        circle2.setPosition(position2);
        
        //move circle 3
        sf::Vector2f position3 = circle3.getPosition();
        position3 += velocity3;
        circle3.setPosition(position3);
        
        //move circle 4
        sf::Vector2f position4 = circle4.getPosition();
        position4 += velocity3;
        circle4.setPosition(position4);
        
        //move circle 5
        sf::Vector2f position5 = circle5.getPosition();
        position5 += velocity3;
        circle5.setPosition(position5);
        
        //move circle 6
        sf::Vector2f position6 = circle6.getPosition();
        position6 += velocity3;
        circle6.setPosition(position6);
        
        //move circle 7
        sf::Vector2f position7 = circle7.getPosition();
        position7 += velocity4;
        circle7.setPosition(position7);
        
        //move bullet
        sf::Vector2f bulletPosition = bullet.getPosition();
        bulletPosition += bvelocity;
        bullet.setPosition(bulletPosition);
        
        // get the bounding box of the entity
        sf::FloatRect boundingBox = circle.getGlobalBounds();

        // check collision with a point
        sf::Vector2f point = bullet.getPosition();
        if (boundingBox.contains(point))
        {
            circle.setFillColor(sf::Color(0, 0, 0));
        }
        
        window.clear(sf::Color::Black);
        window.draw(circle);
        window.draw(circle2);
        window.draw(circle3);
        window.draw(circle4);
        window.draw(circle5);
        window.draw(circle6);
        window.draw(circle7);
        window.draw(bullet);
        window.display();
        
        int bottom = 900;
        int c1 = rand() % 255, c2 = rand() % 255, c3 = rand() % 255, c4 = rand() % 255, c5 = rand() % 255, c6 = rand() % 255, c7 = rand() % 255, c8 = rand() % 255, c9 = rand() % 255, c10 = rand() % 255, c11 = rand() % 255, c12 = rand() % 255, c13 = rand() % 255, c14 = rand() % 255, c15 = rand() % 255, c16 = rand() % 255, c17 = rand() % 255, c18 = rand() % 255, c19 = rand() % 255, c20 = rand() % 255, c21 = rand() % 255;
        
        if (position.y > bottom){
            circle.setPosition(0.f, 0.f);
            circle.setFillColor(sf::Color(c1, c2, c3));
        }
        if (position2.y > bottom){
            circle2.setPosition(100.f, -100.f);
            circle2.setFillColor(sf::Color(c4, c5, c6));
        }
        if (position3.y > bottom){
            circle3.setPosition(200.f, -100.f);
            circle3.setFillColor(sf::Color(c7, c8, c9));
        }
        if (position4.y > bottom){
            circle4.setPosition(300.f, -100.f);
            circle4.setFillColor(sf::Color(c10, c11, c12));
        }
        if (position5.y > bottom){
            circle5.setPosition(400.f, -100.f);
            circle5.setFillColor(sf::Color(c13, c14, c15));
        }
        if (position6.y > bottom){
            circle6.setPosition(500.f, -100.f);
            circle6.setFillColor(sf::Color(c16, c17, c18));
        }
        if (position7.y > bottom){
            circle7.setPosition(600.f, -100.f);
            circle7.setFillColor(sf::Color(c19, c20, c21));
        }
    }

    return 0;
}
