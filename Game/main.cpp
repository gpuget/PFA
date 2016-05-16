#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Character.h"
#include "MenuController.h"
#include "GameController.h"

using namespace std;

//Width and height
#define SCREEN_W 800
#define SCREEN_H 600

//Selected options and current menu
int selected=0;
int current_menu=0;
//Difficulty and music state
int difficulty=0;
bool music_state=true;

//Draw texts in the window
void draw(sf::RenderWindow& w, sf::Text* t, int n){
    for(int i=0; i<n; i++){
        w.draw(t[i]);
    }
}

int main(void){
    //800x600 window entitled LGGP Project with a fix size
    //Screen frame rate limited at 60Hz
    sf::RenderWindow main_window(sf::VideoMode(SCREEN_W,SCREEN_H), "LGGP Project", sf::Style::Close);
    main_window.setFramerateLimit(60);

    //800x600 window entitled LGGP Project with a fix size
    //Screen frame rate limited at 60Hz
    sf::RenderWindow game_window(sf::VideoMode(SCREEN_W,SCREEN_H), "LGGP Project (IN GAME)", sf::Style::None);
    game_window.setFramerateLimit(60);
    game_window.setVisible(false);
    game_window.setActive(false);
    GameController gc(game_window);

    //Scott head selected as icon for the window
    sf::Image icon;
    icon.loadFromFile("img/icon.png");
    main_window.setIcon(100,100,icon.getPixelsPtr());
    game_window.setIcon(100,100,icon.getPixelsPtr());

    //Select the background
    sf::Texture bgt;
    bgt.loadFromFile("img/background.jpg");
    sf::RectangleShape bg = sf::RectangleShape(sf::Vector2f(800,600));
    bg.setTexture(&bgt);

    //Music by Toby Fox
    sf::Music music;
    sf::Music music2;
    music.openFromFile("audio/menu.wav");
    music.setLoop(true);
    music.setVolume(50.);
    music.play();

    //Validation song
    sf::SoundBuffer buffer;
    buffer.loadFromFile("audio/validation.wav");
    sf::Sound sound;
    sound.setBuffer(buffer);

    //Clear the window with a black screen
    main_window.clear(sf::Color::Black);

    sf::Event event;
    int limit;
    sf::Font font1, font2;
    font1.loadFromFile("font/impact.ttf");
    font2.loadFromFile("font/Minecraft.ttf"); //Craftron Gaming
    sf::Text* titles;
    sf::Text* options;
    ifstream scores_file("scores.txt");
    string main_string[MenuController::MAIN_LIMIT] = {"PLAY", "OPTIONS", "SCORES", "CREDITS", "QUIT"};
    string options_string[MenuController::OP_LIMIT]= {"DIFFICULTY : NOOB", "MUSIC : ON", "BACK"};
    string scores_string[MenuController::SC_LIMIT]= {"", "", "", "", "BACK"};
    string credits_string[MenuController::CR_LIMIT]= {"DEVELOPER : LEO GARREAU",
                                                        "DEVELOPER : GAETAN PUGET",
                                                        "SPRITES : MAVERICK PK",
                                                        "MUSIC : TOBY FOX",
                                                        "FONT : CRAFTRON GAMING",
                                                        "BACK"
                                                    };

    while(main_window.isOpen()){
        switch(current_menu){
            case MenuController::MAIN_ID :
                limit=MenuController::MAIN_LIMIT;

                //Window is listening events
                while(main_window.pollEvent(event)){
                    //Window closed
                    if(event.type==sf::Event::Closed) main_window.close();

                    //Key pressed
                    if(event.type==sf::Event::KeyPressed){
                        switch(event.key.code){
                            //Previous selection
                            case sf::Keyboard::Up : selected = (selected+(limit-1))%limit;
                            break;

                            //Next selection
                            case sf::Keyboard::Down : selected = (selected+1)%limit;
                            break;

                            //Press ENTER
                            case sf::Keyboard::Return : sound.play();
                                switch(selected){
                                    //Quit
                                    case MenuController::MAIN_QUIT :
                                        main_window.close();
                                    break;

                                    //Options menu
                                    case MenuController::MAIN_OPTIONS :
                                        current_menu=MenuController::OP_ID;
                                        selected=0;
                                    break;

                                    //Scores menu
                                    case MenuController::MAIN_SCORES :
                                        current_menu=MenuController::SC_ID;
                                        selected=0;
                                    break;

                                    //Credits menu
                                    case MenuController::MAIN_CREDITS :
                                        current_menu=MenuController::CR_ID;
                                        selected=0;
                                    break;

                                    //Play
                                    case MenuController::MAIN_PLAY :
                                        current_menu=MenuController::PLAY_ID;
                                        selected=0;
                                        music.stop();
                                        music.openFromFile("audio/game.wav");
                                        music.play();
                                    break;
                                }
                            break;

                            default :
                            break;
                        }
                    }
                }

                //Draw the background
                main_window.draw(bg);
                //Mark title
                titles=new sf::Text[3];
                MenuController::printTitles(titles, 3, font1, SCREEN_W, SCREEN_H);
                //Mark options
                options = new sf::Text[limit];
                MenuController::printOptions(main_string, options, limit, font2, SCREEN_W, SCREEN_H, selected);
                //Draw titles and options
                draw(main_window, titles, 3);
                draw(main_window, options, limit);

                main_window.display();
            break;

            //Options menu
            case MenuController::OP_ID :
                limit=MenuController::OP_LIMIT;

                //Window is listening events
                while(main_window.pollEvent(event)){
                    //Window closed
                    if(event.type==sf::Event::Closed) main_window.close();

                    //Key pressed
                    if(event.type==sf::Event::KeyPressed){
                        switch(event.key.code){
                            //Previous selection
                            case sf::Keyboard::Up : selected = (selected+(limit-1))%limit;
                            break;

                            //Next selection
                            case sf::Keyboard::Down : selected = (selected+1)%limit;
                            break;

                            case sf::Keyboard::Left :
                                switch(selected){
                                    //Change difficulty
                                    case MenuController::OP_DIFFICULTY :
                                        if(difficulty==2){
                                            difficulty--;
                                            options_string[MenuController::OP_DIFFICULTY]="DIFFICULTY : NORMAL";
                                            sound.play();
                                        }else if(difficulty==1){
                                            difficulty--;
                                            options_string[MenuController::OP_DIFFICULTY]="DIFFICULTY : NOOB";
                                            sound.play();
                                        }
                                    break;

                                    //Change music state
                                    case MenuController::OP_MUSIC :
                                        if(!music_state){
                                            music_state=!music_state;
                                            options_string[MenuController::OP_MUSIC]="MUSIC : ON";
                                            music.play();
                                        }
                                    break;
                                }
                            break;

                            case sf::Keyboard::Right :
                                switch(selected){
                                    //Change difficulty
                                    case MenuController::OP_DIFFICULTY :
                                        if(difficulty==0){
                                            difficulty++;
                                            options_string[MenuController::OP_DIFFICULTY]="DIFFICULTY : NORMAL";
                                            sound.play();
                                        }else if(difficulty==1){
                                            difficulty++;
                                            options_string[MenuController::OP_DIFFICULTY]="DIFFICULTY : TRY HARDER";
                                            sound.play();
                                        }
                                    break;

                                    //Change music state
                                    case MenuController::OP_MUSIC :
                                        if(music_state){
                                            music_state=!music_state;
                                            options_string[MenuController::OP_MUSIC]="MUSIC : OFF";
                                            music.pause();
                                        }
                                    break;
                                }
                            break;

                            //Press ENTER
                            case sf::Keyboard::Return :
                                switch(selected){
                                    //Go to Main menu
                                    case MenuController::OP_BACK :
                                        current_menu=MenuController::MAIN_ID;
                                        selected=0;
                                        sound.play();
                                    break;
                                }
                            break;

                            default:
                            break;
                        }
                    }
                }
                //Draw the background
                main_window.draw(bg);
                //Mark title
                MenuController::printTitles(titles, 3, font1, SCREEN_W, SCREEN_H);
                //Mark options
                options = new sf::Text[limit];
                MenuController::printOptions(options_string, options, limit, font2, SCREEN_W, SCREEN_H, selected);
                //Draw titles and options
                draw(main_window, titles, 3);
                draw(main_window, options, limit);

                main_window.display();
            break;

            //Scores menu
            case MenuController::SC_ID :
                selected=MenuController::SC_BACK;
                limit=MenuController::SC_LIMIT;

                //Window is listening events
                while(main_window.pollEvent(event)){
                    //Window closed
                    if(event.type==sf::Event::Closed) main_window.close();

                    //Key pressed
                    if(event.type==sf::Event::KeyPressed){
                        switch(event.key.code){
                            //Press ENTER
                            case sf::Keyboard::Return :
                                switch(selected){
                                    //Go to Main menu
                                    case MenuController::SC_BACK :
                                        current_menu=MenuController::MAIN_ID;
                                        selected=0;
                                        sound.play();
                                    break;
                                }
                            break;

                            default:
                            break;
                        }
                    }
                }
                //Draw the background
                main_window.draw(bg);
                //Mark title
                MenuController::printTitles(titles, 3, font1, SCREEN_W, SCREEN_H);
                //Mark options
                options = new sf::Text[limit];
                for(int i=0;i<limit-1;i++) getline(scores_file, scores_string[i]);
                MenuController::printOptions(scores_string, options, limit, font2, SCREEN_W, SCREEN_H, selected);
                //Draw titles and options
                draw(main_window, titles, 3);
                draw(main_window, options, limit);

                main_window.display();
            break;

            //Credits menu
            case MenuController::CR_ID :
                selected=MenuController::CR_BACK;
                limit=MenuController::CR_LIMIT;

                //Window is listening events
                while(main_window.pollEvent(event)){
                    //Window closed
                    if(event.type==sf::Event::Closed) main_window.close();

                    //Key pressed
                    if(event.type==sf::Event::KeyPressed){
                        switch(event.key.code){
                            //Press ENTER
                            case sf::Keyboard::Return :
                                switch(selected){
                                    //Go to Main menu
                                    case MenuController::CR_BACK :
                                        current_menu=MenuController::MAIN_ID;
                                        selected=0;
                                        sound.play();
                                    break;
                                }
                            break;

                            default:
                            break;
                        }
                    }
                }
                //Draw the background
                main_window.draw(bg);
                //Mark options
                options = new sf::Text[limit];
                MenuController::printOptions(credits_string, options, limit, font2, SCREEN_W, SCREEN_H, selected);
                //Draw titles and options
                draw(main_window, options, limit);

                main_window.display();
            break;

            case MenuController::PLAY_ID :
                main_window.setActive(false);
                main_window.setVisible(false);
                game_window.setActive(true);
                game_window.setVisible(true);

                //Select the background
                bgt.loadFromFile("img/bg1.jpg");
                bg = sf::RectangleShape(sf::Vector2f(1600,600));
                bg.setTexture(&bgt);

                //Window is listening events
                while(game_window.pollEvent(event)){
                    //Window closed
                    if(event.type==sf::Event::Closed) game_window.close();
                }

                //Key pressed
                    if(event.type==sf::Event::KeyPressed){
                        switch(event.key.code){
                            case sf::Keyboard::Left:
                                gc.moveHero(sf::Vector2f(-10,0));
                            break;

                            case sf::Keyboard::Right:
                                gc.moveHero(sf::Vector2f(10,0));
                            break;

                            case sf::Keyboard::Up:
                                gc.moveHero(sf::Vector2f(0,-20));
                            break;

                            default:
                            break;
                        }
                    }
                gc.update();
                game_window.draw(bg);
                gc.draw();
                game_window.display();
            break;
        }
    }

    free(titles);
    free(options);

    return 0;
}
