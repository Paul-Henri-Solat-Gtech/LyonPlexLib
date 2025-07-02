// Events.h
#pragma once


struct CollisionEvent {
    struct Payload {
        Entity a, b;
        // vous pouvez ajouter point de contact, normal, etc.
    };
};

// (plus tard) struct TriggerEnterEvent { … };
// etc.