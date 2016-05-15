#ifndef CHARACTER_H
#define CHARACTER_H

////////////////////////////////////////////////////////////
// Header
////////////////////////////////////////////////////////////
#include <TouchableObject.h>
#include <Attack.h>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

////////////////////////////////////////////////////////////
/// \brief Game characters
///
////////////////////////////////////////////////////////////
class Character : public TouchableObject
{
    public:
        Character();

        ////////////////////////////////////////////////////////////
        /// \brief Constructor
        ///
        /// \param speed Character speed
        /// \param hp Hearth points
        ///
        /// Create an \link TouchableObject with movement speed and hearth points
        ///
        ////////////////////////////////////////////////////////////
        Character(int id, const sf::FloatRect box, const sf::Vector2f speed, int hp, Attack& a);

        ////////////////////////////////////////////////////////////
        /// \brief Destructor
        ///
        ////////////////////////////////////////////////////////////
        virtual ~Character();

        ////////////////////////////////////////////////////////////
        /// \brief Getter of current hearth points
        ///
        /// \return Current HP
        ///
        ////////////////////////////////////////////////////////////
        int getHp() { return hp; }

        ////////////////////////////////////////////////////////////
        /// \brief Setter of hearth points
        ///
        /// \param val New heath points value
        ///
        ////////////////////////////////////////////////////////////
        void setHp(int val);

        ////////////////////////////////////////////////////////////
        /// \brief Getter of character speed
        ///
        /// \return Speed
        ///
        ////////////////////////////////////////////////////////////
        sf::Vector2f getSpeed() { return speed; }

        ////////////////////////////////////////////////////////////
        /// \brief Setter of the X component of character speed
        ///
        /// \param val New value
        ///
        ////////////////////////////////////////////////////////////
        void setSpeedX(float val) { speed.x = val; }

        ////////////////////////////////////////////////////////////
        /// \brief Setter of the Y component of character speed
        ///
        /// \param val New value
        ///
        ////////////////////////////////////////////////////////////
        void setSpeedY(float val) { speed.y = val; }

        ////////////////////////////////////////////////////////////
        /// \brief Getter of the vulnerability
        ///
        /// \return Vulnerability
        ///
        ////////////////////////////////////////////////////////////
        bool isVulnerable() { return vulnerable; }

        ////////////////////////////////////////////////////////////
        /// \brief Setter of the vulnerability
        ///
        /// \param val New vulnerability value
        ///
        ////////////////////////////////////////////////////////////
        void setVulnerable(bool val){vulnerable = val;}

        ////////////////////////////////////////////////////////////
        /// \brief Attack resolution
        ///
        /// \param target Attack target
        ///
        /// Attack the target if it is possible and deal the damage of the character attack
        ///
        ////////////////////////////////////////////////////////////
        virtual int attack(TouchableObject& target);

        ////////////////////////////////////////////////////////////
        /// \brief Deal damage
        ///
        /// \param damage Dealt damage
        ///
        /// Reduce the current hearth points
        ///
        ////////////////////////////////////////////////////////////
        int hurt(int damage);

        ////////////////////////////////////////////////////////////
        /// \brief Determine the type of the object
        ///
        /// Return true if the object is an \link Attack
        ///
        ////////////////////////////////////////////////////////////
        bool isAttack(){ return false; }

        ////////////////////////////////////////////////////////////
        /// \brief Determine the type of the object
        ///
        /// Return true if the object is an \link Character
        ///
        ////////////////////////////////////////////////////////////
        bool isCharacter(){ return true; }

        ////////////////////////////////////////////////////////////
        /// \brief Determine if the character is dead
        ///
        /// Return true if hearth points are negative or null
        ///
        ////////////////////////////////////////////////////////////
        bool isDead();

        ////////////////////////////////////////////////////////////
        /// \brief Determine the type of the object
        ///
        /// Return true if the object is an \link Obstacle
        ///
        ////////////////////////////////////////////////////////////
        bool isObstacle(){ return false; }

        ////////////////////////////////////////////////////////////
        /// \brief Determine the type of the object
        ///
        /// Return true if the object is an \link Pickable
        ///
        ////////////////////////////////////////////////////////////
        bool isPickable(){ return false; }

        void print();

    protected:
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        int hp;                 /// Current HP
        int hpMax;              /// HP maximum
        sf::Vector2f speed;     /// Movement speed
        Attack* atq;             /// Attack
        bool vulnerable;        /// Vulnerability

    private:
};

#endif // CHARACTER_H
