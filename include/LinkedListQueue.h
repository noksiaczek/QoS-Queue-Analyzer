//
// Created by kamil on 5/31/2026.
//

#ifndef QOS_QUEUE_ANALYZER_LINKEDLISTQUEUE_H
#define QOS_QUEUE_ANALYZER_LINKEDLISTQUEUE_H

#include "MinHeapQueue.h"
#include <stdexcept>

/**
 * @brief Klasa symulująca kolejkę priorytetową przy użyciu listy jednokierunkowej.
 * Implementacja służy jako wariant referencyjny (Narzędzie B) do testów wydajnościowych
 * algorytmów QoS.
 */
class LinkedListQueue {
private:
    /**
     * @brief Struktura pojedynczego węzła listy jednokierunkowej.
     */
    struct Node {
        NetworkPacket data; /**< Dane pakietu sieciowego */
        Node* next;         /**< Wskaźnik na kolejny węzeł w liście */
    };

    Node* head; /**< Wskaźnik na początek listy */

public:
    /**
     * @brief Konstruktor domyślny, inicjalizuje pustą listę.
     */
    LinkedListQueue() : head(nullptr) {}

    /**
     * @brief Destruktor, zwalnia pamięć wszystkich węzłów listy, zapobiegając wyciekom.
     */
    ~LinkedListQueue() {
        while (!empty()) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    /**
     * @brief Sprawdza, czy lista jest pusta.
     * @return true jeśli lista nie zawiera żadnych węzłów, false w przeciwnym razie.
     */
    bool empty() const {
        return head == nullptr;
    }

    /**
     * @brief Wstawia nowy pakiet na początek listy (dopinanie do głowy).
     * Złożoność czasowa operacji wynosi O(1).
     * @param packet Obiekt pakietu gotowy do dodania.
     */
    void insert(const NetworkPacket& packet) {
        head = new Node{packet, head};
    }

    /**
     * @brief Przeszukuje listę i zwraca pakiet o najwyższym priorytecie (najmniejszej wartości).
     * Złożoność czasowa operacji wynosi O(N).
     * @return const NetworkPacket& Referencja do pakietu o najwyższym priorytecie.
     * @throws std::runtime_error Wyrzuca wyjątek, jeśli funkcja zostanie wywołana na pustej liście.
     */
    const NetworkPacket& front() const {
        if (empty()) throw std::runtime_error("Kolejka jest pusta");

        Node* curr = head;
        Node* minNode = head;

        while (curr != nullptr) {
            if (curr->data.prio < minNode->data.prio) {
                minNode = curr;
            }
            curr = curr->next;
        }
        return minNode->data;
    }

    /**
     * @brief Usuwa z listy pakiet o najwyższym priorytecie.
     * Złożoność czasowa operacji wynosi O(N).
     */
    void pop() {
        if (empty()) return;

        Node* curr = head;
        Node* prev = nullptr;

        Node* minNode = head;
        Node* minPrev = nullptr;

        while (curr != nullptr) {
            if (curr->data.prio < minNode->data.prio) {
                minNode = curr;
                minPrev = prev;
            }
            prev = curr;
            curr = curr->next;
        }

        if (minPrev == nullptr) {
            head = minNode->next;
        } else {
            minPrev->next = minNode->next;
        }

        delete minNode;
    }
};
#endif //QOS_QUEUE_ANALYZER_LINKEDLISTQUEUE_H
