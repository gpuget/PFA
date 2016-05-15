#ifndef HTH_H
#define HTH_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Attack.h>

////////////////////////////////////////////////////////////
/// \brief Hand to hand specific attack
///
////////////////////////////////////////////////////////////
class HtH : public Attack
{
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Constructor
        ///
        /// Create an \link Attack
        ///
        ////////////////////////////////////////////////////////////
        HtH(int id, const sf::FloatRect box, int damage, float atqSpeed);

        ////////////////////////////////////////////////////////////
        /// \brief Destructor
        ///
        ////////////////////////////////////////////////////////////
        virtual ~HtH();

        ////////////////////////////////////////////////////////////
        /// \brief Determine the attack type
        ///
        /// Return true if the attack is a hand to hand attack
        ///
        ////////////////////////////////////////////////////////////
        bool isHtH(){ return true; }

        ////////////////////////////////////////////////////////////
        /// \brief Determine the attack type
        ///
        /// Return true if the attack is a distance attack
        ///
        ////////////////////////////////////////////////////////////
        bool isProjectile(){ return false; }

    protected:

    private:
};

#endif // HTH_H
