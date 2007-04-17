
#ifndef PIECES_APPLICATION_H
#define PIECES_APPLICATION_H

#include "Pieces/global"

#include <string>


namespace pcs
{
class ApplicationPrivate;


/**
 * \class Application
 * \brief Pieces application.
 *
 * This class provides a singleton object that every Pieces application, host or
 * peer, must contain. This is typically done by allocating an object on the
 * stack in the main function.
 *
 * The application object is available through the global app pointer.
 * \author Robin Pedersen
 */
class Application
{
public:
    Application(int argc, char** argv);

    ~Application();

    int argc() const;
    std::string arg(int index) const;

private:
    DISABLE_COPY(Application);

    ApplicationPrivate* d;
};

extern Application* app;

} // namespace pcs

#endif // PIECES_APPLICATION_H
