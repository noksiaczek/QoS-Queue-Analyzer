//
// Created by kamil on 5/31/2026.
//

#ifndef QOS_QUEUE_ANALYZER_MINHEAPQUEUE_H
#define QOS_QUEUE_ANALYZER_MINHEAPQUEUE_H

#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>

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


    /**
     *  @brief Sprawdza, czy lista jest pusta
     * @return True, jeśli lista jest pusta, False w przeciwnym wypadku
     */
    [[nodiscard]] bool empty() const;



    /**
     * @brief Pobiera najważniejszy pakiet z kolejki bez jego usuwania.
     * * @return const NetworkPacket& Referencja do pakietu o najwyższym priorytecie (na szczycie kopca).
     * @throws std::runtime_error Wyrzuca wyjątek, jeśli spróbujemy odczytać z pustej kolejki.
     */
    [[nodiscard]] const NetworkPacket& front() const;


    /**
     * @brief Ustawia priorytet wybranego indeksu na nowy
     * @param index index elementu, który ma zostać zmieniony
     * @param newPrio priorytet, jaki chcemy ustawić.
     */
    void increaseKey (int index, int newPrio);


    /**
     * @brief Wyswietla aktualny stan kopca w formie poziomego drzewa w konsoli.
     * Korzen znajduje sie z lewej strony ekranu, a kolejne poziomy sa odsuwane w prawo.
     * Metoda dziala rekurencyjnie, wypisujac najpierw prawe poddrzewo, potem wezel, a na koncu lewe.
     * @param index Indeks obecnego wezla w wektorze (domyslnie 0 - korzen).
     * @param level Aktualny poziom zaglebienia w drzewie, sluzacy do obliczania wciec (domyslnie 0).
     */
    void printTree(int index = 0, int level = 0) const {
        if (index >= heap.size()) return;

        printTree(2 * index + 2, level + 1);

        for (int i = 0; i < level; i++) {
            std::cout << "       ";
        }

        std::cout << "-> [" << heap[index].prio << "]\n";

        printTree(2 * index + 1, level + 1);
    }
};



#endif //QOS_QUEUE_ANALYZER_MINHEAPQUEUE_H
