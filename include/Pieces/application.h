
#ifndef PIECES_APPLICATION_H
#define PIECES_APPLICATION_H

#include "Pieces/global"

#include <string>


namespace pcs
{
class ApplicationPrivate;


/**
 * \class Application application.h <Pieces/Application>
 * \brief Pieces application.
 *
 * This class provides a singleton object that every Pieces application, host or
 * peer, must contain. This is typically done by allocating an object on the
 * stack in the main function.
 *
 * The application object is available through the global app pointer.
 *
 * \author Robin Pedersen
 */
class Application
{
public:

    /**
     * Create application object.
     *
     * Initializes Pieces.
     *
     * The \a argc and \a argv parameters should be the same as the parameters
     * passed to the main function of the user application.
     */
    Application(int argc, char** argv);

    /**
     * Uninitialized Pieces.
     */
    ~Application();

    /**
     * Returns the number of command line arguments passed to the application.
     */
    int argc() const;

    /**
     * Returns the commend line argument at a given position as a string.
     */
    std::string arg(int index) const;

private:
    DISABLE_COPY(Application);

    ApplicationPrivate* d;
};


/**
 * Global pointer to the Application object.
 *
 * This can be used to access command line arguments from anywhere in an
 * application.
 *
 * \relates Application
 */
extern Application* app;

} // namespace pcs

#endif // PIECES_APPLICATION_H
