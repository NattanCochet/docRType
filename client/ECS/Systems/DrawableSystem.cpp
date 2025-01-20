/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** DrawableSystem
*/

#include "../Systems.hpp"

int Systems::drawableSystem(World &world, Network *network)
{
    Registry &r = world.getRegistry();
    Registry &rOnline = world.getOnlineRegistry();
    sf::RenderWindow *window = world.getWindow();
    ComponentArray<Position> &position = r.get_components<Position>();
    ComponentArray<Drawable> &drawables = r.get_components<Drawable>();
    ComponentArray<Clickable> &clickable = r.get_components<Clickable>();
    ComponentArray<Position> &positionOnline = rOnline.get_components<Position>();
    ComponentArray<Drawable> &drawablesOnline = rOnline.get_components<Drawable>();
    ComponentArray<Clickable> &clickableOnline = rOnline.get_components<Clickable>();

    std::size_t index = 0;

    for (std::optional<Drawable> &drawable : drawables) {
        if (drawable && drawable.has_value() && position[index] && position[index].has_value()) {
            switch (drawable->getKind()) {
            case Drawable::SPRITE:
                drawSprites(index, position, drawable, world);
                break;
            case Drawable::TEXT:
                drawText(index, position, drawable, world);
                break;
            case Drawable::BUTTON:
                drawButton(index, position, drawable, clickable, world);
                break;
            default:
                break;
            }
        }
        index++;
    }
    index = 0;
    for (std::optional<Drawable> &drawable : drawablesOnline) {
        if (drawable && drawable.has_value() && positionOnline[index] && positionOnline[index].has_value()) {
            switch (drawable->getKind()) {
            case Drawable::SPRITE:
                drawSprites(index, positionOnline, drawable, world);
                break;
            case Drawable::TEXT:
                drawText(index, positionOnline, drawable, world);
                break;
            case Drawable::BUTTON:
                drawButton(index, positionOnline, drawable, clickableOnline, world);
                break;
            default:
                break;
            }
        }
        index++;
    }
    return 0;
}

void Systems::drawSprites(
    size_t index, ComponentArray<Position> position, std::optional<Drawable> &drawable, World &world)
{
    sf::Sprite *sprite = world.getSprite(drawable->getPath());
    sf::IntRect *rect = drawable->getRect();
    sprite->setOrigin(rect->width / 2, rect->height / 2);
    localAnimations(index, drawable, world);
    sprite->setTextureRect(*drawable->getRect());
    sprite->setRotation(drawable->getAngle());
    // std::cout << "J'affiche le sprite n° " << index << " c'est : " << drawable->getPath();
    // std::cout << " Position : " << position[index]->getPosition().x << "," << position[index]->getPosition().y;
    // std::cout << " Rect : left " << rect->left << " top " << rect->top << " width " << rect->width << " height " <<
    // rect->height; std::cout << " rotation : " << drawable->getAngle() << std::endl;
    if (position[index] && position[index].has_value())
        sprite->setPosition(position[index]->getPosition());
    world.getWindow()->draw(*sprite);
}

void Systems::localAnimations(size_t index, std::optional<Drawable> &drawable, World &world)
{
    sf::Clock *clock = drawable->getClock();
    sf::Time timeSpend = clock->getElapsedTime();
    float seconds = timeSpend.asSeconds();
    sf::IntRect *rect = drawable->getRect();
    std::string name = drawable->getPath();
    Registry &r = world.getRegistry();
    if (name == "background" && seconds > 0.08) {
        if (rect->left >= 3179)
            drawable->setRect({0, rect->top, rect->width, rect->height});
        else
            drawable->setRect({rect->left + 2, rect->top, rect->width, rect->height});
        drawable->restartClock();
    }
    if (name == "explosion" && seconds > 0.1) {
        if (rect->left >= 216 - 36)
            r.kill_entity(r.entity_from_index(index));
        else
            drawable->setRect({rect->left + 36, rect->top, rect->width, rect->height});
        drawable->restartClock();
    }
}

void Systems::drawText(size_t index, ComponentArray<Position> position, std::optional<Drawable> &drawable, World &world)
{
    sf::Text *text = world.getText(drawable->getPath());
    int sizeCharacter = drawable->getSizeChar();
    text->setString(drawable->getMessage());
    text->setFillColor(drawable->getColorText());
    text->setCharacterSize(sizeCharacter);
    text->setScale(drawable->getScale());
    sf::FloatRect middle = text->getLocalBounds();
    text->setOrigin(middle.left + middle.width / 2.0, middle.top + middle.height / 2.0);
    text->setRotation(drawable->getAngle());
    if (position[index] && position[index].has_value())
        text->setPosition(position[index]->getPosition());
    world.getWindow()->draw(*text);
}

void Systems::drawButton(size_t index, ComponentArray<Position> position, std::optional<Drawable> &drawable,
    ComponentArray<Clickable> clickable, World &world)
{
    if (index == world.getTextWritting()) {
        std::vector<std::pair<World::PRESS, sf::Keyboard::Key>> keyActions = world.getKeyActions();
        for (auto it = keyActions.begin(); it != keyActions.end(); it++) {
            if (it->first != World::PRESSED)
                continue;
            if (clickable[index]->getKindButton() == Clickable::NUMBUTTON) {
                Buttons::writeNumButton(it->second, world, index);
            } else {
                changeText(it->second, drawable);
            }
        }
        world.clearKeyAction();
    }
    if (index == world.getControlWritting()) {
        std::vector<std::pair<World::PRESS, sf::Keyboard::Key>> keyActions = world.getKeyActions();
        for (auto it = keyActions.begin(); it != keyActions.end(); it++) {
            if (it->first != World::PRESSED)
                continue;
            changeKey(it->second, world, index);
            break;
        }
        world.clearKeyAction();
    }
    sf::RectangleShape *rectangle = world.getRectangle("rectangle");
    sf::Vector2f size = drawable->getSizeRectangle();
    sf::Text *text = world.getText(drawable->getPath());
    sf::FloatRect middle;
    int sizeCharacter = drawable->getSizeChar();
    rectangle->setSize(size);
    rectangle->setOrigin(size.x / 2.0, size.y / 2.0);
    rectangle->setFillColor(drawable->getColor());
    rectangle->setRotation(drawable->getAngle());
    if (position[index] && position[index].has_value())
        rectangle->setPosition(position[index]->getPosition());
    world.getWindow()->draw(*rectangle);
    std::string msg = drawable->getMessage();
    if (msg == "" && clickable[index]->getKindButton() == Clickable::TEXTBUTTON) {
        Buttons::textButton_t *infos = static_cast<Buttons::textButton_t *>(clickable[index]->getInfos());
        text->setString(infos->_messageDefault);
        text->setFillColor({0, 0, 0, 58});
    } else if (msg == "" && clickable[index]->getKindButton() == Clickable::NUMBUTTON) {
        Buttons::NumButton_t *infos = static_cast<Buttons::NumButton_t *>(clickable[index]->getInfos());
        text->setString(infos->_messageDefault);
        text->setFillColor({0, 0, 0, 58});
    } else {
        text->setString(msg);
        text->setFillColor(drawable->getColorText());
    }
    text->setCharacterSize(sizeCharacter);
    text->setScale(drawable->getScale());
    middle = text->getLocalBounds();
    text->setOrigin(middle.left + middle.width / 2.0, middle.top + middle.height / 2.0);
    text->setRotation(drawable->getAngle());
    if (position[index] && position[index].has_value())
        text->setPosition(position[index]->getPosition());
    world.getWindow()->draw(*text);
}

void Systems::changeText(sf::Keyboard::Key key, std::optional<Drawable> &drawable)
{
    std::string message = drawable->getMessage();
    if (key < 26) {
        char c = key + 'a';
        drawable->setMessage(message + c);
    }
    if (key >= 26 && key <= 35) {
        char c = key - 26 + '0';
        drawable->setMessage(message + c);
    }
    if (key >= 75 && key <= 84) {
        char c = key - 75 + '0';
        drawable->setMessage(message + c);
    }
    switch (key) {
    case sf::Keyboard::Space:
        drawable->setMessage(message + " ");
        break;
    case sf::Keyboard::BackSpace:
        if (message.size() > 0)
            message.pop_back();
        drawable->setMessage(message);
        break;
    default:
        break;
    }
}

void Systems::changeKey(sf::Keyboard::Key key, World &world, std::size_t index)
{
    ComponentArray<Clickable> &clickables = world.getRegistry().get_components<Clickable>();
    ComponentArray<Drawable> &drawables = world.getRegistry().get_components<Drawable>();

    void *buttonT = clickables[index]->getInfos();
    if (buttonT && clickables[index]->getKindButton() == Clickable::KEYBUTTON) {
        Buttons::KeyButton_t *button = static_cast<Buttons::KeyButton_t *>(buttonT);
        drawables[index]->setColor(button->_defaultColor);
        world.setControlWritting(-1);
        if (!Buttons::writeKeyButton(key, world, index)) {
            *button->_key = sf::Keyboard::Unknown;
        } else {
            checkKeyUsed(key, world);
            *button->_key = key;
        }
    }
}

void Systems::checkKeyUsed(sf::Keyboard::Key key, World &world)
{
    ComponentArray<Clickable> &clickables = world.getRegistry().get_components<Clickable>();
    ComponentArray<Drawable> &drawables = world.getRegistry().get_components<Drawable>();

    std::size_t index = 0;

    for (std::optional<Clickable> &clickable : clickables) {
        void *buttonT = clickable->getInfos();
        if (buttonT && clickable->getKindButton() == Clickable::KEYBUTTON) {
            Buttons::KeyButton_t *button = static_cast<Buttons::KeyButton_t *>(buttonT);
            if (*button->_key == key) {
                *button->_key = sf::Keyboard::Unknown;
                drawables[index]->setMessage("EMPTY");
                break;
            }
        }
        index++;
    }
}