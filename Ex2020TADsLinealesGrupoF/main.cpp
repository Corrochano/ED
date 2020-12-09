/*
 * ---------------------------------------------------
 *     ESTRUCTURAS DE DATOS - PRIMER EXAMEN
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Solo se corregir� el c�digo contenido entre
  * las etiquetas <answer> y </answer>. Toda modificaci�n fuera
  * de esas etiquetas no ser� corregida.
  */

  /*@ <answer>
   *
   * Nombre y apellidos: _�lvaro_Corrochano_L�pez_
   *
   *@ </answer> */

   /*
    * Implementa las operaciones pedidas en el ejercicio al final de
    * este fichero, entre las etiquetas.
    */


#include <iostream>
#include <fstream>
#include <cassert>

    /* --------------------------------------------------------------------
     * Clase ListLinkedDouble
     * --------------------------------------------------------------------
     * Implementa el TAD lista mediante una lista doblemente enlazada
     * circular con nodo fantasma
     * --------------------------------------------------------------------
     */

template <typename T>
class ListLinkedDouble {
private:
    struct Node {
        T value;
        Node* next;
        Node* prev;
    };

public:
    ListLinkedDouble() : num_elems(0) {
        head = new Node;
        head->next = head;
        head->prev = head;
    }

    ListLinkedDouble(const ListLinkedDouble& other) : ListLinkedDouble() {
        copy_nodes_from(other);
        num_elems = other.num_elems;
    }

    ~ListLinkedDouble() {
        delete_nodes();
    }

    void push_front(const T& elem) {
        insert(cbegin(), elem);
    }

    void push_back(const T& elem) {
        insert(cend(), elem);
    }

    void pop_front() {
        erase(cbegin());
    }

    void pop_back() {
        assert(num_elems > 0);
        Node* target = head->prev;
        target->prev->next = head;
        head->prev = target->prev;
        delete target;
        num_elems--;
    }

    int size() const {
        return num_elems;
    }

    bool empty() const {
        return num_elems == 0;
    };

    const T& front() const {
        assert(num_elems > 0);
        return head->next->value;
    }

    T& front() {
        assert(num_elems > 0);
        return head->next->value;
    }

    const T& back() const {
        assert(num_elems > 0);
        return head->prev->value;
    }

    T& back() {
        assert(num_elems > 0);
        return head->prev->value;
    }

    const T& operator[](int index) const {
        assert(0 <= index && index < num_elems);
        Node* result_node = nth_node(index);
        return result_node->value;
    }

    T& operator[](int index) {
        assert(0 <= index && index < num_elems);
        Node* result_node = nth_node(index);
        return result_node->value;
    }

    ListLinkedDouble& operator=(const ListLinkedDouble& other) {
        if (this != &other) {
            delete_nodes();
            head = new Node;
            head->next = head->prev = head;
            copy_nodes_from(other);
            num_elems = other.num_elems;
        }
        return *this;
    }

    void display(std::ostream& out) const;

    void display() const {
        display(std::cout);
    }

    template <typename U>
    class gen_iterator {
    public:
        gen_iterator& operator++() {
            assert(current != head);
            current = current->next;
            return *this;
        }

        gen_iterator operator++(int) {
            assert(current != head);
            gen_iterator antes = *this;
            current = current->next;
            return antes;
        }

        U& operator*() const {
            assert(current != head);
            return current->value;
        }

        bool operator==(const gen_iterator& other) const {
            return (head == other.head) && (current == other.current);
        }

        bool operator!=(const gen_iterator& other) const {
            return !(*this == other);
        }

        friend class ListLinkedDouble;

    private:
        gen_iterator(Node* head, Node* current) : head(head), current(current) { }
        Node* head;
        Node* current;
    };

    using iterator = gen_iterator<T>;
    using const_iterator = gen_iterator<const T>;

    iterator begin() {
        return iterator(head, head->next);
    }

    iterator end() {
        return iterator(head, head);
    }

    const_iterator begin() const {
        return const_iterator(head, head->next);
    }

    const_iterator end() const {
        return const_iterator(head, head);
    }

    const_iterator cbegin() const {
        return const_iterator(head, head->next);
    }

    const_iterator cend() const {
        return const_iterator(head, head);
    }

    iterator insert(const_iterator it, const T& elem) {
        // Comprobamos que el iterador pertenece a la misma
        // lista en la que realizamos la inserci�n.
        assert(it.head == head);
        Node* new_node = new Node{ elem, it.current, it.current->prev };
        it.current->prev->next = new_node;
        it.current->prev = new_node;
        num_elems++;
        return iterator(head, new_node);
    }

    iterator erase(const_iterator it) {
        // Comprobamos que el iterador pertenece a la misma
        // lista en la que realizamos la inserci�n, y que no
        // estamos en el �ltimo elemento.
        assert(it.head == head && it.current != head);
        Node* target = it.current;
        it.current->prev->next = it.current->next;
        it.current->next->prev = it.current->prev;
        iterator result(head, it.current->next);
        delete target;
        num_elems--;
        return result;
    }

    void concat_reverse(ListLinkedDouble& other);

    void print() const;


private:
    Node* head;
    int num_elems;

    Node* nth_node(int n) const;
    void delete_nodes();
    void copy_nodes_from(const ListLinkedDouble& other);
};



template <typename T>
typename ListLinkedDouble<T>::Node* ListLinkedDouble<T>::nth_node(int n) const {
    int current_index = 0;
    Node* current = head->next;

    while (current_index < n && current != head) {
        current_index++;
        current = current->next;
    }

    return current;
}

template <typename T>
void ListLinkedDouble<T>::delete_nodes() {
    Node* current = head->next;
    while (current != head) {
        Node* target = current;
        current = current->next;
        delete target;
    }

    delete head;
}

template <typename T>
void ListLinkedDouble<T>::copy_nodes_from(const ListLinkedDouble& other) {
    Node* current_other = other.head->next;
    Node* last = head;

    while (current_other != other.head) {
        Node* new_node = new Node{ current_other->value, head, last };
        last->next = new_node;
        last = new_node;
        current_other = current_other->next;
    }
    head->prev = last;
}

template <typename T>
void ListLinkedDouble<T>::display(std::ostream& out) const {
    out << "[";
    if (head->next != head) {
        out << head->next->value;
        Node* current = head->next->next;
        while (current != head) {
            out << ", " << current->value;
            current = current->next;
        }
    }
    out << "]";
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const ListLinkedDouble<T>& l) {
    l.display(out);
    return out;
}


/* --------------------------------------------------------------------
 * Implementa el m�todo pedido aqu�
 * --------------------------------------------------------------------
 *
 * Puedes anadir los m�todos privados auxiliares que quieras. Para eso
 * puedes declararlos en la clase, pero has de implementarlos aqu�, entre
 * las etiquetas <answer> y </answer>.
 *
 *@ <answer>
 */

template <typename T>
void ListLinkedDouble<T>::print() const {
    std::cout << "[";
    if (head->next != head) {
        std::cout << head->next->value;
        Node* current = head->next->next;
        while (current != head) {
            std::cout << ", " << current->value;
            current = current->next;
        }
    }
    std::cout << "]";

    std::cout << '\n';
}


template <typename T>
void ListLinkedDouble<T>::concat_reverse(ListLinkedDouble& other) {
    
    if (other.empty()) return; // si la otra est� vac�a, me quedo igual

    Node* last = other.head->prev; // nodo al que empieza en el �ltimo de la otra lista
    Node* lastPrev = other.head->prev; // nodo que va en el anterior al otro

     do {
        if (lastPrev != other.head) { // si no es fantasma
            lastPrev = lastPrev->prev; // va uno para atr�s
        }

        this->head->prev->next = last; // el siguiente a mi �ltimo es su �ltimo
        this->head->prev = last; // mi �ltimo es su �ltimo
        last->next = head; // el siguiente a su �ltimo es mi fantasma

        last = lastPrev; // last va hacia atr�s
     } while (lastPrev != other.head); // mientras el anterior a m� no sea el fantasma

     num_elems += other.num_elems; // actualizo el n�mero de elementos que tengo
}



// Funci�n para tratar cada uno de los casos de prueba
void tratar_caso() {
    ListLinkedDouble<int> lista1, lista2;
    int nums, aux;

    std::cin >> nums;

    for (int i = 0; i < nums; i++) {
        std::cin >> aux;

        lista1.push_back(aux);
    }

    std::cin >> nums;

    for (int i = 0; i < nums; i++) {
        std::cin >> aux;

        lista2.push_back(aux);
    }

    lista1.concat_reverse(lista2);

    lista1.print();

    lista1.~ListLinkedDouble();
    lista2.~ListLinkedDouble();
    
}

/*@ </answer> */


int main() {
    int num_casos;


    std::cin >> num_casos;

    while (num_casos > 0) {
        tratar_caso();
        num_casos--;
    }


    system("PAUSE");


    return 0;
}