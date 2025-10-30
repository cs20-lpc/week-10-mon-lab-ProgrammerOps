template <typename Key, typename Val>
unsigned ArrayListDictionary<Key, Val>::numComps = 0;

template <typename Key, typename Val>
ArrayListDictionary<Key, Val>::ArrayListDictionary(int i)
: list(new ArrayList<Record>(i)) { }

template <typename Key, typename Val>
ArrayListDictionary<Key, Val>::ArrayListDictionary(const ArrayListDictionary<Key, Val>& copyObj) {
    copy(copyObj);
}

template <typename Key, typename Val>
ArrayListDictionary<Key, Val>& ArrayListDictionary<Key, Val>::operator=(const ArrayListDictionary<Key, Val>& rightObj) {
    if (this != &rightObj) {
        clear();
        copy(rightObj);
    }
    return *this;
}

template <typename Key, typename Val>
ArrayListDictionary<Key, Val>::~ArrayListDictionary() {
    delete list;
}

template <typename Key, typename Val>
Val ArrayListDictionary<Key, Val>::binSearchIter(const Key& target, int left, int right) const {
    // TODO

while (left <= right) {                        // while our search window still has cards inside
        int mid = (left + right) / 2;             // pick the middle card (split the row in half)
        const Record rec = list->getElement(mid); // peek at that middle card
        ++numComps;                                // compare target word with the middle card’s word

        if (rec.k == target) {                    // exact match?
            return rec.v;                         // found it → return the value on that card
        }

        ++numComps;                                // another comparison to decide which half to keep
        if (target < rec.k) {                     // if our word would come before the middle (alphabetically earlier)
            right = mid - 1;                      // shrink the window to the left half
        } else {                                  // otherwise it should be after the middle
            left = mid + 1;                       // shrink the window to the right half
        }
    }
    throw -1;                                      // window empty → not found

}

template <typename Key, typename Val>
Val ArrayListDictionary<Key, Val>::binSearchRec(const Key& target, int left, int right) const {
    // TODO

if (left > right) {                            // base case: search window is empty
        throw -1;                                  // nothing left → not found
    }
    int mid = (left + right) / 2;                  // choose the middle of the current window
    const Record rec = list->getElement(mid);      // look at the middle card
    ++numComps;                                     // compare target with the middle card’s word

    if (rec.k == target) {                         // exact match?
        return rec.v;                               // found it → return value
    }

    ++numComps;                                     // count the decision comparison (which side?)
    if (target < rec.k) {                          // should live on the left side (earlier alphabet)
        return binSearchRec(target, left, mid - 1);// recurse into the left half
    } else {                                        // otherwise it should be on the right side
        return binSearchRec(target, mid + 1, right);// recurse into the right half
    }


}

template <typename Key, typename Val>
void ArrayListDictionary<Key, Val>::clear() {
    list->clear();
}

template <typename Key, typename Val>
void ArrayListDictionary<Key, Val>::copy(const ArrayListDictionary<Key, Val>& copyObj) {
    list = new ArrayList<Record>(*copyObj.list);
}

template <typename Key, typename Val>
Val ArrayListDictionary<Key, Val>::find(const Key& k) const {
    numComps = 0;

    try {
        return seqSearchIter(k);
        // return seqSearchRec(k);
        // return binSearchIter(k, 0, list->getLength() - 1);
        // return binSearchRec(k, 0, list->getLength() - 1);
    }
    catch (...) {
        throw string("find: error, unsuccessful search, target key not found");
    }
}

template <typename Key, typename Val>
unsigned ArrayListDictionary<Key, Val>::getNumComps() {
    return numComps;
}

template <typename Key, typename Val>
void ArrayListDictionary<Key, Val>::insert(const Key& k, const Val& v) {
    list->append(Record(k, v));
}

template <typename Key, typename Val>
void ArrayListDictionary<Key, Val>::remove(const Key& k) {
    bool flag = false;

    for (int i = 0; i < list->getLength(); i++) {
        if (list->getElement(i).k == k) {
            list->remove(i);
            flag = true;
            break;
        }
    }

    if (!flag) {
        throw string("remove: error, unable to find record with matching key to remove");
    }
}

template <typename Key, typename Val>
Val ArrayListDictionary<Key, Val>::seqSearchIter(const Key& target) const {
    // TODO
 
int n = list->getLength();                      // how many cards (records) do we have on the table?
    for (int i = 0; i < n; ++i) {                   // start at card 0 and walk one step at a time
        const Record rec = list->getElement(i);     // pick up the i-th card to peek at its word (key)
        ++numComps;                                 // we are comparing target word with this card’s word — count 1 compare
        if (rec.k == target) {                      // is this the word we’re looking for?
            return rec.v;                           // yes! return the treasure/value written on this card
        }                                           // otherwise, keep walking to the next card
    }
    throw -1;                                       // checked all cards and didn’t find it → toss a “not found” signal

}

template <typename Key, typename Val>
Val ArrayListDictionary<Key, Val>::seqSearchRec(const Key& target, int i) const {
    // TODO

int n = list->getLength();                      // total number of cards on the table
    if (i >= n) {                                   // base case: our finger walked past the last card
        throw -1;                                   // nothing left to check → not found
    }
    const Record rec = list->getElement(i);         // peek at the i-th card
    ++numComps;                                     // compare this card’s word with our target word
    if (rec.k == target) {                          // if they match…
        return rec.v;                               // …we found the treasure! return its value
    }
    return seqSearchRec(target, i + 1);             // not yet → ask our “smaller self” to check the next card

}

template <typename Key, typename Val>
int ArrayListDictionary<Key, Val>::size() const {
    return list->getLength();
}
