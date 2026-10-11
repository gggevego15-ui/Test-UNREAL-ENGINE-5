#include "TestUE5GameMode.h"
#include "FirstPersonTestCharacter.h"

ATestUE5GameMode::ATestUE5GameMode()
{
    DefaultPawnClass = AFirstPersonTestCharacter::StaticClass();
}
