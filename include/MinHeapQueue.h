//
// Created by kamil on 5/31/2026.
//

#ifndef QOS_QUEUE_ANALYZER_MINHEAPQUEUE_H
#define QOS_QUEUE_ANALYZER_MINHEAPQUEUE_H

#include <vector>
#include <string>
#include <stdexcept>

/**
 * @brief Struktura reprezentująca pojedynczy pakiet wpadający na interfejs routera.
 */
struct NetworkPacket {
    int prio;           /**< Priorytet pakietu (1 - najwyższy, 10 - najniższy) */
    std::string type;   /**< Nazwa aplikacji lub typu ruchu (np. "MS Teams") */
};

/**
 * @brief Klasa symulująca kolejkę priorytetową dla mechanizmów QoS.
 * * Wykorzystuje strukturę kopca minimalnego (Min-Heap) do sortowania przychodzącego
 * ruchu sieciowego. Gwarantuje, że pakiety krytyczne (np. routing, głos)
 * opuszczą interfejs przed ruchem o niskim priorytecie (np. P2P, torrenty).
 */
class MinHeapQueue {
private:
    std::vector<NetworkPacket> heap;
    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    /**
     * @brief Usuwa najważniejszy pakiet z kolejki (symulacja wypuszczenia w sieć).
     */
    void pop();
    /**
     * @brief Dodaje nowy pakiet do kolejki i przywraca właściwości kopca (tonięcie/wypływanie).
     * * @param newPacket Obiekt pakietu gotowy do obsługi przez router.
     */
    void insert(const NetworkPacket &newPacket);
    [[nodiscard]] bool empty() const;
    /**
     * @brief Pobiera najważniejszy pakiet z kolejki bez jego usuwania.
     * * @return const NetworkPacket& Referencja do pakietu o najwyższym priorytecie (na szczycie kopca).
     * @throws std::runtime_error Wyrzuca wyjątek, jeśli spróbujemy odczytać z pustej kolejki.
     */
    [[nodiscard]] const NetworkPacket& front() const;
    void increaseKey (int index, int newPrio);
};



#endif //QOS_QUEUE_ANALYZER_MINHEAPQUEUE_H
