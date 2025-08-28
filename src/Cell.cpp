#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Cell.hpp"
#include "Colors.hpp"

Cell::~Cell() = default;

Cell::Cell() : alive_(false), entity_(nullptr), color_(Colors::kBackgroundColor) {}

Cell::Cell(bool alive, std::unique_ptr<Entity> entity)
    : alive_(alive), entity_(std::move(entity)) {
        if (entity_) {
            color_ = GetEntityColor(entity_->Type());
        }
        else {
            color_ = Colors::kBackgroundColor;
        }
}

// Copy constructor
Cell::Cell(const Cell& other) 
    : alive_(other.alive_), color_(other.color_) {
    
    if (other.entity_) {
        // Clone the entity using our new Clone method
        entity_ = other.entity_->Clone();
    } else {
        entity_ = nullptr;
    }
}

// Copy assignment operator
Cell& Cell::operator=(const Cell& other) {
    if (this != &other) {  // Protect against self-assignment
        alive_ = other.alive_;
        color_ = other.color_;
        
        if (other.entity_) {
            entity_ = other.entity_->Clone();
        } else {
            entity_.reset();  // Clear our current entity
        }
    }
    return *this;
}

// Move constructor
Cell::Cell(Cell&& other) noexcept
    : alive_(other.alive_),
      color_(other.color_),
      entity_(std::move(other.entity_)) {
    other.alive_ = false;
    other.color_ = Colors::kBackgroundColor;
}

// Move assignment operator
Cell& Cell::operator=(Cell&& other) noexcept {
    if (this != &other) {
        alive_ = other.alive_;
        color_ = other.color_;
        entity_ = std::move(other.entity_);
        
        other.alive_ = false;
        other.color_ = Colors::kBackgroundColor;
    }
    return *this;
}

sf::Color Cell::GetColor() const {
    if (entity_) {
        float frac = static_cast<float>(entity_->GetHP()) / 100.0f;
        frac = std::clamp(frac, 0.0f, 1.0f);

        sf::Color bg = Colors::kBackgroundColor;

        // Blend each channel toward background: result = bg*(1-frac) + entity*frac
        unsigned char r = static_cast<unsigned char>(bg.r * (1.0f - frac) + color_.r * frac + 0.5f);
        unsigned char g = static_cast<unsigned char>(bg.g * (1.0f - frac) + color_.g * frac + 0.5f);
        unsigned char b = static_cast<unsigned char>(bg.b * (1.0f - frac) + color_.b * frac + 0.5f);

        return sf::Color(r, g, b, 255);
    }

    return color_;
}

void Cell::SetEntity(std::unique_ptr<Entity> entity) {
    if (entity_ == entity) return;
    if (!entity) {
        RemoveEntity();
        return;
    }

    entity_ = std::move(entity);
    color_ = GetEntityColor(entity_->Type());
    alive_ = entity_ != nullptr;
}

void Cell::RemoveEntity() {
    entity_.reset();
    color_ = Colors::kBackgroundColor;
    alive_ = false;
}
