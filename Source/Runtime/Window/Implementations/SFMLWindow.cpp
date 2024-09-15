#include "SFMLWindow.h"


void ASFMLWindow::Construct() {
    AWindow::Construct();
    Window = new sf::RenderWindow(sf::VideoMode(200, 200), "Astral Engine");
}

void ASFMLWindow::Tick(float DeltaTime) {
    AWindow::Tick(DeltaTime);
}

void ASFMLWindow::Close() {
    delete Window;
    Window = nullptr;
}

sf::RenderWindow* ASFMLWindow::GetPrivateWindow() const {
    return Window;
}
