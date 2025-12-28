#include<AddressesBuffer.h>

void AddressesBuffer::add(void* address) {
    /* move the pointer to point to the last item */
    /* then, obtain a superficial copy */
    void** addressToAdd = (startAddress + count);
    /* adds the address after the start address in the buffer */
    *addressToAdd = address;
    count++;
} 

void AddressesBuffer::add(int index, void* address) {
    /* adds on the count if the location was empty previously */
    if (startAddress[index] == NULL) {
        ++count;
    }
    startAddress[index] = address;
}

void AddressesBuffer::removeAt(int index) {
    startAddress[index] = NULL;
    count--;
}

void AddressesBuffer::removeAll() {
    for (int i = 0; i < count; i++) {
        this->removeAt(i);
    }
}

void AddressesBuffer::deallocateAt(int index) {
    BufferUtils::deleteBuffer(startAddress[index]);
}

void AddressesBuffer::deallocateAll() {
    BufferUtils::freeBufferCells(startAddress, count);
    this->resetToStartAddress();
}

void* AddressesBuffer::getAddress(int index) {
    return startAddress[index];
}

int AddressesBuffer::indexOf(void* address) {
    for (int i = 0; i < *getAddressesCount(); i++) {
        if (startAddress[i] == address) {
            return i;
        }
    }
    return ERR_OPERATION_FAILED;
}

int* AddressesBuffer::getAddressesCount() {
    return &count;
}