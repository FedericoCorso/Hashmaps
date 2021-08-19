#ifndef MULTISET_H
#define MULTISET_H

#include <iostream>
#include <unordered_map> /// libreria necessaria per le unordered map
#include <string>
#include <sstream> /// libreria per usare stringstream

/// includo alcuni namespace, evitando così di portare all'interno del mio programma tutto il namespace std
using std::unordered_map;
using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::stringstream;

/**
 * A MultiSet is here implemented as an unordered map in which the key represent the name of the element and the value associated
 * the multiplicity of the same.
*/
template<typename T>
class MultiSet{
    private:
        unordered_map <T, int> umap;

    public:
        /**
         * Empty Constructor, initializes an empty MultiSet
         * 
        */
       MultiSet(){
           //this allows me to access private attributes from the inside of a class
           this->umap = {}; /// come inizializzare una umap vuota
       }

     /** Adds one instance of element el to the multiset
           MUST run in O(1)
       */
       void add(const T el){
           ///uso la parola chiave const poichè T è il tipo della key, la quale ricordiamo deve essere immutabile
           cout << "DEBUG: adding " << el << endl;
           /// check if 'el' already exists in the unordered map -> use .count() method which is O(1)
           if(this->umap.count(el) == 1){ ///count method returns 1 if the key is found, otherwise return 0 and no key is created.
                this->umap[el] += 1; //multiplicity increased by one, which means that a new element has been added
           }else{
               this->umap[el] = 1; //which means creating a new key and setting its value to 1
           }
}
       /**
        *  RETURN the multiplicity of element el in the multiset
           - If no instance of el is present, return 0.
           MUST run in O(1)
           ----
           This means I need to return the value associated with the corresponding key.
           So first I need to find the key -> in O(1) soo I need to use .count(key) method
           then I need to access the value and return it, it's better to use the .at() method
           because it throws an exception if the key is empty.
           You can't use [] operator because it's not a const method but here "el" is a key marked as const

           Note that get is a const method because it just reads from the data structure
       */
       int get(const T el) const {

           if(this->umap.count(el) == 1){
               return this->umap.at(el); ///remember that .at() method throws exception if nothing is found
           }
           else{
               return 0;
           }
        }
       
       /** Removes n instances of element el from the multiset (that
            is, reduces el multiplicity by n)
            If n is negative, throws std::invalid_argument
            If n represents a multiplicity bigger than el current
            multiplicity, throws std::out_of_range
            NOTE: multiset multiplicities are never negative
            MUST run in O(1)
            ----

        */
       void removen(const T el, const int n){
           /// voglio rimuovere le copie key-value in cui value == 0
           /// noto come input dei parametri di tipo const, non possono essere modificati.
           cout << "DEBUG: removing " << el << ", " << to_string(n) << endl;
           if(n < 0){
               throw std::invalid_argument("Provided n is negative: " + to_string(n));
           }
           else if(n == 0){
               return; /// non faccio nulla perchè sto dicendo di non cancellare alcuna istanza
           }
           
           int current; /// variabile ausiliaria per inserire la molteplicità attuale di el, questo perchè non voglio modificare la molteplicità nella data structure
           if (this->umap.count(el)==1){ /// ovvero se la key esiste nella mappa
                current = this->umap[el]; /// passo una copia del valore associato a el
           }else{
               current = 0; /// setto a zero la molteplicità corrente dell'elemento el
           }
           if(current < n){
               throw std::out_of_range(string("Tried to remove ") + to_string(n) + "elements, but only " + to_string(current) + "were found");

           }else if(current == n && this->umap.count(el) == 1){
               this->umap.erase(el);
           }else{
               this->umap[el] = current - n; /// change the value associated with key
           }
        }
       /**
        * Here I need to print to the terminal the data structure so I need to iterate throughout all the elements in the 
        * MultiSet.
       */
       string as_string(){
           stringstream ss;
           bool first = true; /// this auxiliary variable is needed on order to print different things when you reach the end of the map
           ss << "{" << endl;
           for(std::pair<T, int> element:this->umap){
               if(!first){
                   ss<<","<<endl;
               }
               ss<<" {" << element.first << " , " << element.second << "}";
               first = false;
           }
           ss << endl << "}" << endl;
           return ss.str();
        }
       
       /**
        * RETURN the number of elements within the multiset (sum of all
        multiplicites)
        *
        * MUST run in O(k) where k is the number of keys
        * ---
        * It's a const method so it won't change the data structure
        * I need to get the value associated with each key and sum it to other values of all the other keys
       */
       int size() const{
           int sum=0;
           for(std::pair<T, int>element:this->umap){
               sum += element.second;
           }
           return sum;
        }

};

#endif