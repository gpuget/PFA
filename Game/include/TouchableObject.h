#ifndef TOUCHABLEOBJECT_H
#define TOUCHABLEOBJECT_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics/Rect.hpp>

////////////////////////////////////////////////////////////
/// \brief Object with a hitbox which can be touched by \link Attack
///
////////////////////////////////////////////////////////////
class TouchableObject
{
    public:

        TouchableObject();
        ////////////////////////////////////////////////////////////
        /// \brief Constructor
        ///
        /// \param id Identifier
        /// \param box Physical rectangle representation
        ///
        /// Create an object with a identifier and a rectangular hitbox
        ///
        ///
        ////////////////////////////////////////////////////////////

        TouchableObject(int id, const sf::FloatRect box);

        ////////////////////////////////////////////////////////////
        /// \brief Destructor
        ///
        ////////////////////////////////////////////////////////////
        virtual ~TouchableObject();

        ////////////////////////////////////////////////////////////
        /// \brief Getter of identifier
        ///
        /// \return Identifier
        ////////////////////////////////////////////////////////////
        int getId() { return id; }

        ////////////////////////////////////////////////////////////
        /// \brief Getter of hitbox
        ///
        /// \return Hitbox
        ////////////////////////////////////////////////////////////
        sf::FloatRect getHitbox() { return hitbox; }



        ////////////////////////////////////////////////////////////
        /// \brief Getter of position X
        ///
        /// \return Position X
        ///
        ////////////////////////////////////////////////////////////
        float getX() { return hitbox.left; }

        ////////////////////////////////////////////////////////////
        /// \brief Getter of position Y
        ///
        /// \return Position Y
        ///
        ////////////////////////////////////////////////////////////
        float getY() { return hitbox.top; }



        ////////////////////////////////////////////////////////////
        /// \brief Setter of position X and Y
        ///
        /// \param x
        /// \param y
        ///
        ////////////////////////////////////////////////////////////
        void setPosition(float x, float y);

        ////////////////////////////////////////////////////////////
        /// \brief Determine the collision
        ///
        /// \param to Other TouchableObject which can be in collision
        ///
        /// Return true if the two objects are in collision
        ///
        ////////////////////////////////////////////////////////////
        bool intersects(TouchableObject& to);

        ////////////////////////////////////////////////////////////
        /// \brief Determine the type of the object
        ///
        /// Return true if the object is an \link Attack
        ///
        ////////////////////////////////////////////////////////////
        virtual bool isAttack()=0;

        ////////////////////////////////////////////////////////////
        /// \brief Determine the type of the object
        ///
        /// Return true if the object is an \link Character
        ///
        ////////////////////////////////////////////////////////////
        virtual bool isCharacter()=0;

        ////////////////////////////////////////////////////////////
        /// \brief Determine the type of the object
        ///
        /// Return true if the object is an \link Obstacle
        ///
        ////////////////////////////////////////////////////////////
        virtual bool isObstacle()=0;

        ////////////////////////////////////////////////////////////
        /// \brief Determine the type of the object
        ///
        /// Return true if the object is an \link Pickable
        ///
        ////////////////////////////////////////////////////////////
        virtual bool isPickable()=0;

    protected:
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        int id;                 /// Identifier
        sf::FloatRect hitbox;     /// Rectangular hitbox

    private:

};

#endif // TOUCHABLEOBJECT_H
